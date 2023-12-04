#include <stdio.h>
#include <stdlib.h>
// this program is at its very early stages..
// only blacks pawn can be moved
void displayBoard(int board[8][8]);
void initializeBoard(int board[8][8]);
void move(int board[8][8], int x1, int y1, int x2, int y2);
int main(void) {
    int board[8][8];
    int x1, y1, x2, y2;
    initializeBoard(board);
    while(1) {
        displayBoard(board);
        scanf("%i %i %i %i", &x1, &y1, &x2, &y2);
        move(board, x1, y1, x2, y2);
        system("clear");
    }
    return 0;
}

void displayBoard(int board[8][8]) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j] == 0) {
                printf(".");
            }
            else if(board[i][j] == 1) {
                printf("K");
            }
            else if(board[i][j] == 2) {
                printf("Q");
            }
            else if(board[i][j] == 3) {
                printf("R");
            }
            else if(board[i][j] == 4) {
                printf("B");
            }
            else if(board[i][j] == 5) {
                printf("N");
            }
            else if(board[i][j] == 6) {
                printf("P");
            }
            else if(board[i][j] == 7) {
                printf("k");
            }
            else if(board[i][j] == 8) {
                printf("q");
            }
            else if(board[i][j] == 9) {
                printf("r");
            }
            else if(board[i][j] == 10) {
                printf("b");
            }
            else if(board[i][j] == 11) {
                printf("n");
            }
            else if(board[i][j] == 12) {
                printf("p");
            }
            printf("  ");
        }
        printf("\n");
    }
}
void initializeBoard(int board[8][8]) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }
    board[0][0] = 3;
    board[0][1] = 5;
    board[0][2] = 4;
    board[0][3] = 2;
    board[0][4] = 1;
    board[0][5] = 4;
    board[0][6] = 5;
    board[0][7] = 3;

    board[1][0] = 6;
    board[1][1] = 6;
    board[1][2] = 6;
    board[1][3] = 6;
    board[1][4] = 6;
    board[1][5] = 6;
    board[1][6] = 6;
    board[1][7] = 6;

    board[6][0] = 12;
    board[6][1] = 12;
    board[6][2] = 12;
    board[6][3] = 12;
    board[6][4] = 12;
    board[6][5] = 12;
    board[6][6] = 12;
    board[6][7] = 12;

    board[7][0] = 9;
    board[7][1] = 11;
    board[7][2] = 10;
    board[7][3] = 8;
    board[7][4] = 7;
    board[7][5] = 10;
    board[7][6] = 11;
    board[7][7] = 9;
    
}
void move(int board[8][8], int x1, int y1, int x2, int y2) {
    if(board[y1][x1] == 6) {
        if(y1 == 1) {
            if((x1 == x2 && y1 == (y2 - 1))) {
            board[y1][x1] = 0;
            board[y2][x2] = 6;
            }
            else {
                printf("Invalid\n");
            }
        }
    }
}