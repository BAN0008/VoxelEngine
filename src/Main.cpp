#include <iostream>
#include <GLFW/glfw3.h>
#include "Renderer.hpp"
#include "Shader.hpp"
#include "VertexBuffer.hpp"
#include "TextureArray.hpp"
#include "GL.hpp"

const char* vertex_shader_code =
R"(#version 440 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_texture_coordinate;
out vec3 f_texture_coordinate;
void main() {
	gl_Position = vec4(a_position, 1.0);
	f_texture_coordinate = a_texture_coordinate;
})";

const char* fragment_shader_code =
R"(#version 440 core
in vec3 f_texture_coordinate;
out vec4 out_color;
uniform sampler2DArray u_texture_array;
void main() {
	out_color = texture(u_texture_array, f_texture_coordinate);
})";

const float vertices[] = {
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	 1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f
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
			shader.SetUniformInt("u_texture_array", 0);
			VertexBuffer vertex_buffer({Float3, Float3}, vertices, 3);
			TextureArray texture_array("../res/test.png", 32, 32);
			texture_array.Bind(0);
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
