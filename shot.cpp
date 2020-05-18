#include "DxLib.h"
#include "main.h"
#include "shot.h"
#include "KeyCheck.h"


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
void SystemInit(void)
{
	shotImage[PLAYER_1] = LoadGraph("image/プレイヤー１弾.png");
}

void GameInit(void)
{
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		Shot[sh].visible = false;
		Shot[sh].pos.x = 0;
		Shot[sh].pos.y = 0;
		Shot[sh].size.x = 16;
		Shot[sh].size.y = 16;
		Shot[sh].sizeOffset.x = Shot[sh].size.x / 2;
		Shot[sh].sizeOffset.y = Shot[sh].size.y / 2;
		Shot[sh].lifeMax = 20;
		Shot[sh].life = 0;
		Shot[sh].moveSpeed = 10;
	}
}

void Control(void)
{

	if (CheckHitKey(KEY_INPUT_LCONTROL))
	{
		Shotflag = true;
	}
	if (Shotflag == true)
	{
		ShotPosX = ShotPosX + ShotSpeed;
	}
}

void Draw(void)
{
	if (Shotflag == true)
	{
		DrawGraph(ShotPosX, ShotPosY, ShotImage, true);
	}
}

void CreateShot(XY pos)
{
	if (Shotflag == false)
	{
		Shotflag = true;
		ShotPosX = pos.x;
		ShotPosY = pos.y;
	}
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