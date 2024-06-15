#ifndef _MAP_H_
#define _MAP_H_

#include <ncurses.h>
#include <ctime>
#include <vector>
#include "position.h"
#include "missions.h"

class Map {
public:
    void draw_map(const std::vector<Position>& map) const;
    void printScorePlaytime(time_t start_time, int growth_items_collected, int poison_items_collected, int current_length, const Mission& mission) const;
};

#endif
