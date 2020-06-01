#pragma once

#ifdef MP_PLATFORM_WINDOWS

extern Murphy::Application* Murphy::CreateApplication();

int main(int argc, char** argv)
{
    Murphy::Log::Init();
    MP_CORELOG_WARN("HELLO FROM MURPHY");
    MP_LOG_INFO("HELLO {0}", "Khoi");

    auto app = Murphy::CreateApplication();
    app->Run();
    delete app;
}
#endif