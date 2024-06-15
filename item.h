#ifndef _ITEM_H_
#define _ITEM_H_

#include <vector>
#include <ctime>
#include "position.h"
#include "snake.h"

enum ItemType {
    GROWTH,
    POISON
};

struct Item {
    Position position;
    ItemType type;
    time_t creation_time;  // 아이템 생성 시간 추가
};

class ItemManager {
public:
    void set_probabilities(double growth_prob, double poison_prob);
    void create_item(int max_x, int max_y, const std::vector<Position>& walls);
    bool check_item(Snake& snake, int& growth_items_collected, int& poison_items_collected);
    void draw_items() const;
    void clear_items(); // 아이템 초기화 함수 추가
    void remove_old_items(); // 오래된 아이템 제거 함수 추가

private:
    std::vector<Item> items;
    double growth_prob;
    double poison_prob;
};

#endif
