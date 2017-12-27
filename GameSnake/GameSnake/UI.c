/********************************************
[文件名]		    UI.c
[功能模块和目的]    贪吃蛇的游戏界面处理部分
********************************************/
//导入自定义头文件
#include "UI.h"
#include "Game.h"
#include "Rank.h"
void DrawSnake(Snake* pSnake);//声明画蛇函数
/********************************
[函数名称]		MainMenu
[函数功能]	    输出菜单
[参    数]		输入:无
				输出:菜单
[返 回 值]		无
*********************************/
void MainMenu()
{
	system("cls");//清屏
	//打印菜单样式
	printf("\t\t*********************************************\n");
	printf("\t\t*               贪吃蛇小游戏                *\n");
	printf("\t\t*                                           *\n");
	printf("\t\t*     ◎◎◎◎◎◎  ◎◎◎◎◎              *\n");
	printf("\t\t*     ◎        ◎◎◎      ◎◎○   ☆     *\n");
	printf("\t\t*     ◎                                    *\n");
	printf("\t\t*     ◎        1、开始游戏                 *\n");
	printf("\t\t*     ◎        2、排行榜                   *\n");
	printf("\t\t*     ◎        3、操作介绍       ◎◎◎    *\n");
	printf("\t\t*     ◎        4、退出           ◎        *\n");
	printf("\t\t*     ◎                          ◎        *\n");
	printf("\t\t*     ◎◎◎◎◎◎◎◎◎◎◎◎◎◎◎        *\n");
	printf("\t\t*********************************************\n");
}
/*************************
[函数名称]		StartGame
[函数功能]	    启动游戏
[参    数]		输入:无
				输出:菜单
[返 回 值]		无
**************************/
void StartGame()
{
	system("cls");//清屏
	printf("\t\t\t贪吃蛇小游戏\n");
	printf("分数:000速度:01\n");
	//打印游戏背景界面
	printf("**************************************************************\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                     按任意键开始游戏                       *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("*                                                            *\n");
	printf("**************************************************************\n");
	getch();//暂停界面
	Location(22,11);
	printf("                        ");//清除“按任意键开始”（在当前光标所在位置处绘制图形）
	GamePlay();//启动游戏
}
/********************************
[函数名称]		SnakeRank
[函数功能]	    游戏排行榜
[参    数]		输入:分数数组
				输出:游戏分数
[返 回 值]		无
**********************************/
void SnakeRank()
{
	int i = 0;//设置循环变量
	Score aScore[10];//定义分数结构体数组aScore
	memset(aScore,NULL,sizeof(Score)*10);//初始化（清空）此数组
	system("cls");
	printf("\t\t\t\t   【排行榜】\n\t\t\t        按任意键返回菜单\n");
	printf("\t\t-------------------------------------------------\n");
	printf("\t\t|名次   玩家姓名\t\t\t分数\t |\n");
	ReadScore(aScore);//读取更新后的排行榜信息，并保存到数组aScore中
	for (i = 0;i < 10;i++)
	{
		//【%02d表示不足的数补0，如11就是11而1改为01】【没0的空格补齐】
		printf("\t\t|%02d     name:%-20s\tscore:%03d|\n",i+1,
			strlen(aScore[i].aName)==0?("null"):(aScore[i].aName),aScore[i].iScore);
		//输出内容为：名次、玩家姓名（若第一次玩游戏则需将玩家名设为null）、当前元素的分数
	}
	printf("\t\t-------------------------------------------------\n");
	getch();
}
/********************************
[函数名称]		SnakeIntroduce
[函数功能]	    游戏介绍
[参    数]		输入:无
				输出:游戏介绍
[返 回 值]		无
**********************************/
void SnakeIntroduce()
{
	system("cls");
	//游戏操作介绍
	printf("\t\t\t\t   【游戏介绍】\n\t\t\t        按任意键返回菜单\n");
	printf("\t\t\t\t-----------------\n");
	printf("\t\t\t\t按键操作说明\n");
	printf("\t\t\t\t1、按a或A向左移动\n");
	printf("\t\t\t\t2、按d或D向右移动\n");
	printf("\t\t\t\t3、按w或W向上移动\n");
	printf("\t\t\t\t4、按s或S向下移动\n");
	printf("\t\t\t\t5、按空格键暂停/继续\n");
	printf("\t\t\t\t-----------------\n");
	printf("\t\t\t\t游戏注意事项\n");
	printf("\t\t\t\t1、没有设置通关分数\n");
	printf("\t\t\t\t2、最高分没有上限\n");
	printf("\t\t\t\t-----------------\n");
	printf("\t\t\t\t排行榜说明\n");
	printf("\t\t\t\t1、游戏只收录了分数排行榜前十名\n");
	printf("\t\t\t\t2、只有当玩家分数最少高于第10名时才上榜\n");
	printf("\t\t\t\t3、当有玩家进入前十，自动踢掉最后一名\n");
	printf("\t\t\t\t-----------------\n");
	printf("\t\t\t\t游戏结束说明\n");
	printf("\t\t\t\t1、贪吃蛇撞上四周的墙壁时，结束游戏\n");
	printf("\t\t\t\t2、贪吃蛇撞上自己时，结束游戏\n");
	getch();
}

/********************************
[函数名称]		SwitchCursor
[函数功能]	    光标隐藏函数
[参    数]		输入:无
				输出:无
[返 回 值]		无
**********************************/
void SwitchCursor(int iFlag)
{
	//设置隐藏光标模式
	CONSOLE_CURSOR_INFO cursor_info = {1,iFlag};//参数1：厚薄度；参数2：是否显示光标
	//隐藏光标函数
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);//设置光标属性：隐藏光标

}
/******************************************
[函数名称]		Location
[函数功能]		坐标跳转,重新定位光标的位置
[参    数]		输入:iX iY
				输出:新的坐标
[返 回 值]		无
********************************************/
void Location(int iX,int iY)
{
	COORD pos;//定义COORD结构体变量pos【其中X和Y是它的成员，通过修改pos.X和pos.Y的值就可以实现光标的位置控制】（COORD是Windows API中定义的一种结构，表示一个字符在控制台屏幕上的坐标）
	HANDLE hOut;//HANDLE：句柄，是Windows用来表示对象的。在Windows程序中，有各种各样的资源（窗口、图标、光标等），系统在创建这些资源时会为它们分配内存，并返回标示这些资源的标示号，即句柄。
	pos.X=iX;//COORD pos变量接受传过来的坐标
	pos.Y=iY;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出的句柄【STD_OUTPUT_HANDLE：将输出的光标位置转到pos这个结构体的坐标上】
	SetConsoleCursorPosition(hOut,pos);//函数设置光标的位置，跳转到当前指定的坐标
	//输出句柄，将输出的光标位置转到pos这个结构体的坐标上（SetConsoleCursorPosition是API中定位光标位置的函数）
}
/******************************************
[函数名称]		DrawSnake
[函数功能]		绘制蛇身
[参    数]		输入:指针变量pSnake
				输出:蛇头、蛇身
[返 回 值]		无
********************************************/
void DrawSnake(Snake* pSnake)
{
	//遍历链表打印链表的每个节点，实现贪吃蛇的绘制
	Body* pNode=pSnake->pHead;
	Location(pNode->iX*2+1,pNode->iY+3);
	printf("○");//打印头
	while (pNode->next!=NULL)
	{
		pNode=pNode->next;
		Location(pNode->iX*2+1,pNode->iY+3);
	    printf("◎");//打印身子
	}
}
