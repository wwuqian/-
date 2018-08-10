#define _CRT_SECURT_NO_WARNING   1
#include<stdio.h>
#include<string.h>
#include "game.h"
#include<time.h>
#include<stdlib.h>

void menu()
{
	printf("**********************************\n");//菜单选项
	printf("***********   1.play   ***********\n");
	printf("***********   0.exit   ***********\n");
	printf("**********************************\n");
}
 enum Option
  {
     EXIT,
     PLAY
  };

void game()
{
	int x = 0;
	int y = 0;
	int win = 0;
	char mine[ROWS+2][COLS+2] = {0};
	char show[ROWS+2][COLS+2] = {0};
	
    srand((unsigned int)time(NULL));
    memset(mine,'0',sizeof(char)*(ROWS+2)*(COLS+2));//初始化棋盘，显示‘0’
	memset(show,'*',sizeof(char)*(ROWS+2)*(COLS+2));//初始化棋盘，显示‘*’
	display(show, ROWS ,COLS);
    set_mine(mine, ROWS, COLS);//用来存雷
	display(show, ROWS ,COLS);	   
	
	while(win<COLS*ROWS-DEFAULT_COUNT)
	{
		
		printf("请输入坐标:>");
		scanf("%d%d", &x, &y);
		if(mine[x][y] == '1')
		{
			printf("很抱歉，你被炸死了!\n");
			break;
		}
		else
		{
			int count = 0;
			win++;
		    count = get_mine_count(mine, x, y);
			show[x][y] = count+'0';
	        display(show, ROWS ,COLS);
		}

	}
	if(win>=COLS*ROWS-DEFAULT_COUNT)
	{
	    printf("排雷成功\n");
	}
}


int main()
{
     int input = 0;
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