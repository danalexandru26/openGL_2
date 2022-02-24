#include"Shader.hpp"

Shader::Shader(std::string const vertex_path, std::string const fragment_path)
{
	Shader_data source = parse_shader(vertex_path, fragment_path);
	create_shader(source.vertex_source, source.fragment_source);
}

Shader::~Shader()
{
	glDeleteProgram(shader_ID);
}

Shader_data Shader::parse_shader(std::string const vertex_path, std::string const fragment_path)
{
	Shader_data vf_shader;

	std::stringstream ss[2];
	std::string line;

	std::ifstream vertex_file(vertex_path);
	std::ifstream fragment_file(fragment_path);

	ss[0] << vertex_file.rdbuf();
	ss[1] << fragment_file.rdbuf();

	return { ss[0].str(), ss[1].str() };
}

void Shader::create_shader(std::string const& vertex, std::string const& fragment)
{
	unsigned int v_id, f_id;
	std::cout << vertex << fragment;

	v_id = glCreateShader(GL_VERTEX_SHADER);
	const char* v_source = vertex.c_str();
	glShaderSource(v_id, 1, &v_source, nullptr);
	glCompileShader(v_id);

	f_id = glCreateShader(GL_FRAGMENT_SHADER);
	const char* f_source = fragment.c_str();
	glShaderSource(f_id, 1, &f_source, nullptr);
	glCompileShader(f_id);

	shader_ID = glCreateProgram();
	glAttachShader(shader_ID, v_id);
	glAttachShader(shader_ID, f_id);
	glLinkProgram(shader_ID);

	glDeleteShader(v_id);
	glDeleteShader(f_id);
}

void Shader::use()
{
	glUseProgram(shader_ID);
}

void Shader::set_float(std::string const& name, float* value) const
{
	glUniform4f(glGetUniformLocation(shader_ID, name.c_str()), value[0], value[1], value[2], value[3]);
}

void Shader::set_float(std::string const& name, float value) const
{
	glUniform1f(glGetUniformLocation(shader_ID, name.c_str()), value);
}

void Shader::set_matrix4(std::string const& name, const glm::mat4& trans) const
{
	glUniformMatrix4fv(glGetUniformLocation(shader_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(trans));
}