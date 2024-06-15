#include "snake.h"

Snake::Snake(int start_x, int start_y) {
    for (int i = 0; i < initial_length; ++i) {
        body.push_back({start_x, start_y + i});
    }
}

Snake::Snake(const Snake& other) : body(other.body) {
    // 복사 생성자: 다른 Snake 객체의 body를 복사
}

Snake& Snake::operator=(const Snake& other) {
    if (this != &other) {
        body = other.body;
    }
    return *this;
}

void Snake::move(int dx, int dy) {
    Position new_head = {body.front().x + dx, body.front().y + dy};
    body.push_front(new_head);
    body.pop_back();
}

void Snake::grow() {
    body.push_back(body.back());
}

void Snake::shrink() {
    if (body.size() > 1) {
        body.pop_back();
    }
}

bool Snake::check_collision(int max_x, int max_y, const std::vector<Position>& walls) {
    Position head = body.front();
    if (head.x <= 0 || head.x >= max_x || head.y <= 0 || head.y >= max_y) {
        return true; // 벽과 충돌
    }
    for (size_t i = 1; i < body.size(); ++i) {
        if (head.x == body[i].x && head.y == body[i].y) {
            return true; // 자기 몸과 충돌
        }
    }
    for (const auto& wall : walls) {
        if (head.x == wall.x && head.y == wall.y) {
            return true; // 생성된 벽과 충돌
        }
    }
    return false;
}

bool Snake::is_alive() const {
    return body.size() >= initial_length;
}
