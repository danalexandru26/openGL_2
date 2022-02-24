#include"Triangle.hpp"

Triangle::Triangle(float* vertices)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VBO.init(vertices, sizeof(vertices));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

Triangle::Triangle(glm::vec3& center, float radius, float alpha, float tv)
{
	auto alpha_a = glm::radians(alpha);
	auto alpha_b = glm::radians(180.0f - alpha);
	auto alpha_c = glm::radians(tv + alpha);

	float vertices[] =
	{
		radius * cos(alpha_a) + center.x, radius * sin(alpha_a) + center.y, 0.0f,
		radius * cos(alpha_b) + center.x, radius * sin(alpha_b) + center.y, 0.0f,
		radius * cos(alpha_c) + center.x, radius * sin(alpha_c) + center.y, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VBO.init(vertices, sizeof(vertices));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}