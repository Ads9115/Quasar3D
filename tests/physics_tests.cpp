#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <qs/physics/world.h>

using Catch::Matchers::WithinAbs;

TEST_CASE("Particle falls under gravity") {
    qs::World world;
    world.particles.push_back({qs::Vec3(0, 10, 0), qs::Vec3(0, 0, 0)});

    for (int i = 0; i < 60; ++i) world.step(1.0f / 60.0f);   // simulate 1 second

    // After 1 second of free fall, velocity should be about -9.81 m/s.
    REQUIRE_THAT(world.particles[0].velocity.y, WithinAbs(-9.81, 0.01));
}

TEST_CASE("Convention: right-handed, Y-up, radians") {
    // Rotating +X by +90 degrees around +Y should give -Z in a right-handed system.
    qs::Quat q = glm::angleAxis(glm::radians(90.0f), qs::Vec3(0, 1, 0));
    qs::Vec3 r = q * qs::Vec3(1, 0, 0);

    REQUIRE_THAT(r.x, WithinAbs(0.0, 1e-5));
    REQUIRE_THAT(r.y, WithinAbs(0.0, 1e-5));
    REQUIRE_THAT(r.z, WithinAbs(-1.0, 1e-5));
}
