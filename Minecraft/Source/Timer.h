#pragma once

class Timer {
private:
	float m_CurrentTime;
	float m_TimeLimit;

	bool m_IsRunning;
public:
	Timer(float timeLimit);
	Timer(int frameRate);
	~Timer();

	void Update(float deltaTime);

	bool IsRunning();
	bool IsFinished();

	void Start();
	void Stop();
	void Toggle();

	void Reset();
};