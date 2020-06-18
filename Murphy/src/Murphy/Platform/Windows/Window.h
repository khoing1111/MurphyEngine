#pragma once

#include <windowsx.h>

#include "Murphy/Window.h"
#include "Murphy/IO/WindowEvents.h"
#include "Murphy/IO/MouseEvents.h"



namespace Murphy::Windows
{
    class Window: public ::Murphy::Window
    {
    public:
        Window(const HWND m_WindowRef);
        virtual ~Window();

        virtual unsigned int GetWidth() const override 
        { 
            RECT rect;
            GetWindowRect(m_WindowRef, &rect);
            return rect.right - rect.left;
        }

        virtual unsigned int GetHeight() const override
        {
            RECT rect;
            GetWindowRect(m_WindowRef, &rect);
            return rect.bottom - rect.top;

        }

        virtual bool IsOpen() const override { return IsWindow(m_WindowRef); }
        virtual bool HasFocus() const override { return GetFocus() == m_WindowRef; }
        virtual void Close() const override { if (IsWindow(m_WindowRef)) DestroyWindow(m_WindowRef); }

        virtual void Update(float timeDelta) const override { PollInputs(); }

        virtual void Clear() const override { /* TODO:*/ }
        virtual void Display() const override { /* TODO:*/ }

        static MP_UPTR<Window> Create(HINSTANCE hInstance, const std::wstring windowClassName, int nCmdShow, const WindowProps& props);
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    private:
        void PollInputs() const;

    private:
        HWND m_WindowRef;
    };

}
