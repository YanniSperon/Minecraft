#include "Timer.h"

Timer::Timer(float timeLimit)
	: m_CurrentTime(0.0f), m_IsRunning(true), m_TimeLimit(timeLimit)
{

}

Timer::Timer(int frameRate)
	: m_CurrentTime(0.0f), m_IsRunning(true), m_TimeLimit(1.0f / (float) frameRate)
{

}

Timer::~Timer()
{

}

void Timer::Update(float deltaTime)
{
	if (m_IsRunning) {
		m_CurrentTime += deltaTime;
	}
}

bool Timer::IsRunning()
{
	return m_IsRunning;
}

bool Timer::IsFinished()
{
	return m_CurrentTime >= m_TimeLimit;
}

void Timer::Start()
{
	m_IsRunning = true;
}

void Timer::Stop()
{
	m_IsRunning = false;
}

void Timer::Toggle()
{
	m_IsRunning = !m_IsRunning;
}

void Timer::Reset()
{
	m_CurrentTime -= m_TimeLimit;
}
