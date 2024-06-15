#ifndef _MISSIONS_H_
#define _MISSIONS_H_

struct Mission {
    int target_growth_items;  // 목표 + 아이템 개수
    int target_poison_items;  // 목표 - 아이템 개수
    int target_length;        // 목표 몸 길이
};

const Mission missions[] = {
    {5, 2, 10},  // 스테이지 1
    {10, 3, 15}, // 스테이지 2
    {15, 4, 20}, // 스테이지 3
    {20, 5, 25}, // 스테이지 4
    {25, 6, 30}  // 스테이지 5
};

#endif
