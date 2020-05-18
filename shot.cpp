#include "DxLib.h"
#include "main.h"
#include "shot.h"
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
	shotImage[PLAYER_1] = LoadGraph("image/プレイヤー１弾.png");
}

void shotGameInit(void)
{
	for (int sh = 0; sh < SHOT_MAX; sh++)
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

	for (int sc = 0; sc < SHOT_MAX;sc++)
	{
		if (shot[sc].visible)
		{
			if (shot[sc].moveDir == DIR_UP)
			{
				shot[sc].pos.y -= shot[sc].moveSpeed;
			}
		}
	}
}

void shotDraw(void)
{
	for (int s; s < SHOT_MAX; s++)
	{

	}
	/*if (Shotflag == true)
	{
		DrawGraph(ShotPosX, ShotPosY, ShotImage, true);
	}*/
}

void CreateShot(XY pPos,MOVE_DIR pDir)
{
	for (int cs = 0; cs < SHOT_MAX; cs++)
	{

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

XY GetPos(void)
{
	//return { ShotPosX, ShotPosY };
}

XY GetSize(void)
{
	//return { SHOT_SIZE_X, SHOT_SIZE_Y };
}

bool visible(void)
{
	//return Shotflag;
}