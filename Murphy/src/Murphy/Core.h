#pragma once

#ifdef MP_PLATFORM_WINDOWS
    #ifdef MP_BUILD_DLL
        #define MURPHY_API __declspec(dllexport)
    #else
        #define MURPHY_API __declspec(dllimport)
    #endif
#else
    #error Murphy only support Windows!
#endif

#define MP_UPTR std::unique_ptr
#define MP_SPTR std::shared_ptr
#define MP_WPTR std::weak_ptr
