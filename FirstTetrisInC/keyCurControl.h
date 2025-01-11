#ifndef __KEYCURCONTROL_H__
#define __KEYCURCONTROL_H__

#include "point.h"

void SetCurrentCursorPos(int x, int y);
point GetCurrentCursorPos(void);
void RemoveCursor(void);

int ProcessKeyInput(void);

void InitKeyDelayRate(int rate);
void KeyDelaySpeedCtl(int addSpeed);

#endif