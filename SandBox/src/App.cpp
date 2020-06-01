#include <Murphy.h>

class App : public Murphy::Application
{
public:
    App()
    {
    }

    ~App()
    {
    }
};


Murphy::Application* Murphy::CreateApplication()
{
    return new App;
}