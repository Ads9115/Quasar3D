#include <qs/renderer/renderer.h>

#include <glad/gl.h>
#include <qs/core/log.h>

namespace qs {

bool Renderer::init(GLLoader loader) {
    if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(loader))) {
        QS_LOG("renderer", "gladLoadGL failed");
        return false;
    }

    QS_LOG("renderer", "OpenGL %s on %s",
           reinterpret_cast<const char*>(glGetString(GL_VERSION)),
           reinterpret_cast<const char*>(glGetString(GL_RENDERER)));

    glEnable(GL_DEPTH_TEST);
    return true;
}

void Renderer::beginScene(int width, int height) {
    m_scene.resize(width, height);
    m_scene.bind();
    glClearColor(0.24f, 0.24f, 0.25f, 1.0f);   // viewport background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::endScene() {
    Framebuffer::unbind();
}

void Renderer::beginFrame(int width, int height) {
    glViewport(0, 0, width, height);
    glClearColor(0.10f, 0.10f, 0.11f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

} // namespace qs
