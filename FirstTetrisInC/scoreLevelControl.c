#include "common.h"
#include "keyCurControl.h"

#define LEVEL_DIFF	2   // Level to Speedup
#define LEVEL_UP_SCORE_DIFF	20   // Score to Levelup

static int curGameLevel = 1;
static int curGameScore = 0;

void ShowCurrentScoreAndLevel(void)
{
	SetCurrentCursorPos(30, 4);
	printf("¢¾ Level : %d		¢¾", curGameLevel);

	SetCurrentCursorPos(30, 7);
	printf("¢¾ Score : %d		¢¾", curGameScore);

	SetCurrentCursorPos(30, 11);
	printf("          ¡è Rotate    ");
	SetCurrentCursorPos(30, 14);
	printf("Move L ¡ç    ¡æ Move R ");
	SetCurrentCursorPos(30, 17);
	printf("          ¡é Drop    ");
}

void GameLevelUp(void)
{
	++curGameLevel;
	KeyDelaySpeedCtl(LEVEL_DIFF);
}

void AddGameScore(int score)
{
	if (score < 1)
		return;

	curGameScore += score;

	// Level up (by score)
	if (curGameScore >= curGameLevel * LEVEL_UP_SCORE_DIFF)
		GameLevelUp();
}