#include "DxLib.h"
#include "main.h"
#include "shot.h"


//�R���X�g���N�^
Shot::Shot(const char image[])
{
	ShotImage = LoadGraph(image);
	//ShotImage = LoadGraph("image/�e.png");
	ShotPosX = 100;
	ShotPosY = 100;
	ShotSpeed = 15;
	Shotflag = true;  //�e��ł�true
}

//�f�X�g���N�^
Shot::~Shot()
{

}


//�v���g�^�C�v�錾
void Shot::SystemInit(void)
{

}

void Shot::GameInit(void)
{

}

void Shot::Control(void)
{

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