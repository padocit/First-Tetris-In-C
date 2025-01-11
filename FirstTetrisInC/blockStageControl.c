/* blockStageControl.c
 * Block and Stage Control - Definition
 */

#include "common.h"
#include "blockInfo.h"
#include "point.h"
#include "keyCurControl.h"

// Game Board size
#define GBOARD_WIDTH	10
#define GBOARD_HEIGHT	20

// Game Board Position
#define GBOARD_ORIGIN_X	4
#define GBOARD_ORIGIN_Y	2

static int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2] = { 0, };
static point blockCoord[4];
static int blockIdx;

// Block size = Collider
static int blockWidth;   // Right edge, need to add to cursor position
static int blockLength;  // Bottom edge, need to add to cursor position

static int currentBlockModel;     // Index
static int curPosX, curPosY;
static int rotateSte;

void DrawSolidBlocks(void)
{
	int cursX, cursY;

	for (int y = 0; y < GBOARD_HEIGHT; ++y)
	{
		for (int x = 1; x < GBOARD_WIDTH + 1; ++x)
		{
			cursX = x * 2 + GBOARD_ORIGIN_X;
			cursY = y + GBOARD_ORIGIN_Y;
			SetCurrentCursorPos(cursX, cursY);

			if (gameBoardInfo[y][x] == 1)
				printf("■");
			else
				printf("  ");
		}
	}
}

// Complex..
void RemoveFillUpLine(void)    
{
	int x,y;
	int line;

	for (y = GBOARD_HEIGHT - 1; y > 0; --y)
	{
		for (x = 1; x < GBOARD_WIDTH + 1; ++x)
		{
			if (gameBoardInfo[y][x] != 1)
				break;
		}
		
		if (x == (GBOARD_WIDTH + 1))    // Filled up line
		{
			for (line = 0; y - line > 0; ++line)       
			{
				memcpy(&gameBoardInfo[y - line][1], 
					&gameBoardInfo[(y - line) - 1][1], 
					GBOARD_WIDTH * sizeof(int));
			}

			++y;   // Check current row again (Because upper blocks went down)
			AddGameScore(10);
			ShowCurrentScoreAndLevel();
		}
	}

	DrawSolidBlocks();
}

void SolidCurrentBlock(void)
{
	while (BlockDown());
}

// Collision Detection
// 1 = Collided, 0 = Not Collided
int DetectCollision(int xPos, int yPos, char blockmodel[][4])    
{
	int arrX;
	int arrY;
	arrX = (xPos - GBOARD_ORIGIN_X) / 2;
	arrY = yPos - GBOARD_ORIGIN_Y;

	for (int x = 0; x < 4; ++x)
	{
		for (int y = 0; y < 4; ++y)
		{
			if (blockmodel[y][x] == 1 && gameBoardInfo[arrY + y][arrX + x] == 1)
				return 1;
		}
	}

	return 0;
}

void FreezeBlock(void)
{
	int arrX;
	int arrY;
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			arrX = (curPosX - GBOARD_ORIGIN_X) / 2;
			arrY = curPosY - GBOARD_ORIGIN_Y;

			if (blockModel[GetCurrentBlockIdx()][y][x] == 1)
				gameBoardInfo[arrY + y][arrX + x] = 1;
		}
	}
}

int IsGameOver(void)
{
	if (DetectCollision(curPosX, curPosY, blockModel[GetCurrentBlockIdx()]))
		return 1;
	else
		return 0;
}

// Init new block position (Cursor Position)
void InitNewBlockPos(int x, int y)
{
	if (x < 0 || y < 0)
		return;

	curPosX = x;
	curPosY = y;

	SetCurrentCursorPos(x, y);
}

// Choose a random block shape
void ChooseBlock(void)
{
	srand((int)time(NULL));
	currentBlockModel = (rand() % NUM_OF_BLOCK_MODEL) * 4;
}

// Current block = the block we need to print now
int GetCurrentBlockIdx(void)
{
	return currentBlockModel + rotateSte;
}

