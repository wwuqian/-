#define _CRT_SECURT_NO_WARNING   1
#include<stdio.h>
#include "game.h"
#include<stdlib.h>

void display(char arr[ROWS+2][COLS+2],int rows,int cols)//打印12*12棋盘
{
	int i = 0;
	int j = 0;
	printf("   ");
	for(i=0; i<=rows; i++)
	{
	   printf("%d ", i);
	}
	  printf("\n");
	for(i=1; i<=rows; i++)
	{
		printf("%2d ", i);
	   for(j=1; j<=cols; j++)
	   {
	       printf("%c ",arr[i][j]);
	   }
	}
       printf("\n");
}

int get_rand_num()
{
   return rand()%10+1;
}
void set_mine(char arr[ROWS+2][COLS+2], int rows, int cols)//布雷
{
    int count = DEFAULT_COUNT;
    while(count)
	{
	   int x = get_rand_num;//%10产生0~9
	   int y = get_rand_num;
       if(arr[x][y] == '0')
	   {
	      arr[x][y] = '1';
		  count--;
	   }
	}
}

int get_mine_count(char arr[ROWS+2][COLS+2], int x, int y)
{
     return (arr[x-1][y-1]-'0'+arr[x][y-1]-'0'+arr[x+1][y-1]-'0'+
	   arr[x+1][y]-'0'+arr[x+1][y+1]-'0'+
	   arr[x][y+1]-'0'+arr[x-1][y+1]-'0');

}




