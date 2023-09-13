#pragma once
class TimeRecord {
private:
	float m_deltaTime = 0.f;
	float m_lastFrame = 0.f;

public:
	void Update(float currentTime) {
		m_deltaTime = currentTime - m_lastFrame;
		m_lastFrame = currentTime;
	}

	float GetFrameRate() {
		if (m_deltaTime <= 1e-6)
			return 0.f;
		return 1.f / m_deltaTime;
	}

};