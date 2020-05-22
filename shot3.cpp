#include "DxLib.h"
#include "main.h"
#include "shot.h"
#include "shot3.h"
#include "player.h"
#include "player2.h"
#include "player3.h"
#include "player4.h"
#include "stage.h"
#include "KeyCheck.h"

int shot3Image[PLAYER_MAX];
CHARACTER shot3[PLAYER_SHOT3_MAX];
////�R���X�g���N�^
//Shot::Shot(int no, int PosX, int PosY, const char image[])
//{
//	ShotNo = no;
//	ShotImage = LoadGraph(image);
//	//ShotImage = LoadGraph("image/�e.png");
//	ShotPosX = 100;
//	ShotPosY = 100;
//	ShotSpeed = 5;
//	Shotflag = false;  //�e��ł�true
//}
//
////�f�X�g���N�^
//Shot::~Shot()
//{
//
//}


//�v���g�^�C�v�錾
void shot3SystemInit(void)
{
	//shot3Image[PLAYER_1] = LoadGraph("image/�v���C���[1�e.png");
	//shot3Image[PLAYER_2] = LoadGraph("image/�v���C���[2�e.png");
	shot3Image[PLAYER_3] = LoadGraph("image/�v���C���[3�e.png");
	//shot3Image[PLAYER_4] = LoadGraph("image/�v���C���[4�e.png");
}

void shot3GameInit(void)
{
	for (int sh = 0; sh < PLAYER_SHOT3_MAX; sh++)
	{
		shot3[sh].visible = false;
		shot3[sh].pos.x = 0;
		shot3[sh].pos.y = 0;
		shot3[sh].size.x = 32;
		shot3[sh].size.y = 32;
		shot3[sh].sizeOffset.x = shot3[sh].size.x / 2;
		shot3[sh].sizeOffset.y = shot3[sh].size.y / 2;
		shot3[sh].lifeMax = 100;
		shot3[sh].life = 0;
		shot3[sh].moveSpeed = 10;
	}
}

void shot3Control(void)
{

	for (int sc = 0; sc < PLAYER_SHOT3_MAX;sc++)
	{
		if (shot3[sc].visible)
		{
			if (shot3[sc].moveDir == DIR_UP)shot3[sc].pos.y -= shot3[sc].moveSpeed;
			if (shot3[sc].moveDir == DIR_RIGHT)shot3[sc].pos.x += shot3[sc].moveSpeed;
			if (shot3[sc].moveDir == DIR_DOWN)shot3[sc].pos.y += shot3[sc].moveSpeed;
			if (shot3[sc].moveDir == DIR_LEFT)shot3[sc].pos.x -= shot3[sc].moveSpeed;

			if (!IsPass(shot3[sc].pos))
			{
				shot3[sc].visible = false;
			}
			/*if (ShotCheckHit(shot[sc].pos, shot[sc].size.x) == true)shot[sc].life = 0;*/
			//if (shot2CheckHit(shot3[sc].pos, shot3[sc].size.x) == true)shot3[sc].life = 0;
			if (Shot3CheckHit(shot3[sc].pos, shot3[sc].size.x) == true)shot3[sc].life = 0;
			//if (Shot4CheckHit(shot[sc].pos, shot[sc].size.x) == true)shot[sc].life = 0;

			if (shot3[sc].life < 0)
			{
				shot3[sc].visible = false;
			}
		}
	}
}

void shot3Draw(void)
{
	for (int s = 0; s < PLAYER_SHOT3_MAX; s++)
	{
		if (shot3[s].visible)
		{
			DrawGraph(shot3[s].pos.x - shot3[s].sizeOffset.x + MAP_OFFSET_X,
				shot3[s].pos.y - shot3[s].sizeOffset.y + MAP_OFFSET_Y,
				shot3Image[PLAYER_3],
				true);
		}

	}
	/*if (shot3flag == true)
	{
		DrawGraph(shot3PosX, shot3PosY, shot3Image, true);
	}*/
}

void CreateShot3(XY pPos, XY poffset, MOVE_DIR pDir)
{
	for (int cs = 0; cs < PLAYER_SHOT3_MAX; cs++)
	{
		if (!shot3[cs].visible)
		{
			shot3[cs].visible = true;

			if (shot3[cs].visible)
			{
				shot3[cs].pos.x = pPos.x;
				shot3[cs].pos.y = pPos.y;
				shot3[cs].moveDir = pDir;
				if (shot3[cs].moveDir == DIR_UP)shot3[cs].pos.y -= poffset.y;
				if (shot3[cs].moveDir == DIR_RIGHT)shot3[cs].pos.x += poffset.x;
				if (shot3[cs].moveDir == DIR_DOWN)shot3[cs].pos.y += poffset.y;
				if (shot3[cs].moveDir == DIR_LEFT)shot3[cs].pos.x -= poffset.x;
				shot3[cs].life = shot3[cs].lifeMax;
				break;
			}
		}
	}
	/*if (shot3flag == false)
	{
		shot3flag = true;
		shot3PosX = pos.x;
		shot3PosY = pos.y;
	}*/
}

void DeleteShot3(void)
{
	for (int s = 0; s < PLAYER_SHOT3_MAX; s++)
	{
		if (shot3[s].visible)
		{
			shot3[s].visible = false;
		}
	}
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