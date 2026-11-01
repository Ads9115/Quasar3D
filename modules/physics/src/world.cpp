#include <qs/physics/world.h>

namespace qs {

void World::step(float dt) {
    for (Particle& p : particles) {
        p.velocity += gravity * dt;     // forces change velocity
        p.position += p.velocity * dt;  // velocity changes position
    }
}

} // namespace qs
