#define _CRT_SECURT_NO_WARNING   1
#include<stdio.h>
#include<string.h>
#include "game.h"
#include<time.h>
#include<stdlib.h>

void menu()
{
	printf("**********************************\n");//�˵�ѡ��
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
    memset(mine,'0',sizeof(char)*(ROWS+2)*(COLS+2));//��ʼ�����̣���ʾ��0��
	memset(show,'*',sizeof(char)*(ROWS+2)*(COLS+2));//��ʼ�����̣���ʾ��*��
	display(show, ROWS ,COLS);
    set_mine(mine, ROWS, COLS);//��������
	display(show, ROWS ,COLS);	   
	
	while(win<COLS*ROWS-DEFAULT_COUNT)
	{
		
		printf("����������:>");
		scanf("%d%d", &x, &y);
		if(mine[x][y] == '1')
		{
			printf("�ܱ�Ǹ���㱻ը����!\n");
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
	    printf("���׳ɹ�\n");
	}
}


int main()
{
     int input = 0;
    do
	{
	    menu();//��ʾ�˵�
		printf("��ѡ��>:");
	    scanf("%d", &input);
		switch(input)    //��Ϸ���߼�
		{
		  case PLAY:       //����1���������Ϸ,�ɶ�����ǿ
			  game();
			  break;    //����0�����˳�
		  case EXIT:        
			  break;
		  default :
		     printf("ѡ���������������!!!\n");
		     break;
		}

	}while(input);
return 0;

}