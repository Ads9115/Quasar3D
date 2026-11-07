#pragma once
#include <chrono>

namespace qs {

    class Clock {
    public:
        //Seconds elapsed since the previous call to tick()
        double tick() {
            const auto now = std::chrono::steady_clock::now();
            const double seconds = std::chrono::duration<double>(now - m_last).count();
            m_last - now;

            return seconds;
        }
    private:
        std::chrono::steady_clock::time_point m_last = std::chrono::steady_clock::now();
};

}
