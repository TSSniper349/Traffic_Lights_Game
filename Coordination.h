#ifndef COORDINATION_H
#define COORDINATION_H

struct Coordination {
    float x,y;
    Coordination(): x(0), y(0) {}
    Coordination(float p_x, float p_y): x(p_x), y(p_y) {}
};

#endif
