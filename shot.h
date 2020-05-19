//#pragma once
#define SHOT_SIZE_X 32
#define SHOT_SIZE_Y 32

#define PLAYER_SHOT_MAX 1

void shotSystemInit(void);
void shotGameInit(void);
void shotControl(void);
void shotDraw(void);

void CreateShot(XY pPos, MOVE_DIR pDir);
void DeleteShot(void);

XY GetPos(void);
XY GetSize(void);
bool visible(void);