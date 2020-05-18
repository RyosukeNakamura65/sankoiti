//#pragma once
#define SHOT_SIZE_X 32
#define SHOT_SIZE_Y 32

#define SHOT_MAX 1

void SystemInit(void);
void GameInit(void);
void Control(void);
void Draw(void);

void CreateShot(XY pos);
void DeleteShot(void);

XY GetPos(void);
XY GetSize(void);
bool visible(void);