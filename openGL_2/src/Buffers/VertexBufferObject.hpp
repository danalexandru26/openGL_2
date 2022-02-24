#pragma once

#include<glad/glad.h>

class Vertex_Buffer
{
public:
	Vertex_Buffer() = default;
	Vertex_Buffer(const void* data, unsigned int size);
	~Vertex_Buffer();

	void init(const void* data, unsigned int size);
	void bind();
	void unbind();

private:
	unsigned int Buffer_ID;
};