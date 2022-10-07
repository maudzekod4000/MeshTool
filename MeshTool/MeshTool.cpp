#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include "src/files/FileReader.h"
#include "src/parser/GeometryObjectBuilder.h"
#include "src/models/factories/MeshFactory.h"
#include "src/statistics/MeshStatistics.h"
#include "src/algorithms/MeshAlgorithms.h"

// Graphics related
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "src/graphics/Graphics.h"
#include "src/graphics/Window.h"
#include "src/graphics/opengl/vbo/VertexBufferObject.h"
#include "src/graphics/opengl/vao/VertexArrayObject.h"
#include "src/graphics/opengl/ebo/ElementBufferObject.h"
#include "src/graphics/opengl/shader/ShaderProgram.h"
#include "src/graphics/KeyboardInput.h"
#include "src/graphics/camera/FPSCamera.h"

#include "src/viewer/GPUBufferLoader.h"
#include "src/viewer/MeshLoader.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

FPSCamera camera;

int main(int argc, char** argv)
{
  Graphics g;
  g.init();
  std::shared_ptr<Window> windowPtr = std::make_shared<Window>();
  windowPtr->init(800, 600, "Mesh Tool");
  windowPtr->makeActive();

  if (!g.loadFunctionDefinitions())
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  ShaderProgram shader;
  shader.init();
  shader.attachVertexShader("shaders/vertex_shader");
  shader.attachFragmentShader("shaders/fragment_shader");
  shader.link();
  shader.use();

  KeyboardInput keyboard;
  keyboard.init(windowPtr);

  windowPtr->registerCursorPositionCallback(mouse_callback);
  camera.init(45.0f, 800 / 600, 0.1f, 100.0f, Point3D(0.0f, 0.0f, -3.0f), Point3D(0.0f), 800, 600);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(windowPtr->getRaw(), true);
  ImGui_ImplOpenGL3_Init("#version 130");

  bool showMeshStatisticsTool = true;
  bool meshLoaded = false;
  auto labelColor = ImVec4(0, 0, 1, 1);

  auto drawTriangleStats = [&labelColor](std::string label, const MeshStatistics::StatsTriangle& triangle) {
    ImGui::TextColored(labelColor, label.c_str());
    
    ImGui::Text("Vertex 1: (%f, %f, %f)", triangle.a.position.x, triangle.a.position.y, triangle.a.position.z);
    ImGui::Text("Vertex 2: (%f, %f, %f)", triangle.b.position.x, triangle.b.position.y, triangle.b.position.z);
    ImGui::Text("Vertex 3: (%f, %f, %f)", triangle.c.position.x, triangle.c.position.y, triangle.c.position.z);
    ImGui::Text("Area: %f", triangle.area);
  };
  auto drawMeshStatistics = [&drawTriangleStats, &labelColor](const MeshStatistics::Stats& stats) {
    drawTriangleStats("Smallest triangle:", stats.smallest);
    drawTriangleStats("Largest triangle:", stats.largest);
    ImGui::TextColored(labelColor, "Average Area: %f", stats.avgArea);
    ImGui::TextColored(labelColor, "Triangle Count: %d", stats.triangleCount);
  };

  const char* meshItems[3] = { "task_input/pyramid.json", "task_input/teapot.json", "task_input/lucy.json" };
  int selectedItemIdx = -1;
  int previousIndex = selectedItemIdx;
  auto meshLoaderPtr = std::make_shared<MeshLoader>();

  while (true) {
    windowPtr->clear();

    g.pollEvents();

    if (selectedItemIdx != previousIndex) {
      // Load a new mesh
      meshLoaderPtr.reset();
      meshLoaderPtr = std::make_shared<MeshLoader>();
      meshLoaderPtr->load(meshItems[selectedItemIdx]);
      meshLoaded = true;
      previousIndex = selectedItemIdx;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Mesh Statistics", &showMeshStatisticsTool, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Combo("Select Mesh", &selectedItemIdx, meshItems, IM_ARRAYSIZE(meshItems));
    
    if (meshLoaded) {
      drawMeshStatistics(meshLoaderPtr->stats);
    }

    if (ImGui::Button("Subdivide") && meshLoaded) {
      auto subdividedMesh = std::move(MeshAlgorithms::subdivide2(*meshLoaderPtr->mesh.get()));
      meshLoaderPtr.reset();
      meshLoaderPtr = std::make_shared<MeshLoader>();
      meshLoaderPtr->load(std::move(subdividedMesh));
    }

    ImGui::End();

    if (keyboard.isKeyPressed(GLFW_KEY_W)) {
      camera.moveForward();
    }
    else if (keyboard.isKeyPressed(GLFW_KEY_S)) {
      camera.moveBackward();
    }
    else if (keyboard.isKeyPressed(GLFW_KEY_A)) {
      camera.moveLeft();
    }
    else if (keyboard.isKeyPressed(GLFW_KEY_D)) {
      camera.moveRight();
    }
    else if (keyboard.isKeyPressed(GLFW_KEY_M)) {
      windowPtr->toggleCursor();
    }

    shader.setUniformMat4("view", camera.getView());
    shader.setUniformMat4("projection", camera.getProjection());

    if (meshLoaded) {
      glDrawElements(GL_TRIANGLES, meshLoaderPtr->indicesCount, GL_UNSIGNED_INT, 0);
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    windowPtr->swapBuffers();
  }

  return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
  camera.onMouseMove(xpos, ypos);
}