#include "map.h"
#include <cstdlib>

void Map::draw_map(const std::vector<Position>& map) const {
    for (const auto& pos : map) {
        if ((pos.x == 0 && pos.y == 0) || (pos.x == 0 && pos.y == 22) || 
            (pos.x == 22 && pos.y == 0) || (pos.x == 22 && pos.y == 22)) {
            mvaddch(pos.y, pos.x, 'X');
        } else {
            mvaddch(pos.y, pos.x, '0');
        }
    }
}

void Map::printScorePlaytime(time_t start_time, int growth_items_collected, int poison_items_collected, int current_length, const Mission& mission) const {
    time_t current_time = time(nullptr);
    int play_time = static_cast<int>(difftime(current_time, start_time));
    
    int minutes = play_time / 60;
    int seconds = play_time % 60;

    mvprintw(1, 24, "Time: %02d:%02d", minutes, seconds);
    mvprintw(2, 24, "Growth Items: %d/%d", growth_items_collected, mission.target_growth_items);
    mvprintw(3, 24, "Poison Items: %d/%d", poison_items_collected, mission.target_poison_items);
    mvprintw(4, 24, "Length: %d/%d", current_length, mission.target_length);
}
