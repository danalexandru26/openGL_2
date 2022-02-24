#pragma once

#include<iostream>
#include<cmath>
#include<vector>
#include<array>

#include"../../Buffers/IndexBuffer.hpp"
#include"../../Buffers/VertexBufferObject.hpp"

class sierpinsky_fractal
{
public:
	sierpinsky_fractal(float triangle[9], std::size_t depth);
	~sierpinsky_fractal();

	void use(std::size_t depth);

private:
	void sierpinsky(float triangle[9], float* points, std::size_t depth, std::size_t index, std::size_t& j);

private:
	std::size_t depth;

	unsigned int* VAO_2;
	unsigned int** indices;
	float** vertices;
	
	std::vector<Index_Buffer> EBO;
	std::vector<Vertex_Buffer> VBO;
};