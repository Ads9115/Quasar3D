#include <cmath>
#include <cstdio>

struct Result {
    float x;        // final pos
    float energy;   // TOTAL Energy = 1/2mv^2 + 1/2kx^2
    float time;     // time actually simulated
};
// Compares spring simulation results using different time step sizes.
Result simulate(float dt, float totalTime) {
    const float k = 400.0f;
    const float m = 1.0f;
    float x = 1.0f;
    float v = 0.0f;

    int steps = static_cast<int>(std::lround(totalTime / dt));

    for (int i = 0; i < steps; i++) {
        float a = -(k / m) * x;
        v += a * dt;
        x += v * dt;
    }

    float energy = 0.5f * m * v * v + 0.5f * k * x * x;
    return {x, energy, steps * dt};
}

int main() {
    const float dts[] = {1.0f / 240, 1.0f / 60, 1.0f / 30, 1.0f / 15, 0.12f};
    std::printf("%-10s %-12s %-12s %-12s\n", "dt", "x (sim)", "x (true)", "energy");

    for (float dt : dts) {
        Result r = simulate(dt, 2.0f);
        float truth = std::cos(20.0f * r.time);
        std::printf("%-10.5f %-12.4f %-12.4f %-12.2f\n", dt, r.x, truth, r.energy);
    }
}
