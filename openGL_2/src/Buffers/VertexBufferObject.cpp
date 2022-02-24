#include"VertexBufferObject.hpp"

Vertex_Buffer::Vertex_Buffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &Buffer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer_ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

Vertex_Buffer::~Vertex_Buffer()
{
	glDeleteBuffers(1, &Buffer_ID);
}

void Vertex_Buffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Vertex_Buffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, Buffer_ID);
}

void Vertex_Buffer::init(const void* data, unsigned int size)
{
	glGenBuffers(1, &Buffer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer_ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
