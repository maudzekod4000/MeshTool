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
  shader.attachVertexShader("src/graphics/shaders/vertex_shader");
  shader.attachFragmentShader("src/graphics/shaders/fragment_shader");
  shader.link();
  shader.use();

  KeyboardInput keyboard;
  keyboard.init(windowPtr);

  windowPtr->registerCursorPositionCallback(mouse_callback);
  windowPtr->disableCursor();
  camera.init(45.0f, 800 / 600, 0.1f, 100.0f, Point3D(0.0f, 0.0f, -3.0f), Point3D(0.0f), 800, 600);

  FileReader reader;
  reader.load("task_input/pyramid.json");

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

  VertexArrayObject vao;
  vao.init();
  vao.bind();
  

  ElementBufferObject ebo;
  ebo.init();

  // Transform vector of indices to array
  size_t indicesCount = o.trianglesIndices.size();
  unsigned int* indices = new unsigned int[indicesCount];

  for (size_t idx = 0; idx < indicesCount; idx++) {
    indices[idx] = o.trianglesIndices[idx];
  }

  ebo.bind();
  ebo.fillBuffer(indices, indicesCount);

  vao.addAttribute(VertexAttribute{ 0,3,3,0 });

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (true) {
    windowPtr->clear();

    g.pollEvents();

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

    shader.setUniformMat4("view", camera.getView());
    shader.setUniformMat4("projection", camera.getProjection());

    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

    windowPtr->swapBuffers();
  }

  return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
  camera.onMouseMove(xpos, ypos);
}