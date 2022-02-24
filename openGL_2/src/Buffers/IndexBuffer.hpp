#pragma once

#include<glad/glad.h>

class Index_Buffer
{
public:
	Index_Buffer() = default;
	Index_Buffer(const void* data, unsigned int size);
	
	~Index_Buffer();

	void init(const void* data, unsigned int size);
	void bind();
	void unbind();

private:
	unsigned int EBO_id;
};