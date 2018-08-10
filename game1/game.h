#ifndef  __GAME_H__    //函数声明
#define  __GAME_H__
#define ROWS  3
#define COLS  3

 void  init_board(char board[ROWS][COLS], int rows, int cols);//初始化棋盘函数
 void  display_board(char board[ROWS][COLS], int rows, int cols);//打印棋盘
 void  player_move(char board[ROWS][COLS], int rows, int cols);
	 
 void  computer_move(char board[ROWS][COLS], int rows, int cols);
 char  check_win(char board[ROWS][COLS], int rows, int cols);
   
#endif //结束__GAME_H__
