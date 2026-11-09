#include <qs/core/clock.h>
#include <qs/core/fixed_timestep.h>
#include <qs/core/log.h>
#include <qs/editor/editor.h>
#include <qs/physics/world.h>
#include <qs/platform/window.h>
#include <qs/renderer/camera.h>
#include <qs/renderer/renderer.h>

int main() {
    qs::Window window(1280, 720, "Quasar3D");
    if (!window.ok()) return 1;

    qs::Renderer renderer;
    if (!renderer.init(&qs::Window::getProcAddress)) return 1;

    qs::Editor editor;
    if (!editor.init(window)) return 1;

    qs::Camera camera;

    qs::Clock clock;
    qs::FixedTimestep fixed(1.0 / 60.0);

    qs::World world;
    qs::Particle p;
    p.position = qs::Vec3(0.0f, 100.0f, 0.0f);
    p.prevPosition = p.position;
    world.particles.push_back(p);

    double realTime = 0.0;
    long totalSteps = 0;
    int vpW = 800, vpH = 600;   // viewport panel size, as measured last frame

    while (!window.shouldClose()) {
        window.pollEvents();

        const double frameTime = clock.tick();
        realTime += frameTime;

        const int n = fixed.advance(frameTime);
        for (int i = 0; i < n; ++i) world.step(static_cast<float>(fixed.dt()));
        totalSteps += n;

        // 1. Draw the 3D scene into the off-screen image.
        renderer.beginScene(vpW, vpH, camera);
        renderer.drawGrid();
        // Later: bodies, debug lines.
        renderer.endScene();

        // 2. Clear the real window, then draw the editor on top of it.
        int fbWidth = 0, fbHeight = 0;
        window.framebufferSize(fbWidth, fbHeight);
        renderer.beginFrame(fbWidth, fbHeight);

        editor.beginFrame();
        qs::FrameStats stats;
        stats.frameMs = frameTime * 1000.0;
        stats.stepsThisFrame = n;
        stats.totalSteps = totalSteps;
        stats.simTime = totalSteps * fixed.dt();
        stats.alpha = fixed.alpha();
        stats.viewportW = vpW;
        stats.viewportH = vpH;
        editor.drawStats(stats);

        const qs::ViewportInput in = editor.drawViewport(renderer.sceneTexture(), vpW, vpH);
        if (in.orbit) camera.orbit(in.dx, in.dy);
        if (in.pan)   camera.pan(in.dx, in.dy, static_cast<float>(vpH));
        if (in.scroll != 0.0f) camera.zoom(in.scroll);

        editor.endFrame();

        window.swapBuffers();
    }

    QS_LOG("app", "ran %.2f s, %ld physics steps (%.1f per second)",
           realTime, totalSteps, totalSteps / realTime);
}
