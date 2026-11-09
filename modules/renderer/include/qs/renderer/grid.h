#pragma once
#include <cstdint>
#include <qs/math/types.h>

namespace qs {

class Grid {
public:
    Grid() = default;
    ~Grid();
    Grid(const Grid&) = delete;
    Grid& operator=(const Grid&) = delete;

    bool init(); // compiles the shader call after openGL is loaded
    void draw(const Mat4& view, const Mat4& proj, const Vec3& cameraPos, float farPlane);

private:
    uint32_t m_program = 0;
    uint32_t m_vao = 0;      // core profile needs VAO bound even with no vertex data
    int m_locViewProj = -1;
    int m_locInvViewProj = -1;
    int m_locCamPos = -1;
    int m_locFar = -1;
};

}
