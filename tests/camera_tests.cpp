#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <glm/gtc/constants.hpp>
#include <qs/renderer/camera.h>

using Catch::Matchers::WithinAbs;

TEST_CASE("View matrix puts the target straight ahead at the orbit distance") {
    qs::Camera cam;
    cam.target = qs::Vec3(1, 2, 3);
    cam.distance = 5.0f;
    cam.yaw = 0.0f;
    cam.pitch = 0.0f;

    const glm::vec4 p = cam.view() * glm::vec4(cam.target, 1.0f);
    REQUIRE_THAT(p.x, WithinAbs(0.0, 1e-5));
    REQUIRE_THAT(p.y, WithinAbs(0.0, 1e-5));
    REQUIRE_THAT(p.z, WithinAbs(-5.0, 1e-5));   // -Z is "forward" in view space
}

TEST_CASE("Pitch is clamped so the camera never flips over") {
    qs::Camera cam;
    cam.orbit(0.0f, 1e6f);
    REQUIRE(cam.pitch < glm::half_pi<float>());
    cam.orbit(0.0f, -2e6f);
    REQUIRE(cam.pitch > -glm::half_pi<float>());
}

TEST_CASE("Pan slides the target perpendicular to the view direction") {
    qs::Camera cam;
    cam.yaw = 0.7f;
    cam.pitch = 0.3f;
    cam.distance = 8.0f;

    const qs::Vec3 before = cam.target;
    const qs::Vec3 forward = glm::normalize(cam.target - cam.position());
    cam.pan(40.0f, -25.0f, 720.0f);
    const qs::Vec3 moved = cam.target - before;

    REQUIRE(glm::length(moved) > 0.0f);
    REQUIRE_THAT(glm::dot(moved, forward), WithinAbs(0.0, 1e-5));
}

TEST_CASE("Zoom is clamped") {
    qs::Camera cam;
    cam.zoom(1e6f);
    REQUIRE(cam.distance == qs::Camera::kMinDistance);
    cam.zoom(-1e6f);
    REQUIRE(cam.distance == qs::Camera::kMaxDistance);
}
