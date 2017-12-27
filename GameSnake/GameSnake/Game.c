/***************************************
[�ļ���]		    Game.c
[����ģ���Ŀ��]	̰���ߵ��߼�������
****************************************/
#include "Game.h"
#include "UI.h"
#include <time.h>
#include "Rank.h"
#define _CRT_SECURE_NO_WARNINGS
void DrawSnake(Snake* pSnake);//�������ߺ���
/************************
[��������]		GamePlay
[��������]		��Ϸ��ʼ
[��    ��]		����:��
				���:��
[�� �� ֵ]		��
*************************/
void GamePlay()
{
	//�������bRunning����Ϊ�Ƿ�ײǽ�ı�־
	BOOL bRunning=TRUE;
	//���ٶ�̬����ռ�
	Snake* pSnake=(Snake*)malloc(sizeof(Snake));
	Food* pFood=(Food*)malloc(sizeof(Food));
	int i = 0,j = 0;
	//�趨��������
	int iX;
	int iY;
	//����������ٶȱ���
	int iScore=0;
	int iSpeed=200;
	//��������ṹ������aScore
	Score aScore[NUM];
	memset(aScore,NULL,sizeof(Score)*NUM);//��ʼ��������գ�������
	InitSnake(pSnake);//��ʼ����
	DrawSnake(pSnake);//����
	Sleep(iSpeed);//ˢ��һ�Σ���ֵԽ���˶�Խ����
	MakeFood(pFood,pSnake);//����ʳ��
	while(bRunning)//��Ϸ��ѭ��
	{
		KeyPress(pSnake);//�ж��ߵķ���
		Move(pSnake);//�����ƶ��ߵ�ͷ���
		iX=pSnake->pHead->iX;
		iY=pSnake->pHead->iY;
		//Ȼ���ж��ߵĴ��״̬
		if(iX<0||iY<0||iX>WIDTH-1||iY>HEIGHT-1||CheckBody(iX,iY,pSnake))//�������ˣ���ɾ��β�ڵ㲢������Ϸ
		{
			bRunning = FALSE;
			Location(22,11);
			printf("��Ϸ��������������˳�");//ײǽ֮����ʾ��Ϸ����
		}
		else//���߻��ţ�ɾ��β�ڵ�
		{
			if (iX==pFood->iX&&iY==pFood->iY)//����Ե�ʳ����
			{
				MakeFood(pFood,pSnake);//������ʳ��
				Location(5,1);
				printf("%03d",++iScore);//ͳ�Ʒ���
				if (iScore%10==0)//ͳ���ٶ�
				{
					Location(14,1);
					iSpeed=iSpeed-20;
					printf("%02d",(220-iSpeed)/20);
				}
			}
			else
			{
				RemoveNode(pSnake);//ɾ��β�ڵ�
			}
			DrawSnake(pSnake);//���Ż���
		}
		Sleep(iSpeed);
	}//����ѭ��ʵ���ߵ��ƶ�
	EndGame(pSnake);//��Ϸ�������ͷ���
	getch();
	//�ٶ�ȡ���������浽�ṹ������aScore��
	ReadScore(aScore);
	//�ڶԴ������������ʹ洢����
	for (i = 0;i < NUM;i++)//��ʼ�Ƚϵ�ǰ������ṹ�������е�ֵ
	{
		if (iScore > aScore[i].iScore)//�����һ��Ū��ȥ
		{
			for (j = 8 ;j >= i;j--)
			{
				/*memcpy(&aScore[j+i],&aScore[j],sizeof(Score));*/
			strcpy(aScore[j+1].aName,aScore[j].aName);
			aScore[j + 1].iScore = aScore[j].iScore;//�ѳɼ�������������Ūһλ
			}
			system("cls");
			SwitchCursor(1);//��������ʾ���
			printf("\t\t\t���������������Enterȷ��\n");
			gets(aScore[i].aName);//�����������
			aScore[i].iScore = iScore;//������ҷ���
			SwitchCursor(0);//���ع��
			break;//�˳�ѭ��
		}
	}
	//�۽������е�����д��dat�ļ��������µ����а�
	WriteScore(aScore);
}
/******************************************
[��������]		InitSnake
[��������]		��ʼ����
[��    ��]		����:pSnake �ߵ����Խṹ��
				���:pSnake �ߵ����Խṹ��
[�� �� ֵ]		��
*******************************************/
void InitSnake(Snake* pSnake)
{
	int i=0;
	//��ʼ���ṹ���Ա��ʹ����Ϊ3���������ҡ�����Ϊnull
	pSnake->eDir=RIGHT;
	pSnake->len=LEN;
	pSnake->pHead=NULL;
	for(i=0;i<LEN;i++)
	{
		AddNode(i+3,3,pSnake);//���ӽڵ�
	}
}
/******************************************
[��������]		AddNode
[��������]		��ӽڵ�
[��    ��]		����:iX ������
                     iY ������
                     pSnake �ߵ����Խṹ��
				���:pSnake �ߵ����Խṹ��
[�� �� ֵ]		��
*******************************************/
void AddNode(int iX,int iY,Snake* pSnake)
{
	//����ڵ㣬�����ٿɿ��ڴ湩��������ʹ��
	Body* pNode=(Body*)malloc(sizeof(Body));
	//�Ѻ��������긳��pNode
	pNode->iX=iX;
	pNode->iY=iY;
	//ͷ�巨����ڵ�
	pNode->next=pSnake->pHead;
	pSnake->pHead=pNode;
}
/*******************************************************************************
[��������]		EndGame
[��������]		��Ϸ�������ͷ��ߡ�malloc()��������Ŀռ䣬��Ҫfree()�����ͷš�
[��    ��]		����:pSnake �ߵ����Խṹ��
				���:��
[�� �� ֵ]		��
********************************************************************************/
void EndGame(Snake* pSnake)
{
	Body* pNode;//�����µĽڵ�
	while (pSnake->pHead!=NULL)//���������ߣ�����
	{
		pNode=pSnake->pHead;//ͷ�ڵ㸳ֵ��Node
		pSnake->pHead=pSnake->pHead->next; //ͷ������һλ
		free(pNode);//�ͷ�pNode
	}
	free(pSnake);//�ͷ���
}
/******************************************
[��������]		Move
[��������]		�ƶ���ͷ
[��    ��]		����:pSnake �ߵ����Խṹ��
				���:pSnake �ߵ����Խṹ��
[�� �� ֵ]		��
*******************************************/
void Move(Snake* pSnake)//�����ƶ�����
{
	int iX=pSnake->pHead->iX;
	int iY=pSnake->pHead->iY;
	switch(pSnake->eDir)//����switch��䣬�ж��ߵ��ƶ�����Ȼ�����AddNode���������Ӧ������
	{
	//�����ƶ��ķ������AddNode��������������
	case UP:AddNode(iX,iY-1,pSnake);break;//���������ֻ��������-1
	case DOWN:AddNode(iX,iY+1,pSnake);break;//���������ֻ��������+1
	case LEFT:AddNode(iX-1,iY,pSnake);break;//���������ֻ�������-1
	case RIGHT:AddNode(iX+1,iY,pSnake);break;//���������ֻ�������+1
	}
}
/******************************************
[��������]		RemoveNode
[��������]		����β�ڵ�
[��    ��]		����:pSnake �ߵ����Խṹ��
				���:pSnake �ߵ����Խṹ��
[�� �� ֵ]		��
*******************************************/
void RemoveNode(Snake* pSnake)
{
	Body* pNode=pSnake->pHead;
	Body* pTempNode;
	//�������������ڶ���β�ڵ�
	while(pNode->next!=NULL)
	{
		pTempNode=pNode;
		pNode=pNode->next;//����һλ��β�ڵ�
	}
	Location(pNode->iX*2+1,pNode->iY+3);
	printf("  ");
	pTempNode->next=NULL;//�ÿ�β�ڵ�
	free(pNode);//free��β�ڵ�
}
/******************************************
[��������]		KeyPress
[��������]		��÷���
[��    ��]		����:pSnake �ߵ����Խṹ��
				���:pSnake �ߵ����Խṹ��
[�� �� ֵ]		��
*******************************************/
void KeyPress(Snake* pSnake)
{
	int iInput=0;//��������źŵı���
	if (kbhit())//kbhit��شӼ���������ź�
	{
		iInput=getch();//��ȡ������ź�
		switch(iInput)
		{
		case 'a':
		case 'A':
			{
				if(pSnake->eDir!=RIGHT)
				{
					pSnake->eDir=LEFT;//a��A�����ֻ׼����
				}
				break;
			}
		case 'd':
		case 'D':
			{
				if(pSnake->eDir!=LEFT)
				{
					pSnake->eDir=RIGHT;//d��D�����ֻ׼���Ҷ�
				}
				break;
			}
		case 'w':
		case 'W':
			{
				if(pSnake->eDir!=DOWN)
				{
					pSnake->eDir=UP;//w��W�����ֻ׼���϶�
				}
				break;
			}
		case 's':
		case 'S':
			{
				if(pSnake->eDir!=UP)
				{
					pSnake->eDir=DOWN;//s��S�����ֻ׼���¶�
				}
				break;
			}
		case ' ':system("pause>>null");break;//���¿ո����ͣ���߼���
		}
	}
}
/*************************************
[��������]		MakeFood
[��������]		����ʳ��
[��    ��]		����:pFood ʳ��ṹ��
				���:pFood ʳ��ṹ��
[�� �� ֵ]		��
**************************************/
void MakeFood(Food* pFood,Snake* pSnake)
{
	/*int iX = 0;
	int iY = 0;
	srand(time(NULL));*/
	int iX=rand()%WIDTH;//���������
	int iY=rand()%HEIGHT;
	while(CheckBody(iX,iY,pSnake))//�ж���������꣬��ʳ����������ʱ�����������ʳ��
	{
		iX=rand()%WIDTH;
	    iY=rand()%HEIGHT;
	}
	//���ʳ�ﲻ�������ϣ���iX,iY����pFood�������µ�ʳ��
	pFood->iX=iX;
	pFood->iY=iY;
	Location(pFood->iX*2+1,pFood->iY+3);//����ʳ���λ�ò���ӡʳ��
	printf("��");
}
/***************************************************
[��������]		CheckBody
[��������]		���������жϴ���������Ƿ���������
[��    ��]		����:iX ������
                     iY ������
                     pSnake �ߵ����Խṹ��
				���:TRUE ��������
                     FALSE ����������
[�� �� ֵ]		BOOLֵ
****************************************************/
BOOL CheckBody(int iX,int iY,Snake* pSnake)
{
	Body* pNode=pSnake->pHead->next;//����ṹ��ָ��pNode
	while(pNode!=NULL)
	{
		if (pNode->iX==iX&&pNode->iY==iY)//���ʳ���������Ͼͷ���1��ʹѭ������
		{
			return TRUE;
		}
		pNode=pNode->next;//pNode����һλ
	}
	return FALSE;//��pNodeһ��ʼΪ�գ��ͷ���0
}