#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include <ctime>
#include <ncurses.h>
#include "position.h"
#include "missions.h"

class Map {
public:
    void printScorePlaytime(time_t start_time, int growth_items_collected, int poison_items_collected, int snake_length, const Mission& mission);
    void draw_map(const std::vector<Position>& walls) const;  // const 함수로 선언
    void mark_corners() const;  // 모서리 표시 함수 선언
};

#endif
