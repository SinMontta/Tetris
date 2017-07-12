/*һЩ��������ķ���*/

#include"head.h"

extern diaType diaList[7];
extern diaTypeP newDia;
extern int gameBoardArray[12][20];

/**************************************************************
*Function Name	:	drawGameStarUI
*Description	:	������ʼ��Ϸ������
*Be called		:	main()
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void drawGameStarUI()
{
	settextstyle(30, 0, _T("����"));
	TCHAR s[] = _T("�밴�س���ʼ��Ϸ");
	outtextxy(300, 400, s);
}

/**************************************************************
*Function Name	:	drawGameUI
*Description	:	������Ϸ������
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

	settextstyle(20, 0, _T("����"));
	TCHAR s1[] = _T("��һ��");
	outtextxy(670, 30, s1);
	TCHAR s2[] = _T("�ȼ�");
	outtextxy(680, 350, s2);
	TCHAR s3[] = _T("�÷�");
	outtextxy(680, 500, s3);
	TCHAR s4[] = _T("����˵��");
	outtextxy(660, 650, s4);
	settextstyle(16, 0, _T("����"));
	TCHAR s5[] = _T("w,a,s,d���Ʒ���");
	outtextxy(640, 730, s5);
	TCHAR s6[] = _T("�س�����ͣ��");
	outtextxy(650, 760, s6);
	TCHAR s7[] = _T("�ո���������䡣");
	outtextxy(640, 790, s7);
}

/**************************************************************
*Function Name	:	drawDiamond
*Description	:	����һ�񷽿�
*Be called		:	drawGameBoard��drawNowDia
*Input			:	
					x		:	�����������Ϸ��ͼ����ϵ��x����
					y		:	�����������Ϸ��ͼ����ϵ��x����
					color	:	������ɫ
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
*Description	:	������һ������
*Be called		:	playGame
*Input			:	
					num		:	������������������
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
*Description	:	�������ڿ��Ƶķ���
*Be called		:	playGame
*Input			:	
					down	:	�����ƶ��ĸ���
					left	:	�����ƶ��ĸ���
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
*Description	:	������Ϸ���
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
*Description	:	������Ϸ��ͣ
*Be called		:	getUserHit
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void drawGamePause()
{
	settextstyle(30, 0, _T("����"));
	TCHAR s[] = _T("��Ϸ��ͣ");
	outtextxy(220, 400, s);
}

/**************************************************************
*Function Name	:	drawGameOverUI
*Description	:	������Ϸ��������
*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void drawGameOverUI()
{
	settextstyle(30, 0, _T("����"));
	TCHAR s[] = _T("��Ϸ�����������ˣ�");
	outtextxy(300, 400, s);
}

/**************************************************************
*Function Name	:	drawGameScore
*Description	:	������Ϸ�÷�
*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void drawGameScore(int score)
{
	settextstyle(16, 0, _T("����"));
	TCHAR s[10];
	_stprintf(s, _T("%d"), score);
	outtextxy(680, 550, s);
}

/**************************************************************
*Function Name	:	drawGameLevel
*Description	:	������Ϸ�ȼ�
*Be called		:	playGame
*Input			:	None
*Output			:	None
*Return			:	None
**************************************************************/

void drawGameLevel(int level)
{
	settextstyle(16, 0, _T("����"));
	TCHAR s[10];
	_stprintf(s, _T("%d"), level);
	outtextxy(690, 400, s);
}