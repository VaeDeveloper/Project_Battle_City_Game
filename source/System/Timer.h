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
    bool bIsRunning;
    double Time_Left;
    std::function<void()> Callback;
};
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
