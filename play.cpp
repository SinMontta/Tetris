//��Ϸ��Ҫ�߼�

#include"head.h"

static void getUserHit(int *pleft, int *pdown);
static void turnDia(int left, int down);
static int canMove(int newLeft, int newDown);
static void addDia(int left, int down);
static void removeLine(int y);
static int checkFull();
static int gameOver();

extern diaTypeP newDia;
extern int gameBoardArray[12][20];

/**************************************************************
*Function Name	:	playGame
*Description	:	��Ϸ����Ҫ�߼�
*Be called		:	main
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void playGame()
{
	int left, down, wait, speed, score = 0, i, j = 0, level = 0;
	int num,nextNum;
	int *pleft = &left, *pdown = &down;
	
	wait = 0;
	speed = 50;
	left = 3;
	down = -2;	//ʹ�������Ϸ����м��Ϸ���ʼ����
	srand((unsigned)time(NULL));
	num = getNewNum();	//���������ڿ��Ƶķ������һ������
	nextNum = getNewNum();	
	initGameBoardArray();	//��ʼ����Ϸ���
	getNewDia(num);		//��ʼ�����ڿ��Ƶķ���
	
	BeginBatchDraw();
	while (1)
	{
		cleardevice();
		drawGameUI();	//������ϷUI
		drawNextDia(nextNum);	//������һ������
		drawGameScore(score);	//������Ϸ����
		drawGameLevel(level);	//������Ϸ����
		drawGameBoard();	//������Ϸ���
		drawNowDia(left, down);		//�������ڿ��Ƶķ���
		FlushBatchDraw();    //������ͼ���ܣ�����������˸  
		wait++;
		if (kbhit())	//�����̱��û�
		{
			getUserHit(pleft, pdown);
		}
		if (canMove(left, down + 1))	
		{
			if (wait == speed)		
			{
				down++;
				wait = 0;
			}
		}
		//��������������ƶ�����ѷ���д����Ϸ��壬���»���µķ���
		else
		{
			if(wait == speed)
			{ 
				addDia(left, down);
				num = nextNum;
				nextNum = getNewNum();
				getNewDia(num);
				left = 3;
				down = -2;
				wait = 0;
			}
			
		}

		//����Ƿ������У��������������мӷ�����
		for (i = checkFull(); i > 0; i--)
		{
			score += 100;
			j++;
			if (j == 10)
			{
				level++;
				j = 0;
				speed -= 5;
				if (speed < 0)
				{
					speed = 5;
				}
			}
		}
		//�����Ϸ�Ƿ��Ѿ�����������������ѭ��
		if (gameOver())
		{
			cleardevice();
			drawGameOverUI();
			break;
		}
		Sleep(20);	//�߳���ͣ������cpuռ��
	}
	EndBatchDraw();
}

/**************************************************************
*Function Name	:	getUserHit
*Description	:	����û��Ƿ��û������ض���
*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void getUserHit(int *pleft, int *pdown)
{
	int key, left, down;
	left = *pleft;
	down = *pdown;
	key = getch();
	switch (key)
	{
	case'w':
	case'W':
		turnDia(left, down);
		break;
	case'a':
	case'A':
		if (canMove(left - 1, down))
		{
			(*pleft)--;
		}
		break;
	case's':
	case'S':
		if (canMove(left, down + 1))
		{
			(*pdown)++;
		}
		break;
	case'd':
	case'D':
		if (canMove(left + 1, down))
		{
			(*pleft)++;
		}
		break;
	case 13://��ͣ��Ϸ��ֱ��д��ѭ����������
		drawGamePause();
		FlushBatchDraw();
		while (getch()!=13)
		{
			Sleep(100);
		};
		cleardevice();
		break;
	case 32:
		while (canMove(left, *pdown + 1))
		{
			(*pdown)++;
		}
		break;
	default:break;
	}
}

/**************************************************************
*Function Name	:	turnDia
*Description	:	��ת���飬���Է������������ת
*Be called		:	getUserHit
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void turnDia(int left, int down)
{
	int temp[4][4];
	int i, j;
	
	//�����������ת����
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			temp[3 - j][i] = newDia->var[i][j];
		}
	}

	//�ж��Ƿ������ת
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (gameBoardArray[j + left + 1][i + down + 1] && temp[i][j])
			{
				return;//��������ת��ֱ�ӷ���
			}
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			newDia->var[i][j] = temp[i][j];
		}
	}
}

/**************************************************************
*Function Name	:	canMove
*Description	:	�жϷ����Ƿ�����ƶ�
*Be called		:	playGame��getUserHit
*Input			:	
					newLeft		:	�ƶ����left������д��
									left��1����ʽ
					newDown		:	�ƶ����down������д��
									down��1����ʽ
*Output			:	None
*Return			:	None
**************************************************************/

int canMove(int newLeft, int newDown)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (gameBoardArray[j + newLeft + 1][i + newDown + 1] && newDia->var[i][j])
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

/**************************************************************
*Function Name	:	addDia
*Description	:	�����ڿ��Ƶķ���д����Ϸ���
*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void addDia(int left, int down)
{
	int i, j;
	//������ӣ�ע���±�
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			gameBoardArray[i + left + 1][j + down + 1] += newDia->var[j][i];
		}
	}
}

/**************************************************************
*Function Name	:	removeLine
*Description	:	����
*Be called		:	checkFull
*Input			:	
					y	:	Ҫ��ȥ������
*Output			:	None
*Return			:	None
**************************************************************/

void removeLine(int y)
{
	int i,j;

	//��������
	for (i = 1; i < 11; i++)
	{
		for (j = y; j > 1; j--)
		{
			gameBoardArray[i][j] = gameBoardArray[i][j - 1];
		}
		gameBoardArray[i][1] = 0;
	}
}

/**************************************************************
*Function Name	:	checkFull
*Description	:	����Ƿ����в���������
*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	
					t	:	��ȥ������
**************************************************************/

int checkFull()
{
	int i, j, k = 0, t=0;

	for (j = 1; j < 19; j++)
	{
		for (i = 1; i < 11; i++)
		{
			if (gameBoardArray[i][j])
			{
				k++;//ʹ�ñ������ж��Ƿ�һ�ж���1
			}
		}
		if (k == 10)
		{
			removeLine(j);
			t++;//ʹ�÷���ֵt��ȷ��һ�����˶�����
		}
		k = 0;
	}
	return t;
}

/**************************************************************
*Function Name	:	gameOver()
*Description	:	�ж���Ϸ�Ƿ����
*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	
					TRUE	:	��Ϸ����
					FALSE	:	��Ϸ��û����
**************************************************************/

int gameOver()
{
	int i;

	for (i = 1; i < 11; i++)
	{
		if (gameBoardArray[i][0])
		{
			return TRUE;
		}
	}
	return FALSE;
}