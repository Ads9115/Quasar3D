#pragma once
#include <qs/platform/window.h>

namespace qs {

class Renderer {
public:
    //Loading OpenGL funcs
    bool init(GLLoader loader);

    void beginFrame(int width, int height);
};

}
