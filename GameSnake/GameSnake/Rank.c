/******************************************
[�ļ���]		    Rank.c
[����ģ���Ŀ��]    ̰���ߵ����а�����
******************************************/
#include "Rank.h"
#include<stdio.h>
#include<stdlib.h>
/*********************************
[��������]		ReadScore
[��������]	    ��ȡ����
[��    ��]		����:�����е���Ϣ
				���:�������ļ�
[�� �� ֵ]		��
**********************************/
void ReadScore(Score *aScore)
{
	//���ļ�
	FILE *fp = fopen("score.dat","rb");//�����ļ�ָ�룬��ֻ��Ȩ�޴��ļ�
	//�ж��ļ��Ƿ�Ϊ��
	if (fp==NULL)
	{
		return;//���ļ�ֱ�ӷ���
	}
	//��ȡ�ļ�
	if (fread(aScore,sizeof(Score),NUM,fp)==0)
	{
		return;
	}
	//�ر��ļ�
	fclose(fp);
	fp = NULL;//ʹfp����ָ��NULL����ֹҰָ�����
}
/*********************************
[��������]		WriteScore
[��������]	    ��¼�ɼ�
[��    ��]		����:�û��������Ϣ
				���:�������ļ�
[�� �� ֵ]		��
**********************************/
void WriteScore(Score *aScore)
{
	//���ļ�
	FILE *fp = fopen("score.dat","wb");//�����ļ�ָ�룬��ֻдȨ�޴��ļ�
	if (fp==NULL)
	{
		return;
	}
	//д���ļ�
	if (fwrite(aScore,sizeof(Score),NUM,fp)==0)//����ļ�Ϊ�յ�,10��Ҫ����д��size�ֽڵ�������ĸ���
	{
		return;
	}
	//�ر��ļ�
	fclose(fp);
	fp = NULL;//ʹfp����ָ��NULL
}
