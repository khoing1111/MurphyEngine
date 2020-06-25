#pragma once

#ifdef MP_PLATFORM_WINDOWS

#ifndef UNICODE
#define UNICODE
#endif

#include "Murphy/Platform/Windows/Window.h"
#include "Murphy/Platform/Windows/Window.cpp"
#include "Murphy/Graphics/Core.cpp"
#include "Murphy/Platform/Graphics/DirectX/Renderer.h"
#include "Murphy/Platform/Graphics/DirectX/ConstantBuffer.h"

extern MP_UPTR<Murphy::Application> Murphy::CreateApplication(Murphy::Window&, Murphy::Renderer&);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    Murphy::Log::Init();
    namespace MPDX = Murphy::DirectX;
    namespace DX = DirectX;

    auto windowProps = Murphy::WindowProps(L"Murphy Test Application", 1920, 1080, Murphy::DisplayStyle::Fullscreen);
    auto window = Murphy::Windows::Window::Create(hInstance, L"Murphy", nCmdShow, windowProps);
    if (!window) 
    {
        MP_CORELOG_ERROR("Unable to create new window!");
        return 0;
    }

    auto renderer = MPDX::Renderer(*window);
    if (!renderer.Init())
    {
        MP_CORELOG_ERROR("Unable to intilize Direct3D renderer!");
        return 0;
    }

    // Create and bind Perspective Constant Buffer
    MPDX::VertexConstantBuffer<DX::XMMATRIX> perspectiveConstantBuffer;
    float screenRatio = (float)window->GetHeight() / (float)window->GetWidth();
    DX::XMMATRIX perspectiveMat = DX::XMMatrixTranslation(0.0f, 0.0f, 8.0f) * DX::XMMatrixPerspectiveLH(1.0f, screenRatio, 0.5, 10.0f);
    if (!MPDX::VertexConstantBuffer<DX::XMMATRIX>::Create(
        renderer, perspectiveMat, &perspectiveConstantBuffer, 0u
    ))
    {
        MP_CORELOG_ERROR("Unable to create perspective constant buffer!");
        return 0;
    }

    perspectiveConstantBuffer.Bind(renderer);

    auto app = Murphy::CreateApplication(*window, renderer);
    app->Run();

    return 0;
}
#endif