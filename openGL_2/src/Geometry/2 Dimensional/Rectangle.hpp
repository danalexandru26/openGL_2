#pragma once

#include"2D Mesh.hpp"

class Rectangle : public Mesh_2D
{
public:
	Rectangle(glm::vec3& center, float height, float width);
};