#include <cstdio>
#include <qs/core/fixed_timestep.h>
#include <qs/physics/world.h>

// Change this to 5.0f to see why prevPosition must be initialized.
constexpr float kStartX = 0.0f;

int main() {
    qs::FixedTimestep fixed(1.0 / 60.0);   // physics at 60 Hz

    qs::World world;
    world.gravity = qs::Vec3(0.0f);        // no gravity: pure constant motion

    qs::Particle p;
    p.position = qs::Vec3(kStartX, 0.0f, 0.0f);
    p.velocity = qs::Vec3(1.0f, 0.0f, 0.0f);   // 1 m/s along +X
    p.prevPosition = p.position;                // TODO 3: a new object has no history, so "previous" = start
    world.particles.push_back(p);

    const double frameTime = 1.0 / 144.0;  // screen at 144 Hz
    float lastRaw = kStartX, lastSmooth = kStartX;

    std::printf("%-6s %-6s %-8s %-10s %-10s %-10s %-10s\n",
                "frame", "steps", "alpha", "raw x", "raw dx", "smooth x", "smooth dx");

    for (int frame = 1; frame <= 12; ++frame) {
        int n = fixed.advance(frameTime);
        for (int i = 0; i < n; ++i) world.step(static_cast<float>(fixed.dt()));

        const qs::Particle& q = world.particles[0];
        float alpha = static_cast<float>(fixed.alpha());

        float raw = q.position.x;
        float smooth = q.prevPosition.x + (q.position.x - q.prevPosition.x) * alpha;   // TODO 4

        std::printf("%-6d %-6d %-8.3f %-10.5f %-10.5f %-10.5f %-10.5f\n",
                    frame, n, alpha, raw, raw - lastRaw, smooth, smooth - lastSmooth);
        lastRaw = raw;
        lastSmooth = smooth;
    }
}
