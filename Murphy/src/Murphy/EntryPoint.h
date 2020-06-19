#pragma once

#ifdef MP_PLATFORM_WINDOWS

#ifndef UNICODE
#define UNICODE
#endif

#include "Murphy/Platform/Windows/Window.h"
#include "Murphy/Platform/Windows/Window.cpp"
#include "Murphy/Platform/Graphics/DirectX/Renderer.h"

extern MP_UPTR<Murphy::Application> Murphy::CreateApplication(Murphy::Window&, Murphy::Renderer&);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    Murphy::Log::Init();

    auto windowProps = Murphy::WindowProps(L"Murphy Test Application", 1920, 1080, Murphy::DisplayStyle::Fullscreen);
    auto window = Murphy::Windows::Window::Create(hInstance, L"Murphy", nCmdShow, windowProps);
    if (!window) 
    {
        MP_CORELOG_ERROR("Unable to create new window!");
        return 0;
    }

    auto renderer = Murphy::DirectX::Renderer(*window);
    if (!renderer.Init())
    {
        MP_CORELOG_ERROR("Unable to intilize Direct3D renderer!");
        return 0;
    }

    auto app = Murphy::CreateApplication(*window, renderer);
    app->Run();

    return 0;
}
#endif