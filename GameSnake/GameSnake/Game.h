//防止重复定义
#ifndef GAME_H
#define GAME_H
#include <Windows.h>
#include <stdio.h>
//定义宏变量
#define LEN 3//定义蛇身长度
#define WIDTH 30//宽度
#define HEIGHT 22//高度
//设计数据结构
typedef enum DIRECTION//枚举蛇的行动方向，并重命名为eDir
{
	UP,//上
	DOWN,//下
	LEFT,//左
	RIGHT,//右
}eDir;

typedef struct BODY//定义蛇身结构体，并重命名为Body。设计思路：蛇头节点的横纵坐标，以及指向下一个节点的指针
{
	int iX;//定义横坐标
	int iY;//定义纵坐标
	struct BODY *next;//定义蛇身的下一个结构体指针
}Body;

typedef struct SNAKE//定义蛇的属性，并重命名为Snake
{
	int len;//定义蛇的长度
	int eDir;//蛇的方向
	Body *pHead;//定义蛇身的头指针（用来指向上方的iX与iY）
}Snake;

typedef struct FOOD//定义食物结构体，并重命名为Food。设计思路：食物出现的坐标
{
	int iX;//定义横坐标
	int iY;//定义纵坐标
}Food;
//游戏功能声明函数
void GamePlay();//游戏开始函数
void InitSnake(Snake* pSnake);//初始化蛇函数
void AddNode(int iX,int iY,Snake* pSnake);//增加节点函数
void EndGame(Snake* pSnake);//释放蛇函数
void Move(Snake* pSnake);//蛇移动函数
void RemoveNode(Snake* pSnake);//
void KeyPress(Snake* pSnake);//方向移动控制函数
void MakeFood(Food* pFood,Snake* pSnake);//产生食物函数
BOOL CheckBody(int iX,int iY,Snake* pSnake);//检查蛇身函数，判断蛇的存活状态

#endif