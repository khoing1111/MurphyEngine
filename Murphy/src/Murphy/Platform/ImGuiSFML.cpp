#include "mppch.h"
#include "ImGuiSFML.h"


namespace Murphy::ImGuiSFML
{
    sf::Cursor* s_mouseCursors[ImGuiMouseCursor_COUNT];
    bool s_mouseCursorLoaded[ImGuiMouseCursor_COUNT];

    static const unsigned int NULL_JOYSTICK_ID = sf::Joystick::Count;
    static unsigned int s_joystickId = NULL_JOYSTICK_ID;

    static sf::Texture* s_fontTexture = nullptr;
    static bool s_windowHasFocus = false;

    const char* GetClipboadText(void* /*userData*/) {
        std::basic_string<sf::Uint8> tmp = sf::Clipboard::getString().toUtf8();
        return std::string(tmp.begin(), tmp.end()).c_str();
    }

    void SetClipboardText(void* /*userData*/, const char* text) {
        sf::Clipboard::setString(sf::String::fromUtf8(text, text + std::strlen(text)));
    }

    void LoadMouseCursor(ImGuiMouseCursor imguiCursorType,
        sf::Cursor::Type sfmlCursorType) {
        s_mouseCursors[imguiCursorType] = new sf::Cursor();
        s_mouseCursorLoaded[imguiCursorType] =
            s_mouseCursors[imguiCursorType]->loadFromSystem(sfmlCursorType);
    }

    ImTextureID ConvertGLTextureHandleToImTextureID(GLuint glTextureHandle) {
        ImTextureID textureID = (ImTextureID)NULL;
        std::memcpy(&textureID, &glTextureHandle, sizeof(GLuint));
        return textureID;
    }

    void UpdateFontTexture() {
        ImGuiIO& io = ImGui::GetIO();
        unsigned char* pixels;
        int width, height;

        io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

        sf::Texture& texture = *s_fontTexture;
        texture.create(width, height);
        texture.update(pixels);

        io.Fonts->TexID =
            ConvertGLTextureHandleToImTextureID(texture.getNativeHandle());
    }

