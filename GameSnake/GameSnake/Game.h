//��ֹ�ظ�����
#ifndef GAME_H
#define GAME_H
#include <Windows.h>
#include <stdio.h>
//��������
#define LEN 3//����������
#define WIDTH 30//���
#define HEIGHT 22//�߶�
//������ݽṹ
typedef enum DIRECTION//ö���ߵ��ж����򣬲�������ΪeDir
{
	UP,//��
	DOWN,//��
	LEFT,//��
	RIGHT,//��
}eDir;

typedef struct BODY//��������ṹ�壬��������ΪBody�����˼·����ͷ�ڵ�ĺ������꣬�Լ�ָ����һ���ڵ��ָ��
{
	int iX;//���������
	int iY;//����������
	struct BODY *next;//�����������һ���ṹ��ָ��
}Body;

typedef struct SNAKE//�����ߵ����ԣ���������ΪSnake
{
	int len;//�����ߵĳ���
	int eDir;//�ߵķ���
	Body *pHead;//���������ͷָ�루����ָ���Ϸ���iX��iY��
}Snake;

typedef struct FOOD//����ʳ��ṹ�壬��������ΪFood�����˼·��ʳ����ֵ�����
{
	int iX;//���������
	int iY;//����������
}Food;
//��Ϸ������������
void GamePlay();//��Ϸ��ʼ����
void InitSnake(Snake* pSnake);//��ʼ���ߺ���
void AddNode(int iX,int iY,Snake* pSnake);//���ӽڵ㺯��
void EndGame(Snake* pSnake);//�ͷ��ߺ���
void Move(Snake* pSnake);//���ƶ�����
void RemoveNode(Snake* pSnake);//
void KeyPress(Snake* pSnake);//�����ƶ����ƺ���
void MakeFood(Food* pFood,Snake* pSnake);//����ʳ�ﺯ��
BOOL CheckBody(int iX,int iY,Snake* pSnake);//������������ж��ߵĴ��״̬

#endif