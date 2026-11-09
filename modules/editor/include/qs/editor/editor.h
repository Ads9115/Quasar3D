#pragma once
#include <qs/platform/window.h>

namespace qs {

// number of stat panel displayed (Plain Data)
struct FrameStats {
    double frameMs = 0.0;
    int stepsThisFrame = 0;
    long totalSteps = 0;
    double simTime = 0.0;
    double alpha = 0.0;
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
    void endFrame();

private:
    bool m_initialized = false;
    bool m_showDemo = false;
};

}
