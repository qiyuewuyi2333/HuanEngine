#pragma once

namespace Huan
{
class TimeStep
{
  public:
    TimeStep(float time = 0.0f) : myTime(time)
    {
    }

    operator float() const
    {
        return myTime;
    }

    float getSeconds() const
    {
        return myTime;
    }
    float getMilliseconds() const
    {
        return myTime * 1000.0f;
    }

  private:
    float myTime;
};
} // namespace Huan