/*��Ϸ��ʼǰ�ĳ�ʼ��*/

#include"head.h"

int gameBoardArray[12][20] = { 0 };		//������Ϸ����ͼ��Ϊȫ�ֱ���

diaTypeP newDia;	//�����ķ��飬Ϊȫ�ֱ���

diaType diaList[7] =
{
	{ { { 0,0,0,0 },{ 0,1,1,0 },{ 0,1,1,0 },{ 0,0,0,0 } }, LIGHTCYAN },
	{ { { 0,0,1,0 },{ 0,0,1,0 },{ 0,1,1,0 },{ 0,0,0,0 } }, YELLOW },
	{ { { 0,1,0,0 },{ 0,1,0,0 },{ 0,1,1,0 },{ 0,0,0,0 } }, GREEN },
	{ { { 0,0,0,0 },{ 0,1,0,0 },{ 1,1,1,0 },{ 0,0,0,0 } }, RED },
	{ { { 0,0,0,0 },{ 0,1,1,0 },{ 1,1,0,0 },{ 0,0,0,0 } }, MAGENTA },
	{ { { 0,0,0,0 },{ 1,1,0,0 },{ 0,1,1,0 },{ 0,0,0,0 } }, CYAN },
	{ { { 0,0,0,0 },{ 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 } }, BROWN },
};	//7�ֲ�ͬ�ķ���

/**************************************************************
*Function Name	:	initGameBoardArray
*Description	:	��ʼ����Ϸ����ͼ������Ȧ��Χǽ�ж��Ƿ����
					�������£�
					100000000001
					100000000001
					100000000001
					100000000001
					100000000001
					100000000001
					100000000001
					100000000001
					100000000001
					100000000001
					100000000001
					100000000001
					100000000001
					100000000001
					100000000001
					100000000001
					100000000001
					100000000001
					100000000001
					111111111111

*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void initGameBoardArray()
{
	int i;
	for (i = 0; i < 12; i++)
	{
		gameBoardArray[i][19] = 1;
	}
	for (i = 0; i < 20; i++)
	{
		gameBoardArray[0][i] = 1;
		gameBoardArray[11][i] = 1;
	}
}

/**************************************************************
*Function Name	:	getNewNum
*Description	:	��ȡ�µ������
*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	
					num		:	�����
**************************************************************/

int getNewNum()
{
	int num;
	num = rand() % 7;
	return num;
}

/**************************************************************
*Function Name	:	getNewDia
*Description	:	��ȡ�¿��Ƶķ���
*Be called		:	playGame
*Input			:	
					num		:	������������������
*Output			:	None
*Return			:	None
**************************************************************/

void getNewDia(int num)
{
	int i,j;

	//���Ʒ���
	newDia = (diaTypeP)malloc(sizeof(diaType));
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			newDia->var[i][j] = diaList[num].var[i][j];
		}
	}
	newDia->color = diaList[num].color;
}

