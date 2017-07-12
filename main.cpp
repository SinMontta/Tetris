#include"head.h"

void main()
{
	initgraph(840, 940);
	cleardevice();
	drawGameStarUI();
	if (getch() == 13)
	{
		playGame();
	}
	getch();
	closegraph();


}