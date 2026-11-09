#pragma once

#include <cstdint>
#include <qs/platform/window.h>

namespace qs {

// number of stat panel displayed (Plain Data)
struct FrameStats {
    double frameMs = 0.0;
    int stepsThisFrame = 0;
    long totalSteps = 0;
    double simTime = 0.0;
    double alpha = 0.0;
    int viewportW = 0;
    int viewportH = 0;
};

struct ViewportInput {
    bool orbit = false;
    bool pan = false;
    float dx = 0.0f, dy = 0.0f;
    float scroll = 0.0f;
};

class Editor {
public:
    Editor() = default;
    ~Editor();
    Editor(const Editor&) = delete;
    Editor& operator=(const Editor&) = delete;

    bool init(Window& window);
    void beginFrame();
    void drawStats(const FrameStats& stats);
    // Shows the scene image. Writes the panel's current size (pixels) into width/height,
    // which the app uses to size next frame's scene render.
    ViewportInput drawViewport(uint32_t sceneTexture, int& width, int& height);

    void endFrame();

private:
    bool m_initialized = false;
    bool m_showDemo = false;
    bool m_dragging = false;
};

}
