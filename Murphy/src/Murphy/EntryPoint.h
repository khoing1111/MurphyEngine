#pragma once

#ifdef MP_PLATFORM_WINDOWS

extern Murphy::Application* Murphy::CreateApplication();

int main(int argc, char** argv)
{
    Murphy::Log::Init();
    auto app = Murphy::CreateApplication();
    app->Run();
    delete app;
}
#endif