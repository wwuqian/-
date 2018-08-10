#define _CRT_SECURT_NO_WARNING   1

#ifndef  __GAME_H__
#define  __GAME_H__
#define  ROWS 10
#define  COLS 10

#define  DEFAULT_COUNT  99

void display(char arr[ROWS+2][COLS+2], int rows, int cols);
void set_mine(char arr[ROWS+2][COLS+2], int rows, int cols);
int get_mine_count(char arr[ROWS+2][COLS+2], int x, int y);

#endif  //结束__GAME_H__
