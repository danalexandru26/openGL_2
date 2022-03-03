#include"Rectangle.hpp"


Rectangle::Rectangle(glm::vec3& center, float height, float width)
{
	const auto x = center.x + width / 2.0f;
	const auto y = center.y + height / 2.0f;

	float vertices[] =
	{
	   -x, -y, 0.0f,
	   -x,  y, 0.0f,
	    x,  y, 0.0f,
	    x, -y, 0.0f
	};

	unsigned int indices[] =
	{
		0, 1, 2, 0, 3, 2
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VBO.init(vertices, sizeof(vertices));
	EBO.init(indices, sizeof(indices));

	VBO.bind();
	EBO.bind();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
