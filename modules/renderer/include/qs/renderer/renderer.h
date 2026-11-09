#pragma once

#include <cstdint>
#include <qs/platform/window.h>
#include <qs/renderer/camera.h>
#include <qs/renderer/grid.h>
#include <qs/renderer/framebuffer.h>

namespace qs {

class Renderer {
public:
    //Loading OpenGL funcs
    bool init(GLLoader loader);

    void beginScene(int width, int height, const Camera& camera);
    void drawGrid();
    void endScene();
    uint32_t sceneTexture() const { return m_scene.colorTexture();}

    void beginFrame(int width, int height);

private:
    Framebuffer m_scene;
    Grid m_grid;

    Mat4 m_view{1.0f};
    Mat4 m_proj{1.0f};
    Vec3 m_camPos{0.0f};
    float m_far = 500.0f;
};

}
