#pragma once
#include <vector>
#include <qs/math/types.h>

namespace qs {

struct Particle {
    Vec3 position;
    Vec3 velocity;
    Vec3 prevPosition;
};

// Everything the simulation needs lives inside World. No global variables.
class World {
public:
    Vec3 gravity{0.0f, -9.81f, 0.0f};   // Y-up
    std::vector<Particle> particles;

    void step(float dt);   // advance time by dt seconds
};

} // namespace qs
