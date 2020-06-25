#pragma once

#include <exception>
#include <Windows.h>
#include <system_error>

namespace Murphy::Windows
{
    class HRESULTException : public std::exception
    {
    public:
        HRESULTException(HRESULT& hr) : std::exception(std::system_category().message(hr).c_str())
        {
        }

        HRESULTException(std::string& message, HRESULT& hr) 
            : std::exception(
                (message + " -- " + std::system_category().message(hr)).c_str()
            )
        {}
    };
}