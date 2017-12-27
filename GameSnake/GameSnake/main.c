/***************************************
[文件名]		    main.c
[功能模块和目的]    贪吃蛇主函数处理部分
*****************************************/
//调用自定义头文件
#include "UI.h"
#define _CRT_SECURE_NO_WARNINGS
//主函数开始
int main()
{
	int iKey=0;
	do
	{
		SwitchCursor(0);//0代表隐藏光标
		MainMenu();//调用主菜单函数
		iKey = getch();//获取一个选择按钮
		switch(iKey)
		{
		case '1':StartGame();break;//调用开始游戏函数
		case '2':SnakeRank();break;//调用排行榜函数
		case '3':SnakeIntroduce();break;//调用游戏结束函数
		case '4':printf("\t\t\t\t游戏退出!\n");break;//退出游戏
		default:printf("error!");break;
		}
	}while(iKey!='4');
system("pause");
return 0;
}

