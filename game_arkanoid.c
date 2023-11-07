#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
// #include <ncurses.h>

#define WIDTH 65
#define HEIGHT 25

typedef struct {
    int x, y, w;
} TRacket;

typedef struct {
    float x, y;
    int ix, iy;
    float alfa;
    float speed;
} TBall;

char field[HEIGHT][WIDTH + 1];
TRacket racket;
TBall ball;
int count = 0;
int maxCount = 0;

void putBall() {
    field[ball.iy][ball.ix] = 'o';
}

void moveBall(float x, float y) {
    ball.x = x;
    ball.y = y;
    ball.ix = (int)round(ball.x);
    ball.iy = (int)round(ball.y);
}

void initBall() {
    moveBall(racket.x + racket.w / 2, racket.y - 1);
    ball.alfa = -1;
    ball.speed = 0.5;
}

void autoMoveBall() {
    if(ball.alfa < 0) {
        ball.alfa += M_PI*2;
    }
    if(ball.alfa > M_PI * 2) {
        ball.alfa -= M_PI*2;
    }
    TBall ball2 = ball;

    moveBall(ball.x + cos(ball.alfa) * ball.speed, ball.y + sin(ball.alfa) * ball.speed);

    if(field[ball.iy][ball.ix] == '#' || field[ball.iy][ball.ix] == '=') {
        if(field[ball.iy][ball.ix] == '=') {
            count++;
        }
        if(ball.ix != ball2.ix && ball.iy != ball2.iy) {
            if(field[ball2.iy][ball.ix] == field[ball.iy][ball2.ix]) {
                ball2.alfa = ball2.alfa + M_PI;
            } else {
                if(field[ball2.iy][ball.ix] == '#') {
                     ball2.alfa = 2*M_PI - ball2.alfa + M_PI;
                } else {
                    ball2.alfa = 2*M_PI - ball2.alfa;
                }
            }
        } else if(ball.iy == ball2.iy) {
            ball2.alfa = 2*M_PI - ball2.alfa + M_PI;
        } else {
            ball2.alfa = 2*M_PI - ball2.alfa;
        }
        ball = ball2;
        autoMoveBall();
    }

}

void initRacket() {
    racket.w = 7;
    racket.x = (WIDTH - racket.w) / 2;
    racket.y = HEIGHT - 1;
}

void putRacket() {
    for(int i = racket.x; i < racket.x + racket.w; i++) {
        field[racket.y][i] = '=';
    }
}

void moveRacket(int x) {
    racket.x = x;
    if(racket.x < 1) {
        racket.x = 1;
    }

    if(racket.x + racket.w >= WIDTH) {
        racket.x = WIDTH - 1 - racket.w;
    }
}

void initField() {
    for(int i = 0; i < WIDTH; i++) {
        field[0][i] = '#';
        field[0][WIDTH] = '\0';
    }

    strncpy(field[1], field[0], WIDTH + 1);

    for(int i = 1; i < WIDTH - 1; i++) {
        field[1][i] = ' ';
    }

    for(int i = 2; i < HEIGHT; i++) {
        strncpy(field[i], field[1], WIDTH + 1);
    }

    if(count > 1 && count <= 2) {
        for(int i = 20; i < 50; i++) {
            field[10][i] = '#';
        } 
    }

    if(count > 2 && count <= 3) {
        for(int i = 30; i < 39; i++) {
            field[15][i] = '#';
        } 
        for(int i = 10; i < 19; i++) {
            field[19][i] = '#';
        } 
        for(int i = 43; i < 55; i++) {
            field[6][i] = '#';
        } 
    }

    if(count > 3) {
        for(int i = 13; i < 22; i++) {
            field[i][9] = '#';
        } 
        for(int i = 5; i < 9; i++) {
            field[i][24] = '#';
        } 
        for(int i = 12; i < 23; i++) {
            field[i][37] = '#';
        } 
        for(int i = 6; i < 10; i++) {
            field[i][48] = '#';
        } 
    }
}

void printfField() {
    for(int i = 0; i < HEIGHT; i++) {
        printf("%s\n", field[i]);
        // if(i == 3) {
        //     printf("    %d", count);
        // }
        // if(i == 4) {
        //     printf("    %d", maxCount);
        // }
        // if(i < HEIGHT - 1) {
        //     printf("\n");
        // }
        }
    if(count <= 1) {
        printf("                             Level 1\n");
    }
    if(count > 1 && count <= 2) {
        printf("                             Level 2\n");
    }
    if(count > 2 && count <= 3) {
        printf("                             Level 3\n");
    }
    if(count > 3) {
        printf("                             Level 4\n");
    } 
    
    printf("                              Hits %d\n                          Max hits %d\n", count, maxCount);
    }

    // void setCur(int x, int y) {
    //     COORD coord;
    //     coord.X = x;
    //     coord.Y = y;
    // }

int main() {
    // initscr();
    
    char key;

    bool run = false;

   initRacket();
   initBall();

   do {
    system("clear");
    // printf("\033[H\033[J");

    if(run) {
        autoMoveBall();
    }

    if(ball.iy > HEIGHT) {
        run = false;
        if(count > maxCount) {
            maxCount = count;
        }
        count = 0;
    }

   initField();
   putRacket();
   putBall();
   printfField();
    
    key = getchar();
    if(key == 'w') {
        run = true;
    }
    if(key == 'a') {
        moveRacket(racket.x - 6);
    }
    if(key == 'd') {
        moveRacket(racket.x + 6);
    }
    if(!run) {
        moveBall(racket.x + racket.w / 2, racket.y - 1);
    }
    // refresh();
   }

//     if(GetKeyState('A') < 0) moveRacket(racket.x -1);
//     if(GetKeyState('D') < 0) moveRacket(racket.x + 1);
        // Sleep(10);
   while(key != 'q');
//    while(GetKeyState(VK_ESCAPE) >= 0);

    // endwin();

    return 0;
}