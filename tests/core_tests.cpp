#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <qs/core/fixed_timestep.h>

using Catch::Matchers::WithinAbs;

TEST_CASE("Accumulator: hand traced example") {
    qs::FixedTimestep fixed(0.01);

    REQUIRE(fixed.advance(0.025) == 2);
    REQUIRE(fixed.advance(0.004) == 0);
    REQUIRE(fixed.advance(0.013) == 2);
    REQUIRE(fixed.advance(0.030) == 3);

    REQUIRE_THAT(fixed.accumulator(), WithinAbs(0.002, 1e-9));
}
