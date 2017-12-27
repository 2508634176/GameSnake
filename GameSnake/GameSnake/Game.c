/***************************************
[文件名]		    Game.c
[功能模块和目的]	贪吃蛇的逻辑处理部分
****************************************/
#include "Game.h"
#include "UI.h"
#include <time.h>
#include "Rank.h"
#define _CRT_SECURE_NO_WARNINGS
void DrawSnake(Snake* pSnake);//声明画蛇函数
/************************
[函数名称]		GamePlay
[函数功能]		游戏开始
[参    数]		输入:无
				输出:无
[返 回 值]		无
*************************/
void GamePlay()
{
	//定义变量bRunning来作为是否撞墙的标志
	BOOL bRunning=TRUE;
	//开辟动态分配空间
	Snake* pSnake=(Snake*)malloc(sizeof(Snake));
	Food* pFood=(Food*)malloc(sizeof(Food));
	int i = 0,j = 0;
	//设定横纵坐标
	int iX;
	int iY;
	//定义分数与速度变量
	int iScore=0;
	int iSpeed=200;
	//定义分数结构体数组aScore
	Score aScore[NUM];
	memset(aScore,NULL,sizeof(Score)*NUM);//初始化（即清空）此数组
	InitSnake(pSnake);//初始化蛇
	DrawSnake(pSnake);//画蛇
	Sleep(iSpeed);//刷新一次（数值越大运动越慢）
	MakeFood(pFood,pSnake);//产生食物
	while(bRunning)//游戏主循环
	{
		KeyPress(pSnake);//判断蛇的方向
		Move(pSnake);//首先移动蛇的头结点
		iX=pSnake->pHead->iX;
		iY=pSnake->pHead->iY;
		//然后判断蛇的存活状态
		if(iX<0||iY<0||iX>WIDTH-1||iY>HEIGHT-1||CheckBody(iX,iY,pSnake))//若蛇死了，不删除尾节点并结束游戏
		{
			bRunning = FALSE;
			Location(22,11);
			printf("游戏结束！按任意键退出");//撞墙之后提示游戏结束
		}
		else//若蛇活着，删除尾节点
		{
			if (iX==pFood->iX&&iY==pFood->iY)//如果吃到食物了
			{
				MakeFood(pFood,pSnake);//再生成食物
				Location(5,1);
				printf("%03d",++iScore);//统计分数
				if (iScore%10==0)//统计速度
				{
					Location(14,1);
					iSpeed=iSpeed-20;
					printf("%02d",(220-iSpeed)/20);
				}
			}
			else
			{
				RemoveNode(pSnake);//删除尾节点
			}
			DrawSnake(pSnake);//接着画蛇
		}
		Sleep(iSpeed);
	}//利用循环实现蛇的移动
	EndGame(pSnake);//游戏结束后释放蛇
	getch();
	//①读取分数，并存到结构体数组aScore中
	ReadScore(aScore);
	//②对此数组进行排序和存储数据
	for (i = 0;i < NUM;i++)//开始比较当前分数与结构体数组中的值
	{
		if (iScore > aScore[i].iScore)//把最后一名弄出去
		{
			for (j = 8 ;j >= i;j--)
			{
				/*memcpy(&aScore[j+i],&aScore[j],sizeof(Score));*/
			strcpy(aScore[j+1].aName,aScore[j].aName);
			aScore[j + 1].iScore = aScore[j].iScore;//把成绩和姓名都往后弄一位
			}
			system("cls");
			SwitchCursor(1);//清屏并显示光标
			printf("\t\t\t输入玩家姓名并按Enter确认\n");
			gets(aScore[i].aName);//输入玩家姓名
			aScore[i].iScore = iScore;//存入玩家分数
			SwitchCursor(0);//隐藏光标
			break;//退出循环
		}
	}
	//③将数组中的数据写入dat文件【保存新的排行榜】
	WriteScore(aScore);
}
/******************************************
[函数名称]		InitSnake
[函数功能]		初始化蛇
[参    数]		输入:pSnake 蛇的属性结构体
				输出:pSnake 蛇的属性结构体
[返 回 值]		无
*******************************************/
void InitSnake(Snake* pSnake)
{
	int i=0;
	//初始化结构体成员，使长度为3、方向向右、蛇身为null
	pSnake->eDir=RIGHT;
	pSnake->len=LEN;
	pSnake->pHead=NULL;
	for(i=0;i<LEN;i++)
	{
		AddNode(i+3,3,pSnake);//增加节点
	}
}
/******************************************
[函数名称]		AddNode
[函数功能]		添加节点
[参    数]		输入:iX 横坐标
                     iY 纵坐标
                     pSnake 蛇的属性结构体
				输出:pSnake 蛇的属性结构体
[返 回 值]		无
*******************************************/
void AddNode(int iX,int iY,Snake* pSnake)
{
	//定义节点，并开辟可控内存供整个程序使用
	Body* pNode=(Body*)malloc(sizeof(Body));
	//把横纵轴坐标赋给pNode
	pNode->iX=iX;
	pNode->iY=iY;
	//头插法插入节点
	pNode->next=pSnake->pHead;
	pSnake->pHead=pNode;
}
/*******************************************************************************
[函数名称]		EndGame
[函数功能]		游戏结束后。释放蛇。malloc()函数申请的空间，需要free()函数释放。
[参    数]		输入:pSnake 蛇的属性结构体
				输出:无
[返 回 值]		无
********************************************************************************/
void EndGame(Snake* pSnake)
{
	Body* pNode;//都有新的节点
	while (pSnake->pHead!=NULL)//遍历整条蛇（链表）
	{
		pNode=pSnake->pHead;//头节点赋值给Node
		pSnake->pHead=pSnake->pHead->next; //头结点后移一位
		free(pNode);//释放pNode
	}
	free(pSnake);//释放蛇
}
/******************************************
[函数名称]		Move
[函数功能]		移动蛇头
[参    数]		输入:pSnake 蛇的属性结构体
				输出:pSnake 蛇的属性结构体
[返 回 值]		无
*******************************************/
void Move(Snake* pSnake)//定义移动函数
{
	int iX=pSnake->pHead->iX;
	int iY=pSnake->pHead->iY;
	switch(pSnake->eDir)//调用switch语句，判断蛇的移动方向，然后调用AddNode函数计算对应的坐标
	{
	//根据移动的方向调用AddNode函数，计算坐标
	case UP:AddNode(iX,iY-1,pSnake);break;//如果向上则只需纵坐标-1
	case DOWN:AddNode(iX,iY+1,pSnake);break;//如果向下则只需纵坐标+1
	case LEFT:AddNode(iX-1,iY,pSnake);break;//如果向左则只需横坐标-1
	case RIGHT:AddNode(iX+1,iY,pSnake);break;//如果向右则只需横坐标+1
	}
}
/******************************************
[函数名称]		RemoveNode
[函数功能]		擦除尾节点
[参    数]		输入:pSnake 蛇的属性结构体
				输出:pSnake 蛇的属性结构体
[返 回 值]		无
*******************************************/
void RemoveNode(Snake* pSnake)
{
	Body* pNode=pSnake->pHead;
	Body* pTempNode;
	//遍历链表到倒数第二个尾节点
	while(pNode->next!=NULL)
	{
		pTempNode=pNode;
		pNode=pNode->next;//后移一位到尾节点
	}
	Location(pNode->iX*2+1,pNode->iY+3);
	printf("  ");
	pTempNode->next=NULL;//置空尾节点
	free(pNode);//free掉尾节点
}
/******************************************
[函数名称]		KeyPress
[函数功能]		获得方向
[参    数]		输入:pSnake 蛇的属性结构体
				输出:pSnake 蛇的属性结构体
[返 回 值]		无
*******************************************/
void KeyPress(Snake* pSnake)
{
	int iInput=0;//定义接收信号的变量
	if (kbhit())//kbhit监控从键盘输入的信号
	{
		iInput=getch();//获取输入的信号
		switch(iInput)
		{
		case 'a':
		case 'A':
			{
				if(pSnake->eDir!=RIGHT)
				{
					pSnake->eDir=LEFT;//a或A的情况只准往左动
				}
				break;
			}
		case 'd':
		case 'D':
			{
				if(pSnake->eDir!=LEFT)
				{
					pSnake->eDir=RIGHT;//d或D的情况只准往右动
				}
				break;
			}
		case 'w':
		case 'W':
			{
				if(pSnake->eDir!=DOWN)
				{
					pSnake->eDir=UP;//w或W的情况只准往上动
				}
				break;
			}
		case 's':
		case 'S':
			{
				if(pSnake->eDir!=UP)
				{
					pSnake->eDir=DOWN;//s或S的情况只准往下动
				}
				break;
			}
		case ' ':system("pause>>null");break;//按下空格键暂停或者继续
		}
	}
}
/*************************************
[函数名称]		MakeFood
[函数功能]		生成食物
[参    数]		输入:pFood 食物结构体
				输出:pFood 食物结构体
[返 回 值]		无
**************************************/
void MakeFood(Food* pFood,Snake* pSnake)
{
	/*int iX = 0;
	int iY = 0;
	srand(time(NULL));*/
	int iX=rand()%WIDTH;//产生随机数
	int iY=rand()%HEIGHT;
	while(CheckBody(iX,iY,pSnake))//判断事物的坐标，当食物在蛇身上时，随机再生成食物
	{
		iX=rand()%WIDTH;
	    iY=rand()%HEIGHT;
	}
	//如果食物不在蛇身上，将iX,iY赋给pFood，产生新的食物
	pFood->iX=iX;
	pFood->iY=iY;
	Location(pFood->iX*2+1,pFood->iY+3);//锁定食物的位置并打印食物
	printf("☆");
}
/***************************************************
[函数名称]		CheckBody
[函数功能]		遍历链表判断传入的坐标是否在链表上
[参    数]		输入:iX 横坐标
                     iY 纵坐标
                     pSnake 蛇的属性结构体
				输出:TRUE 在链表上
                     FALSE 不在链表上
[返 回 值]		BOOL值
****************************************************/
BOOL CheckBody(int iX,int iY,Snake* pSnake)
{
	Body* pNode=pSnake->pHead->next;//定义结构体指针pNode
	while(pNode!=NULL)
	{
		if (pNode->iX==iX&&pNode->iY==iY)//如果食物在蛇身上就返回1，使循环继续
		{
			return TRUE;
		}
		pNode=pNode->next;//pNode后移一位
	}
	return FALSE;//若pNode一开始为空，就返回0
}