#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <deque>
#include <vector>
#include <ncurses.h>
#include "position.h"

class Snake {
public:
    Snake(int start_x, int start_y);
    Snake(const Snake& other); // 복사 생성자
    Snake& operator=(const Snake& other); // 복사 할당 연산자

    void move(int dx, int dy);
    void grow();
    void shrink(); // 새로운 함수: 몸을 줄이는 기능
    bool check_collision(int max_x, int max_y, const std::vector<Position>& walls);
    bool is_alive() const; // 함수가 const로 선언됨

    std::deque<Position> body;
private:
    const int initial_length = 3;
};

#endif
