#pragma once
#include <glm/mat4x4.hpp>

class Shader
{
public:
	Shader(const char* p_vertex_shader_code, const char* p_fragment_shader_code);
	Shader(const Shader&) = delete;
	~Shader();

	void Bind();

	void SetUniformInt(int p_location, int p_value);
	void SetUniformVec3(int p_location, float p_x, float p_y, float p_z);
	void SetUniformMat4(int p_location, const glm::mat4& p_value);
private:
	unsigned int m_program_id;
};
