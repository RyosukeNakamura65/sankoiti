#include "DxLib.h"
#include "main.h"
#include "shot.h"
#include "KeyCheck.h"


//コンストラクタ
Shot::Shot(int no, int PosX, int PosY, const char image[])
{
	ShotNo = no;
	ShotImage = LoadGraph(image);
	//ShotImage = LoadGraph("image/弾.png");
	ShotPosX = 100;
	ShotPosY = 100;
	ShotSpeed = 5;
	Shotflag = false;  //弾を打つとtrue
}

//デストラクタ
Shot::~Shot()
{

}


//プロトタイプ宣言
void Shot::SystemInit(void)
{

}

void Shot::GameInit(void)
{

}

void Shot::Control(void)
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

void Shot::Draw(void)
{
	if (Shotflag == true)
	{
		DrawGraph(ShotPosX, ShotPosY, ShotImage, true);
	}
}

void Shot::CreateShot(XY pos)
{
	if (Shotflag == false)
	{
		Shotflag = true;
		ShotPosX = pos.x;
		ShotPosY = pos.y;
	}
}

void Shot::DeleteShot(void)
{

}

XY Shot::GetPos(void)
{
	return { ShotPosX, ShotPosY };
}

XY Shot::GetSize(void)
{
	return { SHOT_SIZE_X, SHOT_SIZE_Y };
}

bool Shot::visible(void)
{
	return Shotflag;
}