#include <qs/renderer/grid.h>

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <qs/core/log.h>

namespace qs {
namespace {

// One triangle that covers the whole screen, generated from gl_VertexID (no vertex buffer).
// For each corner we also compute where its near-plane and far-plane points are in the world.
const char* kVertexSrc = R"GLSL(
#version 450 core
layout(location = 0) out vec3 vNear;
layout(location = 1) out vec3 vFar;
uniform mat4 uInvViewProj;

vec3 unproject(vec2 ndc, float z) {
    vec4 p = uInvViewProj * vec4(ndc, z, 1.0);
    return p.xyz / p.w;
}

void main() {
    vec2 uv  = vec2((gl_VertexID << 1) & 2, gl_VertexID & 2);   // (0,0) (2,0) (0,2)
    vec2 ndc = uv * 2.0 - 1.0;                                  // (-1,-1) (3,-1) (-1,3)
    vNear = unproject(ndc, -1.0);
    vFar  = unproject(ndc,  1.0);
    gl_Position = vec4(ndc, 0.0, 1.0);
}
)GLSL";

const char* kFragmentSrc = R"GLSL(
#version 450 core
layout(location = 0) in vec3 vNear;
layout(location = 1) in vec3 vFar;
layout(location = 0) out vec4 fragColor;

uniform mat4  uViewProj;
uniform vec3  uCamPos;
uniform float uFar;

// 1 on a grid line, 0 between lines. Lines stay about one pixel wide at any distance.
float gridLine(vec2 coord, float cell) {
    vec2 c = coord / cell;
    vec2 w = max(fwidth(c), vec2(1e-6));
    vec2 g = abs(fract(c - 0.5) - 0.5) / w;
    return 1.0 - min(min(g.x, g.y), 1.0);
}

void main() {
    // Where does this pixel's ray hit the plane y = 0?
    float dy = vFar.y - vNear.y;
    if (abs(dy) < 1e-6) discard;
    float t = -vNear.y / dy;
    if (t <= 0.0) discard;
    vec3 pos = vNear + t * (vFar - vNear);

    // Write the true depth so objects drawn later sort correctly against the grid.
    vec4 clip = uViewProj * vec4(pos, 1.0);
    gl_FragDepth = (clip.z / clip.w) * 0.5 + 0.5;

    vec2 coord = pos.xz;
    vec2 px = fwidth(coord);                 // world units covered by one pixel
    float pixelWorld = max(px.x, px.y);

    // Fade each line set out before it gets denser than the pixels (prevents shimmer).
    float minor = gridLine(coord, 1.0)  * (1.0 - smoothstep(0.15, 0.6, pixelWorld));
    float major = gridLine(coord, 10.0) * (1.0 - smoothstep(1.5,  6.0, pixelWorld));

    vec3  col = vec3(0.75);
    float a   = max(minor * 0.18, major * 0.35);

    float xAxis = 1.0 - min(abs(coord.y) / max(px.y, 1e-6), 1.0);   // the line z = 0
    float zAxis = 1.0 - min(abs(coord.x) / max(px.x, 1e-6), 1.0);   // the line x = 0
    if (xAxis > 0.0) { col = mix(col, vec3(0.90, 0.25, 0.30), xAxis); a = max(a, xAxis * 0.9); }
    if (zAxis > 0.0) { col = mix(col, vec3(0.30, 0.50, 0.95), zAxis); a = max(a, zAxis * 0.9); }

    // Fade out with distance from the camera.
    a *= 1.0 - smoothstep(uFar * 0.2, uFar * 0.5, length(pos - uCamPos));

    if (a < 0.01) discard;
    fragColor = vec4(col, a);
}
)GLSL";

GLuint compile(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    GLint ok = 0;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetShaderInfoLog(s, sizeof(log), nullptr, log);
        QS_LOG("renderer", "shader compile error: %s", log);
        glDeleteShader(s);
        return 0;
    }
    return s;
}

} // namespace

bool Grid::init() {
    GLuint vs = compile(GL_VERTEX_SHADER, kVertexSrc);
    GLuint fs = compile(GL_FRAGMENT_SHADER, kFragmentSrc);
    if (!vs || !fs) return false;

    m_program = glCreateProgram();
    glAttachShader(m_program, vs);
    glAttachShader(m_program, fs);
    glLinkProgram(m_program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    GLint ok = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetProgramInfoLog(m_program, sizeof(log), nullptr, log);
        QS_LOG("renderer", "program link error: %s", log);
        return false;
    }

    m_locViewProj    = glGetUniformLocation(m_program, "uViewProj");
    m_locInvViewProj = glGetUniformLocation(m_program, "uInvViewProj");
    m_locCamPos      = glGetUniformLocation(m_program, "uCamPos");
    m_locFar         = glGetUniformLocation(m_program, "uFar");

    glCreateVertexArrays(1, &m_vao);
    return true;
}

Grid::~Grid() {
    if (m_vao)     glDeleteVertexArrays(1, &m_vao);
    if (m_program) glDeleteProgram(m_program);
}

void Grid::draw(const Mat4& view, const Mat4& proj, const Vec3& cameraPos, float farPlane) {
    const Mat4 viewProj = proj * view;
    const Mat4 invViewProj = glm::inverse(viewProj);

    glUseProgram(m_program);
    glUniformMatrix4fv(m_locViewProj, 1, GL_FALSE, glm::value_ptr(viewProj));
    glUniformMatrix4fv(m_locInvViewProj, 1, GL_FALSE, glm::value_ptr(invViewProj));
    glUniform3fv(m_locCamPos, 1, glm::value_ptr(cameraPos));
    glUniform1f(m_locFar, farPlane);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    glDisable(GL_BLEND);
}

} // namespace qs
