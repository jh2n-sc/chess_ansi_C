#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// for adding entities
void addEntity(int board[8][8], int y1, int x1, int value);

// for checking shadow board legal moves(my flipping invention)
int chShadowBoardInit(int board[8][8], int wsboard[8][8], int bsboard[8][8], int x1, int y1, int x2, int y2, int turn);

// for converting input to decimal
int converter(int *y1, int *x1, int *y2, int *x2, char *pos, char *mov);

// for displaying the board
void displayBoard(int board[8][8]);

// for initializing the board(my shi)
void initializeBoard(int board[8][8]);

// for detecting checkmates | stalemate
int mateChecker(int board[8][8], int turn);

// for moving the pieces
void move(int board[8][8], int y1, int x1, int y2, int x2);

// checks for promotion
int promotion(int board[8][8], int turn);

// for checking shadow board(again, but it is mainly for the king)
int shadowBoardChecker(int board[8][8], int x1, int y1, int x2, int y2, int turn);

// for generating shadow board(really cool name to be honest)
void shadowBoardInit(int board[8][8], int wsboard[8][8], int bsboard[8][8]);

int main(void)
{
    int board[8][8];
    int wsboard[8][8];
    int bsboard[8][8];
    char pos[5];
    int turn = 0;
    char mov[5];
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    int inv = 1;
    initializeBoard(board);
    shadowBoardInit(board, wsboard, bsboard);
    char *strMove[3] = {"White", "Black"};
    do
    {
        displayBoard(board);
        printf("%s to move\n", strMove[turn]);
        printf("Enter move (e2 e4): ");
        while (inv == 1)
        {
            scanf("%3s %3s", pos, mov);
            converter(&y1, &x1, &y2, &x2, pos, mov);
            if (!(chShadowBoardInit(board, wsboard, bsboard, x1, y1, x2, y2, turn) == 0 || shadowBoardChecker(board, x1, y1, x2, y2, turn) == -1))
            {
                inv = 0;
            }
            else
            {
                printf("Invalid move\n");
            }
        }
        move(board, y1, x1, y2, x2);
        x1 = 0;
        y1 = 0;
        x2 = 0;
        y2 = 0;
        if (mateChecker(board, turn) == 1)
        {
            printf("Checkmate: by %s\n", strMove[turn]);
            getchar();
            printf("Press any key to continue.");
            getchar();
        }
        else if (mateChecker(board, turn) == 2)
        {
            printf("Draw: by stalemate\n");
            getchar();
            printf("Press any key to continue.");
            getchar();
        }
        if (turn == 1)
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (board[i][j] == 30)
                    {
                        board[i][j] = 26;
                    }
                }
            }
            turn = 0;
        }
        else if (turn == 0)
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (board[i][j] == 10)
                    {
                        board[i][j] = 6;
                    }
                }
            }
            turn = 1;
        }
        system("clear");
        inv = 1;
    } while (1);
    return 0;
}
void addEntity(int board[8][8], int y1, int x1, int value)
{
    // for stuff
    board[y1][x1] = value;
}
int chShadowBoardInit(int board[8][8], int wsboard[8][8], int bsboard[8][8], int x1, int y1, int x2, int y2, int turn)
{
    int retVal = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            wsboard[i][j] = 0;
        }
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            bsboard[i][j] = 0;
        }
    }
    if (turn == 1)
    {
        if (board[y1][x1] > 0 && board[y1][x1] < 11)
        {
            // black king
            if (board[y1][x1] == 1 || board[y1][x1] == 7)
            {
                for (int y = -1; y < 2; y++)
                {
                    for (int x = -1; x < 2; x++)
                    {
                        if (!((y1 + y > 7) || (y1 + y < 0)))
                        {
                            if (!((x1 + x > 7) || (x1 + x < 0)))
                            {
                                if (!(board[y1 + y][x1 + x] > 0 && board[y1 + y][x1 + x] < 11))
                                {
                                    bsboard[y1 + y][x1 + x] = -1;
                                }
                            }
                        }
                    }
                }
            }
            // black queen
            else if (board[y1][x1] == 2)
            {
                // right down
                for (int x = x1 + 1, y = y1 + 1; x < 8 && y < 8; x++, y++)
                {
                    if (board[y][x] == 0)
                    {
                        bsboard[y][x] = -1;
                    }
                    else if (board[y][x] > 21)
                    {
                        bsboard[y][x] = -2;
                        break;
                    }
                    else if (board[y][x] > 0 && board[y][x] < 11)
                    {
                        bsboard[y][x] = 0;
                        break;
                    }
                }
                // left down
                for (int x = x1 - 1, y = y1 + 1; x > -1 && y < 8; x--, y++)
                {
                    if (board[y][x] == 0)
                    {
                        bsboard[y][x] = -1;
                    }
                    else if (board[y][x] > 21)
                    {
                        bsboard[y][x] = -2;
                        break;
                    }
                    else if (board[y][x] > 0 && board[y][x] < 11)
                    {
                        bsboard[y][x] = 0;
                        break;
                    }
                }
                // right up
                for (int x = x1 + 1, y = y1 - 1; x < 8 && y > -1; x++, y--)
                {
                    if (board[y][x] == 0)
                    {
                        bsboard[y][x] = -1;
                    }
                    else if (board[y][x] > 21)
                    {
                        bsboard[y][x] = -2;
                        break;
                    }
                    else if (board[y][x] > 0 && board[y][x] < 11)
                    {
                        bsboard[y][x] = 0;
                        break;
                    }
                }
                // left up
                for (int x = x1 - 1, y = y1 - 1; x > -1 && y > -1; x--, y--)
                {
                    if (board[y][x] == 0)
                    {
                        bsboard[y][x] = -1;
                    }
                    else if (board[y][x] > 21)
                    {
                        bsboard[y][x] = -2;
                        break;
                    }
                    else if (board[y][x] > 0 && board[y][x] < 11)
                    {
                        bsboard[y][x] = 0;
                        break;
                    }
                }
                // right
                for (int x = x1 + 1; x < 8; x++)
                {
                    if (board[y1][x] == 0)
                    {
                        bsboard[y1][x] = -1;
                    }
                    else if (board[y1][x] > 21)
                    {
                        bsboard[y1][x] = -2;
                        break;
                    }
                    else if (board[y1][x] > 0 && board[y1][x] < 11)
                    {
                        bsboard[y1][x] = 0;
                        break;
                    }
                }

                // down
                for (int y = y1 + 1; y < 8; y++)
                {
                    if (board[y][x1] == 0)
                    {
                        bsboard[y][x1] = -1;
                    }
                    else if (board[y][x1] > 21)
                    {
                        bsboard[y][x1] = -2;
                        break;
                    }
                    else if (board[y][x1] > 0 && board[y][x1] < 11)
                    {
                        bsboard[y][x1] = 0;
                        break;
                    }
                }

                // left
                for (int x = x1 - 1; x > -1; x--)
                {
                    if (board[y1][x] == 0)
                    {
                        bsboard[y1][x] = -1;
                    }
                    else if (board[y1][x] > 21)
                    {
                        bsboard[y1][x] = -2;
                        break;
                    }
                    else if (board[y1][x] > 0 && board[y1][x] < 11)
                    {
                        bsboard[y1][x] = 0;
                        break;
                    }
                }

                // up
                for (int y = y1 - 1; y > -1; y--)
                {
                    if (board[y][x1] == 0)
                    {
                        bsboard[y][x1] = -1;
                    }
                    else if (board[y][x1] > 21)
                    {
                        bsboard[y][x1] = -2;
                        break;
                    }
                    else if (board[y][x1] > 0 && board[y][x1] < 11)
                    {
                        bsboard[y][x1] = 0;
                        break;
                    }
                }
            }
            // black rook
            else if (board[y1][x1] == 3 || board[y1][x1] == 8)
            {
                // right
                for (int x = x1 + 1; x < 8; x++)
                {
                    if (board[y1][x] == 0)
                    {
                        bsboard[y1][x] = -1;
                    }
                    else if (board[y1][x] > 21)
                    {
                        bsboard[y1][x] = -2;
                        break;
                    }
                    else if (board[y1][x] > 0 && board[y1][x] < 11)
                    {
                        bsboard[y1][x] = 0;
                        break;
                    }
                }

                // down
                for (int y = y1 + 1; y < 8; y++)
                {
                    if (board[y][x1] == 0)
                    {
                        bsboard[y][x1] = -1;
                    }
                    else if (board[y][x1] > 21)
                    {
                        bsboard[y][x1] = -2;
                        break;
                    }
                    else if (board[y][x1] > 0 && board[y][x1] < 11)
                    {
                        bsboard[y][x1] = 0;
                        break;
                    }
                }

                // left
                for (int x = x1 - 1; x > -1; x--)
                {
                    if (board[y1][x] == 0)
                    {
                        bsboard[y1][x] = -1;
                    }
                    else if (board[y1][x] > 21)
                    {
                        bsboard[y1][x] = -2;
                        break;
                    }
                    else if (board[y1][x] > 0 && board[y1][x] < 11)
                    {
                        bsboard[y1][x] = 0;
                        break;
                    }
                }

                // up
                for (int y = y1 - 1; y > -1; y--)
                {
                    if (board[y][x1] == 0)
                    {
                        bsboard[y][x1] = -1;
                    }
                    else if (board[y][x1] > 21)
                    {
                        bsboard[y][x1] = -2;
                        break;
                    }
                    else if (board[y][x1] > 0 && board[y][x1] < 11)
                    {
                        bsboard[y][x1] = 0;
                        break;
                    }
                }
            }
            // black bishop
            else if (board[y1][x1] == 4)
            {
                // right down
                for (int x = x1 + 1, y = y1 + 1; x < 8 && y < 8; x++, y++)
                {
                    if (board[y][x] == 0)
                    {
                        bsboard[y][x] = -1;
                    }
                    else if (board[y][x] > 21)
                    {
                        bsboard[y][x] = -2;
                        break;
                    }
                    else if (board[y][x] > 0 && board[y][x] < 11)
                    {
                        bsboard[y][x] = 0;
                        break;
                    }
                }
                // left down
                for (int x = x1 - 1, y = y1 + 1; x > -1 && y < 8; x--, y++)
                {
                    if (board[y][x] == 0)
                    {
                        bsboard[y][x] = -1;
                    }
                    else if (board[y][x] > 21)
                    {
                        bsboard[y][x] = -2;
                        break;
                    }
                    else if (board[y][x] > 0 && board[y][x] < 11)
                    {
                        bsboard[y][x] = 0;
                        break;
                    }
                }
                // right up
                for (int x = x1 + 1, y = y1 - 1; x < 8 && y > -1; x++, y--)
                {
                    if (board[y][x] == 0)
                    {
                        bsboard[y][x] = -1;
                    }
                    else if (board[y][x] > 21)
                    {
                        bsboard[y][x] = -2;
                        break;
                    }
                    else if (board[y][x] > 0 && board[y][x] < 11)
                    {
                        bsboard[y][x] = 0;
                        break;
                    }
                }
                // left up
                for (int x = x1 - 1, y = y1 - 1; x > -1 && y > -1; x--, y--)
                {
                    if (board[y][x] == 0)
                    {
                        bsboard[y][x] = -1;
                    }
                    else if (board[y][x] > 21)
                    {
                        bsboard[y][x] = -2;
                        break;
                    }
                    else if (board[y][x] > 0 && board[y][x] < 11)
                    {
                        bsboard[y][x] = 0;
                        break;
                    }
                }
            }
            // black knight
            else if (board[y1][x1] == 5)
            {
                int arr[8] = {-1, -2, +1, +2, -1, +2, +1, -2};
                for (int x = 0, y = 7; x < 8 && y > -1; x++, y--)
                {
                    // bsboard[i+arr[y]][x1+arr[x]] = -1;
                    if (!((y1 + arr[y] > 7) || (y1 + arr[y] < 0)))
                    {
                        if (!((x1 + arr[x] > 7) || (x1 + arr[x] < 0)))
                        {
                            if (board[y1 + arr[y]][x1 + arr[x]] == 0)
                            {
                                bsboard[y1 + arr[y]][x1 + arr[x]] = -1;
                            }
                            else if (board[y1 + arr[y]][x1 + arr[x]] > 21)
                            {
                                bsboard[y1 + arr[y]][x1 + arr[x]] = -2;
                            }
                            else if (board[y1 + arr[y]][x1 + arr[x]] > 0 && board[y1 + arr[y]][x1 + arr[x]] < 11)
                            {
                                bsboard[y1 + arr[y]][x1 + arr[x]] = 0;
                            }
                        }
                    }
                }
            }
            // black pawn
            else if (board[y1][x1] == 6)
            {
                for (int x = -1; x < 2; x += 2)
                {
                    if (!(((y1 + 1) > 7) || ((y1 + 1) < 0)))
                    {
                        if (!((x1 + x > 7) || (x1 + x < 0)))
                        {
                            if (board[y1 + 1][x1 + x] > 11)
                            {
                                bsboard[y1 + 1][x1 + x] = -1;
                            }
                            else if (board[y1][x1 + x] == 30)
                            {
                                bsboard[y1 + 1][x1 + x] = -1;
                                if (x1 + x == x2)
                                {
                                    addEntity(board, y1, x1 + x, 0);
                                }
                            }
                        }
                    }
                }
                if (board[y1 + 1][x1] == 0 && (y1 + 1 < 8 && y1 + 1 > -1))
                {
                    bsboard[y1 + 1][x1] = -1;
                }
            }
            else if (board[y1][x1] == 9)
            {
                for (int x = -1; x < 2; x += 2)
                {
                    if (!(((y1 + 1) > 7) || ((y1 + 1) < 0)))
                    {
                        if (!((x1 + x > 7) || (x1 + x < 0)))
                        {
                            if ((board[y1 + 1][x1 + x] > 11))
                            {
                                bsboard[y1 + 1][x1 + x] = -1;
                            }
                        }
                    }
                }
                for (int y = 1; y < 3; y++)
                {
                    if (board[y1 + y][x1] == 0 && (y1 + y < 8 && y1 + y > -1))
                    {
                        bsboard[y1 + y][x1] = -1;
                    }
                }
            }
        }
        // white pieces

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j] > 11)
                {
                    if (board[i][j] == 21 || board[i][j] == 27)
                    {
                        for (int y = -1; y < 2; y++)
                        {
                            for (int x = -1; x < 2; x++)
                            {
                                if (!((i + y > 7) || (i + y < 0)))
                                {
                                    if (!((j + x > 7) || (j + x < 0)))
                                    {
                                        wsboard[i + y][j + x] = -1;
                                    }
                                }
                            }
                        }
                    }
                    // white queen
                    else if (board[i][j] == 22)
                    {
                        // right down
                        for (int x = j + 1, y = i + 1; x < 8 && y < 8; x++, y++)
                        {
                            if (board[y][x] == 0)
                            {
                                wsboard[y][x] = -1;
                            }
                            else if (board[y][x] > 0)
                            {
                                wsboard[y][x] = -1;
                                break;
                            }
                        }
                        // left down
                        for (int x = j - 1, y = i + 1; x > -1 && y < 8; x--, y++)
                        {
                            if (board[y][x] == 0)
                            {
                                wsboard[y][x] = -1;
                            }
                            else if (board[y][x] > 0)
                            {
                                wsboard[y][x] = -1;
                                break;
                            }
                        }
                        // right up
                        for (int x = j + 1, y = i - 1; x < 8 && y > -1; x++, y--)
                        {
                            if (board[y][x] == 0)
                            {
                                wsboard[y][x] = -1;
                            }
                            else if (board[y][x] > 0)
                            {
                                wsboard[y][x] = -1;
                                break;
                            }
                        }
                        // left up
                        for (int x = j - 1, y = i - 1; x > -1 && y > -1; x--, y--)
                        {
                            if (board[y][x] == 0)
                            {
                                wsboard[y][x] = -1;
                            }
                            else if (board[y][x] > 0)
                            {
                                wsboard[y][x] = -1;
                                break;
                            }
                        }
                        // right
                        for (int x = j + 1; x < 8; x++)
                        {
                            if (board[i][x] == 0)
                            {
                                wsboard[i][x] = -1;
                            }
                            else if (board[i][x] > 0)
                            {
                                wsboard[i][x] = -1;
                                break;
                            }
                        }

                        // down
                        for (int y = i + 1; y < 8; y++)
                        {
                            if (board[y][j] == 0)
                            {
                                wsboard[y][j] = -1;
                            }
                            else if (board[y][j] > 0)
                            {
                                wsboard[y][j] = -1;
                                break;
                            }
                        }

                        // left
                        for (int x = j - 1; x > -1; x--)
                        {
                            if (board[i][x] == 0)
                            {
                                wsboard[i][x] = -1;
                            }
                            else if (board[i][x] > 0)
                            {
                                wsboard[i][x] = -1;
                                break;
                            }
                        }

                        // up
                        for (int y = i - 1; y > -1; y--)
                        {
                            if (board[y][j] == 0)
                            {
                                wsboard[y][j] = -1;
                            }
                            else if (board[y][j] > 0)
                            {
                                wsboard[y][j] = -1;
                                break;
                            }
                        }
                    }
                    // white rook
                    else if (board[i][j] == 23 || board[i][j] == 28)
                    {
                        // right
                        for (int x = j + 1; x < 8; x++)
                        {
                            if (board[i][x] == 0)
                            {
                                wsboard[i][x] = -1;
                            }
                            else if (board[i][x] > 0)
                            {
                                wsboard[i][x] = -1;
                                break;
                            }
                        }

                        // down
                        for (int y = i + 1; y < 8; y++)
                        {
                            if (board[y][j] == 0)
                            {
                                wsboard[y][j] = -1;
                            }
                            else if (board[y][j] > 0)
                            {
                                wsboard[y][j] = -1;
                                break;
                            }
                        }

                        // left
                        for (int x = j - 1; x > -1; x--)
                        {
                            if (board[i][x] == 0)
                            {
                                wsboard[i][x] = -1;
                            }
                            else if (board[i][x] > 0)
                            {
                                wsboard[i][x] = -1;
                                break;
                            }
                        }

                        // up
                        for (int y = i - 1; y > -1; y--)
                        {
                            if (board[y][j] == 0)
                            {
                                wsboard[y][j] = -1;
                            }
                            else if (board[y][j] > 0)
                            {
                                wsboard[y][j] = -1;
                                break;
                            }
                        }
                    }
                    // white bishop
                    else if (board[i][j] == 24)
                    {
                        // right down
                        for (int x = j + 1, y = i + 1; x < 8 && y < 8; x++, y++)
                        {
                            if (board[y][x] == 0)
                            {
                                wsboard[y][x] = -1;
                            }
                            else if (board[y][x] > 0)
                            {
                                wsboard[y][x] = -1;
                                break;
                            }
                        }
                        // left down
                        for (int x = j - 1, y = i + 1; x > -1 && y < 8; x--, y++)
                        {
                            if (board[y][x] == 0)
                            {
                                wsboard[y][x] = -1;
                            }
                            else if (board[y][x] > 0)
                            {
                                wsboard[y][x] = -1;
                                break;
                            }
                        }
                        // right up
                        for (int x = j + 1, y = i - 1; x < 8 && y > -1; x++, y--)
                        {
                            if (board[y][x] == 0)
                            {
                                wsboard[y][x] = -1;
                            }
                            else if (board[y][x] > 0)
                            {
                                wsboard[y][x] = -1;
                                break;
                            }
                        }
                        // left up
                        for (int x = j - 1, y = i - 1; x > -1 && y > -1; x--, y--)
                        {
                            if (board[y][x] == 0)
                            {
                                wsboard[y][x] = -1;
                            }
                            else if (board[y][x] > 0)
                            {
                                wsboard[y][x] = -1;
                                break;
                            }
                        }
                    }
                    // white knight
                    else if (board[i][j] == 25)
                    {
                        int arr[8] = {-1, -2, +1, +2, -1, +2, +1, -2};
                        for (int x = 0, y = 7; x < 8 && y > -1; x++, y--)
                        {
                            // wsboard[i+arr[y]][j+arr[x]] = -1;
                            if (!((i + arr[y] > 7) || (i + arr[y] < 0)))
                            {
                                if (!((j + arr[x] > 7) || (j + arr[x] < 0)))
                                {
                                    wsboard[i + arr[y]][j + arr[x]] = -1;
                                }
                            }
                        }
                    }
                    // white pawn
                    else if (board[i][j] == 26)
                    {
                        for (int x = -1; x < 2; x += 2)
                        {
                            if (!(((i - 1) > 7) || ((i - 1) < 0)))
                            {
                                if (!((j + x > 7) || (j + x < 0)))
                                {
                                    wsboard[i - 1][j + x] = -1;
                                }
                            }
                        }
                    }
                }
            }
        }

        if ((board[y1][x1] == 1 || board[y1][x1] == 7) && bsboard[y2][x2] < 0)
        {
            if (wsboard[y2][x2] >= 0)
            {
                retVal = 1;
            }
            else if (bsboard[y2][x2] < 0)
            {
                retVal = -1;
            }
        }
        else if (board[y1][x1] == 7 && y2 < 0 && x2 < 0)
        {
            int count = 0;
            if (x2 == -10)
            {
                for (int kk = x1 + 1; kk < 8; kk++)
                {
                    if (board[y1][kk] == 0)
                    {
                        count++;
                    }
                }
                if (board[y1][7] == 8)
                {
                    if (count == 2)
                    {
                        retVal = 1;
                        return retVal;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
            else if (x2 == -20)
            {
                for (int kk = x1 - 1; kk > 0; kk--)
                {
                    if (board[y1][kk] == 0)
                    {
                        count++;
                    }
                }
                if (board[y1][0] == 8)
                {
                    if (count == 3)
                    {
                        retVal = 1;
                        return retVal;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
        }
        else if (bsboard[y2][x2] < 0)
        {
            retVal = 1;
        }
    }
    // white turn
    else if (turn == 0)
    {
        if (board[y1][x1] > 11)
        {
            // white king
            if (board[y1][x1] == 21 || board[y1][x1] == 27)
            {
                for (int y = -1; y < 2; y++)
                {
                    for (int x = -1; x < 2; x++)
                    {
                        if (!((y1 + y > 7) || (y1 + y < 0)))
                        {
                            if (!((x1 + x > 7) || (x1 + x < 0)))
                            {
                                if (!(board[y1 + y][x1 + x] > 0 && board[y1 + y][x1 + x] < 11))
                                {
                                    wsboard[y1 + y][x1 + x] = -1;
                                }
                            }
                        }
                    }
                }
            }
            // white queen
            else if (board[y1][x1] == 22)
            {
                // right down
                for (int x = x1 + 1, y = y1 + 1; x < 8 && y < 8; x++, y++)
                {
                    if (board[y][x] == 0)
                    {
                        wsboard[y][x] = -1;
                    }
                    else if (board[y][x] > 0 && board[y][x] < 11)
                    {
                        wsboard[y][x] = -2;
                        break;
                    }
                    else if (board[y][x] > 21)
                    {
                        wsboard[y][x] = 0;
                        break;
                    }
                }
                // left down
                for (int x = x1 - 1, y = y1 + 1; x > -1 && y < 8; x--, y++)
                {
                    if (board[y][x] == 0)
                    {
                        wsboard[y][x] = -1;
                    }
                    else if (board[y][x] > 0 && board[y][x] < 11)
                    {
                        wsboard[y][x] = -2;
                        break;
                    }
                    else if (board[y][x] > 21)
                    {
                        wsboard[y][x] = 0;
                        break;
                    }
                }
                // right up
                for (int x = x1 + 1, y = y1 - 1; x < 8 && y > -1; x++, y--)
                {
                    if (board[y][x] == 0)
                    {
                        wsboard[y][x] = -1;
                    }
                    else if (board[y][x] > 0 && board[y][x] < 11)
                    {
                        wsboard[y][x] = -2;
                        break;
                    }
                    else if (board[y][x] > 21)
                    {
                        wsboard[y][x] = 0;
                        break;
                    }
                }
                // left up
                for (int x = x1 - 1, y = y1 - 1; x > -1 && y > -1; x--, y--)
                {
                    if (board[y][x] == 0)
                    {
                        wsboard[y][x] = -1;
                    }
                    else if (board[y][x] > 0 && board[y][x] < 11)
                    {
                        wsboard[y][x] = -2;
                        break;
                    }
                    else if (board[y][x] > 21)
                    {
                        wsboard[y][x] = 0;
                        break;
                    }
                }
                // right
                for (int x = x1 + 1; x < 8; x++)
                {
                    if (board[y1][x] == 0)
                    {
                        wsboard[y1][x] = -1;
                    }
                    else if (board[y1][x] > 0 && board[y1][x] < 11)
                    {
                        wsboard[y1][x] = -2;
                        break;
                    }
                    else if (board[y1][x] > 21)
                    {
                        wsboard[y1][x] = 0;
                        break;
                    }
                }

                // down
                for (int y = y1 + 1; y < 8; y++)
                {
                    if (board[y][x1] == 0)
                    {
                        wsboard[y][x1] = -1;
                    }
                    else if (board[y][x1] > 0 && board[y][x1] < 11)
                    {
                        wsboard[y][x1] = -2;
                        break;
                    }
                    else if (board[y][x1] > 21)
                    {
                        wsboard[y][x1] = 0;
                        break;
                    }
                }

                // left
                for (int x = x1 - 1; x > -1; x--)
                {
                    if (board[y1][x] == 0)
                    {
                        wsboard[y1][x] = -1;
                    }
                    else if (board[y1][x] > 0 && board[y1][x] < 11)
                    {
                        wsboard[y1][x] = -2;
                        break;
                    }
                    else if (board[y1][x] > 21)
                    {
                        wsboard[y1][x] = 0;
                        break;
                    }
                }

                // up
                for (int y = y1 - 1; y > -1; y--)
                {
                    if (board[y][x1] == 0)
                    {
                        wsboard[y][x1] = -1;
                    }
                    else if (board[y][x1] > 0 && board[y][x1] < 11)
                    {
                        wsboard[y][x1] = -2;
                        break;
                    }
                    else if (board[y][x1] > 21)
                    {
                        wsboard[y][x1] = 0;
                        break;
                    }
                }
            }
            // white rook
            else if (board[y1][x1] == 23 || board[y1][x1] == 28)
            {
                // right
                for (int x = x1 + 1; x < 8; x++)
                {
                    if (board[y1][x] == 0)
                    {
                        wsboard[y1][x] = -1;
                    }
                    else if (board[y1][x] > 0 && board[y1][x] < 11)
                    {
                        wsboard[y1][x] = -2;
                        break;
                    }
                    else if (board[y1][x] > 21)
                    {
                        wsboard[y1][x] = 0;
                        break;
                    }
                }

                // down
                for (int y = y1 + 1; y < 8; y++)
                {
                    if (board[y][x1] == 0)
                    {
                        wsboard[y][x1] = -1;
                    }
                    else if (board[y][x1] > 0 && board[y][x1] < 11)
                    {
                        wsboard[y][x1] = -2;
                        break;
                    }
                    else if (board[y][x1] > 21)
                    {
                        wsboard[y][x1] = 0;
                        break;
                    }
                }

                // left
                for (int x = x1 - 1; x > -1; x--)
                {
                    if (board[y1][x] == 0)
                    {
                        wsboard[y1][x] = -1;
                    }
                    else if (board[y1][x] > 21)
                    {
                        wsboard[y1][x] = -2;
                        break;
                    }
                    else if (board[y1][x] > 0 && board[y1][x] < 11)
                    {
                        wsboard[y1][x] = 0;
                        break;
                    }
                }

                // up
                for (int y = y1 - 1; y > -1; y--)
                {
                    if (board[y][x1] == 0)
                    {
                        wsboard[y][x1] = -1;
                    }
                    else if (board[y][x1] > 0 && board[y][x1] < 11)
                    {
                        wsboard[y][x1] = -2;
                        break;
                    }
                    else if (board[y][x1] > 21)
                    {
                        wsboard[y][x1] = 0;
                        break;
                    }
                }
            }
            // white bishop
            else if (board[y1][x1] == 24)
            {
                // right down
                for (int x = x1 + 1, y = y1 + 1; x < 8 && y < 8; x++, y++)
                {
                    if (board[y][x] == 0)
                    {
                        wsboard[y][x] = -1;
                    }
                    else if (board[y][x] > 0 && board[y][x] < 11)
                    {
                        wsboard[y][x] = -2;
                        break;
                    }
                    else if (board[y][x] > 21)
                    {
                        wsboard[y][x] = 0;
                        break;
                    }
                }
                // left down
                for (int x = x1 - 1, y = y1 + 1; x > -1 && y < 8; x--, y++)
                {
                    if (board[y][x] == 0)
                    {
                        wsboard[y][x] = -1;
                    }
                    else if (board[y][x] > 0 && board[y][x] < 11)
                    {
                        wsboard[y][x] = -2;
                        break;
                    }
                    else if (board[y][x] > 21)
                    {
                        wsboard[y][x] = 0;
                        break;
                    }
                }
                // right up
                for (int x = x1 + 1, y = y1 - 1; x < 8 && y > -1; x++, y--)
                {
                    if (board[y][x] == 0)
                    {
                        wsboard[y][x] = -1;
                    }
                    else if (board[y][x] > 0 && board[y][x] < 11)
                    {
                        wsboard[y][x] = -2;
                        break;
                    }
                    else if (board[y][x] > 21)
                    {
                        wsboard[y][x] = 0;
                        break;
                    }
                }
                // left up
                for (int x = x1 - 1, y = y1 - 1; x > -1 && y > -1; x--, y--)
                {
                    if (board[y][x] == 0)
                    {
                        wsboard[y][x] = -1;
                    }
                    else if (board[y][x] > 0 && board[y][x] < 11)
                    {
                        wsboard[y][x] = -2;
                        break;
                    }
                    else if (board[y][x] > 21)
                    {
                        wsboard[y][x] = 0;
                        break;
                    }
                }
            }
            // white knight
            else if (board[y1][x1] == 25)
            {
                int arr[8] = {-1, -2, +1, +2, -1, +2, +1, -2};
                for (int x = 0, y = 7; x < 8 && y > -1; x++, y--)
                {
                    // wsboard[i+arr[y]][x1+arr[x]] = -1;
                    if (!((y1 + arr[y] > 7) || (y1 + arr[y] < 0)))
                    {
                        if (!((x1 + arr[x] > 7) || (x1 + arr[x] < 0)))
                        {
                            if (board[y1 + arr[y]][x1 + arr[x]] == 0)
                            {
                                wsboard[y1 + arr[y]][x1 + arr[x]] = -1;
                            }
                            else if (board[y1 + arr[y]][x1 + arr[x]] > 0 && board[y1 + arr[y]][x1 + arr[x]] < 11)
                            {
                                wsboard[y1 + arr[y]][x1 + arr[x]] = -2;
                            }
                            else if (board[y1 + arr[y]][x1 + arr[x]] > 21)
                            {
                                wsboard[y1 + arr[y]][x1 + arr[x]] = 0;
                            }
                        }
                    }
                }
            }
            // white pawn
            else if (board[y1][x1] == 26)
            {
                for (int x = -1; x < 2; x += 2)
                {
                    if (!(((y1 - 1) > 7) || ((y1 - 1) < 0)))
                    {
                        if (!((x1 + x > 7) || (x1 + x < 0)))
                        {
                            if ((board[y1 - 1][x1 + x] < 10 && board[y1 - 1][x1 + x] > 0))
                            {
                                wsboard[y1 - 1][x1 + x] = -1;
                            }
                            else if (board[y1][x1 + x] == 10)
                            {
                                wsboard[y1 - 1][x1 + x] = -1;
                                if (x1 + x == x2)
                                {
                                    addEntity(board, y1, x1 + x, 0);
                                }
                            }
                        }
                    }
                }
                if (board[y1 - 1][x1] == 0 && (y1 - 1 > -1))
                {
                    wsboard[y1 - 1][x1] = -1;
                }
            }
            else if (board[y1][x1] == 29)
            {
                for (int x = -1; x < 2; x += 2)
                {
                    if (!(((y1 - 1) > 7) || ((y1 - 1) < 0)))
                    {
                        if (!((x1 + x > 7) || (x1 + x < 0)))
                        {
                            if ((board[y1 - 1][x1 + x] < 11 && board[y1 - 1][x1 + x] > 0))
                            {
                                wsboard[y1 - 1][x1 + x] = -1;
                            }
                        }
                    }
                }
                for (int y = 1; y < 3; y++)
                {
                    if (board[y1 - y][x1] == 0 && (y1 - y < 8 && y1 - y > -1))
                    {
                        wsboard[y1 - y][x1] = -1;
                    }
                }
            }
        }
        // black pieces
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j] > 0 && board[i][j] < 11)
                {
                    if (board[i][j] == 1 || board[i][j] == 7)
                    {
                        for (int y = -1; y < 2; y++)
                        {
                            for (int x = -1; x < 2; x++)
                            {
                                if (!((i + y > 7) || (i + y < 0)))
                                {
                                    if (!((j + x > 7) || (j + x < 0)))
                                    {
                                        bsboard[i + y][j + x] = -1;
                                    }
                                }
                            }
                        }
                    }
                    // black queen
                    else if (board[i][j] == 2)
                    {
                        // right down
                        for (int x = j + 1, y = i + 1; x < 8 && y < 8; x++, y++)
                        {
                            if (board[y][x] == 0)
                            {
                                bsboard[y][x] = -1;
                            }
                            else if (board[y][x] > 0)
                            {
                                bsboard[y][x] = -1;
                                break;
                            }
                        }
                        // left down
                        for (int x = j - 1, y = i + 1; x > -1 && y < 8; x--, y++)
                        {
                            if (board[y][x] == 0)
                            {
                                bsboard[y][x] = -1;
                            }
                            else if (board[y][x] > 0)
                            {
                                bsboard[y][x] = -1;
                                break;
                            }
                        }
                        // right up
                        for (int x = j + 1, y = i - 1; x < 8 && y > -1; x++, y--)
                        {
                            if (board[y][x] == 0)
                            {
                                bsboard[y][x] = -1;
                            }
                            else if (board[y][x] > 0)
                            {
                                bsboard[y][x] = -1;
                                break;
                            }
                        }
                        // left up
                        for (int x = j - 1, y = i - 1; x > -1 && y > -1; x--, y--)
                        {
                            if (board[y][x] == 0)
                            {
                                bsboard[y][x] = -1;
                            }
                            else if (board[y][x] > 0)
                            {
                                bsboard[y][x] = -1;
                                break;
                            }
                        }
                        // right
                        for (int x = j + 1; x < 8; x++)
                        {
                            if (board[i][x] == 0)
                            {
                                bsboard[i][x] = -1;
                            }
                            else if (board[i][x] > 0)
                            {
                                bsboard[i][x] = -1;
                                break;
                            }
                        }

                        // down
                        for (int y = i + 1; y < 8; y++)
                        {
                            if (board[y][j] == 0)
                            {
                                bsboard[y][j] = -1;
                            }
                            else if (board[y][j] > 0)
                            {
                                bsboard[y][j] = -1;
                                break;
                            }
                        }

                        // left
                        for (int x = j - 1; x > -1; x--)
                        {
                            if (board[i][x] == 0)
                            {
                                bsboard[i][x] = -1;
                            }
                            else if (board[i][x] > 0)
                            {
                                bsboard[i][x] = -1;
                                break;
                            }
                        }

                        // up
                        for (int y = i - 1; y > -1; y--)
                        {
                            if (board[y][j] == 0)
                            {
                                bsboard[y][j] = -1;
                            }
                            else if (board[y][j] > 0)
                            {
                                bsboard[y][j] = -1;
                                break;
                            }
                        }
                    }
                    // black rook
                    else if (board[i][j] == 3 || board[i][j] == 8)
                    {
                        // right
                        for (int x = j + 1; x < 8; x++)
                        {
                            if (board[i][x] == 0)
                            {
                                bsboard[i][x] = -1;
                            }
                            else if (board[i][x] > 0)
                            {
                                bsboard[i][x] = -1;
                                break;
                            }
                        }

                        // down
                        for (int y = i + 1; y < 8; y++)
                        {
                            if (board[y][j] == 0)
                            {
                                bsboard[y][j] = -1;
                            }
                            else if (board[y][j] > 0)
                            {
                                bsboard[y][j] = -1;
                                break;
                            }
                        }

                        // left
                        for (int x = j - 1; x > -1; x--)
                        {
                            if (board[i][x] == 0)
                            {
                                bsboard[i][x] = -1;
                            }
                            else if (board[i][x] > 0)
                            {
                                bsboard[i][x] = -1;
                                break;
                            }
                        }

                        // up
                        for (int y = i - 1; y > -1; y--)
                        {
                            if (board[y][j] == 0)
                            {
                                bsboard[y][j] = -1;
                            }
                            else if (board[y][j] > 0)
                            {
                                bsboard[y][j] = -1;
                                break;
                            }
                        }
                    }
                    // black bishop
                    else if (board[i][j] == 4)
                    {
                        // right down
                        for (int x = j + 1, y = i + 1; x < 8 && y < 8; x++, y++)
                        {
                            if (board[y][x] == 0)
                            {
                                bsboard[y][x] = -1;
                            }
                            else if (board[y][x] > 0)
                            {
                                bsboard[y][x] = -1;
                                break;
                            }
                        }
                        // left down
                        for (int x = j - 1, y = i + 1; x > -1 && y < 8; x--, y++)
                        {
                            if (board[y][x] == 0)
                            {
                                bsboard[y][x] = -1;
                            }
                            else if (board[y][x] > 0)
                            {
                                bsboard[y][x] = -1;
                                break;
                            }
                        }
                        // right up
                        for (int x = j + 1, y = i - 1; x < 8 && y > -1; x++, y--)
                        {
                            if (board[y][x] == 0)
                            {
                                bsboard[y][x] = -1;
                            }
                            else if (board[y][x] > 0)
                            {
                                bsboard[y][x] = -1;
                                break;
                            }
                        }
                        // left up
                        for (int x = j - 1, y = i - 1; x > -1 && y > -1; x--, y--)
                        {
                            if (board[y][x] == 0)
                            {
                                bsboard[y][x] = -1;
                            }
                            else if (board[y][x] > 0)
                            {
                                bsboard[y][x] = -1;
                                break;
                            }
                        }
                    }
                    // black knight
                    else if (board[i][j] == 5)
                    {
                        int arr[8] = {-1, -2, +1, +2, -1, +2, +1, -2};
                        for (int x = 0, y = 7; x < 8 && y > -1; x++, y--)
                        {
                            // bsboard[i+arr[y]][j+arr[x]] = -1;
                            if (!((i + arr[y] > 7) || (i + arr[y] < 0)))
                            {
                                if (!((j + arr[x] > 7) || (j + arr[x] < 0)))
                                {
                                    bsboard[i + arr[y]][j + arr[x]] = -1;
                                }
                            }
                        }
                    }
                    // black pawn
                    else if (board[i][j] == 6)
                    {
                        for (int x = -1; x < 2; x += 2)
                        {
                            if (!(((i - 1) > 7) || ((i - 1) < 0)))
                            {
                                if (!((j + x > 7) || (j + x < 0)))
                                {
                                    bsboard[i + 1][j + x] = -1;
                                }
                            }
                        }
                    }
                }
            }
        }
        if ((board[y1][x1] == 21 || board[y1][x1] == 27) && wsboard[y2][x2] < 0)
        {
            if (bsboard[y2][x2] >= 0)
            {
                retVal = 1;
            }
            else
            {
            }
        }
        else if (wsboard[y2][x2] < 0)
        {
            retVal = 1;
        }
        if (board[y1][x1] == 27 && y2 < 0 && x2 < 20)
        {
            int count = 0;
            if (x2 == -10)
            {
                for (int kk = x1 + 1; kk < 8; kk++)
                {
                    if (board[y1][kk] == 0)
                    {
                        count++;
                    }
                }
                if (board[y1][7] == 28)
                {
                    if (count == 2)
                    {
                        retVal = 1;
                        return retVal;
                    }
                }
            }
            else if (x2 == -20)
            {
                for (int kk = x1 - 1; kk > -1; kk--)
                {
                    if (board[y1][kk] == 0)
                    {
                        count++;
                    }
                }
                if (board[y1][0] == 28)
                {
                    if (count == 3)
                    {
                        retVal = 1;
                        return retVal;
                    }
                }
            }
        }
    }
    if (x1 == x2 && y1 == y2)
    {
        retVal = 0;
    }
    return retVal;
}
int converter(int *y1, int *x1, int *y2, int *x2, char *pos, char *mov)
{
    if (strcmp(pos, "h1") == 0)
    {
        *y1 = 7; // 7
        *x1 = 7; // 7
    }
    else if (strcmp(pos, "h2") == 0)
    {
        *y1 = 6; // 6
        *x1 = 7; // 7
    }
    else if (strcmp(pos, "h3") == 0)
    {
        *y1 = 5; // 5
        *x1 = 7; // 7
    }
    else if (strcmp(pos, "h4") == 0)
    {
        *y1 = 4; // 4
        *x1 = 7; // 7
    }
    else if (strcmp(pos, "h5") == 0)
    {
        *y1 = 3; // 3
        *x1 = 7; // 7
    }
    else if (strcmp(pos, "h6") == 0)
    {
        *y1 = 2; // 2
        *x1 = 7; // 7
    }
    else if (strcmp(pos, "h7") == 0)
    {
        *y1 = 1; // 1
        *x1 = 7; // 7
    }
    else if (strcmp(pos, "h8") == 0)
    {
        *y1 = 0; // 0
        *x1 = 7; // 7
    }
    //
    else if (strcmp(pos, "g1") == 0)
    {
        *y1 = 7; // 7
        *x1 = 6; // 6
    }
    else if (strcmp(pos, "g2") == 0)
    {
        *y1 = 6; // 6
        *x1 = 6; // 6
    }
    else if (strcmp(pos, "g3") == 0)
    {
        *y1 = 5; // 5
        *x1 = 6; // 6
    }
    else if (strcmp(pos, "g4") == 0)
    {
        *y1 = 4; // 4
        *x1 = 6; // 6
    }
    else if (strcmp(pos, "g5") == 0)
    {
        *y1 = 3; // 3
        *x1 = 6; // 6
    }
    else if (strcmp(pos, "g6") == 0)
    {
        *y1 = 2; // 2
        *x1 = 6; // 6
    }
    else if (strcmp(pos, "g7") == 0)
    {
        *y1 = 1; // 1
        *x1 = 6; // 6
    }
    else if (strcmp(pos, "g8") == 0)
    {
        *y1 = 0; // 0
        *x1 = 6; // 6
    }
    //
    else if (strcmp(pos, "f1") == 0)
    {
        *y1 = 7; // 7
        *x1 = 5; // 5
    }
    else if (strcmp(pos, "f2") == 0)
    {
        *y1 = 6; // 6
        *x1 = 5; // 5
    }
    else if (strcmp(pos, "f3") == 0)
    {
        *y1 = 5; // 5
        *x1 = 5; // 5
    }
    else if (strcmp(pos, "f4") == 0)
    {
        *y1 = 4; // 4
        *x1 = 5; // 5
    }
    else if (strcmp(pos, "f5") == 0)
    {
        *y1 = 3; // 3
        *x1 = 5; // 5
    }
    else if (strcmp(pos, "f6") == 0)
    {
        *y1 = 2; // 2
        *x1 = 5; // 5
    }
    else if (strcmp(pos, "f7") == 0)
    {
        *y1 = 1; // 1
        *x1 = 5; // 5
    }
    else if (strcmp(pos, "f8") == 0)
    {
        *y1 = 0; // 0
        *x1 = 5; // 5
    }
    //
    else if (strcmp(pos, "e1") == 0)
    {
        *y1 = 7; // 7
        *x1 = 4; // 4
    }
    else if (strcmp(pos, "e2") == 0)
    {
        *y1 = 6; // 6
        *x1 = 4; // 4
    }
    else if (strcmp(pos, "e3") == 0)
    {
        *y1 = 5; // 5
        *x1 = 4; // 4
    }
    else if (strcmp(pos, "e4") == 0)
    {
        *y1 = 4; // 4
        *x1 = 4; // 4
    }
    else if (strcmp(pos, "e5") == 0)
    {
        *y1 = 3; // 3
        *x1 = 4; // 4
    }
    else if (strcmp(pos, "e6") == 0)
    {
        *y1 = 2; // 2
        *x1 = 4; // 4
    }
    else if (strcmp(pos, "e7") == 0)
    {
        *y1 = 1; // 1
        *x1 = 4; // 4
    }
    else if (strcmp(pos, "e8") == 0)
    {
        *y1 = 0; // 0
        *x1 = 4; // 4
    }
    //
    else if (strcmp(pos, "d1") == 0)
    {
        *y1 = 7; // 7
        *x1 = 3; // 3
    }
    else if (strcmp(pos, "d2") == 0)
    {
        *y1 = 6; // 6
        *x1 = 3; // 3
    }
    else if (strcmp(pos, "d3") == 0)
    {
        *y1 = 5; // 5
        *x1 = 3; // 3
    }
    else if (strcmp(pos, "d4") == 0)
    {
        *y1 = 4; // 4
        *x1 = 3; // 3
    }
    else if (strcmp(pos, "d5") == 0)
    {
        *y1 = 3; // 3
        *x1 = 3; // 3
    }
    else if (strcmp(pos, "d6") == 0)
    {
        *y1 = 2; // 2
        *x1 = 3; // 3
    }
    else if (strcmp(pos, "d7") == 0)
    {
        *y1 = 1; // 1
        *x1 = 3; // 3
    }
    else if (strcmp(pos, "d8") == 0)
    {
        *y1 = 0; // 0
        *x1 = 3; // 3
    }
    //
    else if (strcmp(pos, "c1") == 0)
    {
        *y1 = 7; // 7
        *x1 = 2; // 2
    }
    else if (strcmp(pos, "c2") == 0)
    {
        *y1 = 6; // 6
        *x1 = 2; // 2
    }
    else if (strcmp(pos, "c3") == 0)
    {
        *y1 = 5; // 5
        *x1 = 2; // 2
    }
    else if (strcmp(pos, "c4") == 0)
    {
        *y1 = 4; // 4
        *x1 = 2; // 2
    }
    else if (strcmp(pos, "c5") == 0)
    {
        *y1 = 3; // 3
        *x1 = 2; // 2
    }
    else if (strcmp(pos, "c6") == 0)
    {
        *y1 = 2; // 2
        *x1 = 2; // 2
    }
    else if (strcmp(pos, "c7") == 0)
    {
        *y1 = 1; // 1
        *x1 = 2; // 2
    }
    else if (strcmp(pos, "c8") == 0)
    {
        *y1 = 0; // 0
        *x1 = 2; // 2
    }
    //
    else if (strcmp(pos, "b1") == 0)
    {
        *y1 = 7; // 7
        *x1 = 1; // 1
    }
    else if (strcmp(pos, "b2") == 0)
    {
        *y1 = 6; // 6
        *x1 = 1; // 1
    }
    else if (strcmp(pos, "b3") == 0)
    {
        *y1 = 5; // 5
        *x1 = 1; // 1
    }
    else if (strcmp(pos, "b4") == 0)
    {
        *y1 = 4; // 4
        *x1 = 1; // 1
    }
    else if (strcmp(pos, "b5") == 0)
    {
        *y1 = 3; // 3
        *x1 = 1; // 1
    }
    else if (strcmp(pos, "b6") == 0)
    {
        *y1 = 2; // 2
        *x1 = 1; // 1
    }
    else if (strcmp(pos, "b7") == 0)
    {
        *y1 = 1; // 1
        *x1 = 1; // 1
    }
    else if (strcmp(pos, "b8") == 0)
    {
        *y1 = 0; // 0
        *x1 = 1; // 1
    }
    //
    else if (strcmp(pos, "a1") == 0)
    {
        *y1 = 7; // 7
        *x1 = 0; // 0
    }
    else if (strcmp(pos, "a2") == 0)
    {
        *y1 = 6; // 6
        *x1 = 0; // 0
    }
    else if (strcmp(pos, "a3") == 0)
    {
        *y1 = 5; // 5
        *x1 = 0; // 0
    }
    else if (strcmp(pos, "a4") == 0)
    {
        *y1 = 4; // 4
        *x1 = 0; // 0
    }
    else if (strcmp(pos, "a5") == 0)
    {
        *y1 = 3; // 3
        *x1 = 0; // 0
    }
    else if (strcmp(pos, "a6") == 0)
    {
        *y1 = 2; // 2
        *x1 = 0; // 0
    }
    else if (strcmp(pos, "a7") == 0)
    {
        *y1 = 1; // 1
        *x1 = 0; // 0
    }
    else if (strcmp(pos, "a8") == 0)
    {
        *y1 = 0; // 0
        *x1 = 0; // 0
    }
    else
    {
        printf("Invalid position!\n");
        return 0;
    }
    // this is where the move converter is...
    if (strcmp(mov, "h1") == 0)
    {
        *y2 = 7; // 7
        *x2 = 7; // 7
    }
    else if (strcmp(mov, "h2") == 0)
    {
        *y2 = 6; // 6
        *x2 = 7; // 7
    }
    else if (strcmp(mov, "h3") == 0)
    {
        *y2 = 5; // 5
        *x2 = 7; // 7
    }
    else if (strcmp(mov, "h4") == 0)
    {
        *y2 = 4; // 4
        *x2 = 7; // 7
    }
    else if (strcmp(mov, "h5") == 0)
    {
        *y2 = 3; // 3
        *x2 = 7; // 7
    }
    else if (strcmp(mov, "h6") == 0)
    {
        *y2 = 2; // 2
        *x2 = 7; // 7
    }
    else if (strcmp(mov, "h7") == 0)
    {
        *y2 = 1; // 1
        *x2 = 7; // 7
    }
    else if (strcmp(mov, "h8") == 0)
    {
        *y2 = 0; // 0
        *x2 = 7; // 7
    }
    //
    else if (strcmp(mov, "g1") == 0)
    {
        *y2 = 7; // 7
        *x2 = 6; // 6
    }
    else if (strcmp(mov, "g2") == 0)
    {
        *y2 = 6; // 6
        *x2 = 6; // 6
    }
    else if (strcmp(mov, "g3") == 0)
    {
        *y2 = 5; // 5
        *x2 = 6; // 6
    }
    else if (strcmp(mov, "g4") == 0)
    {
        *y2 = 4; // 4
        *x2 = 6; // 6
    }
    else if (strcmp(mov, "g5") == 0)
    {
        *y2 = 3; // 3
        *x2 = 6; // 6
    }
    else if (strcmp(mov, "g6") == 0)
    {
        *y2 = 2; // 2
        *x2 = 6; // 6
    }
    else if (strcmp(mov, "g7") == 0)
    {
        *y2 = 1; // 1
        *x2 = 6; // 6
    }
    else if (strcmp(mov, "g8") == 0)
    {
        *y2 = 0; // 0
        *x2 = 6; // 6
    }
    //
    else if (strcmp(mov, "f1") == 0)
    {
        *y2 = 7; // 7
        *x2 = 5; // 5
    }
    else if (strcmp(mov, "f2") == 0)
    {
        *y2 = 6; // 6
        *x2 = 5; // 5
    }
    else if (strcmp(mov, "f3") == 0)
    {
        *y2 = 5; // 5
        *x2 = 5; // 5
    }
    else if (strcmp(mov, "f4") == 0)
    {
        *y2 = 4; // 4
        *x2 = 5; // 5
    }
    else if (strcmp(mov, "f5") == 0)
    {
        *y2 = 3; // 3
        *x2 = 5; // 5
    }
    else if (strcmp(mov, "f6") == 0)
    {
        *y2 = 2; // 2
        *x2 = 5; // 5
    }
    else if (strcmp(mov, "f7") == 0)
    {
        *y2 = 1; // 1
        *x2 = 5; // 5
    }
    else if (strcmp(mov, "f8") == 0)
    {
        *y2 = 0; // 0
        *x2 = 5; // 5
    }
    //
    else if (strcmp(mov, "e1") == 0)
    {
        *y2 = 7; // 7
        *x2 = 4; // 4
    }
    else if (strcmp(mov, "e2") == 0)
    {
        *y2 = 6; // 6
        *x2 = 4; // 4
    }
    else if (strcmp(mov, "e3") == 0)
    {
        *y2 = 5; // 5
        *x2 = 4; // 4
    }
    else if (strcmp(mov, "e4") == 0)
    {
        *y2 = 4; // 4
        *x2 = 4; // 4
    }
    else if (strcmp(mov, "e5") == 0)
    {
        *y2 = 3; // 3
        *x2 = 4; // 4
    }
    else if (strcmp(mov, "e6") == 0)
    {
        *y2 = 2; // 2
        *x2 = 4; // 4
    }
    else if (strcmp(mov, "e7") == 0)
    {
        *y2 = 1; // 1
        *x2 = 4; // 4
    }
    else if (strcmp(mov, "e8") == 0)
    {
        *y2 = 0; // 0
        *x2 = 4; // 4
    }
    //
    else if (strcmp(mov, "d1") == 0)
    {
        *y2 = 7; // 7
        *x2 = 3; // 3
    }
    else if (strcmp(mov, "d2") == 0)
    {
        *y2 = 6; // 6
        *x2 = 3; // 3
    }
    else if (strcmp(mov, "d3") == 0)
    {
        *y2 = 5; // 5
        *x2 = 3; // 3
    }
    else if (strcmp(mov, "d4") == 0)
    {
        *y2 = 4; // 4
        *x2 = 3; // 3
    }
    else if (strcmp(mov, "d5") == 0)
    {
        *y2 = 3; // 3
        *x2 = 3; // 3
    }
    else if (strcmp(mov, "d6") == 0)
    {
        *y2 = 2; // 2
        *x2 = 3; // 3
    }
    else if (strcmp(mov, "d7") == 0)
    {
        *y2 = 1; // 1
        *x2 = 3; // 3
    }
    else if (strcmp(mov, "d8") == 0)
    {
        *y2 = 0; // 0
        *x2 = 3; // 3
    }
    //
    else if (strcmp(mov, "c1") == 0)
    {
        *y2 = 7; // 7
        *x2 = 2; // 2
    }
    else if (strcmp(mov, "c2") == 0)
    {
        *y2 = 6; // 6
        *x2 = 2; // 2
    }
    else if (strcmp(mov, "c3") == 0)
    {
        *y2 = 5; // 5
        *x2 = 2; // 2
    }
    else if (strcmp(mov, "c4") == 0)
    {
        *y2 = 4; // 4
        *x2 = 2; // 2
    }
    else if (strcmp(mov, "c5") == 0)
    {
        *y2 = 3; // 3
        *x2 = 2; // 2
    }
    else if (strcmp(mov, "c6") == 0)
    {
        *y2 = 2; // 2
        *x2 = 2; // 2
    }
    else if (strcmp(mov, "c7") == 0)
    {
        *y2 = 1; // 1
        *x2 = 2; // 2
    }
    else if (strcmp(mov, "c8") == 0)
    {
        *y2 = 0; // 0
        *x2 = 2; // 2
    }
    //
    else if (strcmp(mov, "b1") == 0)
    {
        *y2 = 7; // 7
        *x2 = 1; // 1
    }
    else if (strcmp(mov, "b2") == 0)
    {
        *y2 = 6; // 6
        *x2 = 1; // 1
    }
    else if (strcmp(mov, "b3") == 0)
    {
        *y2 = 5; // 5
        *x2 = 1; // 1
    }
    else if (strcmp(mov, "b4") == 0)
    {
        *y2 = 4; // 4
        *x2 = 1; // 1
    }
    else if (strcmp(mov, "b5") == 0)
    {
        *y2 = 3; // 3
        *x2 = 1; // 1
    }
    else if (strcmp(mov, "b6") == 0)
    {
        *y2 = 2; // 2
        *x2 = 1; // 1
    }
    else if (strcmp(mov, "b7") == 0)
    {
        *y2 = 1; // 1
        *x2 = 1; // 1
    }
    else if (strcmp(mov, "b8") == 0)
    {
        *y2 = 0; // 0
        *x2 = 1; // 1
    }
    //
    else if (strcmp(mov, "a1") == 0)
    {
        *y2 = 7; // 7
        *x2 = 0; // 0
    }
    else if (strcmp(mov, "a2") == 0)
    {
        *y2 = 6; // 6
        *x2 = 0; // 0
    }
    else if (strcmp(mov, "a3") == 0)
    {
        *y2 = 5; // 5
        *x2 = 0; // 0
    }
    else if (strcmp(mov, "a4") == 0)
    {
        *y2 = 4; // 4
        *x2 = 0; // 0
    }
    else if (strcmp(mov, "a5") == 0)
    {
        *y2 = 3; // 3
        *x2 = 0; // 0
    }
    else if (strcmp(mov, "a6") == 0)
    {
        *y2 = 2; // 2
        *x2 = 0; // 0
    }
    else if (strcmp(mov, "a7") == 0)
    {
        *y2 = 1; // 1
        *x2 = 0; // 0
    }
    else if (strcmp(mov, "a8") == 0)
    {
        *y2 = 0; // 0
        *x2 = 0; // 0
    }
    else if (strcmp(mov, "000") == 0)
    {
        *y2 = -20;
        *x2 = -20;
    }
    else if (strcmp(mov, "00") == 0)
    {
        *y2 = -20;
        *x2 = -10;
    }
    else
    {
        printf("Invalid position!\n");
        return 0;
    }
    return 0;
}
void displayBoard(int board[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == 0)
            {
                printf(".");
            }
            else if (board[i][j] == 1)
            {
                printf("♚");
            }
            else if (board[i][j] == 2)
            {
                printf("♛");
            }
            else if (board[i][j] == 3)
            {
                printf("♜");
            }
            else if (board[i][j] == 4)
            {
                printf("♝");
            }
            else if (board[i][j] == 5)
            {
                printf("♞");
            }
            else if (board[i][j] == 6)
            {
                printf("♟︎");
            }
            else if (board[i][j] == 7)
            {
                printf("♚");
            }
            else if (board[i][j] == 8)
            {
                printf("♜");
            }
            else if (board[i][j] == 9)
            {
                printf("♟︎");
            }
            else if (board[i][j] == 10)
            {
                printf("♟︎");
            }
            else if (board[i][j] == 21)
            {
                printf("♔");
            }
            else if (board[i][j] == 22)
            {
                printf("♕");
            }
            else if (board[i][j] == 23)
            {
                printf("♖");
            }
            else if (board[i][j] == 24)
            {
                printf("♗");
            }
            else if (board[i][j] == 25)
            {
                printf("♘");
            }
            else if (board[i][j] == 26)
            {
                printf("♙");
            }
            else if (board[i][j] == 27)
            { // unmoved king
                printf("♔");
            }
            else if (board[i][j] == 28)
            { // unmoved rook
                printf("♖");
            }
            else if (board[i][j] == 29)
            { // unmoved pawn
                printf("♙");
            }
            else if (board[i][j] == 30)
            { // en passant pawn
                printf("♙");
            }
            printf("  ");
        }
        if (i == 0)
        {
            printf("8");
        }
        else if (i == 1)
        {
            printf("7");
        }
        else if (i == 2)
        {
            printf("6");
        }
        else if (i == 3)
        {
            printf("5");
        }
        else if (i == 4)
        {
            printf("4");
        }
        else if (i == 5)
        {
            printf("3");
        }
        else if (i == 6)
        {
            printf("2");
        }
        else if (i == 7)
        {
            printf("1");
        }
        printf("\n");
    }
    printf("a  b  c  d  e  f  g  h\n\n");
}
void initializeBoard(int board[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = 0;
        }
    }
    // 20 > are black's pieces
    // 20 < are white's pieces
    board[0][0] = 8;
    board[0][1] = 5;
    board[0][2] = 4;
    board[0][3] = 2;
    board[0][4] = 7;
    board[0][5] = 4;
    board[0][6] = 5;
    board[0][7] = 8;

    board[1][0] = 9;
    board[1][1] = 9;
    board[1][2] = 9;
    board[1][3] = 9;
    board[1][4] = 9;
    board[1][5] = 9;
    board[1][6] = 9;
    board[1][7] = 9;
    // White's board
    board[6][0] = 29;
    board[6][1] = 29;
    board[6][2] = 29;
    board[6][3] = 29;
    board[6][4] = 29;
    board[6][5] = 29;
    board[6][6] = 29;
    board[6][7] = 29;

    board[7][0] = 28;
    board[7][1] = 25;
    board[7][2] = 24;
    board[7][3] = 22;
    board[7][4] = 27;
    board[7][5] = 24;
    board[7][6] = 25;
    board[7][7] = 28;
}
int mateChecker(int board[8][8], int turn)
{
    int mate = 1;
    int dboard1[8][8];
    int dboard2[8][8];
    int nboard[8][8];
    int mboard[8][8];
    int check = 0;

    shadowBoardInit(board, nboard, mboard);
    if (turn == 0)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j] == 1 || board[i][j] == 7)
                {
                    check = nboard[i][j];
                    if (nboard[i][j] > 0)
                    {

                        goto ch;
                    }
                }
            }
        }
    }
    else if (turn == 1)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j] == 21 || board[i][j] == 27)
                {
                    check = mboard[i][j];
                    if (mboard[i][j] > 0)
                    {
                        goto ch;
                    }
                }
            }
        }
    }
