#include "item.h"
#include <cstdlib>
#include <ctime>
#include <ncurses.h>

void ItemManager::set_probabilities(double growth_prob, double poison_prob) {
    this->growth_prob = growth_prob;
    this->poison_prob = poison_prob;
}

void ItemManager::create_item(int max_x, int max_y) {
    Item new_item;
    new_item.position.x = rand() % (max_x - 1) + 1;
    new_item.position.y = rand() % (max_y - 1) + 1;

    // 아이템 타입 설정
    double rand_value = rand() / (double)RAND_MAX;
    if (rand_value < growth_prob) {
        new_item.type = GROWTH;
    } else {
        new_item.type = POISON;
    }

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
