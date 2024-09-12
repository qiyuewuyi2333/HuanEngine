#pragma once
#include "Huan/Core.h"

namespace Huan
{
struct ProfileResult
{
    std::string Name;
    long long Start, End;
    uint32_t ThreadID;
};

struct InstrumentationSession
{
    std::string name;
};

class HUAN_API Instrumentor
{
  private:
    InstrumentationSession* myCurrentSession;
    std::ofstream myOutputStream;
    int myProfileCount;

  public:
    Instrumentor();

    void beginSession(const std::string& name, const std::string& filepath = "results.json");

    void endSession();

    void writeProfile(const ProfileResult& result);

    void writeHeader();

    void writeFooter();

    static Instrumentor& get();
};

class HUAN_API InstrumentationTimer
{
  public:
    InstrumentationTimer(const char* name);

    ~InstrumentationTimer();

    void Stop();

  private:
    const char* myName;
    std::chrono::time_point<std::chrono::high_resolution_clock> myStartTimepoint;
    bool myStopped;
};

} // namespace Huan

#define HUAN_PROFILE 1
#if HUAN_PROFILE
    #define HUAN_PROFILE_BEGIN_SESSION(name, filepath) ::Huan::Instrumentor::get().beginSession(name, filepath)
    #define HUAN_PROFILE_END_SESSION() ::Huan::Instrumentor::get().endSession()
    #define HUAN_PROFILE_SCOPE(name) ::Huan::InstrumentationTimer timer##__LINE__(name);
    #define HUAN_PROFILE_FUNCTION() HUAN_PROFILE_SCOPE(__FUNCSIG__)
#else
    #define HUAN_PROFILE_BEGIN_SESSION(name, filepath)
    #define HUAN_PROFILE_END_SESSION()
    #define HUAN_PROFILE_SCOPE(name)
    #define HUAN_PROFILE_FUNCTION()
#endif