    void Init(MP_SPTR<Murphy::Window> window, bool loadDefaultFont) {
#if __cplusplus < 201103L  // runtime assert when using earlier than C++11 as no
        // static_assert support
        assert(
            sizeof(GLuint) <=
            sizeof(ImTextureID));  // ImTextureID is not large enough to fit GLuint.
#endif

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        // tell ImGui which features we support
        io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.BackendPlatformName = "imgui_impl_sfml";

        // init keyboard mapping
        io.KeyMap[ImGuiKey_Tab] = sf::Keyboard::Tab;
        io.KeyMap[ImGuiKey_LeftArrow] = sf::Keyboard::Left;
        io.KeyMap[ImGuiKey_RightArrow] = sf::Keyboard::Right;
        io.KeyMap[ImGuiKey_UpArrow] = sf::Keyboard::Up;
        io.KeyMap[ImGuiKey_DownArrow] = sf::Keyboard::Down;
        io.KeyMap[ImGuiKey_PageUp] = sf::Keyboard::PageUp;
        io.KeyMap[ImGuiKey_PageDown] = sf::Keyboard::PageDown;
        io.KeyMap[ImGuiKey_Home] = sf::Keyboard::Home;
        io.KeyMap[ImGuiKey_End] = sf::Keyboard::End;
        io.KeyMap[ImGuiKey_Insert] = sf::Keyboard::Insert;
#ifdef ANDROID
        io.KeyMap[ImGuiKey_Backspace] = sf::Keyboard::Delete;
#else
        io.KeyMap[ImGuiKey_Delete] = sf::Keyboard::Delete;
        io.KeyMap[ImGuiKey_Backspace] = sf::Keyboard::BackSpace;
#endif
        io.KeyMap[ImGuiKey_Space] = sf::Keyboard::Space;
        io.KeyMap[ImGuiKey_Enter] = sf::Keyboard::Return;
        io.KeyMap[ImGuiKey_Escape] = sf::Keyboard::Escape;
        io.KeyMap[ImGuiKey_A] = sf::Keyboard::A;
        io.KeyMap[ImGuiKey_C] = sf::Keyboard::C;
        io.KeyMap[ImGuiKey_V] = sf::Keyboard::V;
        io.KeyMap[ImGuiKey_X] = sf::Keyboard::X;
        io.KeyMap[ImGuiKey_Y] = sf::Keyboard::Y;
        io.KeyMap[ImGuiKey_Z] = sf::Keyboard::Z;

        // HACK: No Joystick support for now
        //s_joystickId = getConnectedJoystickId();

        //for (unsigned int i = 0; i < ImGuiNavInput_COUNT; i++) {
        //    s_joystickMapping[i] = NULL_JOYSTICK_BUTTON;
        //}

        //initDefaultJoystickMapping();

        // init rendering
        io.DisplaySize.x = window->GetWidth();
        io.DisplaySize.y = window->GetHeight();

        // clipboard
        io.SetClipboardTextFn = SetClipboardText;
        io.GetClipboardTextFn = GetClipboadText;

        // load mouse cursors
        for (int i = 0; i < ImGuiMouseCursor_COUNT; ++i) {
            s_mouseCursorLoaded[i] = false;
        }

        LoadMouseCursor(ImGuiMouseCursor_Arrow, sf::Cursor::Arrow);
        LoadMouseCursor(ImGuiMouseCursor_TextInput, sf::Cursor::Text);
        LoadMouseCursor(ImGuiMouseCursor_ResizeAll, sf::Cursor::SizeAll);
        LoadMouseCursor(ImGuiMouseCursor_ResizeNS, sf::Cursor::SizeVertical);
        LoadMouseCursor(ImGuiMouseCursor_ResizeEW, sf::Cursor::SizeHorizontal);
        LoadMouseCursor(ImGuiMouseCursor_ResizeNESW, sf::Cursor::SizeBottomLeftTopRight);
        LoadMouseCursor(ImGuiMouseCursor_ResizeNWSE, sf::Cursor::SizeTopLeftBottomRight);

        if (s_fontTexture) {  // delete previously created texture
            delete s_fontTexture;
        }

        s_fontTexture = new sf::Texture;

        if (loadDefaultFont) {
            // this will load default font automatically
            // No need to call AddDefaultFont
            UpdateFontTexture();
        }

        s_windowHasFocus = window->HasFocus();
    }

    void Shutdown() {
        ImGui::GetIO().Fonts->TexID = (ImTextureID)NULL;

        if (s_fontTexture) {  // if internal texture was created, we delete it
            delete s_fontTexture;
            s_fontTexture = NULL;
        }

        for (int i = 0; i < ImGuiMouseCursor_COUNT; ++i) {
            if (s_mouseCursorLoaded[i]) {
                delete s_mouseCursors[i];
                s_mouseCursors[i] = NULL;

                s_mouseCursorLoaded[i] = false;
            }
        }

        ImGui::DestroyContext();
    }

    void OnMouseMove(Murphy::IO::MouseMovedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = { (float)event.GetX(), (float)event.GetY() };
    }

    void OnMousePressed(Murphy::IO::MousePressedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = { (float)event.GetX(), (float)event.GetY() };
        switch (event.GetButton())
        {
        case IO::Mouse::Left:
            io.MouseDown[0] = true;
            break;
        case IO::Mouse::Right:
            io.MouseDown[1] = true;
            break;
        case IO::Mouse::Middle:
        case IO::Mouse::XButton1:
        case IO::Mouse::XButton2:
            io.MouseDown[2] = true;
            break;
        }

        // Update Ctrl, Shift, Alt, Super state
        io.KeyCtrl = io.KeysDown[sf::Keyboard::LControl] || io.KeysDown[sf::Keyboard::RControl];
        io.KeyAlt = io.KeysDown[sf::Keyboard::LAlt] || io.KeysDown[sf::Keyboard::RAlt];
        io.KeyShift = io.KeysDown[sf::Keyboard::LShift] || io.KeysDown[sf::Keyboard::RShift];
        io.KeySuper = io.KeysDown[sf::Keyboard::LSystem] || io.KeysDown[sf::Keyboard::RSystem];
    }

