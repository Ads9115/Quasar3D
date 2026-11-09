#include <qs/renderer/framebuffer.h>

#include <glad/gl.h>
#include <qs/core/log.h>

namespace qs {

Framebuffer::~Framebuffer() { destroy(); }

void Framebuffer::destroy() {
    if (m_fbo)   glDeleteFramebuffers(1, &m_fbo);
    if (m_color) glDeleteTextures(1, &m_color);
    if (m_depth) glDeleteRenderbuffers(1, &m_depth);
    m_fbo = m_color = m_depth = 0;
}

void Framebuffer::resize(int width, int height) {
    if (width < 1) width = 1;
    if (height < 1) height = 1;
    if (width == m_width && height == m_height && m_fbo) return;

    destroy();
    m_width = width;
    m_height = height;

    // OpenGL 4.5 "direct state access" functions: no bind-then-modify dance.
    glCreateFramebuffers(1, &m_fbo);

    glCreateTextures(GL_TEXTURE_2D, 1, &m_color);
    glTextureStorage2D(m_color, 1, GL_RGBA8, width, height);
    glTextureParameteri(m_color, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_color, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(m_color, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(m_color, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glCreateRenderbuffers(1, &m_depth);
    glNamedRenderbufferStorage(m_depth, GL_DEPTH24_STENCIL8, width, height);

    glNamedFramebufferTexture(m_fbo, GL_COLOR_ATTACHMENT0, m_color, 0);
    glNamedFramebufferRenderbuffer(m_fbo, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depth);

    if (glCheckNamedFramebufferStatus(m_fbo, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        QS_LOG("renderer", "framebuffer incomplete (%d x %d)", width, height);
    }
}

void Framebuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, m_width, m_height);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // namespace qs
