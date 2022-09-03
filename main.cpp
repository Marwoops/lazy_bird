#include <iostream>
#include <queue>
#include <ncurses.h>
#include <ctime>

#define UP 122 // Z
#define DOWN 115 // S

int GAP = 5;
int H = 30;
int W = 70;
int DEFAULT_SPEED = 100000;

struct pipe {
    int h;
    int x;
};

pipe generatePipe() {
    pipe p;
    srand(time(NULL));
    p.h = rand() % (H-GAP-1);
    p.x = W;
    return p;
}

void printPipe(pipe p) {
    for (int i = 0; i < p.h; i++) {
        mvprintw(i, p.x, "||");
    }

    for (int i = p.h + GAP; i < H; i++) {
        mvprintw(i, p.x, "||");
    }
}

int main() {
    std::queue<pipe> pipes;
    
    int score = 0;
    int speed = DEFAULT_SPEED;

    // spaceship default position
    int h = H/2;

    // first pipe
    pipe p;
    p.h = H/2;
    p.x = W/2;
    pipes.push(p);
    
    pipes.push(generatePipe());

    initscr();
    nodelay(stdscr, true); 

    clock_t t = clock();
    while(true) {
        if (clock() - t >= speed) {
            t = clock();
            // MOVE PIPES
            pipes.front().x--;
            pipes.back().x--;

            if (pipes.front().x == 0) {
                pipes.pop();
                pipes.push(generatePipe());
                score+=3;
                if (score % 3 == 0) {
                    speed -= DEFAULT_SPEED/20;
                }
            }

            refresh();
            clear();
        }
        
        int c = getch();
        
        if (c == UP) {
            h--;
        } else if (c == DOWN) {
            h++;
        }
        
        pipe p = pipes.front();
        if ((p.x == 3 || p.x == 2) && (h < p.h || h >= p.h + GAP)) {
            break;
        }
        
        mvprintw(h, 3, "O");
        printPipe(pipes.front());
        printPipe(pipes.back());
   
    }
    
    // END SCREEN
    clear();

    mvprintw(H/2, W/2, "SCORE : %d", score);
    refresh();
    
    nodelay(stdscr, false);
    getch();
    
    endwin();
}
