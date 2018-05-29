#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "../Dependencies/glCore/gl_core_4_5.h"
#include <glfw3.h>
#include "Shader.h"
#include "FlyCamera.h"


class Mesh
{	
public:
	Mesh() :triCount(0), vao(0), vbo(0), ibo(0) {};
	virtual ~Mesh();

	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};

	void initialiseQuad();

	void initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount = 0, unsigned int* indices = nullptr);

	void addAABB(const glm::vec3& center, const glm::vec3& extents, const glm::mat4* transform = nullptr);
	void addPyramid(const glm::vec3& center, const glm::vec3& extents, const glm::mat4* transform = nullptr);

	virtual void draw();

protected:

	unsigned int triCount;
	unsigned int vao, vbo, ibo;
};

