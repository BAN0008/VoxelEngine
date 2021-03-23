#pragma once

class Shader
{
public:
	Shader(const char* p_vertex_shader_code, const char* p_fragment_shader_code);
	Shader(const Shader&) = delete;
	~Shader();

	void Bind();

	void SetUniformInt(const char* name, int value);
private:
	unsigned int m_program_id;
};
