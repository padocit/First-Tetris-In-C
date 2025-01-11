#include "common.h"
#include "blockStageControl.h"
#include "keyCurControl.h"
#include "scoreLevelControl.h"

#define START_CURPOS_X	(5*2)
#define START_CURPOS_Y	0

int main(void)
{
	InitKeyDelayRate(5);

	RemoveCursor();

	DrawGameBoard();

	ShowCurrentScoreAndLevel();

	while (1)
	{
		InitNewBlockPos(START_CURPOS_X, START_CURPOS_Y);

		ChooseBlock();

		if (IsGameOver())
			break;

		while (1)
		{
			if (!BlockDown())
			{
				break;
			}
			if (ProcessKeyInput()) // True = Down Arrow
				break;    
		}
	}

	SetCurrentCursorPos(10, 10);
	puts("GAME OVER ^^¢¾");
	Sleep(1000);
	SetCurrentCursorPos(30, 21);
	printf("Made by. padocit ¢Ü ");
	SetCurrentCursorPos(10, 22);
	Sleep(1000);
	return 0;
}
