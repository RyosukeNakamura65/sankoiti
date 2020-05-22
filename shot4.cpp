#include "DxLib.h"
#include "main.h"
#include "shot.h"
#include "shot4.h"
#include "player.h"
#include "player2.h"
#include "player3.h"
#include "player4.h"
#include "stage.h"
#include "KeyCheck.h"

int shot4Image[PLAYER_MAX];
CHARACTER shot4[PLAYER_SHOT4_MAX];
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
void shot4SystemInit(void)
{
	//shot4Image[PLAYER_1] = LoadGraph("image/プレイヤー1弾.png");
	//shot4Image[PLAYER_2] = LoadGraph("image/プレイヤー2弾.png");
	//shot4Image[PLAYER_3] = LoadGraph("image/プレイヤー3弾.png");
	shot4Image[PLAYER_4] = LoadGraph("image/プレイヤー4弾.png");
}

void shot4GameInit(void)
{
	for (int sh = 0; sh < PLAYER_SHOT4_MAX; sh++)
	{
		shot4[sh].visible = false;
		shot4[sh].pos.x = 0;
		shot4[sh].pos.y = 0;
		shot4[sh].size.x = 32;
		shot4[sh].size.y = 32;
		shot4[sh].sizeOffset.x = shot4[sh].size.x / 2;
		shot4[sh].sizeOffset.y = shot4[sh].size.y / 2;
		shot4[sh].lifeMax = 100;
		shot4[sh].life = 0;
		shot4[sh].moveSpeed = 10;
	}
}

void shot4Control(void)
{

	for (int sc = 0; sc < PLAYER_SHOT4_MAX;sc++)
	{
		if (shot4[sc].visible)
		{
			if (shot4[sc].moveDir == DIR_UP)shot4[sc].pos.y -= shot4[sc].moveSpeed;
			if (shot4[sc].moveDir == DIR_RIGHT)shot4[sc].pos.x += shot4[sc].moveSpeed;
			if (shot4[sc].moveDir == DIR_DOWN)shot4[sc].pos.y += shot4[sc].moveSpeed;
			if (shot4[sc].moveDir == DIR_LEFT)shot4[sc].pos.x -= shot4[sc].moveSpeed;

			if (!IsPass(shot4[sc].pos))
			{
				shot4[sc].visible = false;
			}
			/*if (ShotCheckHit(shot[sc].pos, shot[sc].size.x) == true)shot[sc].life = 0;*/
			//if (shot2CheckHit(shot4[sc].pos, shot4[sc].size.x) == true)shot4[sc].life = 0;
			//if (shote3CheckHit(shot4[sc].pos, shot4[sc].size.x) == true)shot4[sc].life = 0;
			if (Shot4CheckHit(shot4[sc].pos, shot4[sc].size.x) == true)shot4[sc].life = 0;

			if (shot4[sc].life < 0)
			{
				shot4[sc].visible = false;
			}
		}
	}
}

void shot4Draw(void)
{
	for (int s = 0; s < PLAYER_SHOT4_MAX; s++)
	{
		if (shot4[s].visible)
		{
			DrawGraph(shot4[s].pos.x - shot4[s].sizeOffset.x + MAP_OFFSET_X,
				shot4[s].pos.y - shot4[s].sizeOffset.y + MAP_OFFSET_Y,
				shot4Image[PLAYER_4],
				true);
		}

	}
	/*if (shot4flag == true)
	{
		DrawGraph(shot4PosX, shot4PosY, shot4Image, true);
	}*/
}

void Createshot4(XY pPos, XY poffset, MOVE_DIR pDir)
{
	for (int cs = 0; cs < PLAYER_SHOT4_MAX; cs++)
	{
		if (!shot4[cs].visible)
		{
			shot4[cs].visible = true;

			if (shot4[cs].visible)
			{
				shot4[cs].pos.x = pPos.x;
				shot4[cs].pos.y = pPos.y;
				shot4[cs].moveDir = pDir;
				if (shot4[cs].moveDir == DIR_UP)shot4[cs].pos.y -= poffset.y;
				if (shot4[cs].moveDir == DIR_RIGHT)shot4[cs].pos.x += poffset.x;
				if (shot4[cs].moveDir == DIR_DOWN)shot4[cs].pos.y += poffset.y;
				if (shot4[cs].moveDir == DIR_LEFT)shot4[cs].pos.x -= poffset.x;
				shot4[cs].life = shot4[cs].lifeMax;
				break;
			}
		}
	}
	/*if (shot4flag == false)
	{
		shot4flag = true;
		shot4PosX = pos.x;
		shot4PosY = pos.y;
	}*/
}

void Deleteshot4(void)
{
	for (int s = 0; s < PLAYER_SHOT4_MAX; s++)
	{
		if (shot4[s].visible)
		{
			shot4[s].visible = false;
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