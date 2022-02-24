#pragma once

#include"2D Mesh.hpp"

class Triangle : public Mesh_2D
{
public:
	Triangle(float* vertices);
	Triangle(glm::vec3& center, float radius, float alpha, float tv);
};