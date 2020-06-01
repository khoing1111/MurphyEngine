#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Murphy
{
    class MURPHY_API Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}


// Core log macros
#define MP_CORELOG_TRACE(...) ::Murphy::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MP_CORELOG_INFO(...) ::Murphy::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MP_CORELOG_WARN(...) ::Murphy::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MP_CORELOG_ERROR(...) ::Murphy::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MP_CORELOG_FATAL(...) ::Murphy::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macors
#define MP_LOG_TRACE(...) ::Murphy::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MP_LOG_INFO(...) ::Murphy::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MP_LOG_WARN(...) ::Murphy::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MP_LOG_ERROR(...) ::Murphy::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MP_LOG_FATAL(...) ::Murphy::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#if define MP_RELEASE || define MP_DIST
    // Strip out low level logs on release
    #define MP_CORELOG_WARN
    #define MP_CORELOG_TRACE
    #define MP_CORELOG_INFO

    #define MP_LOG_WARN
    #define MP_LOG_TRACE
    #define MP_LOG_INFO
#endif


#ifdef MP_DIST
    // Strip all logs on distribution release
    #define MP_CORELOG_ERROR
    #define MP_CORELOG_FATAL

    #define MP_LOG_ERROR
    #define MP_LOG_FATAL
#endif