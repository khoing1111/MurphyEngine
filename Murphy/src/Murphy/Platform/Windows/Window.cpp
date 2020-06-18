#include "mppch.h"
#include "Window.h"


namespace Murphy::Windows
{
    LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    MP_UPTR<Window> Window::Create(HINSTANCE hInstance, const std::wstring windowClassName, int nCmdShow, const WindowProps& props)
    {
        // Register the window class.
        WNDCLASS wc = { };

        wc.lpfnWndProc = Window::WindowProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = windowClassName.c_str();
        RegisterClass(&wc);

        // Create the window.
        HWND hwnd = CreateWindowEx(
            0,                              // Optional window styles.
            windowClassName.c_str(),        // Window class
            props.Title.c_str(),            // Window text
            WS_OVERLAPPEDWINDOW,            // Window style

            // Size and position
            CW_USEDEFAULT, CW_USEDEFAULT, props.Width, props.Height,

            NULL,       // Parent window    
            NULL,       // Menu
            hInstance,  // Instance handle
            NULL        // Additional application data
        );

        if (hwnd == NULL)
            return nullptr;

        ShowWindow(hwnd, nCmdShow);
        return std::make_unique<Window>(hwnd);
    }

    Window::Window(const HWND windowRef)
        : m_WindowRef(windowRef) {}

    Window::~Window()
    {
    }

    void Window::PollInputs() const
    {
        MSG msg = { };
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // Global events that not belong to any specific window
            switch (msg.message)
            {
            case WM_QUIT:
                PropagateEvent(IO::WindowClosedEvent());
                return;
            }

            // Handle Window's specific events
            if (msg.hwnd != m_WindowRef)
                return;

            int xPos, yPos;
            float zDelta;
            switch (msg.message)
            {
            case WM_MOUSEMOVE:
                xPos = GET_X_LPARAM(msg.lParam);
                yPos = GET_Y_LPARAM(msg.lParam);
                PropagateEvent(IO::MouseMovedEvent(xPos, yPos));
                return;
            case WM_LBUTTONDOWN:
                xPos = GET_X_LPARAM(msg.lParam);
                yPos = GET_Y_LPARAM(msg.lParam);
                PropagateEvent(IO::MousePressedEvent(xPos, yPos, Murphy::IO::Mouse::Button::Left));
                return;
            case WM_RBUTTONDOWN:
                xPos = GET_X_LPARAM(msg.lParam);
                yPos = GET_Y_LPARAM(msg.lParam);
                PropagateEvent(IO::MousePressedEvent(xPos, yPos, Murphy::IO::Mouse::Button::Right));
                return;
            case WM_MBUTTONDOWN:
                xPos = GET_X_LPARAM(msg.lParam);
                yPos = GET_Y_LPARAM(msg.lParam);
                PropagateEvent(IO::MousePressedEvent(xPos, yPos, Murphy::IO::Mouse::Button::Middle));
                return;
            case WM_LBUTTONUP:
                xPos = GET_X_LPARAM(msg.lParam);
                yPos = GET_Y_LPARAM(msg.lParam);
                PropagateEvent(IO::MouseReleasedEvent(xPos, yPos, Murphy::IO::Mouse::Button::Left));
                return;
            case WM_RBUTTONUP:
                xPos = GET_X_LPARAM(msg.lParam);
                yPos = GET_Y_LPARAM(msg.lParam);
                PropagateEvent(IO::MouseReleasedEvent(xPos, yPos, Murphy::IO::Mouse::Button::Right));
                return;
            case WM_MBUTTONUP:
                xPos = GET_X_LPARAM(msg.lParam);
                yPos = GET_Y_LPARAM(msg.lParam);
                PropagateEvent(IO::MouseReleasedEvent(xPos, yPos, Murphy::IO::Mouse::Button::Middle));
                return;
            case WM_MOUSEWHEEL:
                xPos = GET_X_LPARAM(msg.lParam);
                yPos = GET_Y_LPARAM(msg.lParam);
                zDelta = GET_WHEEL_DELTA_WPARAM(msg.wParam);
                PropagateEvent(IO::MouseWheelScrolledEvent(xPos, yPos, zDelta));
                return;
            default:
                DispatchMessage(&msg);
                return;
            }
        }
    }
}