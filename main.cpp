#include <ncurses.h>
#include <ctime>
#include <vector>
#include "snake.h"
#include "item.h"
#include "map.h"
#include "gate.h"
#include "position.h"
#include "missions.h"
#include "maps.h"

void show_stage_map(const Map& game_map, const std::vector<Position>& map) {
    clear();
    game_map.draw_map(map);
    mvprintw(10, 24, "New Stage!");
    refresh();
    napms(3000); // 3초 대기
    clear();
}

int main() {
    int stage = 0;
    int growth_items_collected = 0;
    int poison_items_collected = 0;
    time_t start_time = time(nullptr);
    time_t map_show_end_time = 0;

    initscr();            // ncurses 모드 시작
    cbreak();             // 입력을 즉시 읽기
    noecho();             // 입력 문자를 화면에 출력하지 않음
    keypad(stdscr, TRUE); // 특수 키 입력 활성화
    nodelay(stdscr, TRUE); // 입력을 기다리지 않고 진행
    curs_set(0);          // 커서 숨기기

    int max_x = 22, max_y = 22;
    Position snake_start = {max_x / 2, max_y / 2}; // 스네이크 시작 위치
    Snake snake(snake_start.x, snake_start.y);
    ItemManager item_manager;
    item_manager.set_probabilities(0.7, 0.3); // 성장 아이템 70%, 독 아이템 30%로 설정
    Map game_map;

    std::vector<Position> current_map = maps[stage]; // 미리 정의된 맵 사용
    Gate gate_manager;
    gate_manager.create_gate(current_map); // 추가 벽을 제외하지 않음
    time_t last_item_time = start_time;
    time_t last_gate_use_time = 0;

    show_stage_map(game_map, current_map);
    map_show_end_time = time(nullptr) + 3; // 맵을 보여주는 시간이 끝나는 시점

    int dx = 1, dy = 0; // 초기 방향: 오른쪽

    while (true) {
        time_t current_time = time(nullptr);
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                if (dy == 0) { dx = 0; dy = -1; }
                break;
            case KEY_DOWN:
                if (dy == 0) { dx = 0; dy = 1; }
                break;
            case KEY_LEFT:
                if (dx == 0) { dx = -1; dy = 0; }
                break;
            case KEY_RIGHT:
                if (dx == 0) { dx = 1; dy = 0; }
                break;
            case 'q':
                endwin();
                return 0;
        }

        snake.move(dx, dy);

        auto gate_positions = gate_manager.get_gate_positions();
        Position head = snake.body.front();
        if (head.x == gate_positions.first.x && head.y == gate_positions.first.y) {
            Position new_head = gate_manager.get_new_position(head, gate_positions.second, &dx, &dy);
            snake.body.push_front(new_head);
            snake.body.pop_back();
            last_gate_use_time = current_time;
            gate_manager.remove_gates();
        } else if (head.x == gate_positions.second.x && head.y == gate_positions.second.y) {
            Position new_head = gate_manager.get_new_position(head, gate_positions.first, &dx, &dy);
            snake.body.push_front(new_head);
            snake.body.pop_back();
            last_gate_use_time = current_time;
            gate_manager.remove_gates();
        }

        if (snake.check_collision(max_x, max_y, current_map) || !snake.is_alive()) {
            mvprintw(max_y / 2, max_x / 2 - 5, "Game Over");
            refresh();
            break;
        }

        if (item_manager.check_item(snake, growth_items_collected, poison_items_collected)) {
            if (snake.body.size() >= missions[stage].target_length &&
                growth_items_collected >= missions[stage].target_growth_items &&
                poison_items_collected >= missions[stage].target_poison_items) {
                
                // 다음 스테이지로 이동
                stage++;
                if (stage >= sizeof(missions) / sizeof(missions[0])) {
                    mvprintw(max_y / 2, max_x / 2 - 5, "You Win!");
                    refresh();
                    break;
                }

                // 다음 스테이지 초기화
                growth_items_collected = 0;
                poison_items_collected = 0;
                snake = Snake(snake_start.x, snake_start.y);
                current_map = maps[stage]; // 다음 스테이지의 미리 정의된 맵 사용
                gate_manager.create_gate(current_map); // 추가 벽을 제외하지 않음
                item_manager.clear_items(); // 아이템 초기화
                show_stage_map(game_map, current_map); // 새로운 맵을 표시하고 대기
                map_show_end_time = time(nullptr) + 3; // 맵을 보여주는 시간이 끝나는 시점
            }
        }

        if (current_time >= map_show_end_time && current_time - last_item_time >= 5) {
            item_manager.create_item(max_x, max_y);
            last_item_time = current_time;
        }

        if (gate_manager.is_gate_used() && current_time - last_gate_use_time >= 5) {
            gate_manager.create_gate(current_map); // 추가 벽을 제외하지 않음
        }

        clear();
        game_map.draw_map(current_map);
        for (const auto &pos : snake.body) {
            mvaddch(pos.y, pos.x, 'O');
        }
        item_manager.draw_items();
        gate_manager.draw_gates();
        game_map.printScorePlaytime(start_time, growth_items_collected, poison_items_collected, snake.body.size(), missions[stage]);
        refresh();
        napms(100); // 0.1초 대기
    }

    getch();
    endwin(); // ncurses 모드 종료

    return 0;
}
