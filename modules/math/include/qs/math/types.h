#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace qs {

    //naming the math types here
    using Vec3 = glm::vec3;
    using Mat3 = glm::mat3;
    using Quat = glm::quat;

    constexpr float kEpsilon = 1e-6f; // "close enough to zero"

    // glm::normalize on a zzero length vector gives NaN (a broken number that spreads)
    inline Vec3 safeNormalize(const Vec3& v) {
        float len = glm::length(v);
        return len > kEpsilon ? v / len : Vec3(0.0f);
    }

    //glms quat constructor takes (w, x, y, z) preventing mixing up using this func
    inline Quat makeQuat(float x, float y, float z, float w ) {
        return Quat(w, x, y, z);
    }



}
