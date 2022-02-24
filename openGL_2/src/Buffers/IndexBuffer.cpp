#include"IndexBuffer.hpp"

Index_Buffer::Index_Buffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &EBO_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

Index_Buffer::~Index_Buffer()
{
	glDeleteBuffers(1, &EBO_id);
}

void Index_Buffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);
}

void Index_Buffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Index_Buffer::init(const void* data, unsigned int size)
{
	glGenBuffers(1, &EBO_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}