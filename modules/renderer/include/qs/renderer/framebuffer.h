#pragma once
#include <cstdint>

namespace qs {

// An off-screen render target: a color texture plus a depth buffer.
class Framebuffer {
public:
    Framebuffer() = default;
    ~Framebuffer();
    Framebuffer(const Framebuffer&) = delete;
    Framebuffer& operator=(const Framebuffer&) = delete;

    void resize(int width, int height);   // recreates the buffers only if the size changed
    void bind() const;                    // draw into this, and set the viewport to its size
    static void unbind();                 // go back to drawing into the window

    uint32_t colorTexture() const { return m_color; }

private:
    void destroy();

    uint32_t m_fbo = 0;
    uint32_t m_color = 0;
    uint32_t m_depth = 0;
    int m_width = 0;
    int m_height = 0;
};

} // namespace qs
