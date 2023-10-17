#pragma once
#define KEY_UP 0
#define KEY_DOWN 1
#define KEY_LEFT 2
#define KEY_RIGHT 3
#define KEY_KEEP 9
#define KEY_UNDO 4
#define KEY_RESTART 5
#define KEY_ENTER 6
#define KEY_BACK 7
#define KEY_NEXT 8

void setDisplayMemory(int x, int y, int value);

bool keyEmpty();

int keyPop();