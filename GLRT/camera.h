#pragma once
#include "glm/gtc/type_ptr.hpp"

class Camera {
private:
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
	float m_yaw = -90.0f;
	float m_pitch = 0.0f;
	unsigned int m_loop_num = 0;

public:
	
	static const float min_fov, max_fov, min_speed, max_speed;
	// always move toward m_front by default
	void Move(float movement) {
		m_pos += movement * m_front;
		ResetLoopNum();
	}
	// dir should be normalized
	void Move(float movement, glm::vec3 dir) {
		dir = glm::normalize(dir);
		m_pos += movement * dir;
		ResetLoopNum();
	}
	glm::vec3 GetFront() { return m_front; }
	glm::vec3 GetUp() { return m_up; }
	glm::vec3 GetRight() { return m_right; }
	glm::vec3 GetPos() { return m_pos; }
	float GetFov() { return m_fov; }
	float GetSpeed() { return m_speed; }
	float GetNear() { return m_near; }
	float GetWidth() { return m_width; }
	float GetHeight() { return m_height; }
	float GetRatio() { return m_ratio; }
	float GetYaw() { return m_yaw; }
	float GetPitch() { return m_pitch; }
	unsigned int GetLoopNum() { return m_loop_num; }
	
	
	void SetFront(glm::vec3 f) { m_front = glm::normalize(f); ResetLoopNum(); }
	void IncreLoopNum() { m_loop_num++; }
	void ResetLoopNum() { m_loop_num = 0; }
	void SetUp(glm::vec3 u) { m_up = glm::normalize(u); ResetLoopNum(); }
	void SetRight(glm::vec3 r) { m_right = glm::normalize(r); ResetLoopNum(); }
	void SetPos(glm::vec3 p) { m_pos = p; ResetLoopNum(); }
	void UpdateFov(double yoffset) {
		m_fov -= (float)yoffset;
		m_fov = std::clamp(m_fov, min_fov, max_fov);
		ResetLoopNum();
	}
	void SetSpeed(float s) { m_speed = std::clamp(s, min_speed, max_speed); }
	void SetWidthHeight(unsigned int w, unsigned int h) {
		m_width = w;
		m_height = h;
		m_ratio = m_width / m_height;
		ResetLoopNum();
	}
	void UpdateYaw(float offset) { m_yaw += offset; }
	void UpdatePitch(float offset) { m_pitch += offset; m_pitch = std::clamp(m_pitch, -89.f, 89.f); }

};