#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
	m_fov = 45.0f;
	m_position = {0.0f, 0.0f, -3.0f};
	m_yaw   = 0.0f;
	m_pitch = 0.0f;
}

void Camera::ProcessMouseInput(float p_x, float p_y)
{
	m_yaw   += p_x * 0.25f;
	m_pitch -= p_y * 0.25f;

	m_pitch = m_pitch > 89.0f ? 89.0f : m_pitch < -89.0f ? -89.0f : m_pitch;

	UpdateVectors();
}

glm::mat4 Camera::GetMatrix(const Renderer& p_renderer)
{
	return glm::perspectiveFov(m_fov, static_cast<float>(p_renderer.m_width), static_cast<float>(p_renderer.m_height), 0.1f, 10000.0f) * glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::UpdateVectors()
{
	m_front = glm::normalize(glm::vec3(glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch)),
	                                   glm::sin(glm::radians(m_pitch)),
	                                   glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch))));

	m_right = glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)));
	m_up    = glm::normalize(glm::cross(m_right, m_front));
}