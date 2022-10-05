#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include "src/files/FileReader.h"
#include "src/parser/GeometryObjectParser.h"
#include "src/models/factories/MeshFactory.h"
#include "src/analyser/MeshStatistics.h"
#include "src/graphics/opengl/vbo/VertexBufferObject.h"
#include "src/graphics/opengl/vao/VertexArrayObject.h"
#include "src/graphics/opengl/ebo/ElementBufferObject.h"
#include "src/graphics/opengl/shader/ShaderProgram.h"
#include "src/graphics/KeyboardInput.h"

// Graphics related
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "src/graphics/Graphics.h"
#include "src/graphics/Window.h"

using namespace std;
using namespace std::chrono;

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

  while (true) {
    windowPtr->clear();

    string path;

    cout << "Enter json file path, relative to executable: ";

    cin >> path;

    FileReader reader;
    reader.load(path);

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
    vao.addAttribute(VertexAttribute{0,3,3,0});

    ElementBufferObject ebo;
    ebo.init();
    
    // Transform vector of indices to array
    size_t indicesCount = o.trianglesIndices.size();
    unsigned int* indices = new unsigned int[indicesCount];

    for (int idx = 0; idx < indicesCount; idx++) {
      indices[idx] = o.trianglesIndices[idx];
    }

    ebo.bind();
    ebo.fillBuffer(indices, indicesCount);

    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

    windowPtr->swapBuffers();
  }

  return 0;
}
