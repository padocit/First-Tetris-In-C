#ifndef __CURSORACCESS_H__
#define __CURSORACCESS_H__

void DrawSolidBlocks(void);
void RemoveFillUpLine(void);

int DetectCollision(int xPos, int yPos, char blockmodel[][4]);
void FreezeBlock(void);
int IsGameOver(void);

void InitNewBlockPos(int x, int y);
void ChooseBlock(void);
int GetCurrentBlockIdx(void);

void ShowBlock(char blockInfo[][4]);
void DeleteBlock(char blockInfo[][4]);
int BlockDown(void);

void BlockMoveLeft(void);
void BlockMoveRight(void);
void BlockRotate(void);

void DrawGameBoard(void);

#endif