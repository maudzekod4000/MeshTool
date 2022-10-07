#include "MeshToolEngine.h"

#include <iostream>
#include <functional>
#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "algorithms/MeshAlgorithms.h"

void MeshToolEngine::init()
{
  g.init();
  window.init(800, 600, "Mesh Tool");
  window.makeActive();

  if (!g.loadFunctionDefinitions())
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return;
  }

  shader.init();
  shader.attachVertexShader("shaders/vertex_shader");
  shader.attachFragmentShader("shaders/fragment_shader");
  shader.link();
  shader.use();

  keyboard.init(std::make_shared<Window>(window));

  camera.init(45.0f, 800 / 600, 0.1f, 100.0f, Point3D(0.0f, 0.0f, -3.0f), Point3D(0.0f), 800, 600);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  mouse.init(window,
    std::bind(&MeshToolEngine::onMouseMove, this, std::placeholders::_1, std::placeholders::_2));

  meshLoaderPtr = std::make_shared<MeshLoader>();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window.getRaw(), true);
  ImGui_ImplOpenGL3_Init("#version 130");
}

void MeshToolEngine::start()
{
  while (true) {
    window.clear();

    g.pollEvents();

    if (selectedItemIdx != previousIndex) {
      loadNewMesh();
    }

    drawStatsWidget();

    handleEvents();

    shader.setUniformMat4("view", camera.getView());
    shader.setUniformMat4("projection", camera.getProjection());

    if (meshLoaded) {
      glDrawElements(GL_TRIANGLES, meshLoaderPtr->indicesCount, GL_UNSIGNED_INT, 0);
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    window.swapBuffers();
  }
}

void MeshToolEngine::onMouseMove(double x, double y)
{
  camera.onMouseMove(x, y);
}

void MeshToolEngine::handleEvents()
{
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
    window.toggleCursor();
  }
}

void MeshToolEngine::drawTriangleStats(std::string label, const MeshStatistics::StatsTriangle& triangle) const
{
  ImGui::TextColored(labelColor, label.c_str());

  ImGui::Text("Vertex 1: (%f, %f, %f)", triangle.a.position.x, triangle.a.position.y, triangle.a.position.z);
  ImGui::Text("Vertex 2: (%f, %f, %f)", triangle.b.position.x, triangle.b.position.y, triangle.b.position.z);
  ImGui::Text("Vertex 3: (%f, %f, %f)", triangle.c.position.x, triangle.c.position.y, triangle.c.position.z);
  ImGui::Text("Area: %f", triangle.area);
}

void MeshToolEngine::drawMeshStats(const MeshStatistics::Stats& stats) const
{
  drawTriangleStats("Smallest triangle:", stats.smallest);
  drawTriangleStats("Largest triangle:", stats.largest);
  ImGui::TextColored(labelColor, "Average Area: %f", stats.avgArea);
  ImGui::TextColored(labelColor, "Triangle Count: %d", stats.triangleCount);
  ImGui::TextColored(labelColor, "Load Time: %lld ms.", stats.loadTime);
  ImGui::TextColored(labelColor, "Subdivision Time: %lld ms.", subdivisionTime);
}

void MeshToolEngine::loadNewMesh()
{
  resetMeshLoader();

  meshLoaderPtr->load(meshItems[selectedItemIdx]);

  meshLoaded = true;
  previousIndex = selectedItemIdx;
  subdivisionTime = 0;
}

void MeshToolEngine::subdivideMesh()
{
  using namespace std::chrono;
  auto start = high_resolution_clock::now();
  
  auto subdividedMesh = std::move(MeshAlgorithms::subdivide2(*meshLoaderPtr->mesh.get()));
  resetMeshLoader();
  meshLoaderPtr->load(std::move(subdividedMesh));

  auto end = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(end - start);
  subdivisionTime = duration.count();
}

void MeshToolEngine::drawStatsWidget()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("Mesh Statistics", &showMeshStatisticsTool, ImGuiWindowFlags_AlwaysAutoResize);
  ImGui::TextColored(labelColor, "Use M key to enable/disable mouse cursor");
  ImGui::TextColored(labelColor, "and WASD keys and mouse to move around.");
  ImGui::Combo("Select Mesh", &selectedItemIdx, meshItems, IM_ARRAYSIZE(meshItems));

  if (meshLoaded) {
    drawMeshStats(meshLoaderPtr->stats);
  }

  if (meshLoaded && ImGui::Button("Subdivide")) {
    subdivideMesh();
  }

  ImGui::End();
}

void MeshToolEngine::resetMeshLoader()
{
  meshLoaderPtr.reset();
  meshLoaderPtr = std::make_shared<MeshLoader>();
}
