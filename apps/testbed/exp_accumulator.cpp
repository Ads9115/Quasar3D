#include <cmath>
#include <cstdio>

struct Spring {
    float x = 1.0f;
    float v = 0.0f;
    int steps = 0;
};

// Uses an accumulator to run fixed-size physics steps across uneven frame times.
void step(Spring& spring, float dt) {
    constexpr float k = 400.0f;
    constexpr float m = 1.0f;

    float a = -(k  / m) * spring.x;
    spring.v += a * dt;
    spring.x += spring.v * dt;
    ++spring.steps;

}

int main() {
    constexpr float fixedDt = 1.0f / 60.0f;
    const float frameTimes[] = {0.010f, 0.030f, 0.005f, 0.022f};

    Spring spring;
    float accumulator = 0.0f;
    std::printf("%-12s %-16s %-12s %-12s\n",
            "frame time", "physics steps", "position", "leftover");

    for (float frameDt : frameTimes) {
        accumulator += frameDt;
        int stepsThisFrame = 0;

    while (accumulator >= fixedDt) {
        step(spring, fixedDt);
        accumulator -= fixedDt;
        ++stepsThisFrame;
        }
    std::printf("%-12.3f %-16d %-12.4f %-12.5f\n",
            frameDt, stepsThisFrame, spring.x, accumulator);
    }
    float simulatedTime = spring.steps * fixedDt;
    float truth = std::cos(20.0f * simulatedTime);

    std::printf("\nPhysics steps: %d\n", spring.steps);
    std::printf("Simulated time: %.5f\n", simulatedTime);
    std::printf("Simulated position: %.4f\n", spring.x);
    std::printf("True position: %.4f\n", truth);

}
