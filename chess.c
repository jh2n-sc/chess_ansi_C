#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this program is at its very early stages..
// only blacks pawn can be moved
void displayBoard(int board[8][8]);
void initializeBoard(int board[8][8]);
int move(int board[8][8], int y1, int x1, int y2, int x2, int turn);


int converter(int *y1, int *x1, int *y2, int *x2, char *pos, char *mov);
int main(void) {
    int board[8][8];
    int y1 = 0, x1 = 0, y2 = 0, x2 = 0;
    char pos[5];
    char mov[5];
    int turn = 0;
    initializeBoard(board);
    while(1) {
        printf("x1 = %i | y1 = %i | x2 = %i | y2 = %i\n", x1, y1, x2, y2);
        printf("Target: %i\n", board[y2][x2]);
        displayBoard(board);
        if(turn == 0) {
            printf("White's turn\n");
        }
        else {
            printf("Black's turn\n");
        }
        printf("Enter your move(ex: e2 e4): ");
        scanf("%2s %2s", pos, mov);
        converter(&y1, &x1, &y2, &x2, pos, mov);
        while(move(board, y1, x1, y2, x2, turn) != 0) {
            printf("Invalid!!!\n");
            printf("Target: mov%i\n", board[y2][x2]);
            printf("Target: pos%i\n", board[y1][x1]);
            printf("Enter your move(ex: e2 e4): ");
            scanf("%2s %2s", pos, mov);
            converter(&y1, &x1, &y2, &x2, pos, mov);
            //board[y1][x1] = 0;
        }
        if(turn == 0) {
            turn = 1;
        }
        else {
            turn = 0;
        }
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
            else if(board[i][j] == 13) {
                printf("♚");
            }
            else if(board[i][j] == 14) {
                printf("♜");
            }
            else if(board[i][j] == 15) {
                printf("♟︎");
            }
            else if(board[i][j] == 16) {
                printf("♔");
            }
            else if(board[i][j] == 17) {
                printf("♖");
            }
            else if(board[i][j] == 18) {
                printf("♙");
            }
            printf("  ");
        }
        if(i == 0) {
            printf("8");
        }
        else if(i == 1) {
            printf("7");
        }
        else if(i == 2) {
            printf("6");
        }
        else if(i == 3) {
            printf("5");
        }
        else if(i == 4) {
            printf("4");
        }
        else if(i == 5) {
            printf("3");
        }
        else if(i == 6) {
            printf("2");
        }
        else if(i == 7) {
            printf("1");
        }
        printf("\n");
    }
    printf("a  b  c  d  e  f  g  h\n\n");
}
void initializeBoard(int board[8][8]) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }
    board[0][0] = 14;
    board[0][1] = 5;
    board[0][2] = 4;
    board[0][3] = 2;
    board[0][4] = 13;
    board[0][5] = 4;
    board[0][6] = 5;
    board[0][7] = 14;

    board[1][0] = 15;
    board[1][1] = 15;
    board[1][2] = 15;
    board[1][3] = 15;
    board[1][4] = 15;
    board[1][5] = 15;
    board[1][6] = 15;
    board[1][7] = 15;

    board[6][0] = 18;
    board[6][1] = 18;
    board[6][2] = 18;
    board[6][3] = 18;
    board[6][4] = 18;
    board[6][5] = 18;
    board[6][6] = 18;
    board[6][7] = 18;

    board[7][0] = 17;
    board[7][1] = 11;
    board[7][2] = 10;
    board[7][3] = 8;
    board[7][4] = 16;
    board[7][5] = 10;
    board[7][6] = 11;
    board[7][7] = 17;
    
}
int move(int board[8][8], int y1, int x1, int y2, int x2, int turn) {
    int suc = 0;
    int ver = 0;
    if(turn == 1) {
        if(board[y1][x1] == 1) {
            
        }
        //black queen
        if(board[y1][x1] == 2) {
            for(int i = x1 + 1, j = y1 - 1; i < 8 && j > -1; i++, j--) {
                if(x2 == i && y2 == j) {
                    ver = 1;
                }
            }
            for(int i = y1 + 1, j = x1 - 1; i < 8 && j > -1; i++, j--) {
                if(y2 == i && x2 == j) {
                    ver = 1;
                }
            }
            for(int i = y1 + 1, j = x1 + 1; i < 8 && j < 8; i++, j++) {
                if(y2 == i && x2 == j) {
                    ver = 1;
                }
            }
            for(int i = y1 - 1, j = x1 - 1; i > -1 && j > -1; i--, j--) {
                if(y2 == i && x2 == j) {
                    ver = 1;
                }
            }
            if(ver == 1) {
                board[y1][x1] = 0;
                board[y2][x2] = 2;
            } 
            else if(x1 == x2 && y2 != y1 && (y2 >= 0 && y2 < 8)) {
                board[y1][x1] = 0;
                board[y2][x2] = 2;
                ver = 1;
            }
            else if(y1 == y2 && x2 != x1 && (x2 >= 0 && x2 < 8)) {
                board[y1][x1] = 0;
                board[y2][x2] = 2;
                ver = 1;
            }
            else {
                ver = 0;
            }
            if(ver == 0) {
                suc = 1;
            }
            ver = 0;    
        }
        //black rook
        if(board[y1][x1] == 3) {
            if(x1 == x2 && y2 != y1 && (y2 >= 0 && y2 < 8)) {
                board[y1][x1] = 0;
                board[y2][x2] = 3;
            }
            else if(y1 == y2 && x2 != x1 && (x2 >= 0 && x2 < 8)) {
                board[y1][x1] = 0;
                board[y2][x2] = 3;
            }
            else {
                suc = 1;
            }
        }
        //black bishop
        if(board[y1][x1] == 4) {
            for(int i = x1 + 1, j = y1 - 1; i < 8 && j > -1; i++, j--) {
                if(x2 == i && y2 == j) {
                    ver = 1;
                }
            }
            for(int i = y1 + 1, j = x1 - 1; i < 8 && j > -1; i++, j--) {
                if(y2 == i && x2 == j) {
                    ver = 1;
                }
            }
            for(int i = y1 + 1, j = x1 + 1; i < 8 && j < 8; i++, j++) {
                if(y2 == i && x2 == j) {
                    ver = 1;
                }
            }
            for(int i = y1 - 1, j = x1 - 1; i > -1 && j > -1; i--, j--) {
                if(y2 == i && x2 == j) {
                    ver = 1;
                }
            }
            if(ver == 1) {
                board[y1][x1] = 0;
                board[y2][x2] = 4;
            } 
            else {
                suc = 1;
            }
            ver = 0;
        }
        //black knight
        if(board[y1][x1] == 5) {
            if((x1 == x2 + 2 || x1 == x2 + 1 || x1 == x2 - 2 || x1 == x2 - 1)) {
                if((y1 == y2 + 2 || y1 == y2 + 1 || y1 == y2 - 2 || y1 == y2 - 1)) {
                    board[y1][x1] = 0;
                    board[y2][x2] = 5;
                }
            }
        }
        if(board[y1][x1] == 6) {
                if((y1 == (y2 - 1) && x1 == x2)) {
                board[y1][x1] = 0;
                board[y2][x2] = 6;
                }
                else {
                    printf("Invalid\n");
                }
                printf("yahoo\n");
        }
        if(board[y1][x1] == 13) {

        }
        //unmoved black rook
        if(board[y1][x1] == 14) {
            if(x1 == x2 && y2 != y1 && (y2 >= 0 && y2 < 8)) {
                board[y1][x1] = 0;
                board[y2][x2] = 3;
            }
            else if(y1 == y2 && x2 != x1 && (x2 >= 0 && x2 < 8)) {
                board[y1][x1] = 0;
                board[y2][x2] = 3;
            }
            else {
                suc = 1;
            }
        }
        if(board[y1][x1] == 15) {
                if((y1 == (y2 - 1) && x1 == x2)) {
                    board[y1][x1] = 0;
                    board[y2][x2] = 6;
                }
                else if((y1 == (y2 - 2) && x1 == x2)) {
                    board[y1][x1] = 0;
                    board[y2][x2] = 6;
                }
                else {
                    printf("Invalid\n");
                }
                printf("yahoo\n");
        }
        
    }
    if(turn == 0) {
        if(board[y1][x1] == 7) {

        }
        //white queen
        else if(board[y1][x1] == 8) {
            for(int i = x1 + 1, j = y1 - 1; i < 8 && j > -1; i++, j--) {
                if(x2 == i && y2 == j) {
                    ver = 1;
                }
            }
            for(int i = y1 + 1, j = x1 - 1; i < 8 && j > -1; i++, j--) {
                if(y2 == i && x2 == j) {
                    ver = 1;
                }
            }
            for(int i = y1 + 1, j = x1 + 1; i < 8 && j < 8; i++, j++) {
                if(y2 == i && x2 == j) {
                    ver = 1;
                }
            }
            for(int i = y1 - 1, j = x1 - 1; i > -1 && j > -1; i--, j--) {
                if(y2 == i && x2 == j) {
                    ver = 1;
                }
            }
            if(ver == 1) {
                board[y1][x1] = 0;
                board[y2][x2] = 8;
            } 
            else if(x1 == x2 && y2 != y1 && (y2 >= 0 && y2 < 8)) {
                board[y1][x1] = 0;
                board[y2][x2] = 8;
                ver = 1;
            }
            else if(y1 == y2 && x2 != x1 && (x2 >= 0 && x2 < 8)) {
                board[y1][x1] = 0;
                board[y2][x2] = 8;
                ver = 1;
            }
            else {
                ver = 0;
            }
            if(ver == 0) {
                suc = 1;
            }
            ver = 0;   
        }
        else if(board[y1][x1] == 9) {
            if(x1 == x2 && y2 != y1 && (y2 >= 0 && y2 < 8)) {
                board[y1][x1] = 0;
                board[y2][x2] = 9;
            }
            else if(y1 == y2 && x2 != x1 && (x2 >= 0 && x2 < 8)) {
                board[y1][x1] = 0;
                board[y2][x2] = 9;
            }
            else {
                suc = 1;
            }
        }
        //white bishop
        else if(board[y1][x1] == 10) {
            for(int i = x1 + 1, j = y1 - 1; i < 8 && j > -1; i++, j--) {
                if(x2 == i && y2 == j) {
                    ver = 1;
                }
            }
            for(int i = y1 + 1, j = x1 - 1; i < 8 && j > -1; i++, j--) {
                if(y2 == i && x2 == j) {
                    ver = 1;
                }
            }
            for(int i = y1 + 1, j = x1 + 1; i < 8 && j < 8; i++, j++) {
                if(y2 == i && x2 == j) {
                    ver = 1;
                }
            }
            for(int i = y1 - 1, j = x1 - 1; i > -1 && j > -1; i--, j--) {
                if(y2 == i && x2 == j) {
                    ver = 1;
                }
            }
            if(ver == 1) {
                board[y1][x1] = 0;
                board[y2][x2] = 10;
            } 
            else {
                suc = 1;
            }
            ver = 0;
        }
        //white knight
        else if(board[y1][x1] == 11) {
            if((x1 == x2 + 2 || x1 == x2 + 1 || x1 == x2 - 2 || x1 == x2 - 1)) {
                if((y1 == y2 + 2 || y1 == y2 + 1 || y1 == y2 - 2 || y1 == y2 - 1)) {
                    board[y1][x1] = 0;
                    board[y2][x2] = 11;
                }
            }
        }
        else if(board[y1][x1] == 12) {
                if((y1 == (y2 + 1) && x1 == x2)) {
                board[y1][x1] = 0;
                board[y2][x2] = 12;
                }
                else {
                    printf("Invalid\n");
                }
                printf("yahoo\n");
        }
        else if(board[y1][x1] == 16) {

        }
        //unmoved white rook
        else if(board[y1][x1] == 17) {
            if(x1 == x2 && y2 != y1 && (y2 >= 0 && y2 < 8)) {
                board[y1][x1] = 0;
                board[y2][x2] = 9;
            }
            else if(y1 == y2 && x2 != x1 && (x2 >= 0 && x2 < 8)) {
                board[y1][x1] = 0;
                board[y2][x2] = 9;
            }
            else {
                suc = 1;
            }
        }
        //unmoved white pawn
        else if(board[y1][x1] == 18) {
                if((y1 == (y2 + 1) && x1 == x2)) {
                    board[y1][x1] = 0;
                    board[y2][x2] = 12;
                }
                else if((y1 == (y2 + 2) && x1 == x2)) {
                    board[y1][x1] = 0;
                    board[y2][x2] = 12;
                }
                else {
                    printf("Invalid\n");
                }
                printf("yahoo\n");
        }
        else {
        }
        
    }
    return suc;
}
int converter(int *y1, int *x1, int *y2, int *x2, char *pos, char *mov) {
    if(strcmp(pos, "h1") == 0) {
        *y1 = 7;//7
        *x1 = 7;//7
    }
    else if(strcmp(pos, "h2") == 0) {
        *y1 = 6;//6
        *x1 = 7;//7
    }
    else if(strcmp(pos, "h3") == 0) {
        *y1 = 5;//5
        *x1 = 7;//7
    }
    else if(strcmp(pos, "h4") == 0) {
        *y1 = 4;//4
        *x1 = 7;//7
    }
    else if(strcmp(pos, "h5") == 0) {
        *y1 = 3;//3
        *x1 = 7;//7
    }
    else if(strcmp(pos, "h6") == 0) {
        *y1 = 2;//2
        *x1 = 7;//7
    }
    else if(strcmp(pos, "h7") == 0) {
        *y1 = 1;//1
        *x1 = 7;//7
    }
    else if(strcmp(pos, "h8") == 0) {
        *y1 = 0;//0
        *x1 = 7;//7
    }
    //
    else if(strcmp(pos, "g1") == 0) {
        *y1 = 7;//7
        *x1 = 6;//6
    }
    else if(strcmp(pos, "g2") == 0) {
        *y1 = 6;//6
        *x1 = 6;//6
    }
    else if(strcmp(pos, "g3") == 0) {
        *y1 = 5;//5
        *x1 = 6;//6
    }
    else if(strcmp(pos, "g4") == 0) {
        *y1 = 4;//4
        *x1 = 6;//6
    }
    else if(strcmp(pos, "g5") == 0) {
        *y1 = 3;//3
        *x1 = 6;//6
    }
    else if(strcmp(pos, "g6") == 0) {
        *y1 = 2;//2
        *x1 = 6;//6
    }
    else if(strcmp(pos, "g7") == 0) {
        *y1 = 1;//1
        *x1 = 6;//6
    }
    else if(strcmp(pos, "g8") == 0) {
        *y1 = 0;//0
        *x1 = 6;//6
    }
    //
    else if(strcmp(pos, "f1") == 0) {
        *y1 = 7;//7
        *x1 = 5;//5
    }
    else if(strcmp(pos, "f2") == 0) {
        *y1 = 6;//6
        *x1 = 5;//5
    }
    else if(strcmp(pos, "f3") == 0) {
        *y1 = 5;//5
        *x1 = 5;//5
    }
    else if(strcmp(pos, "f4") == 0) {
        *y1 = 4;//4
        *x1 = 5;//5
    }
    else if(strcmp(pos, "f5") == 0) {
        *y1 = 3;//3
        *x1 = 5;//5
    }
    else if(strcmp(pos, "f6") == 0) {
        *y1 = 2;//2
        *x1 = 5;//5
    }
    else if(strcmp(pos, "f7") == 0) {
        *y1 = 1;//1
        *x1 = 5;//5
    }
    else if(strcmp(pos, "f8") == 0) {
        *y1 = 0;//0
        *x1 = 5;//5
    }
    //
    else if(strcmp(pos, "e1") == 0) {
        *y1 = 7;//7
        *x1 = 4;//4
    }
    else if(strcmp(pos, "e2") == 0) {
        *y1 = 6;//6
        *x1 = 4;//4
    }
    else if(strcmp(pos, "e3") == 0) {
        *y1 = 5;//5
        *x1 = 4;//4
    }
    else if(strcmp(pos, "e4") == 0) {
        *y1 = 4;//4
        *x1 = 4;//4
    }
    else if(strcmp(pos, "e5") == 0) {
        *y1 = 3;//3
        *x1 = 4;//4
    }
    else if(strcmp(pos, "e6") == 0) {
        *y1 = 2;//2
        *x1 = 4;//4
    }
    else if(strcmp(pos, "e7") == 0) {
        *y1 = 1;//1
        *x1 = 4;//4
    }
    else if(strcmp(pos, "e8") == 0) {
        *y1 = 0;//0
        *x1 = 4;//4
    }
    //
    else if(strcmp(pos, "d1") == 0) {
        *y1 = 7;//7
        *x1 = 3;//3
    }
    else if(strcmp(pos, "d2") == 0) {
        *y1 = 6;//6
        *x1 = 3;//3
    }
    else if(strcmp(pos, "d3") == 0) {
        *y1 = 5;//5
        *x1 = 3;//3
    }
    else if(strcmp(pos, "d4") == 0) {
        *y1 = 4;//4
        *x1 = 3;//3
    }
    else if(strcmp(pos, "d5") == 0) {
        *y1 = 3;//3
        *x1 = 3;//3
    }
    else if(strcmp(pos, "d6") == 0) {
        *y1 = 2;//2
        *x1 = 3;//3
    }
    else if(strcmp(pos, "d7") == 0) {
        *y1 = 1;//1
        *x1 = 3;//3
    }
    else if(strcmp(pos, "d8") == 0) {
        *y1 = 0;//0
        *x1 = 3;//3
    }
    //
    else if(strcmp(pos, "c1") == 0) {
        *y1 = 7;//7
        *x1 = 2;//2
    }
    else if(strcmp(pos, "c2") == 0) {
        *y1 = 6;//6
        *x1 = 2;//2
    }
    else if(strcmp(pos, "c3") == 0) {
        *y1 = 5;//5
        *x1 = 2;//2
    }
    else if(strcmp(pos, "c4") == 0) {
        *y1 = 4;//4
        *x1 = 2;//2
    }
    else if(strcmp(pos, "c5") == 0) {
        *y1 = 3;//3
        *x1 = 2;//2
    }
    else if(strcmp(pos, "c6") == 0) {
        *y1 = 2;//2
        *x1 = 2;//2
    }
    else if(strcmp(pos, "c7") == 0) {
        *y1 = 1;//1
        *x1 = 2;//2
    }
    else if(strcmp(pos, "c8") == 0) {
        *y1 = 0;//0
        *x1 = 2;//2
    }
    //
    else if(strcmp(pos, "b1") == 0) {
        *y1 = 7;//7
        *x1 = 1;//1
    }
    else if(strcmp(pos, "b2") == 0) {
        *y1 = 6;//6
        *x1 = 1;//1
    }
    else if(strcmp(pos, "b3") == 0) {
        *y1 = 5;//5
        *x1 = 1;//1
    }
    else if(strcmp(pos, "b4") == 0) {
        *y1 = 4;//4
        *x1 = 1;//1
    }
    else if(strcmp(pos, "b5") == 0) {
        *y1 = 3;//3
        *x1 = 1;//1
    }
    else if(strcmp(pos, "b6") == 0) {
        *y1 = 2;//2
        *x1 = 1;//1
    }
    else if(strcmp(pos, "b7") == 0) {
        *y1 = 1;//1
        *x1 = 1;//1
    }
    else if(strcmp(pos, "b8") == 0) {
        *y1 = 0;//0
        *x1 = 1;//1
    }
    //
    else if(strcmp(pos, "a1") == 0) {
        *y1 = 7;//7
        *x1 = 0;//0
    }
    else if(strcmp(pos, "a2") == 0) {
        *y1 = 6;//6
        *x1 = 0;//0
    }
    else if(strcmp(pos, "a3") == 0) {
        *y1 = 5;//5
        *x1 = 0;//0
    }
    else if(strcmp(pos, "a4") == 0) {
        *y1 = 4;//4
        *x1 = 0;//0
    }
    else if(strcmp(pos, "a5") == 0) {
        *y1 = 3;//3
        *x1 = 0;//0
    }
    else if(strcmp(pos, "a6") == 0) {
        *y1 = 2;//2
        *x1 = 0;//0
    }
    else if(strcmp(pos, "a7") == 0) {
        *y1 = 1;//1
        *x1 = 0;//0
    }
    else if(strcmp(pos, "a8") == 0) {
        *y1 = 0;//0
        *x1 = 0;//0
    }
    else {
        printf("Invalid position!\n");
        return 0;
    }
    //this is where the move converter is...
    if(strcmp(mov, "h1") == 0) {
        *y2 = 7;//7
        *x2 = 7;//7
    }
    else if(strcmp(mov, "h2") == 0) {
        *y2 = 6;//6
        *x2 = 7;//7
    }
    else if(strcmp(mov, "h3") == 0) {
        *y2 = 5;//5
        *x2 = 7;//7
    }
    else if(strcmp(mov, "h4") == 0) {
        *y2 = 4;//4
        *x2 = 7;//7
    }
    else if(strcmp(mov, "h5") == 0) {
        *y2 = 3;//3
        *x2 = 7;//7
    }
    else if(strcmp(mov, "h6") == 0) {
        *y2 = 2;//2
        *x2 = 7;//7
    }
    else if(strcmp(mov, "h7") == 0) {
        *y2 = 1;//1
        *x2 = 7;//7
    }
    else if(strcmp(mov, "h8") == 0) {
        *y2 = 0;//0
        *x2 = 7;//7
    }
    //
    else if(strcmp(mov, "g1") == 0) {
        *y2 = 7;//7
        *x2 = 6;//6
    }
    else if(strcmp(mov, "g2") == 0) {
        *y2 = 6;//6
        *x2 = 6;//6
    }
    else if(strcmp(mov, "g3") == 0) {
        *y2 = 5;//5
        *x2 = 6;//6
    }
    else if(strcmp(mov, "g4") == 0) {
        *y2 = 4;//4
        *x2 = 6;//6
    }
    else if(strcmp(mov, "g5") == 0) {
        *y2 = 3;//3
        *x2 = 6;//6
    }
    else if(strcmp(mov, "g6") == 0) {
        *y2 = 2;//2
        *x2 = 6;//6
    }
    else if(strcmp(mov, "g7") == 0) {
        *y2 = 1;//1
        *x2 = 6;//6
    }
    else if(strcmp(mov, "g8") == 0) {
        *y2 = 0;//0
        *x2 = 6;//6
    }
    //
    else if(strcmp(mov, "f1") == 0) {
        *y2 = 7;//7
        *x2 = 5;//5
    }
    else if(strcmp(mov, "f2") == 0) {
        *y2 = 6;//6
        *x2 = 5;//5
    }
    else if(strcmp(mov, "f3") == 0) {
        *y2 = 5;//5
        *x2 = 5;//5
    }
    else if(strcmp(mov, "f4") == 0) {
        *y2 = 4;//4
        *x2 = 5;//5
    }
    else if(strcmp(mov, "f5") == 0) {
        *y2 = 3;//3
        *x2 = 5;//5
    }
    else if(strcmp(mov, "f6") == 0) {
        *y2 = 2;//2
        *x2 = 5;//5
    }
    else if(strcmp(mov, "f7") == 0) {
        *y2 = 1;//1
        *x2 = 5;//5
    }
    else if(strcmp(mov, "f8") == 0) {
        *y2 = 0;//0
        *x2 = 5;//5
    }
    //
    else if(strcmp(mov, "e1") == 0) {
        *y2 = 7;//7
        *x2 = 4;//4
    }
    else if(strcmp(mov, "e2") == 0) {
        *y2 = 6;//6
        *x2 = 4;//4
    }
    else if(strcmp(mov, "e3") == 0) {
        *y2 = 5;//5
        *x2 = 4;//4
    }
    else if(strcmp(mov, "e4") == 0) {
        *y2 = 4;//4
        *x2 = 4;//4
    }
    else if(strcmp(mov, "e5") == 0) {
        *y2 = 3;//3
        *x2 = 4;//4
    }
    else if(strcmp(mov, "e6") == 0) {
        *y2 = 2;//2
        *x2 = 4;//4
    }
    else if(strcmp(mov, "e7") == 0) {
        *y2 = 1;//1
        *x2 = 4;//4
    }
    else if(strcmp(mov, "e8") == 0) {
        *y2 = 0;//0
        *x2 = 4;//4
    }
    //
    else if(strcmp(mov, "d1") == 0) {
        *y2 = 7;//7
        *x2 = 3;//3
    }
    else if(strcmp(mov, "d2") == 0) {
        *y2 = 6;//6
        *x2 = 3;//3
    }
    else if(strcmp(mov, "d3") == 0) {
        *y2 = 5;//5
        *x2 = 3;//3
    }
    else if(strcmp(mov, "d4") == 0) {
        *y2 = 4;//4
        *x2 = 3;//3
    }
    else if(strcmp(mov, "d5") == 0) {
        *y2 = 3;//3
        *x2 = 3;//3
    }
    else if(strcmp(mov, "d6") == 0) {
        *y2 = 2;//2
        *x2 = 3;//3
    }
    else if(strcmp(mov, "d7") == 0) {
        *y2 = 1;//1
        *x2 = 3;//3
    }
    else if(strcmp(mov, "d8") == 0) {
        *y2 = 0;//0
        *x2 = 3;//3
    }
    //
    else if(strcmp(mov, "c1") == 0) {
        *y2 = 7;//7
        *x2 = 2;//2
    }
    else if(strcmp(mov, "c2") == 0) {
        *y2 = 6;//6
        *x2 = 2;//2
    }
    else if(strcmp(mov, "c3") == 0) {
        *y2 = 5;//5
        *x2 = 2;//2
    }
    else if(strcmp(mov, "c4") == 0) {
        *y2 = 4;//4
        *x2 = 2;//2
    }
    else if(strcmp(mov, "c5") == 0) {
        *y2 = 3;//3
        *x2 = 2;//2
    }
    else if(strcmp(mov, "c6") == 0) {
        *y2 = 2;//2
        *x2 = 2;//2
    }
    else if(strcmp(mov, "c7") == 0) {
        *y2 = 1;//1
        *x2 = 2;//2
    }
    else if(strcmp(mov, "c8") == 0) {
        *y2 = 0;//0
        *x2 = 2;//2
    }
    //
    else if(strcmp(mov, "b1") == 0) {
        *y2 = 7;//7
        *x2 = 1;//1
    }
    else if(strcmp(mov, "b2") == 0) {
        *y2 = 6;//6
        *x2 = 1;//1
    }
    else if(strcmp(mov, "b3") == 0) {
        *y2 = 5;//5
        *x2 = 1;//1
    }
    else if(strcmp(mov, "b4") == 0) {
        *y2 = 4;//4
        *x2 = 1;//1
    }
    else if(strcmp(mov, "b5") == 0) {
        *y2 = 3;//3
        *x2 = 1;//1
    }
    else if(strcmp(mov, "b6") == 0) {
        *y2 = 2;//2
        *x2 = 1;//1
    }
    else if(strcmp(mov, "b7") == 0) {
        *y2 = 1;//1
        *x2 = 1;//1
    }
    else if(strcmp(mov, "b8") == 0) {
        *y2 = 0;//0
        *x2 = 1;//1
    }
    //
    else if(strcmp(mov, "a1") == 0) {
        *y2 = 7;//7
        *x2 = 0;//0
    }
    else if(strcmp(mov, "a2") == 0) {
        *y2 = 6;//6
        *x2 = 0;//0
    }
    else if(strcmp(mov, "a3") == 0) {
        *y2 = 5;//5
        *x2 = 0;//0
    }
    else if(strcmp(mov, "a4") == 0) {
        *y2 = 4;//4
        *x2 = 0;//0
    }
    else if(strcmp(mov, "a5") == 0) {
        *y2 = 3;//3
        *x2 = 0;//0
    }
    else if(strcmp(mov, "a6") == 0) {
        *y2 = 2;//2
        *x2 = 0;//0
    }
    else if(strcmp(mov, "a7") == 0) {
        *y2 = 1;//1
        *x2 = 0;//0
    }
    else if(strcmp(mov, "a8") == 0) {
        *y2 = 0;//0
        *x2 = 0;//0
    }
    else {
        printf("Invalid position!\n");
        return 0;
    }
    return 0;

}