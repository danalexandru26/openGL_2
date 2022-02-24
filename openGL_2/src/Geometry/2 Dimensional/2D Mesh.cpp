#include"2D Mesh.hpp"

Mesh_2D::Mesh_2D()
{}

Mesh_2D::Mesh_2D(float* vertices, unsigned int* indices)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VBO.init(vertices, sizeof(indices));
	EBO.init(indices, sizeof(indices));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

Mesh_2D::~Mesh_2D()
{}

void Mesh_2D::render()
{
	glBindVertexArray(VAO);
}