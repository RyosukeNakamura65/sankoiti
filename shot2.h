//#pragma once

#define PLAYER_SHOT2_MAX 4

void shot2SystemInit(void);
void shot2GameInit(void);
void shot2Control(void);
void shot2Draw(void);

void CreateShot2(XY pPos, XY poffset, MOVE_DIR pDir);
void DeleteShot2(void);

XY GetPos2(void);
XY GetSize2(void);
bool visible2(void);

