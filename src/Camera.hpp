#pragma once
#include "Renderer.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
public:
	Camera();

	void ProcessMouseInput(float p_x, float p_y);

	glm::mat4 GetMatrix(const Renderer& p_renderer);

	glm::vec3 m_position;
	glm::vec3 m_front, m_right, m_up;
	float     m_fov;
private:
	void UpdateVectors();

	float m_yaw, m_pitch;
};