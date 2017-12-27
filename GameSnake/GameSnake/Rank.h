//防止重复编译
#ifndef RANK_H
#define RANK_H
#define NUM 10

typedef struct SCORE//定义分数结构体，并重命名为Score
{
	char aName[20];
	int iScore;
}Score;
//函数声明
void ReadScore(Score *aScore);//读取文件函数
void WriteScore(Score *aScore);//写入文件函数

#endif