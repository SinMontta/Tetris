/*游戏开始前的初始化*/

#include"head.h"

int gameBoardArray[12][20] = { 0 };		//创建游戏面板地图，为全局变量

diaTypeP newDia;	//操作的方块，为全局变量

diaType diaList[7] =
{
	{ { { 0,0,0,0 },{ 0,1,1,0 },{ 0,1,1,0 },{ 0,0,0,0 } }, LIGHTCYAN },
	{ { { 0,0,1,0 },{ 0,0,1,0 },{ 0,1,1,0 },{ 0,0,0,0 } }, YELLOW },
	{ { { 0,1,0,0 },{ 0,1,0,0 },{ 0,1,1,0 },{ 0,0,0,0 } }, GREEN },
	{ { { 0,0,0,0 },{ 0,1,0,0 },{ 1,1,1,0 },{ 0,0,0,0 } }, RED },
	{ { { 0,0,0,0 },{ 0,1,1,0 },{ 1,1,0,0 },{ 0,0,0,0 } }, MAGENTA },
	{ { { 0,0,0,0 },{ 1,1,0,0 },{ 0,1,1,0 },{ 0,0,0,0 } }, CYAN },
	{ { { 0,0,0,0 },{ 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 } }, BROWN },
};	//7种不同的方块

/**************************************************************
*Function Name	:	initGameBoardArray
*Description	:	初始化游戏面板地图，最外圈作围墙判断是否出界
					数组如下：
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
*Description	:	获取新的随机数
*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	
					num		:	随机数
**************************************************************/

int getNewNum()
{
	int num;
	num = rand() % 7;
	return num;
}

/**************************************************************
*Function Name	:	getNewDia
*Description	:	获取新控制的方块
*Be called		:	playGame
*Input			:	
					num		:	随机数，代表方块的类型
*Output			:	None
*Return			:	None
**************************************************************/

void getNewDia(int num)
{
	int i,j;

	//复制方块
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

