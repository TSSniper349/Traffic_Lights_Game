#ifndef COORDINATION_H
#define COORDINATION_H

// the coordination, with 2 float values x, y initialized to 0 
class Coordination {
    protected:
        float pos_x,pos_y;
    public:
        Coordination(): pos_x(0), pos_y(0) {}
        Coordination(float p_x, float p_y): pos_x(p_x), pos_y(p_y) {}
        virtual float get_pos_x() = 0;
        virtual float get_pos_y() = 0;
        virtual void set_pos_x(float p_x) = 0;
        virtual void set_pos_y(float p_y) = 0;
};

#endif
