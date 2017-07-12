#pragma once
#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

#define TURE 1
#define FALSE 0
#define diamondWidth  50
#define diamondHeigth  50

typedef struct
{
	int var[4][4];
	COLORREF color;		//标记方块颜色
}diaType, *diaTypeP;

void initGameBoardArray();
int getNewNum();
void getNewDia(int num);
void playGame();
void drawGameUI();
void drawDiamond(int x, int y, COLORREF color);
void drawNextDia(int num);
void drawNowDia(int left, int down);
void drawGameStarUI();
void drawGameBoard();
void drawGamePause();
void drawGameOverUI();
void drawGameScore(int score);
void drawGameLevel(int level);