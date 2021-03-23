#pragma once
#include <GLFW/glfw3.h>

class Renderer
{
public:
	Renderer(int p_width, int p_height);
	~Renderer();

	void OnResize(int p_width, int p_height);

	GLFWwindow* m_window;
};
