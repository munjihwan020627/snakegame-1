#include "map.h"
#include <ncurses.h>
#include <ctime>

void Map::printScorePlaytime(time_t start_time, int growth_items_collected, int poison_items_collected, int snake_length, const Mission& mission) {
    time_t current_time = time(nullptr);
    int play_time = static_cast<int>(difftime(current_time, start_time));

    mvprintw(0, 24, "Play Time: %d", play_time);
    mvprintw(1, 24, "Growth Items: %d/%d", growth_items_collected, mission.target_growth_items);
    mvprintw(2, 24, "Poison Items: %d/%d", poison_items_collected, mission.target_poison_items);
    mvprintw(3, 24, "Snake Length: %d/%d", snake_length, mission.target_length);
}

void Map::draw_map(const std::vector<Position>& walls) const {
    clear();
    for (const auto& wall : walls) {
        mvaddch(wall.y, wall.x, '0');
    }
    mark_corners();  // 모서리 표시 함수 호출
}

void Map::mark_corners() const {
    mvaddch(0, 0, 'X');
    mvaddch(0, 22, 'X');
    mvaddch(22, 0, 'X');
    mvaddch(22, 22, 'X');
}
