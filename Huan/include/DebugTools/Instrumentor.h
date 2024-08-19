#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>

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

class Instrumentor
{
  private:
    InstrumentationSession* myCurrentSession;
    std::ofstream myOutputStream;
    int myProfileCount;

  public:
    Instrumentor() : myCurrentSession(nullptr), myProfileCount(0)
    {
    }

    void beginSession(const std::string& name, const std::string& filepath = "results.json")
    {
        myOutputStream.open(filepath);
        writeHeader();
        myCurrentSession = new InstrumentationSession{name};
    }

    void endSession()
    {
        writeFooter();
        myOutputStream.close();
        delete myCurrentSession;
        myCurrentSession = nullptr;
        myProfileCount = 0;
    }

    void writeProfile(const ProfileResult& result)
    {
        if (myProfileCount++ > 0)
            myOutputStream << ",";

        std::string name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');

        myOutputStream << "{";
        myOutputStream << "\"cat\":\"function\",";
        myOutputStream << "\"dur\":" << (result.End - result.Start) << ',';
        myOutputStream << "\"name\":\"" << name << "\",";
        myOutputStream << "\"ph\":\"X\",";
        myOutputStream << "\"pid\":0,";
        myOutputStream << "\"tid\":" << result.ThreadID << ",";
        myOutputStream << "\"ts\":" << result.Start;
        myOutputStream << "}";

        myOutputStream.flush();
    }

    void writeHeader()
    {
        myOutputStream << "{\"otherData\": {},\"traceEvents\":[";
        myOutputStream.flush();
    }

    void writeFooter()
    {
        myOutputStream << "]}";
        myOutputStream.flush();
    }

    static Instrumentor& get()
    {
        static Instrumentor instance;
        return instance;
    }
};

class InstrumentationTimer
{
  public:
    InstrumentationTimer(const char* name) : myName(name), myStopped(false)
    {
        myStartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~InstrumentationTimer()
    {
        if (!myStopped)
            Stop();
    }

    void Stop()
    {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        long long start =
            std::chrono::time_point_cast<std::chrono::microseconds>(myStartTimepoint).time_since_epoch().count();
        long long end =
            std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        Instrumentor::get().writeProfile({myName, start, end, threadID});

        myStopped = true;
    }

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