#include "gate.h"
#include <cstdlib>
#include <ctime>
#include <ncurses.h>

void Gate::create_gate(const std::vector<Position>& wall_positions) {
    srand(time(0));

    std::vector<Position> valid_positions;
    for (const auto& pos : wall_positions) {
        if (!((pos.x == 0 && pos.y == 0) || (pos.x == 0 && pos.y == 22) || 
              (pos.x == 22 && pos.y == 0) || (pos.x == 22 && pos.y == 22))) {
            valid_positions.push_back(pos);
        }
    }

    int idx_a = rand() % valid_positions.size();
    int idx_b = rand() % valid_positions.size();
    while (idx_b == idx_a) {
        idx_b = rand() % valid_positions.size();
    }

    gate_a = valid_positions[idx_a];
    gate_b = valid_positions[idx_b];
    gate_used = false;
}

void Gate::remove_gates() {
    gate_a = { -1, -1 };
    gate_b = { -1, -1 };
}

std::pair<Position, Position> Gate::get_gate_positions() {
    return std::make_pair(gate_a, gate_b);
}

void Gate::draw_gates() const {
    if (gate_a.x != -1 && gate_a.y != -1) {
        mvaddch(gate_a.y, gate_a.x, 'A');
    }
    if (gate_b.x != -1 && gate_b.y != -1) {
        mvaddch(gate_b.y, gate_b.x, 'B');
    }
}

Position Gate::get_new_position(Position current, Position gate, int* dx, int* dy) {
    int new_x = gate.x;
    int new_y = gate.y;

    if (gate.x == 0) {
        // 좌측 벽
        new_x = gate.x + 1;
        *dx = 1;
        *dy = 0;
    } else if (gate.x == 22) {
        // 우측 벽
        new_x = gate.x - 1;
        *dx = -1;
        *dy = 0;
    } else if (gate.y == 0) {
        // 상단 벽
        new_y = gate.y + 1;
        *dx = 0;
        *dy = 1;
    } else if (gate.y == 22) {
        // 하단 벽
        new_y = gate.y - 1;
        *dx = 0;
        *dy = -1;
    } else {
        // 가운데 벽 또는 추가 벽
        if (*dx == 1) {
            // 오른쪽에서 진입
            new_x = gate.x + 1;
        } else if (*dx == -1) {
            // 왼쪽에서 진입
            new_x = gate.x - 1;
        } else if (*dy == 1) {
            // 아래쪽에서 진입
            new_y = gate.y + 1;
        } else if (*dy == -1) {
            // 위쪽에서 진입
            new_y = gate.y - 1;
        }

        // 진입 방향과 일치하는 방향이 불가능한 경우
        if (new_x <= 0 || new_x >= 22 || new_y <= 0 || new_y >= 22) {
            if (*dx == 1 || *dx == -1) {
                // 좌-우로 진입한 경우
                if (*dx == 1) {
                    new_x = gate.x - 1; // 좌로 진출
                } else {
                    new_x = gate.x + 1; // 우로 진출
                }
                // 진출 방향이 불가능한 경우 시계방향으로 회전
                if (new_x <= 0 || new_x >= 22) {
                    if (*dx == 1) {
                        new_y = gate.y + 1; // 아래로 진출
                    } else {
                        new_y = gate.y - 1; // 위로 진출
                    }
                }
            } else {
                // 상-하로 진입한 경우
                if (*dy == 1) {
                    new_y = gate.y - 1; // 위로 진출
                } else {
                    new_y = gate.y + 1; // 아래로 진출
                }
                // 진출 방향이 불가능한 경우 시계방향으로 회전
                if (new_y <= 0 || new_y >= 22) {
                    if (*dy == 1) {
                        new_x = gate.x + 1; // 우로 진출
                    } else {
                        new_x = gate.x - 1; // 좌로 진출
                    }
                }
            }
        }
    }

    gate_used = true;
    return { new_x, new_y };
}

bool Gate::is_gate_used() const {
    return gate_used;
}
