//#pragma once
#define PLAYER_SHOT3_MAX 4

void shot3SystemInit(void);
void shot3GameInit(void);
void shot3Control(void);
void shot3Draw(void);

void CreateShot3(XY pPos, XY poffset, MOVE_DIR pDir);
void DeleteShot3(void);

XY GetPos3(void);
XY GetSize3(void);
bool visible3(void);
