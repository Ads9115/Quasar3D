#pragma once
#include <algorithm>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <qs/math/types.h>

namespace qs {

class Camera {
public:
    static constexpr float kMinDistance = 0.1f;
    static constexpr float kMaxDistance = 200.0f;

    Vec3 target{0.0f, 0.0f, 0.0f};
    float distance = 10.0f;
    float yaw = 0.6f;
    float pitch = 0.5f;
    float fovY = glm::radians(45.0f);
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    Vec3 position() const {
        const float cp = std::cos(pitch);
        return target + distance * Vec3(cp * std::sin(yaw), std::sin(pitch), cp * std::cos(yaw));
    }
    Mat4 view() const { return glm::lookAt(position(), target, Vec3(0.0f, 1.0f, 0.0f)); }
    Mat4 projection(float aspect) const { return glm::perspective(fovY, aspect, nearPlane, farPlane); }

    // Mouse movement in pixels
    void orbit(float dxPixels, float dyPixels) {
        constexpr float kSensitivity = 0.005f;
        constexpr float kLimit = 1.5707964f - 0.01f;

        yaw -= dxPixels * kSensitivity;
        pitch += dyPixels * kSensitivity;
        pitch = std::clamp(pitch, -kLimit, kLimit);
    }

    //pan : slides the target in the screen plane so the scene follows the cursor
    void pan(float dxPixels, float dyPixels, float viewportHeightPixels) {
        const Vec3 forward = safeNormalize(target - position());
        const Vec3 right = safeNormalize(glm::cross(forward, Vec3(0.0f, 1.0f, 0.0f)));
        const Vec3 up = glm::cross(right, forward);

        const float worldPerPixel = 2.0f * distance * std::tan(fovY * 0.5f) / std::max(viewportHeightPixels, 1.0f);
        target += (-right * dxPixels + up * dyPixels) * worldPerPixel;
    }

    // Scroll "notches": positive zooms in. Multiplicative, so it feels the same at any distance.
    void zoom(float scroll) {
        distance = std::clamp(distance * std::pow(0.9f, scroll), kMinDistance, kMaxDistance);
    }
};
}
