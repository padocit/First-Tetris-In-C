/* keyCurControl.c
 * Keyboard and Cursor Control - Definition
*/

#include "common.h"
#include "point.h"
#include "blockStageControl.h"

#define KEY_SENSITIVE	100
#define SYS_DELAY	20

#define ARROW 224
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

static int keyDelayRate;    // Fast speed if it's big

// Remove Cursor Blinking
void RemoveCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

// Get Cursor Position in Console
point GetCurrentCursorPos(void)
{
	point curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curPoint.x = curInfo.dwCursorPosition.X;
	curPoint.y = curInfo.dwCursorPosition.Y;

	return curPoint;
}

// Set Cursor Position in Console
void SetCurrentCursorPos(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// Down Arrow = return 1
int ProcessKeyInput(void)
{
	int key;
	
	for (int i = 0; i < KEY_SENSITIVE; ++i)
	{
		if (_kbhit())
		{
			key = _getch();

			if (key == ARROW)
			{
				key = _getch();

				switch (key)
				{
				case UP:
					BlockRotate();
					break;
				case LEFT:
					BlockMoveLeft();
					break;
				case RIGHT:
					BlockMoveRight();
					break;
				case DOWN:
					SolidCurrentBlock();
					return 1;
				}
			}
		}
		if (i % keyDelayRate == 0)          //keyDelayRate의 배수마다 Sleep함수 호출
			Sleep(SYS_DELAY);
	}
	return 0;
}

// Speed Control
void InitKeyDelayRate(int rate)
{
	if (rate < 1)
		return;
	keyDelayRate = rate;
}

void KeyDelaySpeedCtl(int addSpeed)
{
	keyDelayRate += addSpeed;
}
/* end of file */