#include <qs/platform/window.h>

#include <GLFW/glfw3.h>
#include <qs/core/log.h>

namespace qs {

Window::Window(int width, int height, const char* title) {
    if (!glfwInit()) {
        QS_LOG("platform", "glfwInit failed");
        return;
    }

    // Ask for OpenGL 4.5, core profile (the modern subset, no legacy functions).
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_window) {
        QS_LOG("platform", "glfwCreateWindow failed");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);                // vsync on: swapBuffers waits for the monitor
}

Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }
}

bool Window::shouldClose() const {
    return m_window && glfwWindowShouldClose(m_window);
}

void Window::pollEvents() {
    glfwPollEvents();
    // Temporary: Esc closes the window. A proper input module comes later.
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
    }
}

void Window::swapBuffers() {
    glfwSwapBuffers(m_window);
}

GLProc Window::getProcAddress(const char* name) {
    return glfwGetProcAddress(name);
}

void Window::framebufferSize(int& width, int& height) const {
    glfwGetFramebufferSize(m_window, &width, &height);
}

} // namespace qs
