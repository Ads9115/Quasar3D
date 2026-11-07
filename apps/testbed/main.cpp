#include <qs/core/clock.h>
#include <qs/core/fixed_timestep.h>
#include <qs/core/log.h>
#include <qs/physics/world.h>
#include <qs/platform/window.h>
#include <qs/renderer/renderer.h>

int main() {
    qs::Window window(1280, 720, "Quasar3D");
    if (!window.ok()) return 1;

    qs::Renderer renderer;
    if (!renderer.init(&qs::Window::getProcAddress)) return 1;

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
        window.pollEvents();

        const double frameTime = clock.tick();
        realTime += frameTime;

        const int n = fixed.advance(frameTime);
        for (int i = 0; i < n; ++i) world.step(static_cast<float>(fixed.dt()));
        totalSteps += n;

        int fbWidth = 0, fbHeight = 0;
        window.framebufferSize(fbWidth, fbHeight);
        renderer.beginFrame(fbWidth, fbHeight);

        // Later: draw physics state here, using fixed.alpha() to interpolate.

        window.swapBuffers();
    }

    QS_LOG("app", "ran %.2f s, %ld physics steps (%.1f per second)",
           realTime, totalSteps, totalSteps / realTime);
}
