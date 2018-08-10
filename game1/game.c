#define  _CET_SECURE_NO_WARNINGS  1
#include "game.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
 void  init_board(char board[ROWS][COLS], int rows, int cols)//初始化棋盘函数
 {
	 /*int i = 0;
	 int j = 0;
	 for(i=0; i<rows; i++)
	 {
	   for(j=0; j<cols; j++)
	    {
            board[i][j] = ' ';
	    }
	 }*/  //用俩个数组进行初始

	 memset(board, ' ', sizeof(char)*cols*rows);//用来设置内存的函数，开辟空间的首地址，初始化成什么，初始多少个字节的空间
 
 }

 void  display_board(char board[ROWS][COLS], int rows, int cols)//打印棋盘
 {
    int i = 0;
	for(i=0; i<rows; i++)
	{
    printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2] );
	if(i != rows-1)
	    printf("---|---|---\n");
	}
 }

 void  player_move(char board[ROWS][COLS], int rows, int cols)//玩家移动
 {
     int x = 0;
	 int y = 0;
	 while(1)
	 {
	    printf("请输入坐标:> ");
	    scanf("%d%d", &x, &y);
        x--;
	    y--;//对应数组下标
        if((x>=0)&&(x<=rows-1)&&(y>=0)&&(y<=cols-1))
	    {
	        if(board[x][y] == ' ')
		     {
		         board[x][y] = 'X';//把X赋给坐标
		            break;
		     }
		    else
		     {
			     printf("请重新输入坐标:> ");
		     }
	     }
	 }
 }

 void  computer_move(char board[ROWS][COLS], int rows, int cols)//电脑移动
 {
	 while(1)
	 {
		int x = rand()%3;
		int y = rand()%3;
	    if(board[x][y] == ' ')
		 {	
			 board[x][y] = '0';
			 break;
		 }	  
	 }
 }

static int is_full(char board[ROWS][COLS], int rows, int cols)
 {
     int i = 0;
	 int j = 0;
	 for(i=0; i<rows; i++)
	 {
	    for(j=0; i<cols; j++)
		{
		   if(board[i][j] == ' ')
			   return 0;//没满
		}
	 
	 }
  }
  char  check_win(char board[ROWS][COLS], int rows, int cols)
  {
     int i = 0;
	 for(i=0; i<rows; i++)
	 {
	     if((board[i][0] == board[i][1])&&(board[i][1] == board[i][2])&&(board[i][1] != ' '))
		  {
		     
		     return board[i][1];
		   }
		 if((board[0][i] == board[1][i])&&(board[1][i] == board[2][i])&&(board[1][i] != ' '))
		  {
		     
		     return board[1][i];
		  }
	 }
       if((board[0][0] == board[1][1])&&(board[1][1] == board[2][2])&&(board[1][1] != ' '))
	    {
		   return board[1][1];
        }
	  if((board[0][2] == board[1][1])&&(board[1][1] == board[2][0])&&(board[1][1] != ' '))
	   {
		  return board[1][1];
       }
      if(is_full(board, rows, cols))
	  {
	     return 'q';//平局
	  }
	  return ' ';//游戏还要继续
  }
 
