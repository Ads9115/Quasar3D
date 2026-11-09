#pragma once

struct GLFWwindow;

namespace qs {
    //Raw OpenGl func pointer and a func that looks one up by name.
    using GLProc = void (*)();
    using GLLoader = GLProc (*)(const char* name);

    // One window for now
    class Window {
    public:
        Window(int width, int height, const char* title);
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        bool ok() const { return m_window != nullptr; }
        bool shouldClose() const;
        void pollEvents();
        void swapBuffers();
        GLFWwindow* handle() const { return m_window; }

        static GLProc getProcAddress(const char* name); // for the renderers lloader
        void framebufferSize(int& width, int& height) const;

    private:
        GLFWwindow* m_window = nullptr;
    };
}
