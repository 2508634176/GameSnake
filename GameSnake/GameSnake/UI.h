//条件编译，防止重复定义
#ifndef UI_H
#define UI_H
#include <conio.h>
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//UI函数声明
void MainMenu();//声明主菜单函数
void SnakeRank();//声明排行榜函数
void SnakeIntroduce();//声明游戏
void StartGame();//声明游戏开始函数
void SwitchCursor(int iFlag);//声明隐藏光标函数
void Location(int iX,int iY);//声明传递坐标函数

#endif