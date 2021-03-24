#include "Shader.hpp"
#include "GL.hpp"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* p_vertex_shader_code, const char* p_fragment_shader_code)
{
	GLint success;
	char info_log[2048];
	GLuint vertex_shader = GL::CreateShader(GL_VERTEX_SHADER);
	GL::ShaderSource(vertex_shader, 1, &p_vertex_shader_code, nullptr);
	GL::CompileShader(vertex_shader);
	GL::GetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GL::GetShaderInfoLog(vertex_shader, 2048, nullptr, info_log);
		std::cerr << "Shader::Shader: Failed to compile vertex shader (" << info_log << ")\n";
	}

	GLuint fragment_shader = GL::CreateShader(GL_FRAGMENT_SHADER);
	GL::ShaderSource(fragment_shader, 1, &p_fragment_shader_code, nullptr);
	GL::CompileShader(fragment_shader);
	GL::GetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GL::GetShaderInfoLog(fragment_shader, 2048, nullptr, info_log);
		std::cerr << "Shader::Shader: Failed to compile fragment shader (" << info_log << ")\n";
	}

	m_program_id = GL::CreateProgram();
	GL::AttachShader(m_program_id, vertex_shader);
	GL::AttachShader(m_program_id, fragment_shader);
	GL::LinkProgram(m_program_id);
	GL::GetProgramiv(m_program_id, GL_LINK_STATUS, &success);
	if (!success) {
		GL::GetProgramInfoLog(m_program_id, 2048, nullptr, info_log);
		std::cerr << "Shader::Shader: Failed to link program (" << info_log << ")\n";
	}
	GL::DetachShader(m_program_id, vertex_shader);
	GL::DetachShader(m_program_id, fragment_shader);
	GL::DeleteShader(vertex_shader);
	GL::DeleteShader(fragment_shader);
}

Shader::~Shader()
{
	GL::DeleteProgram(m_program_id);
}

void Shader::Bind()
{
	GL::UseProgram(m_program_id);
}

void Shader::SetUniformInt(int p_location, int p_value)
{
	GL::ProgramUniform1i(m_program_id, p_location, p_value);
}

void Shader::SetUniformMat4(int p_location, const glm::mat4& p_value)
{
	GL::ProgramUniformMatrix4fv(m_program_id, p_location, 1, GL_FALSE, glm::value_ptr(p_value));
}