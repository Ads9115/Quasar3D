#pragma once

namespace qs {

class FixedTimestep {
public:
    explicit FixedTimestep(double dt) : m_dt(dt) {}

    //will be used to call how many physics steps per frame
    int advance(double frameTime) {
       m_accumulator += frameTime;
       
       int steps = 0;
       while(m_accumulator >= m_dt) {
           m_accumulator -= m_dt;
           ++steps;
       }
        
       return steps;
    }

    double dt() const { return m_dt; }
    double accumulator() const { return m_accumulator; } //for test and debugging

private:
    double m_dt;
    double m_accumulator = 0.0f;
};

}
