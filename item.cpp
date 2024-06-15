#include "item.h"
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <algorithm>

void ItemManager::set_probabilities(double growth_prob, double poison_prob) {
    this->growth_prob = growth_prob;
    this->poison_prob = poison_prob;
}

void ItemManager::create_item(int max_x, int max_y, const std::vector<Position>& walls) {
    if (items.size() >= 3) return; // 동시에 출현할 수 있는 아이템 수 제한

    Item new_item;
    bool valid_position = false;

    while (!valid_position) {
        new_item.position.x = rand() % (max_x - 1) + 1;
        new_item.position.y = rand() % (max_y - 1) + 1;

        valid_position = true;
        for (const auto& wall : walls) {
            if (new_item.position.x == wall.x && new_item.position.y == wall.y) {
                valid_position = false;
                break;
            }
        }
    }

    // 아이템 타입 설정
    double rand_value = rand() / (double)RAND_MAX;
    if (rand_value < growth_prob) {
        new_item.type = GROWTH;
    } else {
        new_item.type = POISON;
    }
    new_item.creation_time = time(nullptr);  // 생성 시간 기록

    items.push_back(new_item);
}

bool ItemManager::check_item(Snake& snake, int& growth_items_collected, int& poison_items_collected) {
    Position head = snake.body.front();
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (head.x == it->position.x && head.y == it->position.y) {
            if (it->type == GROWTH) {
                snake.grow();
                growth_items_collected++;
            } else if (it->type == POISON) {
                snake.shrink();
                poison_items_collected++;
            }
            items.erase(it);
            return true;
        }
    }
    return false;
}

void ItemManager::draw_items() const {
    for (const auto& item : items) {
        char item_char = (item.type == GROWTH) ? 'G' : 'P';
        mvaddch(item.position.y, item.position.x, item_char);
    }
}

void ItemManager::clear_items() {
    items.clear();
}

void ItemManager::remove_old_items() {
    time_t current_time = time(nullptr);
    items.erase(std::remove_if(items.begin(), items.end(),
                               [current_time](const Item& item) {
                                   return difftime(current_time, item.creation_time) >= 6;
                               }), items.end());
}
