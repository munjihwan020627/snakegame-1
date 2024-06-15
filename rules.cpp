#include <time.h>
#include <ncurses.h>


// 게임이 현재 정상적으로 진행되고 있는지 확인하는 함수
bool gamestatus(){
    bool playingnow = true;

    if (fail()){
        
        bool playingnow = false;
        resetgame(false);

    }
    else if(success()){
        bool playingnow = false;
        resetgame(true);

    }
    else{
        bool playingnow = true;
    }
    return playingnow;
}


// 게임종료 or 라운드 종료시 게임판 리셋
void resetgame(bool CheckIsSuccess, int rounds){  // playingnow의 bool값 사용예정
    if (CheckIsSuccess && rounds<=4){     
        nextround();        //success로 종료시 다음 라운드 실행
        map.drawlines(); //아직 링킹 안함 
    }
    else if(CheckIsSuccess && rounds> 4){
        exitgame(true);
    }

    else{
        exitgame(false);
    }
        
}

void nextround(){
    time_t start_time = time(nullptr);
    mvprintw(7,0, "다음라운드");
    while (difftime(time(nullptr), start_time) < 5) {
    }

}


void exitgame(bool T){    

    time_t start_time = time(nullptr);
    if (T){
    mvprintw(7,0, "성공!!!");

    }
    else{
    mvprintw(7,0, "실패!!!");

    }
 while (difftime(time(nullptr), start_time) < 5) {
    }
    endwin();
}


// 각 라운드마다 획득할 포인트를 설정함
int roundpoint(int round){
    switch(round){
        case 1:
        return 1000;  // 여기 값은 적절하게 조정 필요
        case 2:
        return 2000; // 여기 값은 적절하게 조정 필요
        case 3:
        return 3000; // 여기 값은 적절하게 조정 필요
        case 4:
        return 4000; // 여기 값은 적절하게 조정 필요
    }
}

// 성공 점수 계산 방법(각 기준별로 가중치 추가 필요)
int countpoint(int lengthscore,int growthscore,int poisonscore,int gatescore,int secondscore){

    return lengthscore + growthscore + poisonscore + gatescore + secondscore;
}



