#ifndef _GATE_H_
#define _GATE_H_

#include <vector>
#include "position.h"

class Gate {
public:
    void create_gate(const std::vector<Position>& wall_positions);
    void remove_gates();
    std::pair<Position, Position> get_gate_positions();
    void draw_gates() const;
    Position get_new_position(Position current, Position gate, int* dx, int* dy);
    bool is_gate_used() const;

private:
    Position gate_a;
    Position gate_b;
    bool gate_used;
};

#endif
