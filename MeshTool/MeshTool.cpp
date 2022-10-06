#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include "src/files/FileReader.h"
#include "src/parser/GeometryObjectParser.h"
#include "src/models/factories/MeshFactory.h"
#include "src/analyser/MeshStatistics.h"

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

using namespace std;
using namespace std::chrono;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

FPSCamera camera;

int main(int argc, char** argv)
{
  Graphics g;
  g.init();
  std::shared_ptr<Window> windowPtr = make_shared<Window>();
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
  windowPtr->disableCursor();
  camera.init(45.0f, 800 / 600, 0.1f, 100.0f, Point3D(0.0f, 0.0f, -3.0f), Point3D(0.0f), 800, 600);

  FileReader reader;
  reader.load("task_input/teapot.json");

  GeometryObjectParser parser;
  parser.parse(reader.getText());
  reader.~FileReader();
  GeometryObject o = parser.getGeometryObject();

  std::unique_ptr<Mesh> mesh = MeshFactory::create(o);

  MeshStatistics::Stats meshStats = MeshStatistics::gatherStats(mesh->triangles.cbegin(), mesh->triangles.cend());

  cout << "Statistics:" << endl;
  cout << "The smallest triangle is with area " << meshStats.smallest.area << endl;
  cout << "The largest triangle is with area " << meshStats.largest.area << endl;
  cout << "The average area of all triangles is " << meshStats.avgArea << endl;

  VertexArrayObject vao;
  vao.init();
  vao.bind();

  VertexBufferObject vbo;
  vbo.init(GL_ARRAY_BUFFER);
  vbo.bind();

  // Transform vector to array
  size_t componentCount = o.verticesComponents.size();
  float* buffer = new float[componentCount];

  for (int i = 0; i < componentCount; i++) {
    buffer[i] = o.verticesComponents[i];
  }

  vbo.fillBuffer(buffer, componentCount);
  delete[] buffer;

  ElementBufferObject ebo;
  ebo.init();

  // Transform vector of indices to array
  size_t indicesCount = o.trianglesIndices.size();
  unsigned int* indices = new unsigned int[indicesCount];

  for (size_t idx = 0; idx < indicesCount; idx++) {
    indices[idx] = o.trianglesIndices[idx];
  }

  ebo.bind();
  ebo.fillBuffer(indices, indicesCount * sizeof(unsigned int));
  delete[] indices;

  vao.addAttribute(VertexAttribute{ 0,3,3,0 });

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(windowPtr->getRaw(), true);
  ImGui_ImplOpenGL3_Init("#version 130");

  bool showMeshStatisticsTool = true;
  auto labelColor = ImVec4(0, 0, 1, 1);

  auto printTriangle = [&labelColor](std::string label, const MeshStatistics::StatsTriangle& triangle) {
    ImGui::TextColored(labelColor, label.c_str());
    
    ImGui::Text("Vertex 1: (%f, %f, %f)", triangle.a.position.x, triangle.a.position.y, triangle.a.position.z);
    ImGui::Text("Vertex 2: (%f, %f, %f)", triangle.b.position.x, triangle.b.position.y, triangle.b.position.z);
    ImGui::Text("Vertex 3: (%f, %f, %f)", triangle.c.position.x, triangle.c.position.y, triangle.c.position.z);
    ImGui::Text("Area: %f", triangle.area);
  };

  while (true) {
    windowPtr->clear();

    g.pollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Mesh Statistics", &showMeshStatisticsTool, ImGuiWindowFlags_None);
    printTriangle("Smallest triangle:", meshStats.smallest);
    printTriangle("Largest triangle:", meshStats.largest);
    ImGui::TextColored(labelColor, "Average Area: %f", meshStats.avgArea);
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

    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    windowPtr->swapBuffers();
  }

  return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
  camera.onMouseMove(xpos, ypos);
}