// Print block by Index
void ShowBlock(char blockInfo[][4])
{
	point curPos = GetCurrentCursorPos();
	blockIdx = 0;
	/*
	blockWidth = 0;
	blockLength = 0;
	*/
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			SetCurrentCursorPos(curPos.x + (x * 2), curPos.y + y);
			if (blockInfo[y][x] == 1)
			{
				printf("■");
				blockCoord[blockIdx++] = GetCurrentCursorPos();
				/*
				if (blockWidth < x + 1)
					blockWidth = x + 1;
				if (blockLength < y + 1)
					blockLength = y + 1;
					*/
			}
		}
	}
	SetCurrentCursorPos(curPos.x, curPos.y);    //커서 원위치.
}

// Delete block on current cursor position
void DeleteBlock(char blockInfo[][4])
{
	point curPos = GetCurrentCursorPos();

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			SetCurrentCursorPos(curPos.x + (x * 2), curPos.y + y);
			if (blockInfo[y][x] == 1)
				printf("  ");               // 2 space = Block width
		}
	}
	SetCurrentCursorPos(curPos.x, curPos.y);    // Cursor reset
}

// Block down only one row.
// Return 0 = Collided
int BlockDown(void)
{
	if (DetectCollision(curPosX, curPosY + 1, blockModel[GetCurrentBlockIdx()]))
	{
		FreezeBlock();
		RemoveFillUpLine();
		return 0;
	}

	DeleteBlock(blockModel[GetCurrentBlockIdx()]);
	curPosY += 1;
	
	SetCurrentCursorPos(curPosX, curPosY);
	ShowBlock(blockModel[GetCurrentBlockIdx()]);

	return 1;
}

void BlockMoveLeft(void)
{
	if (DetectCollision(curPosX-2, curPosY, blockModel[GetCurrentBlockIdx()]))
		return;

	DeleteBlock(blockModel[GetCurrentBlockIdx()]);
	curPosX -= 2;

	SetCurrentCursorPos(curPosX, curPosY);
	ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

void BlockMoveRight(void)
{
	if (DetectCollision(curPosX + 2, curPosY, blockModel[GetCurrentBlockIdx()]))
		return;

	DeleteBlock(blockModel[GetCurrentBlockIdx()]);
	curPosX += 2;

	SetCurrentCursorPos(curPosX, curPosY);
	ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

// No rotate if already collideds
// Update Block right,bottom collision
void BlockRotate(void)  
{
	int nextSte;
	int beforeRotSte = rotateSte;

	DeleteBlock(blockModel[GetCurrentBlockIdx()]);

	nextSte = rotateSte + 1;
	nextSte %= 4;
	rotateSte = nextSte;
	
	if (DetectCollision(curPosX, curPosY, blockModel[GetCurrentBlockIdx()])) 
	{
		rotateSte = beforeRotSte;
		return;
	}

	SetCurrentCursorPos(curPosX, curPosY);
	ShowBlock(blockModel[GetCurrentBlockIdx()]);
}


// Draw GameBoard to Console
void DrawGameBoard(void)
{
	// Visual
	for (int y = 0; y <= GBOARD_HEIGHT; ++y)
	{
		SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);

		if (y == GBOARD_HEIGHT)
			printf("└");
		else
			printf("│");
	}

	for (int y = 0; y <= GBOARD_HEIGHT; ++y)
	{
		SetCurrentCursorPos(
			GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2,  
			GBOARD_ORIGIN_Y + y);

		if (y == GBOARD_HEIGHT)
			printf("┘");
		else
			printf("│");
	}

	for (int x = 1; x < GBOARD_WIDTH + 1; ++x)
	{
		SetCurrentCursorPos(
			GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);

		printf("─");
	}

	SetCurrentCursorPos(0, 0);

	for (int y = 0; y < GBOARD_HEIGHT; ++y)
	{
		gameBoardInfo[y][0] = 1;
		gameBoardInfo[y][GBOARD_WIDTH + 1] = 1;
	}
	for (int x = 0; x < GBOARD_WIDTH + 2; ++x)
	{
		gameBoardInfo[GBOARD_HEIGHT][x] = 1;
	}
}
