/******************************************
[文件名]		    Rank.c
[功能模块和目的]    贪吃蛇的排行榜处理部分
******************************************/
#include "Rank.h"
#include<stdio.h>
#include<stdlib.h>
/*********************************
[函数名称]		ReadScore
[函数功能]	    读取分数
[参    数]		输入:数组中的信息
				输出:二进制文件
[返 回 值]		无
**********************************/
void ReadScore(Score *aScore)
{
	//打开文件
	FILE *fp = fopen("score.dat","rb");//定义文件指针，以只读权限打开文件
	//判断文件是否为空
	if (fp==NULL)
	{
		return;//空文件直接返回
	}
	//读取文件
	if (fread(aScore,sizeof(Score),NUM,fp)==0)
	{
		return;
	}
	//关闭文件
	fclose(fp);
	fp = NULL;//使fp重新指向NULL，防止野指针出现
}
/*********************************
[函数名称]		WriteScore
[函数功能]	    记录成绩
[参    数]		输入:用户输入的信息
				输出:二进制文件
[返 回 值]		无
**********************************/
void WriteScore(Score *aScore)
{
	//打开文件
	FILE *fp = fopen("score.dat","wb");//定义文件指针，以只写权限打开文件
	if (fp==NULL)
	{
		return;
	}
	//写入文件
	if (fwrite(aScore,sizeof(Score),NUM,fp)==0)//如果文件为空的,10是要进行写入size字节的数据项的个数
	{
		return;
	}
	//关闭文件
	fclose(fp);
	fp = NULL;//使fp重新指向NULL
}