ch:
    if (check < 0)
    {
        if (turn == 0)
        {
            for (int x1 = 0; x1 < 8; x1++)
            {
                for (int y1 = 0; y1 < 8; y1++)
                {
                    if (board[y1][x1] < 11 && board[y1][x1] > 0)
                        ;
                    {
                        for (int x2 = 0; x2 < 8; x2++)
                        {
                            for (int y2 = 0; y2 < 8; y2++)
                            {
                                if ((chShadowBoardInit(board, dboard1, dboard2, x1, y1, x2, y2, 1) == 1))
                                {
                                    if (shadowBoardChecker(board, x1, y1, x2, y2, 1) == 1)
                                    {
                                        mate = 0;
                                        goto ret;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else if (turn == 1)
        {
            for (int x1 = 0; x1 < 8; x1++)
            {
                for (int y1 = 0; y1 < 8; y1++)
                {
                    if (board[y1][x1] > 11)
                    {

                        for (int x2 = 0; x2 < 8; x2++)
                        {
                            for (int y2 = 0; y2 < 8; y2++)
                            {
                                if ((chShadowBoardInit(board, dboard2, dboard1, x1, y1, x2, y2, 0) == 1))
                                {
                                    if (shadowBoardChecker(board, x1, y1, x2, y2, 0) == 1)
                                    {
                                        mate = 0;
                                        goto ret;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    else if (check == 0)
    {
        mate = 2;
        if (turn == 0)
        {
            for (int x1 = 0; x1 < 8; x1++)
            {
                for (int y1 = 0; y1 < 8; y1++)
                {
                    if (board[y1][x1] < 11 && board[y1][x1] > 0)
                        ;
                    {
                        for (int x2 = 0; x2 < 8; x2++)
                        {
                            for (int y2 = 0; y2 < 8; y2++)
                            {
                                if ((chShadowBoardInit(board, dboard1, dboard2, x1, y1, x2, y2, 1) == 1))
                                {
                                    if ((shadowBoardChecker(board, x1, y1, x2, y2, 1) == 1))
                                    {
                                        mate = 0;
                                        goto ret;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else if (turn == 1)
        {
            for (int x1 = 0; x1 < 8; x1++)
            {
                for (int y1 = 0; y1 < 8; y1++)
                {
                    if (board[y1][x1] > 11)
                    {

                        for (int x2 = 0; x2 < 8; x2++)
                        {
                            for (int y2 = 0; y2 < 8; y2++)
                            {
                                if ((chShadowBoardInit(board, dboard2, dboard1, x1, y1, x2, y2, 0) == 1))
                                {
                                    if ((shadowBoardChecker(board, x1, y1, x2, y2, 0) == 1))
                                    {
                                        mate = 0;
                                        goto ret;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        mate = 0;
    }
ret:
    return mate;
}
void move(int board[8][8], int y1, int x1, int y2, int x2)
{
    int inv = 0;
    int tmp;
    if (y2 < 0 && x2 < 0)
    {
        if (board[y1][x1] == 7)
        {
            if (x2 == -10)
            {
                addEntity(board, 0, 4, 0);
                addEntity(board, 0, 7, 0);
                addEntity(board, 0, 6, 1);
                addEntity(board, 0, 5, 3);
            }
            if (x2 == -20)
            {
                addEntity(board, 0, 4, 0);
                addEntity(board, 0, 0, 0);
                addEntity(board, 0, 2, 1);
                addEntity(board, 0, 3, 3);
            }
        }
        else if (board[y1][x1] == 27)
        {
            if (x2 == -10)
            {
                addEntity(board, 7, 4, 0);
                addEntity(board, 7, 7, 0);
                addEntity(board, 7, 6, 21);
                addEntity(board, 7, 5, 23);
            }
            if (x2 == -20)
            {
                addEntity(board, 7, 4, 0);
                addEntity(board, 7, 0, 0);
                addEntity(board, 7, 2, 21);
                addEntity(board, 7, 3, 23);
            }
        }
        inv = 1;
    }
    if (board[y1][x1] == 9 && y2 - y1 == 2)
    {
        board[y1][x1] = 0;
        board[y2][x2] = 10;
        inv = 1;
    }
    else if (board[y1][x1] == 29 && y1 - y2 == 2)
    {
        board[y1][x1] = 0;
        board[y2][x2] = 30;
        inv = 1;
    }
    if (board[y1][x1] == 7)
    {
        board[y1][x1] = 0;
        board[y2][x2] = 1;
        inv = 1;
    }
    else if (board[y1][x1] == 27)
    {
        board[y1][x1] = 0;
        board[y2][x2] = 21;
        inv = 1;
    }
    if (board[y1][x1] == 8)
    {
        board[y1][x1] = 0;
        board[y2][x2] = 3;
        inv = 1;
    }
    else if (board[y1][x1] == 28)
    {
        board[y1][x1] = 0;
        board[y2][x2] = 28;
        inv = 1;
    }
    if (!(y2 < 0 || x2 < 0) && inv == 0)
    {
        tmp = board[y1][x1];
        board[y2][x2] = tmp;
        board[y1][x1] = 0;
    }
}
int promotion(int board[8][8], int turn)
{
    int promo = 0;
    int x = 0;
    int y = 0;
    int mat = 0;
    if (turn == 0)
    {
        y = 0;
        for (int j = 0; j < 8; j++)
        {
            if (board[y][j] == 26)
            {
                promo = 1;
                x = j;
            }
        }
    }
    else if (turn == 1)
    {
        y = 7;
        for (int j = 0; j < 8; j++)
        {
            if (board[y][j] == 6)
            {
                promo = 1;
                x = j;
            }
        }
    }
    if (promo == 1)
    {
        printf("You have a promotion\n");
        printf("Press enter to continue\n");
        getchar();
        getchar();
        if (y == 0)
        {
            printf("Promotion: \n");
            printf("What do you want:\n1. Queen\n2. Rook\n3. Bishop\n4. Knight\n\n");
            while ((scanf("%1i", &mat) == 0 || !(mat > 0 && mat < 5)))
            {
                printf("Invalid!\n");
            }
            addEntity(board, y, x, 21 + mat);
        }
        else if (y == 7)
        {
            printf("Promotion: \n");
            printf("What do you want:\n1. Queen\n2. Rook\n3. Bishop\n4. Knight\n\n");
            while (scanf("%1i", &mat) == 0 || !(mat > 0 && mat < 5))
            {
                printf("Invalid!\n");
            }
            addEntity(board, y, x, 1 + mat);
        }
    }
    return promo;
}
int shadowBoardChecker(int board[8][8], int x1, int y1, int x2, int y2, int turn)
{
    int retVal = -1;
    int mboard[8][8];
    int vboard[8][8];
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            mboard[i][j] = board[i][j];
        }
    }
    // Dmove(mboard, y1, x1, y2, x2);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            vboard[i][j] = 0;
        }
    }
    if (turn == 0)
    {
        if (board[y1][x1] > 11)
        {
            move(mboard, y1, x1, y2, x2);
        }
    }
    else if (turn == 1)
    {
        if (board[y1][x1] > 0 && board[y1][x1] < 11)
        {
            move(mboard, y1, x1, y2, x2);
        }
    }
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (turn == 0)
            {
                if (mboard[i][j] < 11)
                {
                    // black king
                    if (mboard[i][j] == 1 || mboard[i][j] == 7)
                    {
                        for (int y = -1; y < 2; y++)
                        {
                            for (int x = -1; x < 2; x++)
                            {
                                if (!((i + y > 7) || (i + y < 0)))
                                {
                                    if (!((j + x > 7) || (j + x < 0)))
                                    {
                                        vboard[i + y][j + x] = -1;
                                    }
                                }
                            }
                        }
                    }
                    // black queen
                    else if (mboard[i][j] == 2)
                    {
                        // right down
                        for (int x = j + 1, y = i + 1; x < 8 && y < 8; x++, y++)
                        {
                            if (mboard[y][x] == 0)
                            {
                                vboard[y][x] = -1;
                            }
                            else if (mboard[y][x] > 0)
                            {
                                vboard[y][x] = -1;
                                break;
                            }
                        }
                        // left down
                        for (int x = j - 1, y = i + 1; x > -1 && y < 8; x--, y++)
                        {
                            if (mboard[y][x] == 0)
                            {
                                vboard[y][x] = -1;
                            }
                            else if (mboard[y][x] > 0)
                            {
                                vboard[y][x] = -1;
                                break;
                            }
                        }
                        // right up
                        for (int x = j + 1, y = i - 1; x < 8 && y > -1; x++, y--)
                        {
                            if (mboard[y][x] == 0)
                            {
                                vboard[y][x] = -1;
                            }
                            else if (mboard[y][x] > 0)
                            {
                                vboard[y][x] = -1;
                                break;
                            }
                        }
                        // left up
                        for (int x = j - 1, y = i - 1; x > -1 && y > -1; x--, y--)
                        {
                            if (mboard[y][x] == 0)
                            {
                                vboard[y][x] = -1;
                            }
                            else if (mboard[y][x] > 0)
                            {
                                vboard[y][x] = -1;
                                break;
                            }
                        }
                        // right
                        for (int x = j + 1; x < 8; x++)
                        {
                            if (mboard[i][x] == 0)
                            {
                                vboard[i][x] = -1;
                            }
                            else if (mboard[i][x] > 0)
                            {
                                vboard[i][x] = -1;
                                break;
                            }
                        }

                        // down
                        for (int y = i + 1; y < 8; y++)
                        {
                            if (mboard[y][j] == 0)
                            {
                                vboard[y][j] = -1;
                            }
                            else if (mboard[y][j] > 0)
                            {
                                vboard[y][j] = -1;
                                break;
                            }
                        }

                        // left
                        for (int x = j - 1; x > -1; x--)
                        {
                            if (mboard[i][x] == 0)
                            {
                                vboard[i][x] = -1;
                            }
                            else if (mboard[i][x] > 0)
                            {
                                vboard[i][x] = -1;
                                break;
                            }
                        }

                        // up
                        for (int y = i - 1; y > -1; y--)
                        {
                            if (mboard[y][j] == 0)
                            {
                                vboard[y][j] = -1;
                            }
                            else if (mboard[y][j] > 0)
                            {
                                vboard[y][j] = -1;
                                break;
                            }
                        }
                    }
                    // black rook
                    else if (mboard[i][j] == 3 || mboard[i][j] == 8)
                    {
                        // right
                        for (int x = j + 1; x < 8; x++)
                        {
                            if (mboard[i][x] == 0)
                            {
                                vboard[i][x] = -1;
                            }
                            else if (mboard[i][x] > 0)
                            {
                                vboard[i][x] = -1;
                                break;
                            }
                        }

                        // down
                        for (int y = i + 1; y < 8; y++)
                        {
                            if (mboard[y][j] == 0)
                            {
                                vboard[y][j] = -1;
                            }
                            else if (mboard[y][j] > 0)
                            {
                                vboard[y][j] = -1;
                                break;
                            }
                        }

                        // left
                        for (int x = j - 1; x > -1; x--)
                        {
                            if (mboard[i][x] == 0)
                            {
                                vboard[i][x] = -2;
                            }
                            else if (mboard[i][x] > 0)
                            {
                                vboard[i][x] = -2;
                                break;
                            }
                        }

                        // up
                        for (int y = i - 1; y > -1; y--)
                        {
                            if (mboard[y][j] == 0)
                            {
                                vboard[y][j] = -2;
                            }
                            else if (mboard[y][j] > 0)
                            {
                                vboard[y][j] = -2;
                                break;
                            }
                        }
                    }
                    // black bishop
                    else if (mboard[i][j] == 4)
                    {
                        // right down
                        for (int x = j + 1, y = i + 1; x < 8 && y < 8; x++, y++)
                        {
                            if (mboard[y][x] == 0)
                            {
                                vboard[y][x] = -1;
                            }
                            else if (mboard[y][x] > 0)
                            {
                                vboard[y][x] = -1;
                                break;
                            }
                        }
                        // left down
                        for (int x = j - 1, y = i + 1; x > -1 && y < 8; x--, y++)
                        {
                            if (mboard[y][x] == 0)
                            {
                                vboard[y][x] = -1;
                            }
                            else if (mboard[y][x] > 0)
                            {
                                vboard[y][x] = -1;
                                break;
                            }
                        }
                        // right up
                        for (int x = j + 1, y = i - 1; x < 8 && y > -1; x++, y--)
                        {
                            if (mboard[y][x] == 0)
                            {
                                vboard[y][x] = -1;
                            }
                            else if (mboard[y][x] > 0)
                            {
                                vboard[y][x] = -1;
                                break;
                            }
                        }
                        // left up
                        for (int x = j - 1, y = i - 1; x > -1 && y > -1; x--, y--)
                        {
                            if (mboard[y][x] == 0)
                            {
                                vboard[y][x] = -1;
                            }
                            else if (mboard[y][x] > 0)
                            {
                                vboard[y][x] = -1;
                                break;
                            }
                        }
                    }
                    // black knight
                    else if (mboard[i][j] == 5)
                    {
                        int arr[8] = {-1, -2, +1, +2, -1, +2, +1, -2};
                        for (int x = 0, y = 7; x < 8 && y > -1; x++, y--)
                        {
                            // vboard[i+arr[y]][j+arr[x]] = -1;
                            if (!((i + arr[y] > 7) || (i + arr[y] < 0)))
                            {
                                if (!((j + arr[x] > 7) || (j + arr[x] < 0)))
                                {
                                    vboard[i + arr[y]][j + arr[x]] = -1;
                                }
                            }
                        }
                    }
                    // black pawn
                    else if (mboard[i][j] == 6)
                    {
                        for (int x = -1; x < 2; x += 2)
                        {
                            if (!(((i + 1) > 7) || ((i + 1) < 0)))
                            {
                                if (!((j + x > 7) || (j + x < 0)))
                                {
                                    vboard[i + 1][j + x] = -1;
                                }
                            }
                        }
                    }
                }
            }
            else if (turn == 1)
            {
                // white pieces
                if (mboard[i][j] > 11)
                {
                    if (mboard[i][j] == 21 || mboard[i][j] == 27)
                    {
                        for (int y = -1; y < 2; y++)
                        {
                            for (int x = -1; x < 2; x++)
                            {
                                if (!((i + y > 7) || (i + y < 0)))
                                {
                                    if (!((j + x > 7) || (j + x < 0)))
                                    {
                                        vboard[i + y][j + x] = -1;
                                    }
                                }
                            }
                        }
                    }
                    // white queen
                    else if (mboard[i][j] == 22)
                    {
                        // right down
                        for (int x = j + 1, y = i + 1; x < 8 && y < 8; x++, y++)
                        {
                            if (mboard[y][x] == 0)
                            {
                                vboard[y][x] = -1;
                            }
                            else if (mboard[y][x] > 0)
                            {
                                vboard[y][x] = -1;
                                break;
                            }
                        }
                        // left down
                        for (int x = j - 1, y = i + 1; x > -1 && y < 8; x--, y++)
                        {
                            if (mboard[y][x] == 0)
                            {
                                vboard[y][x] = -1;
                            }
                            else if (mboard[y][x] > 0)
                            {
                                vboard[y][x] = -1;
                                break;
                            }
                        }
                        // right up
                        for (int x = j + 1, y = i - 1; x < 8 && y > -1; x++, y--)
                        {
                            if (mboard[y][x] == 0)
                            {
                                vboard[y][x] = -1;
                            }
                            else if (mboard[y][x] > 0)
                            {
                                vboard[y][x] = -1;
                                break;
                            }
                        }
                        // left up
                        for (int x = j - 1, y = i - 1; x > -1 && y > -1; x--, y--)
                        {
                            if (mboard[y][x] == 0)
                            {
                                vboard[y][x] = -1;
                            }
                            else if (mboard[y][x] > 0)
                            {
                                vboard[y][x] = -1;
                                break;
                            }
                        }
                        // right
                        for (int x = j + 1; x < 8; x++)
                        {
                            if (mboard[i][x] == 0)
                            {
                                vboard[i][x] = -1;
                            }
                            else if (mboard[i][x] > 0)
                            {
                                vboard[i][x] = -1;
                                break;
                            }
                        }

                        // down
                        for (int y = i + 1; y < 8; y++)
                        {
                            if (mboard[y][j] == 0)
                            {
                                vboard[y][j] = -1;
                            }
                            else if (mboard[y][j] > 0)
                            {
                                vboard[y][j] = -1;
                                break;
                            }
                        }

                        // left
                        for (int x = j - 1; x > -1; x--)
                        {
                            if (mboard[i][x] == 0)
                            {
                                vboard[i][x] = -1;
                            }
                            else if (mboard[i][x] > 0)
                            {
                                vboard[i][x] = -1;
                                break;
                            }
                        }

                        // up
                        for (int y = i - 1; y > -1; y--)
                        {
                            if (mboard[y][j] == 0)
                            {
                                vboard[y][j] = -1;
                            }
                            else if (mboard[y][j] > 0)
                            {
                                vboard[y][j] = -1;
                                break;
                            }
                        }
                    }
                    // white rook
                    else if (mboard[i][j] == 23 || mboard[i][j] == 28)
                    {
                        // right
                        for (int x = j + 1; x < 8; x++)
                        {
                            if (mboard[i][x] == 0)
                            {
                                vboard[i][x] = -1;
                            }
                            else if (mboard[i][x] > 0)
                            {
                                vboard[i][x] = -1;
                                break;
                            }
                        }

                        // down
                        for (int y = i + 1; y < 8; y++)
                        {
                            if (mboard[y][j] == 0)
                            {
                                vboard[y][j] = -1;
                            }
                            else if (mboard[y][j] > 0)
                            {
                                vboard[y][j] = -1;
                                break;
                            }
                        }

                        // left
                        for (int x = j - 1; x > -1; x--)
                        {
                            if (mboard[i][x] == 0)
                            {
                                vboard[i][x] = -1;
                            }
                            else if (mboard[i][x] > 0)
                            {
                                vboard[i][x] = -1;
                                break;
                            }
                        }

                        // up
                        for (int y = i - 1; y > -1; y--)
                        {
                            if (mboard[y][j] == 0)
                            {
                                vboard[y][j] = -1;
                            }
                            else if (mboard[y][j] > 0)
                            {
                                vboard[y][j] = -1;
                                break;
                            }
                        }
                    }
                    // white bishop
                    else if (mboard[i][j] == 24)
                    {
                        // right down
                        for (int x = j + 1, y = i + 1; x < 8 && y < 8; x++, y++)
                        {
                            if (mboard[y][x] == 0)
                            {
                                vboard[y][x] = -1;
                            }
                            else if (mboard[y][x] > 0)
                            {
                                vboard[y][x] = -1;
                                break;
                            }
                        }
                        // left down
                        for (int x = j - 1, y = i + 1; x > -1 && y < 8; x--, y++)
                        {
                            if (mboard[y][x] == 0)
                            {
                                vboard[y][x] = -1;
                            }
                            else if (mboard[y][x] > 0)
                            {
                                vboard[y][x] = -1;
                                break;
                            }
                        }
                        // right up
                        for (int x = j + 1, y = i - 1; x < 8 && y > -1; x++, y--)
                        {
                            if (mboard[y][x] == 0)
                            {
                                vboard[y][x] = -1;
                            }
                            else if (mboard[y][x] > 0)
                            {
                                vboard[y][x] = -1;
                                break;
                            }
                        }
                        // left up
                        for (int x = j - 1, y = i - 1; x > -1 && y > -1; x--, y--)
                        {
                            if (mboard[y][x] == 0)
                            {
                                vboard[y][x] = -1;
                            }
                            else if (mboard[y][x] > 0)
                            {
                                vboard[y][x] = -1;
                                break;
                            }
                        }
                    }
                    // white knight
                    else if (mboard[i][j] == 25)
                    {
                        int arr[8] = {-1, -2, +1, +2, -1, +2, +1, -2};
                        for (int x = 0, y = 7; x < 8 && y > -1; x++, y--)
                        {
                            // vboard[i+arr[y]][j+arr[x]] = -1;
                            if (!((i + arr[y] > 7) || (i + arr[y] < 0)))
                            {
                                if (!((j + arr[x] > 7) || (j + arr[x] < 0)))
                                {
                                    vboard[i + arr[y]][j + arr[x]] = -1;
                                }
                            }
                        }
                    }
                    // white pawn
                    else if (mboard[i][j] == 26)
                    {
                        for (int x = -1; x < 2; x += 2)
                        {
                            if (!(((i - 1) > 7) || ((i - 1) < 0)))
                            {
                                if (!((j + x > 7) || (j + x < 0)))
                                {
                                    vboard[i - 1][j + x] = -1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    /*   for (int i = 0; i < 8; i++)
      {
          for (int j = 0; j < 8; j++)
          {
              if ((mboard[i][j] > 0 && mboard[i][j] < 11) && vboard[i][j] == -1)
              {
                  vboard[i][j] = -2;
              }
          }
      }
      for (int i = 0; i < 8; i++)
      {
          for (int j = 0; j < 8; j++)
          {
              if ((mboard[i][j] > 11 && mboard[i][j] < 40) && vboard[i][j] == -1)
              {
                  vboard[i][j] = -2;
              }
          }
      } */
    if (turn == 0)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (mboard[i][j] == 21 || mboard[i][j] == 27)
                {
                    if ((vboard[i][j] < 0))
                    {
                        retVal = -1;
                    }
                    else
                    {
                        retVal = 1;
                    }
                }
            }
        }
    }
    else if (turn == 1)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (mboard[i][j] == 1 || mboard[i][j] == 7)
                {
                    if ((vboard[i][j] < 0))
                    {
                        retVal = -1;
                    }
                    else
                    {
                        retVal = 1;
                    }
                }
            }
        }
    }
    if (x1 == x2 && y1 == y2)
    {
        retVal = -1;
    }
    if (board[y1][x1] == 0)
    {
        retVal = -1;
    }
    return retVal;
}
void shadowBoardInit(int board[8][8], int wsboard[8][8], int bsboard[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            wsboard[i][j] = 0;
        }
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            bsboard[i][j] = 0;
        }
    }
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board[i][j] > 0 && board[i][j] < 11)
            {
                // black king
                if (board[i][j] == 1 || board[i][j] == 7)
                {
                    for (int y = -1; y < 2; y++)
                    {
                        for (int x = -1; x < 2; x++)
                        {
                            if (!((i + y > 7) || (i + y < 0)))
                            {
                                if (!((j + x > 7) || (j + x < 0)))
                                {
                                    bsboard[i + y][j + x] = -1;
                                }
                            }
                        }
                    }
                }
                // black queen
                else if (board[i][j] == 2)
                {
                    // right down
                    for (int x = j + 1, y = i + 1; x < 8 && y < 8; x++, y++)
                    {
                        if (board[y][x] == 0)
                        {
                            bsboard[y][x] = -1;
                        }
                        else if (board[y][x] > 0)
                        {
                            bsboard[y][x] = -1;
                            break;
                        }
                    }
                    // left down
                    for (int x = j - 1, y = i + 1; x > -1 && y < 8; x--, y++)
                    {
                        if (board[y][x] == 0)
                        {
                            bsboard[y][x] = -1;
                        }
                        else if (board[y][x] > 0)
                        {
                            bsboard[y][x] = -1;
                            break;
                        }
                    }
                    // right up
                    for (int x = j + 1, y = i - 1; x < 8 && y > -1; x++, y--)
                    {
                        if (board[y][x] == 0)
                        {
                            bsboard[y][x] = -1;
                        }
                        else if (board[y][x] > 0)
                        {
                            bsboard[y][x] = -1;
                            break;
                        }
                    }
                    // left up
                    for (int x = j - 1, y = i - 1; x > -1 && y > -1; x--, y--)
                    {
                        if (board[y][x] == 0)
                        {
                            bsboard[y][x] = -1;
                        }
                        else if (board[y][x] > 0)
                        {
                            bsboard[y][x] = -1;
                            break;
                        }
                    }
                    // right
                    for (int x = j + 1; x < 8; x++)
                    {
                        if (board[i][x] == 0)
                        {
                            bsboard[i][x] = -1;
                        }
                        else if (board[i][x] > 0)
                        {
                            bsboard[i][x] = -1;
                            break;
                        }
                    }

                    // down
                    for (int y = i + 1; y < 8; y++)
                    {
                        if (board[y][j] == 0)
                        {
                            bsboard[y][j] = -1;
                        }
                        else if (board[y][j] > 0)
                        {
                            bsboard[y][j] = -1;
                            break;
                        }
                    }

                    // left
                    for (int x = j - 1; x > -1; x--)
                    {
                        if (board[i][x] == 0)
                        {
                            bsboard[i][x] = -1;
                        }
                        else if (board[i][x] > 0)
                        {
                            bsboard[i][x] = -1;
                            break;
                        }
                    }

                    // up
                    for (int y = i - 1; y > -1; y--)
                    {
                        if (board[y][j] == 0)
                        {
                            bsboard[y][j] = -1;
                        }
                        else if (board[y][j] > 0)
                        {
                            bsboard[y][j] = -1;
                            break;
                        }
                    }
                }
                // black rook
                else if (board[i][j] == 3 || board[i][j] == 8)
                {
                    // right
                    for (int x = j + 1; x < 8; x++)
                    {
                        if (board[i][x] == 0)
                        {
                            bsboard[i][x] = -1;
                        }
                        else if (board[i][x] > 0)
                        {
                            bsboard[i][x] = -1;
                            break;
                        }
                    }

                    // down
                    for (int y = i + 1; y < 8; y++)
                    {
                        if (board[y][j] == 0)
                        {
                            bsboard[y][j] = -1;
                        }
                        else if (board[y][j] > 0)
                        {
                            bsboard[y][j] = -1;
                            break;
                        }
                    }

                    // left
                    for (int x = j - 1; x > -1; x--)
                    {
                        if (board[i][x] == 0)
                        {
                            bsboard[i][x] = -1;
                        }
                        else if (board[i][x] > 0)
                        {
                            bsboard[i][x] = -1;
                            break;
                        }
                    }

                    // up
                    for (int y = i - 1; y > -1; y--)
                    {
                        if (board[y][j] == 0)
                        {
                            bsboard[y][j] = -1;
                        }
                        else if (board[y][j] > 0)
                        {
                            bsboard[y][j] = -1;
                            break;
                        }
                    }
                }
                // black bishop
                else if (board[i][j] == 4)
                {
                    // right down
                    for (int x = j + 1, y = i + 1; x < 8 && y < 8; x++, y++)
                    {
                        if (board[y][x] == 0)
                        {
                            bsboard[y][x] = -1;
                        }
                        else if (board[y][x] > 0)
                        {
                            bsboard[y][x] = -1;
                            break;
                        }
                    }
                    // left down
                    for (int x = j - 1, y = i + 1; x > -1 && y < 8; x--, y++)
                    {
                        if (board[y][x] == 0)
                        {
                            bsboard[y][x] = -1;
                        }
                        else if (board[y][x] > 0)
                        {
                            bsboard[y][x] = -1;
                            break;
                        }
                    }
                    // right up
                    for (int x = j + 1, y = i - 1; x < 8 && y > -1; x++, y--)
                    {
                        if (board[y][x] == 0)
                        {
                            bsboard[y][x] = -1;
                        }
                        else if (board[y][x] > 0)
                        {
                            bsboard[y][x] = -1;
                            break;
                        }
                    }
                    // left up
                    for (int x = j - 1, y = i - 1; x > -1 && y > -1; x--, y--)
                    {
                        if (board[y][x] == 0)
                        {
                            bsboard[y][x] = -1;
                        }
                        else if (board[y][x] > 0)
                        {
                            bsboard[y][x] = -1;
                            break;
                        }
                    }
                }
                // black knight
                else if (board[i][j] == 5)
                {
                    int arr[8] = {-1, -2, +1, +2, -1, +2, +1, -2};
                    for (int x = 0, y = 7; x < 8 && y > -1; x++, y--)
                    {
                        // bsboard[i+arr[y]][j+arr[x]] = -1;
                        if (!((i + arr[y] > 7) || (i + arr[y] < 0)))
                        {
                            if (!((j + arr[x] > 7) || (j + arr[x] < 0)))
                            {
                                bsboard[i + arr[y]][j + arr[x]] = -1;
                            }
                        }
                    }
                }
                // black pawn
                else if (board[i][j] == 6)
                {
                    for (int x = -1; x < 2; x += 2)
                    {
                        if (!(((i + 1) > 7) || ((i + 1) < 0)))
                        {
                            if (!((j + x > 7) || (j + x < 0)))
                            {
                                bsboard[i + 1][j + x] = -1;
                            }
                        }
                    }
                }
            }
            // white pieces
            else if (board[i][j] > 11)
            {
                if (board[i][j] == 21 || board[i][j] == 27)
                {
                    for (int y = -1; y < 2; y++)
                    {
                        for (int x = -1; x < 2; x++)
                        {
                            if (!((i + y > 7) || (i + y < 0)))
                            {
                                if (!((j + x > 7) || (j + x < 0)))
                                {
                                    wsboard[i + y][j + x] = -1;
                                }
                            }
                        }
                    }
                }
                // white queen
                else if (board[i][j] == 22)
                {
                    // right down
                    for (int x = j + 1, y = i + 1; x < 8 && y < 8; x++, y++)
                    {
                        if (board[y][x] == 0)
                        {
                            wsboard[y][x] = -1;
                        }
                        else if (board[y][x] > 0)
                        {
                            wsboard[y][x] = -1;
                            break;
                        }
                    }
                    // left down
                    for (int x = j - 1, y = i + 1; x > -1 && y < 8; x--, y++)
                    {
                        if (board[y][x] == 0)
                        {
                            wsboard[y][x] = -1;
                        }
                        else if (board[y][x] > 0)
                        {
                            wsboard[y][x] = -1;
                            break;
                        }
                    }
                    // right up
                    for (int x = j + 1, y = i - 1; x < 8 && y > -1; x++, y--)
                    {
                        if (board[y][x] == 0)
                        {
                            wsboard[y][x] = -1;
                        }
                        else if (board[y][x] > 0)
                        {
                            wsboard[y][x] = -1;
                            break;
                        }
                    }
                    // left up
                    for (int x = j - 1, y = i - 1; x > -1 && y > -1; x--, y--)
                    {
                        if (board[y][x] == 0)
                        {
                            wsboard[y][x] = -1;
                        }
                        else if (board[y][x] > 0)
                        {
                            wsboard[y][x] = -1;
                            break;
                        }
                    }
                    // right
                    for (int x = j + 1; x < 8; x++)
                    {
                        if (board[i][x] == 0)
                        {
                            wsboard[i][x] = -1;
                        }
                        else if (board[i][x] > 0)
                        {
                            wsboard[i][x] = -1;
                            break;
                        }
                    }

                    // down
                    for (int y = i + 1; y < 8; y++)
                    {
                        if (board[y][j] == 0)
                        {
                            wsboard[y][j] = -1;
                        }
                        else if (board[y][j] > 0)
                        {
                            wsboard[y][j] = -1;
                            break;
                        }
                    }

                    // left
                    for (int x = j - 1; x > -1; x--)
                    {
                        if (board[i][x] == 0)
                        {
                            wsboard[i][x] = -1;
                        }
                        else if (board[i][x] > 0)
                        {
                            wsboard[i][x] = -1;
                            break;
                        }
                    }

                    // up
                    for (int y = i - 1; y > -1; y--)
                    {
                        if (board[y][j] == 0)
                        {
                            wsboard[y][j] = -1;
                        }
                        else if (board[y][j] > 0)
                        {
                            wsboard[y][j] = -1;
                            break;
                        }
                    }
                }
                // white rook
                else if (board[i][j] == 23 || board[i][j] == 28)
                {
                    // right
                    for (int x = j + 1; x < 8; x++)
                    {
                        if (board[i][x] == 0)
                        {
                            wsboard[i][x] = -1;
                        }
                        else if (board[i][x] > 0)
                        {
                            wsboard[i][x] = -1;
                            break;
                        }
                    }

                    // down
                    for (int y = i + 1; y < 8; y++)
                    {
                        if (board[y][j] == 0)
                        {
                            wsboard[y][j] = -1;
                        }
                        else if (board[y][j] > 0)
                        {
                            wsboard[y][j] = -1;
                            break;
                        }
                    }

                    // left
                    for (int x = j - 1; x > -1; x--)
                    {
                        if (board[i][x] == 0)
                        {
                            wsboard[i][x] = -1;
                        }
                        else if (board[i][x] > 0)
                        {
                            wsboard[i][x] = -1;
                            break;
                        }
                    }

                    // up
                    for (int y = i - 1; y > -1; y--)
                    {
                        if (board[y][j] == 0)
                        {
                            wsboard[y][j] = -1;
                        }
                        else if (board[y][j] > 0)
                        {
                            wsboard[y][j] = -1;
                            break;
                        }
                    }
                }
                // white bishop
                else if (board[i][j] == 24)
                {
                    // right down
                    for (int x = j + 1, y = i + 1; x < 8 && y < 8; x++, y++)
                    {
                        if (board[y][x] == 0)
                        {
                            wsboard[y][x] = -1;
                        }
                        else if (board[y][x] > 0)
                        {
                            wsboard[y][x] = -1;
                            break;
                        }
                    }
                    // left down
                    for (int x = j - 1, y = i + 1; x > -1 && y < 8; x--, y++)
                    {
                        if (board[y][x] == 0)
                        {
                            wsboard[y][x] = -1;
                        }
                        else if (board[y][x] > 0)
                        {
                            wsboard[y][x] = -1;
                            break;
                        }
                    }
                    // right up
                    for (int x = j + 1, y = i - 1; x < 8 && y > -1; x++, y--)
                    {
                        if (board[y][x] == 0)
                        {
                            wsboard[y][x] = -1;
                        }
                        else if (board[y][x] > 0)
                        {
                            wsboard[y][x] = -1;
                            break;
                        }
                    }
                    // left up
                    for (int x = j - 1, y = i - 1; x > -1 && y > -1; x--, y--)
                    {
                        if (board[y][x] == 0)
                        {
                            wsboard[y][x] = -1;
                        }
                        else if (board[y][x] > 0)
                        {
                            wsboard[y][x] = -1;
                            break;
                        }
                    }
                }
                // white knight
                else if (board[i][j] == 25)
                {
                    int arr[8] = {-1, -2, +1, +2, -1, +2, +1, -2};
                    for (int x = 0, y = 7; x < 8 && y > -1; x++, y--)
                    {
                        // wsboard[i+arr[y]][j+arr[x]] = -1;
                        if (!((i + arr[y] > 7) || (i + arr[y] < 0)))
                        {
                            if (!((j + arr[x] > 7) || (j + arr[x] < 0)))
                            {
                                wsboard[i + arr[y]][j + arr[x]] = -1;
                            }
                        }
                    }
                }
                // white pawn
                else if (board[i][j] == 26)
                {
                    for (int x = -1; x < 2; x += 2)
                    {
                        if (!(((i - 1) > 7) || ((i - 1) < 0)))
                        {
                            if (!((j + x > 7) || (j + x < 0)))
                            {
                                wsboard[i - 1][j + x] = -1;
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((board[i][j] > 0 && board[i][j] < 11) && bsboard[i][j] == -1)
            {
                bsboard[i][j] = -2;
            }
        }
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((board[i][j] > 11 && board[i][j] < 40) && wsboard[i][j] == -1)
            {
                wsboard[i][j] = -2;
            }
        }
    }
}