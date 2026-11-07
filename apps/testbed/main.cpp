#include <qs/core/clock.h>
#include <qs/core/fixed_timestep.h>
#include <qs/core/log.h>
#include <qs/physics/world.h>
#include <qs/platform/window.h>

int main() {
    qs::Window window(1280, 720, "Quasar3D");
    if (!window.ok()) return 1;

    qs::Clock clock;
    qs::FixedTimestep fixed(1.0 / 60.0);

    qs::World world;
    qs::Particle p;
    p.position = qs::Vec3(0.0f, 100.0f, 0.0f);
    p.prevPosition = p.position;
    world.particles.push_back(p);

    double realTime = 0.0;
    long totalSteps = 0;

    while (!window.shouldClose()) {
        window.pollEvents();                         // 1. collect input

        const double frameTime = clock.tick();       // 2. measure real time
        realTime += frameTime;

        const int n = fixed.advance(frameTime);      // 3. simulate
        for (int i = 0; i < n; ++i) world.step(static_cast<float>(fixed.dt()));
        totalSteps += n;

        // (drawing goes here in Step 3b)

        window.swapBuffers();                        // 4. show the frame; vsync paces the loop
    }

    QS_LOG("app", "ran %.2f s, %ld physics steps (%.1f per second)",
           realTime, totalSteps, totalSteps / realTime);
}
