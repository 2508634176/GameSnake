//��ֹ�ظ�����
#ifndef RANK_H
#define RANK_H
#define NUM 10

typedef struct SCORE//��������ṹ�壬��������ΪScore
{
	char aName[20];
	int iScore;
}Score;
//��������
void ReadScore(Score *aScore);//��ȡ�ļ�����
void WriteScore(Score *aScore);//д���ļ�����

#endif