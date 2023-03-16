#pragma once 

#include <functional>

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
class Timer
{
public:
	Timer();
	void Update(const double delta);
	void Start_Timer(const double duration);
	void Set_Callback(std::function<void()> callback);

private:
	std::function<void()> Callback;
	double Time_Left;
	bool bRunning;

};
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
