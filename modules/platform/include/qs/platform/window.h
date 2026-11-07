#pragma once

struct GLFWwindow;

namespace qs {

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

    private:
        GLFWwindow* m_window = nullptr;
    };
}