    void OnMouseReleased(Murphy::IO::MouseReleasedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = { (float)event.GetX(), (float)event.GetY() };
        switch (event.GetButton())
        {
        case IO::Mouse::Left:
            io.MouseReleased[0] = false;
            break;
        case IO::Mouse::Right:
            io.MouseReleased[1] = false;
            break;
        case IO::Mouse::Middle:
        case IO::Mouse::XButton1:
        case IO::Mouse::XButton2:
            io.MouseReleased[2] = false;
            break;
        }
    }

    GLuint ConvertImTextureIDToGLTextureHandle(ImTextureID textureID) {
        GLuint glTextureHandle;
        std::memcpy(&glTextureHandle, &textureID, sizeof(GLuint));
        return glTextureHandle;
    }

    // Rendering callback
    void RenderDrawLists(ImDrawData* draw_data) {
        ImGui::GetDrawData();
        if (draw_data->CmdListsCount == 0) {
            return;
        }

        ImGuiIO& io = ImGui::GetIO();
        assert(io.Fonts->TexID !=
            (ImTextureID)NULL);  // You forgot to create and set font texture

     // scale stuff (needed for proper handling of window resize)
        int fb_width =
            static_cast<int>(io.DisplaySize.x * io.DisplayFramebufferScale.x);
        int fb_height =
            static_cast<int>(io.DisplaySize.y * io.DisplayFramebufferScale.y);
        if (fb_width == 0 || fb_height == 0) {
            return;
        }
        draw_data->ScaleClipRects(io.DisplayFramebufferScale);

#ifdef GL_VERSION_ES_CL_1_1
        GLint last_program, last_texture, last_array_buffer,
            last_element_array_buffer;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
        glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &last_element_array_buffer);
#else
        glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT);
#endif

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_SCISSOR_TEST);
        glEnable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);

        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

#ifdef GL_VERSION_ES_CL_1_1
        glOrthof(0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f, -1.0f, +1.0f);
#else
        glOrtho(0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f, -1.0f, +1.0f);
#endif

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        for (int n = 0; n < draw_data->CmdListsCount; ++n) {
            const ImDrawList* cmd_list = draw_data->CmdLists[n];
            const unsigned char* vtx_buffer =
                (const unsigned char*)&cmd_list->VtxBuffer.front();
            const ImDrawIdx* idx_buffer = &cmd_list->IdxBuffer.front();

            glVertexPointer(2, GL_FLOAT, sizeof(ImDrawVert),
                (void*)(vtx_buffer + offsetof(ImDrawVert, pos)));
            glTexCoordPointer(2, GL_FLOAT, sizeof(ImDrawVert),
                (void*)(vtx_buffer + offsetof(ImDrawVert, uv)));
            glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(ImDrawVert),
                (void*)(vtx_buffer + offsetof(ImDrawVert, col)));

            for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); ++cmd_i) {
                const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
                if (pcmd->UserCallback) {
                    pcmd->UserCallback(cmd_list, pcmd);
                }
                else {
                    GLuint textureHandle =
                        ConvertImTextureIDToGLTextureHandle(pcmd->TextureId);
                    glBindTexture(GL_TEXTURE_2D, textureHandle);
                    glScissor((int)pcmd->ClipRect.x,
                        (int)(fb_height - pcmd->ClipRect.w),
                        (int)(pcmd->ClipRect.z - pcmd->ClipRect.x),
                        (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
                    glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount,
                        GL_UNSIGNED_SHORT, idx_buffer);
                }
                idx_buffer += pcmd->ElemCount;
            }
        }
#ifdef GL_VERSION_ES_CL_1_1
        glBindTexture(GL_TEXTURE_2D, last_texture);
        glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, last_element_array_buffer);
        glDisable(GL_SCISSOR_TEST);
#else
        glPopAttrib();
#endif
    }
}
