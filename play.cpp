//游戏主要逻辑

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
*Description	:	游戏的主要逻辑
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
	down = -2;	//使方块从游戏面板中间上方开始下落
	srand((unsigned)time(NULL));
	num = getNewNum();	//随机获得正在控制的方块和下一个方块
	nextNum = getNewNum();	
	initGameBoardArray();	//初始化游戏面板
	getNewDia(num);		//初始化正在控制的方块
	
	BeginBatchDraw();
	while (1)
	{
		cleardevice();
		drawGameUI();	//画出游戏UI
		drawNextDia(nextNum);	//画出下一个方块
		drawGameScore(score);	//画出游戏分数
		drawGameLevel(level);	//画出游戏级别
		drawGameBoard();	//画出游戏面板
		drawNowDia(left, down);		//画出正在控制的方块
		FlushBatchDraw();    //用批绘图功能，可以消除闪烁  
		wait++;
		if (kbhit())	//当键盘被敲击
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
		//如果不能再向下移动，则把方块写入游戏面板，重新获得新的方块
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

		//检查是否有满行，若有满行则消行加分升级
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
		//检查游戏是否已经结束，结束则跳出循环
		if (gameOver())
		{
			cleardevice();
			drawGameOverUI();
			break;
		}
		Sleep(20);	//线程暂停，减少cpu占用
	}
	EndBatchDraw();
}

/**************************************************************
*Function Name	:	getUserHit
*Description	:	检测用户是否敲击键盘特定键
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
	case 13://暂停游戏，直接写个循环让他卡着
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
*Description	:	旋转方块，即对方块数组进行旋转
*Be called		:	getUserHit
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void turnDia(int left, int down)
{
	int temp[4][4];
	int i, j;
	
	//进行数组的旋转复制
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			temp[3 - j][i] = newDia->var[i][j];
		}
	}

	//判断是否可以旋转
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (gameBoardArray[j + left + 1][i + down + 1] && temp[i][j])
			{
				return;//不可以旋转，直接返回
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
*Description	:	判断方块是否可以移动
*Be called		:	playGame、getUserHit
*Input			:	
					newLeft		:	移动后的left，建议写成
									left±1的形式
					newDown		:	移动后的down，建议写成
									down±1的形式
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
*Description	:	把正在控制的方块写入游戏面板
*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void addDia(int left, int down)
{
	int i, j;
	//数组相加，注意下标
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
*Description	:	消行
*Be called		:	checkFull
*Input			:	
					y	:	要消去的行数
*Output			:	None
*Return			:	None
**************************************************************/

void removeLine(int y)
{
	int i,j;

	//数组运算
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
*Description	:	检测是否满行并进行消行
*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	
					t	:	消去的行数
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
				k++;//使用变量来判断是否一行都是1
			}
		}
		if (k == 10)
		{
			removeLine(j);
			t++;//使用返回值t来确定一次消了多少行
		}
		k = 0;
	}
	return t;
}

/**************************************************************
*Function Name	:	gameOver()
*Description	:	判断游戏是否结束
*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	
					TRUE	:	游戏结束
					FALSE	:	游戏还没结束
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