#pragma once
#include "DebugTools/Instrumentor.h"
namespace Huan
{
Instrumentor::Instrumentor() : myCurrentSession(nullptr), myProfileCount(0)
{
}
void Instrumentor::beginSession(const std::string& name, const std::string& filepath)
{
    myOutputStream.open(filepath);
    writeHeader();
    myCurrentSession = new InstrumentationSession{name};
}
void Instrumentor::endSession()
{
    writeFooter();
    myOutputStream.close();
    delete myCurrentSession;
    myCurrentSession = nullptr;
    myProfileCount = 0;
}
void Instrumentor::writeProfile(const ProfileResult& result)
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
void Instrumentor::writeHeader()
{
    myOutputStream << "{\"otherData\": {},\"traceEvents\":[";
    myOutputStream.flush();
}
void Instrumentor::writeFooter()
{
    myOutputStream << "]}";
    myOutputStream.flush();
}
Instrumentor& Instrumentor::get()
{
    static Instrumentor instance;
    return instance;
}
InstrumentationTimer::InstrumentationTimer(const char* name) : myName(name), myStopped(false)
{
    myStartTimepoint = std::chrono::high_resolution_clock::now();
}
InstrumentationTimer::~InstrumentationTimer()
{
    if (!myStopped)
        Stop();
}
void InstrumentationTimer::Stop()
{
    auto endTimepoint = std::chrono::high_resolution_clock::now();

    long long start =
        std::chrono::time_point_cast<std::chrono::microseconds>(myStartTimepoint).time_since_epoch().count();
    long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

    uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
    Instrumentor::get().writeProfile({myName, start, end, threadID});

    myStopped = true;
}
} // namespace Huan
