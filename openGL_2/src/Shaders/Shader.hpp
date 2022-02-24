#pragma once

#include<glad/glad.h>
#include<string>
#include<iostream>
#include<sstream>
#include<fstream>

#include<glm/glm/glm.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<glm/glm/gtc/type_ptr.hpp>

struct Shader_data
{
	std::string vertex_source;
	std::string fragment_source;
};

class Shader
{
public:
	Shader(std::string const vertex_path, std::string const fragment_path);
	~Shader();

	Shader_data parse_shader(std::string const vertex_path, std::string const fragment_path);

	void create_shader(std::string const& vertex, std::string const& fragment);
	void use();

	void set_float(std::string const& name, float* value) const;
	void set_float(std::string const& name, float value) const;
	void set_matrix4(std::string const& name, const glm::mat4& trans) const;

private:
	unsigned int shader_ID;
};