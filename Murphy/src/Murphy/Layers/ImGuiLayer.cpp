#include "mppch.h"
#include "ImGuiLayer.h"

#include "imgui.h"

namespace Murphy
{

    ImGuiLayer::ImGuiLayer(MP_SPTR<Window> window)
        : Layer("ImGuiLayer"), m_Window(window)
    {
        Murphy::ImGuiSFML::Init(window);

        // Initialize event dispatchers
        PushEventDispatcher(new IO::MouseMovedEventDispatcher(
            std::bind(&ImGuiLayer::OnMouseMoved, this, std::placeholders::_1)
        ));

        PushEventDispatcher(new IO::MousePressedEventDispatcher(
            std::bind(&ImGuiLayer::OnMousePressed, this, std::placeholders::_1)
        ));

        PushEventDispatcher(new IO::MouseReleasedEventDispatcher(
            std::bind(&ImGuiLayer::OnMouseReleased, this, std::placeholders::_1)
        ));

        PushEventDispatcher(new IO::MouseWheelScrolledEventDispatcher(
            std::bind(&ImGuiLayer::OnMouseWheelScrolledEvent, this, std::placeholders::_1)
        ));
    }

    ImGuiLayer::~ImGuiLayer()
    {
        Murphy::ImGuiSFML::Shutdown();
    }

    void ImGuiLayer::Update(float timeDelta)
    {
        ImGuiIO& io = ImGui::GetIO();
        auto window = m_Window.lock();
        io.DisplaySize = { (float)window->GetWidth(), (float)window->GetHeight() };
        io.DeltaTime = timeDelta;


        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        static float f = 0.0f;
        static int counter = 0;

        ImGui::NewFrame();
        //ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        //ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        //auto clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        //ImGui::ColorEdit3("clear color", (float*)&clearColor); // Edit 3 floats representing a color

        //if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        //    counter++;

        //ImGui::SameLine();
        //ImGui::Text("counter = %d", counter);

        //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        //ImGui::End();
        ImGui::EndFrame();
    }

    int ImGuiLayer::GetImGuiMouseButton(const IO::Mouse::Button& button) const
    {
        switch (button)
        {
        case IO::Mouse::Button::Left:
            return 0;
        case IO::Mouse::Button::Right:
            return 1;
        case IO::Mouse::Button::Middle:
        case IO::Mouse::Button::XButton1:
        case IO::Mouse::Button::XButton2:
            return 2;
        }

        return -1;
    }

    bool ImGuiLayer::OnMouseMoved(IO::MouseMovedEvent & event)
    {
        if (auto window = m_Window.lock(); window && window->HasFocus())
        {
            ImGuiIO& io = ImGui::GetIO();
            io.MousePos = { (float)event.GetX(), (float)event.GetY() };
        }

        return true;
    }

    bool ImGuiLayer::OnMousePressed(IO::MousePressedEvent& event)
    {
        if (auto window = m_Window.lock(); window && window->HasFocus())
        {
            ImGuiIO& io = ImGui::GetIO();
            io.MousePos = { (float)event.GetX(), (float)event.GetY() };
            int mouseButton = GetImGuiMouseButton(event.GetButton());
            if (mouseButton >= 0)
                io.MouseDown[mouseButton] = true;
        }

        return true;
    }

    bool ImGuiLayer::OnMouseReleased(IO::MouseReleasedEvent & event)
    {
        if (auto window = m_Window.lock(); window && window->HasFocus())
        {
            ImGuiIO& io = ImGui::GetIO();
            io.MousePos = { (float)event.GetX(), (float)event.GetY() };
            int mouseButton = GetImGuiMouseButton(event.GetButton());
            if (mouseButton >= 0)
                io.MouseDown[mouseButton] = false;
        }

        return true;
    }

    bool ImGuiLayer::OnMouseWheelScrolledEvent(IO::MouseWheelScrolledEvent& event)
    {
        if (auto window = m_Window.lock(); window && window->HasFocus())
        {
            ImGuiIO& io = ImGui::GetIO();
            io.MousePos = { (float)event.GetX(), (float)event.GetY() };
            io.MouseWheel += event.GetDelta();
        }

        return true;
    }
}