/*一些画出界面的方法*/

#include"head.h"

extern diaType diaList[7];
extern diaTypeP newDia;
extern int gameBoardArray[12][20];

/**************************************************************
*Function Name	:	drawGameStarUI
*Description	:	画出开始游戏主界面
*Be called		:	main()
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void drawGameStarUI()
{
	settextstyle(30, 0, _T("黑体"));
	TCHAR s[] = _T("请按回车开始游戏");
	outtextxy(300, 400, s);
}

/**************************************************************
*Function Name	:	drawGameUI
*Description	:	画出游戏主界面
*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void drawGameUI()
{
	setfillstyle(BS_HATCHED, HS_BDIAGONAL);
	setfillcolor(RED);
	bar(0, 0, 541, 20);
	bar(0, 20, 20, 940);
	bar(521, 20, 541, 940);
	bar(20, 920, 521, 940);

	setlinecolor(WHITE);
	setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 2);
	line(560, 0, 560, 940);

	settextstyle(20, 0, _T("黑体"));
	TCHAR s1[] = _T("下一个");
	outtextxy(670, 30, s1);
	TCHAR s2[] = _T("等级");
	outtextxy(680, 350, s2);
	TCHAR s3[] = _T("得分");
	outtextxy(680, 500, s3);
	TCHAR s4[] = _T("操作说明");
	outtextxy(660, 650, s4);
	settextstyle(16, 0, _T("黑体"));
	TCHAR s5[] = _T("w,a,s,d控制方向，");
	outtextxy(640, 730, s5);
	TCHAR s6[] = _T("回车键暂停，");
	outtextxy(650, 760, s6);
	TCHAR s7[] = _T("空格键快速下落。");
	outtextxy(640, 790, s7);
}

/**************************************************************
*Function Name	:	drawDiamond
*Description	:	画出一格方块
*Be called		:	drawGameBoard、drawNowDia
*Input			:	
					x		:	方块相对于游戏地图坐标系的x坐标
					y		:	方块相对于游戏地图坐标系的x坐标
					color	:	方块颜色
*Output			:	None
*Return			:	None
**************************************************************/

void drawDiamond(int x,int y, COLORREF color)
{
	setlinestyle(PS_SOLID,2);
	setlinecolor(LIGHTGRAY);
	setfillstyle(BS_SOLID);
	setfillcolor(color);
	fillrectangle(
		 x*diamondWidth + 20,
		 y*diamondHeigth + 20,
		(x + 1)*diamondWidth + 20,
		(y + 1)*diamondHeigth + 20);
}

/**************************************************************
*Function Name	:	drawNextDia
*Description	:	画出下一个方块
*Be called		:	playGame
*Input			:	
					num		:	随机数，代表方块的类型
*Output			:	None
*Return			:	None
**************************************************************/

void drawNextDia(int num)
{
	int i, j;

	getNewNum();

	setlinestyle(PS_SOLID, 2);
	setlinecolor(LIGHTGRAY);
	setfillstyle(BS_SOLID);
	setfillcolor(diaList[num].color);

	for (i = 0; i < 4; i++)
	{ 
		for (j = 0; j < 4; j++)
		{
			if (diaList[num].var[i][j])
			{
				fillrectangle(
					j*diamondWidth + 600,
					i*diamondHeigth + 100,
					(j + 1)*diamondWidth + 600,
					(i + 1)*diamondHeigth + 100);
			}
		}
	}
}

/**************************************************************
*Function Name	:	drawNowDia
*Description	:	画出现在控制的方块
*Be called		:	playGame
*Input			:	
					down	:	向下移动的格数
					left	:	向右移动的格数
*Output			:	None
*Return			:	None
**************************************************************/

void drawNowDia(int left, int down)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (newDia->var[i][j])
			{
				if (i + down > -1)
				{
					drawDiamond(j + left, i + down, newDia->color);
				}
			}
		}
	}
}

/**************************************************************
*Function Name	:	drawGameBoard
*Description	:	画出游戏面板
*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void drawGameBoard()
{
	int i, j;

	for (i = 1; i < 11; i++)
	{
		for (j = 1; j < 19; j++)
		{
			if (gameBoardArray[i][j])
			{
				drawDiamond(i - 1, j - 1, WHITE);
			}
		}
	}
}

/**************************************************************
*Function Name	:	drawGamePause
*Description	:	画出游戏暂停
*Be called		:	getUserHit
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void drawGamePause()
{
	settextstyle(30, 0, _T("黑体"));
	TCHAR s[] = _T("游戏暂停");
	outtextxy(220, 400, s);
}

/**************************************************************
*Function Name	:	drawGameOverUI
*Description	:	画出游戏结束画面
*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void drawGameOverUI()
{
	settextstyle(30, 0, _T("黑体"));
	TCHAR s[] = _T("游戏结束！你输了！");
	outtextxy(300, 400, s);
}

/**************************************************************
*Function Name	:	drawGameScore
*Description	:	画出游戏得分
*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void drawGameScore(int score)
{
	settextstyle(16, 0, _T("黑体"));
	TCHAR s[10];
	_stprintf(s, _T("%d"), score);
	outtextxy(680, 550, s);
}

/**************************************************************
*Function Name	:	drawGameLevel
*Description	:	画出游戏等级
*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void drawGameLevel(int level)
{
	settextstyle(16, 0, _T("黑体"));
	TCHAR s[10];
	_stprintf(s, _T("%d"), level);
	outtextxy(690, 400, s);
}