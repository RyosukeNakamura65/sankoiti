#include "DxLib.h"
#include "main.h"
#include "shot.h"
#include "stage.h"
#include "KeyCheck.h"

int shotImage[PLAYER_MAX];
CHARACTER shot[SHOT_MAX];
////コンストラクタ
//Shot::Shot(int no, int PosX, int PosY, const char image[])
//{
//	ShotNo = no;
//	ShotImage = LoadGraph(image);
//	//ShotImage = LoadGraph("image/弾.png");
//	ShotPosX = 100;
//	ShotPosY = 100;
//	ShotSpeed = 5;
//	Shotflag = false;  //弾を打つとtrue
//}
//
////デストラクタ
//Shot::~Shot()
//{
//
//}


//プロトタイプ宣言
void shotSystemInit(void)
{
	shotImage[PLAYER_1] = LoadGraph("image/プレイヤー1弾.png");
	shotImage[PLAYER_2] = LoadGraph("image/プレイヤー2弾.png");
	shotImage[PLAYER_3] = LoadGraph("image/プレイヤー3弾.png");
	shotImage[PLAYER_4] = LoadGraph("image/プレイヤー4弾.png");
}

void shotGameInit(void)
{
	for (int sh = 0; sh < PLAYER_SHOT_MAX; sh++)
	{
		shot[sh].visible = false;
		shot[sh].pos.x = 0;
		shot[sh].pos.y = 0;
		shot[sh].size.x = 16;
		shot[sh].size.y = 16;
		shot[sh].sizeOffset.x = shot[sh].size.x / 2;
		shot[sh].sizeOffset.y = shot[sh].size.y / 2;
		shot[sh].lifeMax = 20;
		shot[sh].life = 0;
		shot[sh].moveSpeed = 10;
	}
}

void shotControl(void)
{

	for (int sc = 0; sc < PLAYER_SHOT_MAX;sc++)
	{
		if (shot[sc].visible)
		{
			if (shot[sc].moveDir == DIR_UP)
			{
				shot[sc].pos.y -= shot[sc].moveSpeed;
			}
			if (shot[sc].moveDir == DIR_RIGHT)
			{
				shot[sc].pos.y += shot[sc].moveSpeed;
			}
			if (shot[sc].moveDir == DIR_DOWN)
			{
				shot[sc].pos.y += shot[sc].moveSpeed;
			}
			if (shot[sc].moveDir == DIR_LEFT)
			{
				shot[sc].pos.y -= shot[sc].moveSpeed;
			}
		}
	}
}



void CreateShot(XY pPos, MOVE_DIR pDir)
{
	for (int cs = 0; cs < PLAYER_SHOT_MAX; cs++)
	{
		if (!shot[cs].visible)
		{
			shot[cs].visible = true;

			if (shot[cs].visible)
			{
				shot[cs].pos.x = pPos.x;
				shot[cs].pos.y = pPos.y;
				shot[cs].moveDir = pDir;
				shot[cs].life = shot[cs].lifeMax;
				break;
			}
		}
	}
	/*if (Shotflag == false)
	{
		Shotflag = true;
		ShotPosX = pos.x;
		ShotPosY = pos.y;
	}*/
}

void DeleteShot(void)
{

}


void shotDraw(void)
{
	for (int s = 0; s < SHOT_MAX; s++)
	{
		DrawGraph(shot[s].pos.x - shot[s].sizeOffset.x + MAP_OFFSET_X,
			shot[s].pos.y - shot[s].sizeOffset.y + MAP_OFFSET_Y,
			shotImage[s],
			true);
	}
	/*if (Shotflag == true)
	{
		DrawGraph(ShotPosX, ShotPosY, ShotImage, true);
	}*/
}
//XY GetPos(void)
//{
//	//return { ShotPosX, ShotPosY };
//}

//XY GetSize(void)
//{
//	//return { SHOT_SIZE_X, SHOT_SIZE_Y };
//}

//bool visible(void)
//{
//	//return Shotflag;
//}