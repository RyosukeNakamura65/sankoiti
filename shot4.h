//#pragma once

#define PLAYER_SHOT4_MAX 4

void shot4SystemInit(void);
void shot4GameInit(void);
void shot4Control(void);
void shot4Draw(void);

void CreateShot4(XY pPos, XY poffset, MOVE_DIR pDir);
void Deleteshot4(void);

XY GetPos4(void);
XY GetSize4(void);
bool visible4(void);

