#pragma once
#include "glm/gtc/type_ptr.hpp"

class Camera {
public:
	glm::vec3 m_pos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f); // should stay normalized
	glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_right = glm::vec3(1.0f, 0.0f, 0.0f);
	float m_fov = 45.0f;
	float m_speed = 0.005f;
	float m_near = 0.1f;
	// sync with the screen size
	float m_width, m_height;
	float m_ratio = 1.5f;

public:
	float m_yaw = -90.0f;
	float m_pitch = 0.0f;
	// always move toward m_front by default
	void Move(float movement) {
		m_pos += movement * m_front;
	}
	// dir should be normalized
	void Move(float movement, glm::vec3 dir) {
		dir = glm::normalize(dir);
		m_pos += movement * dir;
	}
	glm::vec3 GetFront() {
		return m_front;
	}
	glm::vec3 GetUp() {
		return m_up;
	}
	glm::vec3 GetRight() {
		return m_right;
	}
	void SetWidthHeight(unsigned int w, unsigned int h) {
		m_width = w;
		m_height = h;
		m_ratio = m_width / m_height;
	}
	void UpdateFov(double yoffset) {
		m_fov -= (float)yoffset;
		if (m_fov < 1.0f)
			m_fov = 1.0f;
		if (m_fov > 45.0f)
			m_fov = 45.0f;
	}
	void SetFront(glm::vec3 f) {
		m_front = glm::normalize(f);
	}
};