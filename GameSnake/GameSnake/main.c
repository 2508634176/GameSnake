/***************************************
[�ļ���]		    main.c
[����ģ���Ŀ��]    ̰����������������
*****************************************/
//�����Զ���ͷ�ļ�
#include "UI.h"
#define _CRT_SECURE_NO_WARNINGS
//��������ʼ
int main()
{
	int iKey=0;
	do
	{
		SwitchCursor(0);//0�������ع��
		MainMenu();//�������˵�����
		iKey = getch();//��ȡһ��ѡ��ť
		switch(iKey)
		{
		case '1':StartGame();break;//���ÿ�ʼ��Ϸ����
		case '2':SnakeRank();break;//�������а���
		case '3':SnakeIntroduce();break;//������Ϸ��������
		case '4':printf("\t\t\t\t��Ϸ�˳�!\n");break;//�˳���Ϸ
		default:printf("error!");break;
		}
	}while(iKey!='4');
system("pause");
return 0;
}

