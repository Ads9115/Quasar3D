#include <chrono>
#include <cstdio>
#include <thread>

#include <qs/core/clock.h>
#include <qs/core/fixed_timestep.h>
#include <qs/physics/world.h>
#include <qs/core/log.h>


int main() {
    qs::Clock clock;
    qs::FixedTimestep fixed(1.0 / 60.0);

    qs::World world;
    qs::Particle p;
    p.position = qs::Vec3(0.0f, 100.0f, 0.0f);
    p.prevPosition = p.position;
    world.particles.push_back(p);

    double realTime = 0.0;
    long totalSteps = 0;

    while (realTime < 2.0) {

        const double frameTime = clock.tick();
        realTime += frameTime;

        const int n = fixed.advance(frameTime);
        for (int i = 0; i < n; ++i) world.step(static_cast<float>(fixed.dt()));
        totalSteps += n;

        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    const double dt = fixed.dt();
    const double expectedY = 100.0 - 9.81 * dt * dt * totalSteps * (totalSteps + 1) / 2.0;

    QS_LOG("app", "real time %.3f s, steps %ld, simulated %.3f s, bank %.4f s",
           realTime, totalSteps, totalSteps * dt, fixed.accumulator());
    QS_LOG("app", "y = %.4f, expected %.4f", world.particles[0].position.y, expectedY);
}
