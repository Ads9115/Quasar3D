#pragma once

#include <cstdint>
#include <qs/platform/window.h>
#include <qs/renderer/framebuffer.h>

namespace qs {

class Renderer {
public:
    //Loading OpenGL funcs
    bool init(GLLoader loader);

    void beginScene(int width,  int height);
    void endScene();
    uint32_t sceneTexture() const { return m_scene.colorTexture();}

    void beginFrame(int width, int height);

private:
    Framebuffer m_scene;
};

}
