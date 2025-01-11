# First Tetris In C

> My first Tetris game!

- CS50X Final Project
- Language: C

**Video**: https://youtu.be/_uBu5GijA3Y?si=SaGuHGaYwO4erBjJ

**Screenshot**:

![First Tetris in C (CS50X Final Project) - YouTube](https://github.com/user-attachments/assets/ca67680a-e342-45ad-b350-74513153ef21)

---

# Contents

- common.h
- blockInfo.h

1. tetrisMain.c
2. keyCurControl.c
3. blockStageControl.c
4. scoreLevelControl.c



## common.h
This is a header file that collects the headers of basic C libraries available in Windows.
It is convenient for future inclusion. We only need to include this header.

```
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
```

## blockInfo.h
This is a file that creates all the block shapes that can be created in the Tetris game.
You can think of it as similar to the method of drawing a map with 0 and 1 in a 2D game and mapping it with a tilemap.

Ex.
```
char blockModel[][4][4] =
{
	/* ■
	   ■ ■ ■  */
	{
		{0,0,0,0},
		{1,0,0,0},
		{1,1,1,0},
		{0,0,0,0} },
}
```

## tetrisMain.c
tetrisMain.c literally has the main function. There are 3 parts.
It contains the initialization of game, the main while loop, and finally outputs credits and exits.

Initialization: Init the game.
    Init Key Delay Rate -> Remove Cursor -> Draw Game Board -> Show Current Score And Level

Main Loop: Update game and Render it.
    Init New Block Pos -> Choose Block(Random Shape) -> Is Game Over? -> Block Down, Process Key Input

End: Print credits

## keyCurControl.c
Controls the keyboard and cursor according to the input.
At this time, we use the classic library 'consoleapi2.h' provided by MS to conveniently handle the console window cursor such as `GetConsoleCursorInfo()` and `SetConsoleCursorInfo()`.
Define and adjust the operation method and operation sensitivity, etc.

- Remove Cursor
- Get Current Cursor Position
- Set Current Cursor Position
- Process Key Input
- Init Key Delay Rate
- Key Delay Speed Control


## blockStageControl.c
Controls the size and position of the Game Board where Tetris is played, and defines and handles drawing Tetris blocks, erasing a line, collision detection, block freezing, game over, block rotation, etc.

(In fact, it can be called the Tetris basic Gamemode - logic)

- Draw Solid Blocks
- Remove Fill Up Line
- Solid Current Block
- Detect Collision
- Freeze Block
- Is Game Over
- Init New Block Pos
- Choose Block
- Get Current Block Index
- Show Block
- Delete Block
- Block Down
- Block Move Left
- Block Move Right
- Block Rotate
- Draw Game Board


## scoreLevelControl.c
Manages the score and level of the Tetris game. We define a method in which when a certain number of scores are collected, the level goes up by one, and when the level goes up beyond a certain level, the game speed increases.

- Show Current Score And Level
- Game Level Up
- Add Game Score


# References
- [CS50x 2024](https://cs50.harvard.edu/x/2024/)
- [윤성우 - <단계별 프로젝트 중심의 C프로그래밍 파워 업그레이드>](https://product.kyobobook.co.kr/detail/S000001589143)
