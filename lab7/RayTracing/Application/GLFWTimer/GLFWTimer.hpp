#pragma once
#include <functional>
#include <GLFW/glfw3.h>

class GLFWTimer
{
public:
	GLFWTimer()
		: m_startTime(glfwGetTime())
		, m_interval(0)
	{
	}

	void StartTimer(double interval)
	{
		m_startTime = glfwGetTime();
		m_interval = interval;
	}

	bool IsTimeUp()
	{
		double currentTime = glfwGetTime();

		return (currentTime - m_startTime) >= m_interval;
	}

private:
	double m_startTime;
	double m_interval;
};
