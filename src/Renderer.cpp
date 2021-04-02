#include "Renderer.hpp"
#include <iostream>
#include "GL.hpp"
#define LOAD_GL_FUNC(name) (GL::name)  = reinterpret_cast<decltype(GL::name)>(glfwGetProcAddress("gl" #name))

void WindowSizeCallback(GLFWwindow* p_window, int p_width, int p_height)
{
	reinterpret_cast<Renderer*>(glfwGetWindowUserPointer(p_window))->OnResize(p_width, p_height);
}

Renderer::Renderer(int p_width, int p_height) : m_width{p_width}, m_height{p_height}
{
	const char* error_description;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	
	m_window = glfwCreateWindow(m_width, m_height, "VoxelEngine", nullptr, nullptr);
	if (!m_window) {
		glfwGetError(&error_description);
		std::cerr << "Renderer::Renderer: Failed to create window (" << error_description << ")\n";
		return;
	}

	glfwSetWindowUserPointer(m_window, this);

	glfwMakeContextCurrent(m_window);
	int error = glfwGetError(&error_description);
	if (error != GLFW_NO_ERROR) {
		std::cerr << "Renderer::Renderer: Failed to make OpenGL context current (" << error_description << ")\n";
	}

	// Load OpenGL function pointers
	LOAD_GL_FUNC(Enable);
	LOAD_GL_FUNC(CullFace);
	LOAD_GL_FUNC(FrontFace);
	LOAD_GL_FUNC(Clear);
	LOAD_GL_FUNC(Viewport);
	LOAD_GL_FUNC(CreateShader);
	LOAD_GL_FUNC(ShaderSource);
	LOAD_GL_FUNC(CompileShader);
	LOAD_GL_FUNC(GetShaderiv);
	LOAD_GL_FUNC(GetShaderInfoLog);
	LOAD_GL_FUNC(DeleteShader);
	LOAD_GL_FUNC(CreateProgram);
	LOAD_GL_FUNC(DeleteProgram);
	LOAD_GL_FUNC(AttachShader);
	LOAD_GL_FUNC(DetachShader);
	LOAD_GL_FUNC(LinkProgram);
	LOAD_GL_FUNC(GetProgramiv);
	LOAD_GL_FUNC(GetProgramInfoLog);
	LOAD_GL_FUNC(UseProgram);
	LOAD_GL_FUNC(ProgramUniform1i);
	LOAD_GL_FUNC(ProgramUniform3f);
	LOAD_GL_FUNC(ProgramUniform3fv);
	LOAD_GL_FUNC(ProgramUniformMatrix4fv);
	LOAD_GL_FUNC(CreateVertexArrays);
	LOAD_GL_FUNC(DeleteVertexArrays);
	LOAD_GL_FUNC(BindVertexArray);
	LOAD_GL_FUNC(CreateBuffers);
	LOAD_GL_FUNC(DeleteBuffers);
	LOAD_GL_FUNC(NamedBufferData);
	LOAD_GL_FUNC(NamedBufferSubData);
	LOAD_GL_FUNC(VertexArrayVertexBuffer);
	LOAD_GL_FUNC(EnableVertexArrayAttrib);
	LOAD_GL_FUNC(VertexArrayAttribBinding);
	LOAD_GL_FUNC(VertexArrayAttribFormat);
	LOAD_GL_FUNC(DrawArrays);
	LOAD_GL_FUNC(CreateTextures);
	LOAD_GL_FUNC(DeleteTextures);
	LOAD_GL_FUNC(TextureStorage3D);
	LOAD_GL_FUNC(TextureSubImage3D);
	LOAD_GL_FUNC(TextureParameteri);
	LOAD_GL_FUNC(BindTextureUnit);

	GL::Enable(GL_DEPTH_TEST);
	GL::Enable(GL_CULL_FACE);
	GL::FrontFace(GL_CW);
	GL::CullFace(GL_BACK);

	OnResize(m_width, m_height);
	glfwSetWindowSizeCallback(m_window, WindowSizeCallback);
}

Renderer::~Renderer()
{
	if (m_window) glfwDestroyWindow(m_window);
}

void Renderer::OnResize(int p_width, int p_height)
{
	m_width  = p_width;
	m_height = p_height;
	GL::Viewport(0, 0, m_width, m_height);
}
