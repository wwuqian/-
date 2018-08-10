#define  _CRT_SECURE_NO_WARNINGS  1
//主逻辑的实现

#include<stdio.h>
#include "game.h"
#include<time.h>
#include<stdlib.h>
void menu()
{
   printf("********************************\n");
   printf("***********  1.play  ***********\n");
   printf("***********  0.exit   **********\n");
   printf("********************************\n");
}

enum Option   //枚举法，列出选项
{
   EXIT,      //默认0,根据菜单中的选择默认
   PLAY       //默认1

};
void game()
{    
	char board[ROWS][COLS] = {0};//用宏替换
	char ret = 0;//接收返回值
	init_board(board, ROWS, COLS);//初始化棋盘函数
	display_board(board, ROWS, COLS);//打印棋盘
   while(1)
   {
      player_move(board, ROWS, COLS);
	  display_board(board, ROWS, COLS);
	  ret = check_win(board, ROWS, COLS);
	  if(ret != ' ')
		  break;
	  printf("------------\n");
	  computer_move(board, ROWS, COLS);
	  display_board(board, ROWS, COLS);
	  ret = check_win(board, ROWS, COLS);
       if(ret != ' ')
		   break;
   }
      if(ret == 'X')
         printf("玩家赢！\n");
	  else if(ret == '0')
		  printf("电脑赢！\n");
	  else
		  printf("平局\n");  
}

int main()
{
     int input = 0;
	 srand((unsigned int )time(NULL));//产生随机数
    do
	{
	    menu();//显示菜单
		printf("请选择>:");
	    scanf("%d", &input);
		switch(input)    //游戏的逻辑
		{
		  case PLAY:       //输入1，则进行游戏,可读性增强
			  game();
			  break;    //输入0，则退出
		  case EXIT:        
			  break;
		  default :
		     printf("选择错误，请重新输入!!!\n");
		     break;
		}

	}while(input);
return 0;

}
