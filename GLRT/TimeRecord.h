#pragma once
class TimeRecord {
private:
	float m_delta_time = 0.f;
	float m_last_frame = 0.f;

public:
	void Update(float current_time) {
		m_delta_time = current_time - m_last_frame;
		m_last_frame = current_time;
	}

	float GetFrameRate() {
		if (m_delta_time <= 1e-6)
			return 0.f;
		return 1.f / m_delta_time;
	}

	float GetDeltaTime() {
		return m_delta_time;
	}

};