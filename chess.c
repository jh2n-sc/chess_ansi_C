#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this program is at its very early stages..
// only blacks pawn can be moved
void displayBoard(int board[8][8]);
void initializeBoard(int board[8][8]);
void move(int board[8][8], int x1, int y1, int x2, int y2);
int converter(int *x1, int *y1, int *x2, int *y2, char *pos, char *mov);
int main(void) {
    int board[8][8];
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    char pos[5];
    char mov[5];
    initializeBoard(board);
    while(1) {
        printf("%i %i %i %i\n", x1, y1, x2, y2);
        displayBoard(board);
        printf("Enter your move(ex. e4 e6): " );
        scanf("%2s %2s", pos, mov);
        while(converter(&x1, &y1, &x2, &y2, pos, mov) != 1) {
            printf("Enter your move(ex. e4 e6): " );
            scanf("%2s %2s", pos, mov);
        }
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
                printf("♚");
            }
            else if(board[i][j] == 2) {
                printf("♛");
            }
            else if(board[i][j] == 3) {
                printf("♜");
            }
            else if(board[i][j] == 4) {
                printf("♝");
            }
            else if(board[i][j] == 5) {
                printf("♞");
            }
            else if(board[i][j] == 6) {
                printf("♟︎");
            }
            else if(board[i][j] == 7) {
                printf("♔");
            }
            else if(board[i][j] == 8) {
                printf("♕");
            }
            else if(board[i][j] == 9) {
                printf("♖");
            }
            else if(board[i][j] == 10) {
                printf("♗");
            }
            else if(board[i][j] == 11) {
                printf("♘");
            }
            else if(board[i][j] == 12) {
                printf("♙");
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
            printf("yahoo\n");
        }
    }
}
int converter(int *x1, int *y1, int *x2, int *y2, char *pos, char *mov) {
    if(strcmp(pos, "h1") == 0) {
        *x1 = 0;
        *y1 = 0;
    }
    else if(strcmp(pos, "h2") == 0) {
        *x1 = 1;
        *y1 = 0;
    }
    else if(strcmp(pos, "h3") == 0) {
        *x1 = 2;
        *y1 = 0;
    }
    else if(strcmp(pos, "h4") == 0) {
        *x1 = 3;
        *y1 = 0;
    }
    else if(strcmp(pos, "h5") == 0) {
        *x1 = 4;
        *y1 = 0;
    }
    else if(strcmp(pos, "h6") == 0) {
        *x1 = 5;
        *y1 = 0;
    }
    else if(strcmp(pos, "h7") == 0) {
        *x1 = 6;
        *y1 = 0;
    }
    else if(strcmp(pos, "h8") == 0) {
        *x1 = 7;
        *y1 = 0;
    }
    //
    else if(strcmp(pos, "g1") == 0) {
        *x1 = 0;
        *y1 = 1;
    }
    else if(strcmp(pos, "g2") == 0) {
        *x1 = 1;
        *y1 = 1;
    }
    else if(strcmp(pos, "g3") == 0) {
        *x1 = 2;
        *y1 = 1;
    }
    else if(strcmp(pos, "g4") == 0) {
        *x1 = 3;
        *y1 = 1;
    }
    else if(strcmp(pos, "g5") == 0) {
        *x1 = 4;
        *y1 = 1;
    }
    else if(strcmp(pos, "g6") == 0) {
        *x1 = 5;
        *y1 = 1;
    }
    else if(strcmp(pos, "g7") == 0) {
        *x1 = 6;
        *y1 = 1;
    }
    else if(strcmp(pos, "g8") == 0) {
        *x1 = 7;
        *y1 = 1;
    }
    //
    else if(strcmp(pos, "f1") == 0) {
        *x1 = 0;
        *y1 = 2;
    }
    else if(strcmp(pos, "f2") == 0) {
        *x1 = 1;
        *y1 = 2;
    }
    else if(strcmp(pos, "f3") == 0) {
        *x1 = 2;
        *y1 = 2;
    }
    else if(strcmp(pos, "f4") == 0) {
        *x1 = 3;
        *y1 = 2;
    }
    else if(strcmp(pos, "f5") == 0) {
        *x1 = 4;
        *y1 = 2;
    }
    else if(strcmp(pos, "f6") == 0) {
        *x1 = 5;
        *y1 = 2;
    }
    else if(strcmp(pos, "f7") == 0) {
        *x1 = 6;
        *y1 = 2;
    }
    else if(strcmp(pos, "f8") == 0) {
        *x1 = 7;
        *y1 = 2;
    }
    //
    else if(strcmp(pos, "e1") == 0) {
        *x1 = 0;
        *y1 = 3;
    }
    else if(strcmp(pos, "e2") == 0) {
        *x1 = 1;
        *y1 = 3;
    }
    else if(strcmp(pos, "e3") == 0) {
        *x1 = 2;
        *y1 = 3;
    }
    else if(strcmp(pos, "e4") == 0) {
        *x1 = 3;
        *y1 = 3;
    }
    else if(strcmp(pos, "e5") == 0) {
        *x1 = 4;
        *y1 = 3;
    }
    else if(strcmp(pos, "e6") == 0) {
        *x1 = 5;
        *y1 = 3;
    }
    else if(strcmp(pos, "e7") == 0) {
        *x1 = 6;
        *y1 = 3;
    }
    else if(strcmp(pos, "e8") == 0) {
        *x1 = 7;
        *y1 = 3;
    }
    //
    else if(strcmp(pos, "d1") == 0) {
        *x1 = 0;
        *y1 = 4;
    }
    else if(strcmp(pos, "d2") == 0) {
        *x1 = 1;
        *y1 = 4;
    }
    else if(strcmp(pos, "d3") == 0) {
        *x1 = 2;
        *y1 = 4;
    }
    else if(strcmp(pos, "d4") == 0) {
        *x1 = 3;
        *y1 = 4;
    }
    else if(strcmp(pos, "d5") == 0) {
        *x1 = 4;
        *y1 = 4;
    }
    else if(strcmp(pos, "d6") == 0) {
        *x1 = 5;
        *y1 = 4;
    }
    else if(strcmp(pos, "d7") == 0) {
        *x1 = 6;
        *y1 = 4;
    }
    else if(strcmp(pos, "d8") == 0) {
        *x1 = 7;
        *y1 = 4;
    }
    //
    else if(strcmp(pos, "c1") == 0) {
        *x1 = 0;
        *y1 = 5;
    }
    else if(strcmp(pos, "c2") == 0) {
        *x1 = 1;
        *y1 = 5;
    }
    else if(strcmp(pos, "c3") == 0) {
        *x1 = 2;
        *y1 = 5;
    }
    else if(strcmp(pos, "c4") == 0) {
        *x1 = 3;
        *y1 = 5;
    }
    else if(strcmp(pos, "c5") == 0) {
        *x1 = 4;
        *y1 = 5;
    }
    else if(strcmp(pos, "c6") == 0) {
        *x1 = 5;
        *y1 = 5;
    }
    else if(strcmp(pos, "c7") == 0) {
        *x1 = 6;
        *y1 = 5;
    }
    else if(strcmp(pos, "c8") == 0) {
        *x1 = 7;
        *y1 = 5;
    }
    //
    else if(strcmp(pos, "b1") == 0) {
        *x1 = 0;
        *y1 = 6;
    }
    else if(strcmp(pos, "b2") == 0) {
        *x1 = 1;
        *y1 = 6;
    }
    else if(strcmp(pos, "b3") == 0) {
        *x1 = 2;
        *y1 = 6;
    }
    else if(strcmp(pos, "b4") == 0) {
        *x1 = 3;
        *y1 = 6;
    }
    else if(strcmp(pos, "b5") == 0) {
        *x1 = 4;
        *y1 = 6;
    }
    else if(strcmp(pos, "b6") == 0) {
        *x1 = 5;
        *y1 = 6;
    }
    else if(strcmp(pos, "b7") == 0) {
        *x1 = 6;
        *y1 = 6;
    }
    else if(strcmp(pos, "b8") == 0) {
        *x1 = 7;
        *y1 = 6;
    }
    //
    else if(strcmp(pos, "a1") == 0) {
        *x1 = 0;
        *y1 = 7;
    }
    else if(strcmp(pos, "a2") == 0) {
        *x1 = 1;
        *y1 = 7;
    }
    else if(strcmp(pos, "a3") == 0) {
        *x1 = 2;
        *y1 = 7;
    }
    else if(strcmp(pos, "a4") == 0) {
        *x1 = 3;
        *y1 = 7;
    }
    else if(strcmp(pos, "a5") == 0) {
        *x1 = 4;
        *y1 = 7;
    }
    else if(strcmp(pos, "a6") == 0) {
        *x1 = 5;
        *y1 = 7;
    }
    else if(strcmp(pos, "a7") == 0) {
        *x1 = 6;
        *y1 = 7;
    }
    else if(strcmp(pos, "a8") == 0) {
        *x1 = 7;
        *y1 = 7;
    }
    else {
        printf("Invalid position!\n");
        return 0;
    }
    //this is where the move converter is...
    if(strcmp(mov, "h1") == 0) {
        *x2 = 0;
        *y2 = 0;
    }
    else if(strcmp(mov, "h2") == 0) {
        *x2 = 1;
        *y2 = 0;
    }
    else if(strcmp(mov, "h3") == 0) {
        *x2 = 2;
        *y2 = 0;
    }
    else if(strcmp(mov, "h4") == 0) {
        *x2 = 3;
        *y2 = 0;
    }
    else if(strcmp(mov, "h5") == 0) {
        *x2 = 4;
        *y2 = 0;
    }
    else if(strcmp(mov, "h6") == 0) {
        *x2 = 5;
        *y2 = 0;
    }
    else if(strcmp(mov, "h7") == 0) {
        *x2 = 6;
        *y2 = 0;
    }
    else if(strcmp(mov, "h8") == 0) {
        *x2 = 7;
        *y2 = 0;
    }
    //
    else if(strcmp(mov, "g1") == 0) {
        *x2 = 0;
        *y2 = 1;
    }
    else if(strcmp(mov, "g2") == 0) {
        *x2 = 1;
        *y2 = 1;
    }
    else if(strcmp(mov, "g3") == 0) {
        *x2 = 2;
        *y2 = 1;
    }
    else if(strcmp(mov, "g4") == 0) {
        *x2 = 3;
        *y2 = 1;
    }
    else if(strcmp(mov, "g5") == 0) {
        *x2 = 4;
        *y2 = 1;
    }
    else if(strcmp(mov, "g6") == 0) {
        *x2 = 5;
        *y2 = 1;
    }
    else if(strcmp(mov, "g7") == 0) {
        *x2 = 6;
        *y2 = 1;
    }
    else if(strcmp(mov, "g8") == 0) {
        *x2 = 7;
        *y2 = 1;
    }
    //
    else if(strcmp(mov, "f1") == 0) {
        *x2 = 0;
        *y2 = 2;
    }
    else if(strcmp(mov, "f2") == 0) {
        *x2 = 1;
        *y2 = 2;
    }
    else if(strcmp(mov, "f3") == 0) {
        *x2 = 2;
        *y2 = 2;
    }
    else if(strcmp(mov, "f4") == 0) {
        *x2 = 3;
        *y2 = 2;
    }
    else if(strcmp(mov, "f5") == 0) {
        *x2 = 4;
        *y2 = 2;
    }
    else if(strcmp(mov, "f6") == 0) {
        *x2 = 5;
        *y2 = 2;
    }
    else if(strcmp(mov, "f7") == 0) {
        *x2 = 6;
        *y2 = 2;
    }
    else if(strcmp(mov, "f8") == 0) {
        *x2 = 7;
        *y2 = 2;
    }
    //
    else if(strcmp(mov, "e1") == 0) {
        *x2 = 0;
        *y2 = 3;
    }
    else if(strcmp(mov, "e2") == 0) {
        *x2 = 1;
        *y2 = 3;
    }
    else if(strcmp(mov, "e3") == 0) {
        *x2 = 2;
        *y2 = 3;
    }
    else if(strcmp(mov, "e4") == 0) {
        *x2 = 3;
        *y2 = 3;
    }
    else if(strcmp(mov, "e5") == 0) {
        *x2 = 4;
        *y2 = 3;
    }
    else if(strcmp(mov, "e6") == 0) {
        *x2 = 5;
        *y2 = 3;
    }
    else if(strcmp(mov, "e7") == 0) {
        *x2 = 6;
        *y2 = 3;
    }
    else if(strcmp(mov, "e8") == 0) {
        *x2 = 7;
        *y2 = 3;
    }
    //
    else if(strcmp(mov, "d1") == 0) {
        *x2 = 0;
        *y2 = 4;
    }
    else if(strcmp(mov, "d2") == 0) {
        *x2 = 1;
        *y2 = 4;
    }
    else if(strcmp(mov, "d3") == 0) {
        *x2 = 2;
        *y2 = 4;
    }
    else if(strcmp(mov, "d4") == 0) {
        *x2 = 3;
        *y2 = 4;
    }
    else if(strcmp(mov, "d5") == 0) {
        *x2 = 4;
        *y2 = 4;
    }
    else if(strcmp(mov, "d6") == 0) {
        *x2 = 5;
        *y2 = 4;
    }
    else if(strcmp(mov, "d7") == 0) {
        *x2 = 6;
        *y2 = 4;
    }
    else if(strcmp(mov, "d8") == 0) {
        *x2 = 7;
        *y2 = 4;
    }
    //
    else if(strcmp(mov, "c1") == 0) {
        *x2 = 0;
        *y2 = 5;
    }
    else if(strcmp(mov, "c2") == 0) {
        *x2 = 1;
        *y2 = 5;
    }
    else if(strcmp(mov, "c3") == 0) {
        *x2 = 2;
        *y2 = 5;
    }
    else if(strcmp(mov, "c4") == 0) {
        *x2 = 3;
        *y2 = 5;
    }
    else if(strcmp(mov, "c5") == 0) {
        *x2 = 4;
        *y2 = 5;
    }
    else if(strcmp(mov, "c6") == 0) {
        *x2 = 5;
        *y2 = 5;
    }
    else if(strcmp(mov, "c7") == 0) {
        *x2 = 6;
        *y2 = 5;
    }
    else if(strcmp(mov, "c8") == 0) {
        *x2 = 7;
        *y2 = 5;
    }
    //
    else if(strcmp(mov, "b1") == 0) {
        *x2 = 0;
        *y2 = 6;
    }
    else if(strcmp(mov, "b2") == 0) {
        *x2 = 1;
        *y2 = 6;
    }
    else if(strcmp(mov, "b3") == 0) {
        *x2 = 2;
        *y2 = 6;
    }
    else if(strcmp(mov, "b4") == 0) {
        *x2 = 3;
        *y2 = 6;
    }
    else if(strcmp(mov, "b5") == 0) {
        *x2 = 4;
        *y2 = 6;
    }
    else if(strcmp(mov, "b6") == 0) {
        *x2 = 5;
        *y2 = 6;
    }
    else if(strcmp(mov, "b7") == 0) {
        *x2 = 6;
        *y2 = 6;
    }
    else if(strcmp(mov, "b8") == 0) {
        *x2 = 7;
        *y2 = 6;
    }
    //
    else if(strcmp(mov, "a1") == 0) {
        *x2 = 0;
        *y2 = 7;
    }
    else if(strcmp(mov, "a2") == 0) {
        *x2 = 1;
        *y2 = 7;
    }
    else if(strcmp(mov, "a3") == 0) {
        *x2 = 2;
        *y2 = 7;
    }
    else if(strcmp(mov, "a4") == 0) {
        *x2 = 3;
        *y2 = 7;
    }
    else if(strcmp(mov, "a5") == 0) {
        *x2 = 4;
        *y2 = 7;
    }
    else if(strcmp(mov, "a6") == 0) {
        *x2 = 5;
        *y2 = 7;
    }
    else if(strcmp(mov, "a7") == 0) {
        *x2 = 6;
        *y2 = 7;
    }
    else if(strcmp(mov, "a8") == 0) {
        *x2 = 7;
        *y2 = 7;
    }
    else {
        printf("Invalid position!\n");
        return 0;
    }
    return 1;

}