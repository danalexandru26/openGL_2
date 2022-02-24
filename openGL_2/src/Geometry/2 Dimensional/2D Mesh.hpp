#pragma once

#include<iostream>
#include<cmath>
#include<vector>
#include<array>

#include<glm/glm/glm.hpp>

#include"../../Buffers/IndexBuffer.hpp"
#include"../../Buffers/VertexBufferObject.hpp"

class Mesh_2D
{
public:
	Mesh_2D();
	Mesh_2D(float* vertices, unsigned int* indices);

	virtual ~Mesh_2D();

	void render();

protected:
	unsigned int VAO;
	Index_Buffer EBO;
	Vertex_Buffer VBO;
};