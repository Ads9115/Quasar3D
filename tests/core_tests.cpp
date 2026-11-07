#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <qs/core/fixed_timestep.h>
#include <qs/core/clock.h>
#include <thread>

using Catch::Matchers::WithinAbs;

TEST_CASE("Accumulator: hand traced example") {
    qs::FixedTimestep fixed(0.01);

    REQUIRE(fixed.advance(0.025) == 2);
    REQUIRE(fixed.advance(0.004) == 0);
    REQUIRE(fixed.advance(0.013) == 2);
    REQUIRE(fixed.advance(0.030) == 3);

    REQUIRE_THAT(fixed.accumulator(), WithinAbs(0.002, 1e-9));
}

TEST_CASE("Spiral-of-death cap limits catch-up steps") {
    qs::FixedTimestep fixed(0.125, 0.5);
    REQUIRE(fixed.advance(10.0) == 4);   // 10 s is clamped to 0.5 s, which is 4 steps
    REQUIRE_THAT(fixed.accumulator(), WithinAbs(0.0, 1e-12));
}

TEST_CASE("Negative frame time is ignored") {
    qs::FixedTimestep fixed(0.125, 0.5);
    REQUIRE(fixed.advance(-1.0) == 0);
    REQUIRE_THAT(fixed.accumulator(), WithinAbs(0.0, 1e-12));
}

TEST_CASE("Clock measures at least the time slept") {
    qs::Clock clock;
    clock.tick();                                                    // reset the reference point
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    REQUIRE(clock.tick() >= 0.010);                                  // sleep_for waits AT LEAST this long
}
