#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <unordered_map>
#include <climits>
#include "Renderer.hpp"
#include "Shader.hpp"
// #include "VertexBuffer.hpp"
#include "ChunkStorage.hpp"
#include "TextureArray.hpp"
#include "Camera.hpp"
#include "GL.hpp"

/*const char* vertex_shader_code =
R"(#version 440 core
layout (location = 0) in vec3 a_position;
layout (location = 2) in vec3 a_texture_coordinate;
out vec3 f_texture_coordinate;
layout (location = 0) uniform mat4 u_view;
void main() {
	gl_Position = u_view * vec4(a_position, 1.0);
	f_texture_coordinate = a_texture_coordinate;
})";

const char* fragment_shader_code =
R"(#version 440 core
in vec3 f_texture_coordinate;
out vec4 out_color;
layout (location = 1) uniform sampler2DArray u_texture_array;
void main() {
	out_color = texture(u_texture_array, f_texture_coordinate);
})";*/

const char* vertex_shader_code =
R"(#version 440 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec3 a_texture_coordinate;
out vec3 f_frag_pos;
out vec3 f_normal;
out vec3 f_texture_coordinate;
layout (location = 0) uniform mat4 u_view;
layout (location = 1) uniform mat4 u_model;
void main() {
	gl_Position = u_view * u_model * vec4(a_position, 1.0);
	f_frag_pos = vec3(u_model * vec4(a_position, 1.0));
	f_normal = a_normal;
	f_texture_coordinate = a_texture_coordinate;
})";

const char* fragment_shader_code =
R"(#version 440 core
in vec3 f_frag_pos;
in vec3 f_normal;
in vec3 f_texture_coordinate;
out vec4 out_color;
layout (location = 2) uniform sampler2DArray u_texture_array;
layout (location = 3) uniform vec3 u_light_pos;
void main() {
	vec3 light_dir = normalize(u_light_pos - f_frag_pos);
	out_color = texture(u_texture_array, f_texture_coordinate) * (0.1 + max(dot(f_normal, light_dir), 0.0));
})";

static Camera* camera_ptr = nullptr;

void MouseCallback(GLFWwindow* p_window, double p_x, double p_y)
{
	static double prev_x = 0.0f;
	static double prev_y = 0.0f;
	if (glfwGetInputMode(p_window, GLFW_CURSOR) != GLFW_CURSOR_NORMAL) {
		camera_ptr->ProcessMouseInput(p_x - prev_x, p_y - prev_y);
	}
	prev_x = p_x;
	prev_y = p_y;
}

void KeyboardCallback(GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
{
	if (p_key == GLFW_KEY_ESCAPE && p_action == GLFW_PRESS) {
		if (glfwGetInputMode(p_window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
			glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			if (glfwRawMouseMotionSupported()) {
				glfwSetInputMode(p_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
			}
			else {
				std::cerr << "KeyboardCallback: Raw mouse motion not supported\n";
			}
		}
		else {
			glfwSetInputMode(p_window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
			glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
}

std::size_t rotl (std::size_t n, unsigned int c)
{
	const std::size_t mask = (CHAR_BIT * sizeof(n) - 1); // assumes width is a power of 2.
	c &= mask;
	return (n << c) | (n >> ((-c) & mask));
}

std::size_t rotr (std::size_t n, unsigned int c)
{
	const std::size_t mask = (CHAR_BIT * sizeof(n) - 1);
	c &= mask;
	return (n >> c) | (n << ((-c) & mask));
}

namespace std
{
	template<> struct hash<glm::ivec3>
	{
		std::size_t operator()(const glm::ivec3& value) const noexcept
		{
			return rotl(std::hash<int>{}(value.x), 1) ^ rotr(std::hash<int>{}(value.y), 1) ^ rotl(std::hash<int>{}(value.z), 1);
		}
	};
}

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
			shader.SetUniformInt(2, 0);
			shader.SetUniformVec3(3, -10, 10, -10);
			TextureArray texture_array("../res/test.png", 32, 32);
			texture_array.Bind(0);
			Camera camera;
			camera_ptr = &camera;
			shader.SetUniformMat4(0, camera.GetMatrix(renderer));
			glfwSetCursorPosCallback(renderer.m_window, MouseCallback);
			glfwSetKeyCallback(renderer.m_window, KeyboardCallback);

			ChunkStorage chunk_storage(8, 8, 8);
			std::unordered_map<glm::ivec3, unsigned int> chunk_indices;

			unsigned int chunk_index = chunk_indices.emplace(glm::ivec3(0, 0, 0), chunk_storage.NewChunk<true>()).first->second;
			chunk_storage.GenerateChunk(chunk_index);
			chunk_storage.GenerateMesh(chunk_index);
			chunk_index = chunk_indices.emplace(glm::ivec3(1, 0, 0), chunk_storage.NewChunk<true>()).first->second;
			chunk_storage.GenerateChunk(chunk_index);
			chunk_storage.GenerateMesh(chunk_index);

			while (!glfwWindowShouldClose(renderer.m_window)) {
				glfwPollEvents();

				if (glfwGetKey(renderer.m_window, GLFW_KEY_W))          camera.m_position += 0.25f * glm::normalize(glm::vec3(camera.m_front.x, 0.0f, camera.m_front.z));
				if (glfwGetKey(renderer.m_window, GLFW_KEY_A))          camera.m_position -= 0.25f * glm::normalize(glm::vec3(camera.m_right.x, 0.0f, camera.m_right.z));
				if (glfwGetKey(renderer.m_window, GLFW_KEY_S))          camera.m_position -= 0.25f * glm::normalize(glm::vec3(camera.m_front.x, 0.0f, camera.m_front.z));
				if (glfwGetKey(renderer.m_window, GLFW_KEY_D))          camera.m_position += 0.25f * glm::normalize(glm::vec3(camera.m_right.x, 0.0f, camera.m_right.z));
				if (glfwGetKey(renderer.m_window, GLFW_KEY_SPACE))      camera.m_position += 0.25f * glm::vec3(0.0f, 1.0f, 0.0f);
				if (glfwGetKey(renderer.m_window, GLFW_KEY_LEFT_SHIFT)) camera.m_position -= 0.25f * glm::vec3(0.0f, 1.0f, 0.0f);

				shader.SetUniformMat4(0, camera.GetMatrix(renderer));
				GL::Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				for (auto [chunk_pos, chunk_index] : chunk_indices) {
					// TODO: Set chunk transform uniform
					shader.SetUniformMat4(1, glm::translate(glm::mat4(1.0f), {chunk_pos * glm::ivec3(8, 8, 8)}));
					chunk_storage.Render(chunk_index);
				}
				glfwSwapBuffers(renderer.m_window);
			}
		}
	}

	glfwTerminate();
	return 0;
}
