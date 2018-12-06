#pragma once
#include <ctime>
class Timer
{
public:
	static void InitializeDeltaTime()
	{
		m_DeltaTime = (float)(std::clock() / 1000);
	};
	static void CalculateDeltaTime()
	{
		float timeCycle = (float)std::clock() / 1000.0f;
		m_DeltaTime = timeCycle - Last;
		Last = timeCycle;
		total += timeCycle;
	};
	static float GetDeltaTime()
	{
		return m_DeltaTime;
	};
	static float getTotal() { return total; }
private:
	static float Last;
	static float m_DeltaTime;
	static float total;
};

float Timer::Last = 0.0f;
float Timer::m_DeltaTime = 0.0f;
float Timer::total = 0.0f;