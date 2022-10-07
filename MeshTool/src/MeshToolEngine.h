#ifndef MESH_TOOL_ENGINE_H
#define MESH_TOOL_ENGINE_H

#include <memory>
#include <string>

#include <imgui/imgui.h>

#include "graphics/Graphics.h"
#include "graphics/Window.h"
#include "graphics/opengl/vbo/VertexBufferObject.h"
#include "graphics/opengl/vao/VertexArrayObject.h"
#include "graphics/opengl/ebo/ElementBufferObject.h"
#include "graphics/opengl/shader/ShaderProgram.h"
#include "graphics/KeyboardInput.h"
#include "graphics/MouseInput.h"
#include "graphics/camera/FPSCamera.h"

#include "statistics/MeshStatistics.h"
#include "viewer/GPUBufferLoader.h"
#include "viewer/MeshLoader.h"

struct GLFWWindow;

class MeshToolEngine {
public:
	void init();

	void start();
private:
	Graphics g;
	ShaderProgram shader;
	KeyboardInput keyboard;
	MouseInput mouse;
	FPSCamera camera;
	Window window;

	ImVec4 labelColor = ImVec4(0, 1, 1, 1);
	std::shared_ptr<MeshLoader> meshLoaderPtr;
	const char* meshItems[3] = { "task_input/pyramid.json", "task_input/teapot.json", "task_input/lucy.json" };
	bool showMeshStatisticsTool = true;
	bool meshLoaded = false;
	int selectedItemIdx = -1;
	int previousIndex = selectedItemIdx;
	long long subdivisionTime = 0;
	
	void onMouseMove(double x, double y);
	void handleEvents();
	void drawTriangleStats(std::string label, const MeshStatistics::StatsTriangle& triangle) const;
	void drawMeshStats(const MeshStatistics::Stats& stats) const;

	void loadNewMesh();
	void subdivideMesh();
	void drawStatsWidget();

	void resetMeshLoader();
};

#endif // !MESH_TOOL_ENGINE_H
