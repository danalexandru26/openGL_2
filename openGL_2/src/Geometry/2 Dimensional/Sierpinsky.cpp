#include"Sierpinsky.hpp"


sierpinsky_fractal::sierpinsky_fractal(float triangle[9], std::size_t depth)
	:depth{ depth }, EBO{ std::vector<Index_Buffer>(depth) }, VBO{ std::vector<Vertex_Buffer>(depth) }
{
	vertices = new float* [depth];
	indices = new unsigned int* [depth];
	VAO_2 = new unsigned int[depth];

	vertices[1] = new float[9];
	indices[1] = new unsigned int[3];

	for (unsigned int i = 0; i < 3; ++i)
	{
		indices[1][i] = i;
	}

	for (std::size_t i = 0; i < 9; ++i)
	{
		vertices[1][i] = triangle[i];
	}
	
	VBO[1].init(vertices[1], sizeof(float) * 9);
	EBO[1].init(indices[1], sizeof(unsigned int) * 3);

	glGenVertexArrays(1, &VAO_2[1]);
	glBindVertexArray(VAO_2[1]);


	VBO[1].bind();
	EBO[1].bind();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	for (std::size_t i = 2; i < depth; ++i)
	{
		std::size_t index = 0;
		vertices[i] = new float[std::pow(3, i + 1)];
		indices[i] = new unsigned int[std::pow(3, i)];

		for (unsigned int j = 0; j < std::pow(3, i); ++j)
		{
			indices[i][j] = j;
		}
		sierpinsky(triangle, vertices[i], i, 1, index);

		VBO[i].init(vertices[i], sizeof(float) * std::pow(3, i + 1));
		EBO[i].init(indices[i], sizeof(unsigned int) * std::pow(3, i));

		glGenVertexArrays(1, &VAO_2[i]);
		glBindVertexArray(VAO_2[i]);

		VBO[i].bind();
		EBO[i].bind();

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
	}
}

sierpinsky_fractal::~sierpinsky_fractal()
{
	VBO.clear();
	EBO.clear();

	for (std::size_t i = 1; i < depth; ++i)
	{
		delete[] vertices[i];
		delete[] indices[i];
	}
	delete[] VAO_2;
	delete[] indices;
	delete[] vertices;
}

void sierpinsky_fractal::use(std::size_t depth)
{
	glBindVertexArray(VAO_2[depth]);
}

void sierpinsky_fractal::sierpinsky(float triangle[9], float* points, std::size_t depth, std::size_t index, std::size_t& j)
{
	if (index == depth)
	{
		return;
	}

	float AB[] =
	{
		(triangle[0] + triangle[6]) / 2, (triangle[1] + triangle[7]) / 2.0f, 0.0f
	};

	float BC[] =
	{
		(triangle[0] + triangle[3]) / 2, (triangle[1] + triangle[4]) / 2.0f, 0.0f
	};

	float AC[] =
	{
		(triangle[3] + triangle[6]) / 2, (triangle[4] + triangle[7]) / 2.0f, 0.0f
	};

	float triangle_one[] =
	{
		AB[0], AB[1], AB[2],
		AC[0], AC[1], AC[2],
		triangle[6], triangle[7], triangle[8]
	};

	float triangle_two[] =
	{
		triangle[0], triangle[1], triangle[2],
		BC[0], BC[1], BC[2],
		AB[0], AB[1], AB[2]
	};

	float triangle_three[] =
	{
		BC[0], BC[1], BC[2],
		triangle[3], triangle[4], triangle[5],
		AC[0], AC[1], AC[2]
	};

	if (index == depth - 1)
	{
		for (std::size_t i = 0; i < 9; ++i)
		{
			points[j++] = triangle_two[i];
		}

		for (std::size_t i = 0; i < 9; ++i)
		{
			points[j++] = triangle_three[i];
		}

		for (std::size_t i = 0; i < 9; ++i)
		{
			points[j++] = triangle_one[i];
		}
	}

	sierpinsky(triangle_two, points, depth, index + 1, j);
	sierpinsky(triangle_three, points, depth, index + 1, j);
	sierpinsky(triangle_one, points, depth, index + 1, j);
}