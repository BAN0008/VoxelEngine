#include <iostream>
#include <GLFW/glfw3.h>
#include "Renderer.hpp"
#include "Shader.hpp"
#include "VertexBuffer.hpp"
#include "GL.hpp"

const char* vertex_shader_code =
R"(#version 440 core
layout (location = 0) in vec3 a_position;
void main() {
	gl_Position = vec4(a_position, 1.0);
})";

const char* fragment_shader_code =
R"(#version 440 core
out vec4 out_color;
void main() {
	out_color = vec4(1.0, 0.0, 0.0, 1.0);
})";

const float vertices[] = {
	-1.0f, -1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,
	 1.0f,  1.0f, 0.0f
};

int main(int argc, char **argv)
{
	if (!glfwInit()) {
		const char *error_description;
		glfwGetError(&error_description);
		std::cerr << "main: Failed to initialize GLFW (" << error_description << ")\n";
		return -1;
	}

	{
		Renderer renderer(1280, 720);
		if (renderer.m_window) {
			Shader shader(vertex_shader_code, fragment_shader_code);
			shader.Bind();
			VertexBuffer vertex_buffer({Float3}, vertices, 3);
			while (!glfwWindowShouldClose(renderer.m_window)) {
				glfwPollEvents();
				GL::Clear(GL_COLOR_BUFFER_BIT);
				vertex_buffer.Render();
				glfwSwapBuffers(renderer.m_window);
			}
		}
	}

	glfwTerminate();
	return 0;
}
