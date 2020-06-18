#include <Murphy.h>


MP_UPTR<Murphy::Application> Murphy::CreateApplication(Murphy::Window& window)
{
    return std::make_unique<Murphy::Application>(window);
}