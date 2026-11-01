#include <qs/physics/world.h>
#include <qs/core/log.h>

int main() {
    qs::World world;
    world.particles.push_back({qs::Vec3(0, 10, 0), qs::Vec3(0, 0, 0)});

    for (int i = 0; i < 5; ++i) {
        world.step(1.0f / 60.0f);
        QS_LOG("app", "step %d: y = %f", i, world.particles[0].position.y);
    }
}
