#ifndef GPU_BUFFER_LOADER_H
#define GPU_BUFFER_LOADER_H

#include "../graphics/opengl/vao/VertexArrayObject.h"
#include "../graphics/opengl/vbo/VertexBufferObject.h"
#include "../graphics/opengl/ebo/ElementBufferObject.h"

struct GeometryObject;

class GPUBufferLoader {
public:
	void init();
	void loadBuffers(const GeometryObject&);
	void deinit();
private:
	VertexArrayObject vao;
	VertexBufferObject vbo;
	ElementBufferObject ebo;
};

#endif // !GPU_BUFFER_LOADER_H
