#ifndef _MISSIONS_H_
#define _MISSIONS_H_

struct Mission {
    int target_growth_items;  // 목표 + 아이템 개수
    int target_poison_items;  // 목표 - 아이템 개수
    int target_length;        // 목표 몸 길이
};

const Mission missions[] = {
    {1, 0, 4},  // 스테이지 1
    {1, 0, 4}, // 스테이지 2
    {1, 0, 4}, // 스테이지 3
    {1, 0, 4}, // 스테이지 4
    {1, 0, 4}  // 스테이지 5
};

#endif
