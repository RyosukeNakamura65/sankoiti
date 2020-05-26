#include "DxLib.h"
#include "main.h"
#include "shot.h"
#include "shot2.h"
#include "player.h"
#include "player2.h"
#include "player3.h"
#include "player4.h"
#include "stage.h"
#include "Tobitiri.h"
#include "KeyCheck.h"

int shot2Image[PLAYER_MAX];
CHARACTER shot2[PLAYER_SHOT2_MAX];
int shot2Cnt;
int reloadtime2;			//リロードの時間
int reloadtime2MAX;		//リロードの最大時間
int reloadFlag2;			//リロードのフラグ
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
void shot2SystemInit(void)
{
	//shot2Image[PLAYER_1] = LoadGraph("image/プレイヤー1弾.png");
	shot2Image[PLAYER_2] = LoadGraph("image/プレイヤー2弾.png");
	//shot2Image[PLAYER_3] = LoadGraph("image/プレイヤー3弾.png");
	//shot2Image[PLAYER_4] = LoadGraph("image/プレイヤー4弾.png");
}

void shot2GameInit(void)
{
	for (int sh = 0; sh < PLAYER_SHOT2_MAX; sh++)
	{
		shot2[sh].visible = false;
		shot2[sh].pos.x = 0;
		shot2[sh].pos.y = 0;
		shot2[sh].size.x = 32;
		shot2[sh].size.y = 32;
		shot2[sh].sizeOffset.x = shot2[sh].size.x / 2;
		shot2[sh].sizeOffset.y = shot2[sh].size.y / 2;
		shot2[sh].lifeMax = 100;
		shot2[sh].life = 0;
		shot2[sh].moveSpeed = 10;
	}
	shot2Cnt = 0;
	reloadtime2MAX = 15;
	reloadtime2 = 0;
	reloadtime2 = PLAYER_SHOT2_MAX;
}

void shot2Control(void)
{

	for (int sc = 0; sc < PLAYER_SHOT2_MAX;sc++)
	{
		if (shot2[sc].visible)
		{
			if (shot2[sc].moveDir == DIR_UP)shot2[sc].pos.y -= shot2[sc].moveSpeed;
			if (shot2[sc].moveDir == DIR_RIGHT)shot2[sc].pos.x += shot2[sc].moveSpeed;
			if (shot2[sc].moveDir == DIR_DOWN)shot2[sc].pos.y += shot2[sc].moveSpeed;
			if (shot2[sc].moveDir == DIR_LEFT)shot2[sc].pos.x -= shot2[sc].moveSpeed;

			if (!IsPass(shot2[sc].pos))
			{
				shot2[sc].visible = false;
				SetBlockEffect(shot2[sc].pos, EFFECT_C_PINK);
			}
			if (ShotCheckHit(shot2[sc].pos, shot2[sc].size.x) == true)shot2[sc].life = 0;
			//if (Shot2CheckHit(shot2[sc].pos, shot2[sc].size.x) == true)shot2[sc].visible = false;
			if (Shot3CheckHit(shot2[sc].pos, shot2[sc].size.x) == true)shot2[sc].life = 0;
			if (Shot4CheckHit(shot2[sc].pos, shot2[sc].size.x) == true)shot2[sc].life = 0;

			if (shot2[sc].life < 0)
			{
				shot2[sc].visible = false;
			}
		}
	}
	if (0 >= reloadtime2)
	{
		reloadFlag2 = true;
	}
	if (reloadFlag2 == true)
	{
		shot2Cnt++;
		if (shot2Cnt > 100)
		{
			reloadFlag2 = false;
			shot2Cnt = 0;
			reloadtime2 = PLAYER_SHOT2_MAX;
		}
	}
}

void shot2Draw(void)
{
	for (int s = 0; s < PLAYER_SHOT2_MAX; s++)
	{
		if (shot2[s].visible)
		{
			DrawGraph(shot2[s].pos.x - shot2[s].sizeOffset.x + MAP_OFFSET_X,
				shot2[s].pos.y - shot2[s].sizeOffset.y + MAP_OFFSET_Y,
				shot2Image[PLAYER_2],
				true);
		}

	}
	DrawFormatString(100, 50, GetColor(255, 255, 255), "shot2Cnt = %d", shot2Cnt);
	/*if (shot2flag == true)
	{
		DrawGraph(shot2PosX, shot2PosY, shot2Image, true);
	}*/
}

void CreateShot2(XY pPos, XY poffset, MOVE_DIR pDir)
{
	if (reloadFlag2)
	{

	}
	else
	{

	}
	if (reloadFlag2 == false)
	{
		for (int cs = 0; cs < PLAYER_SHOT2_MAX; cs++)
		{
			if (!shot2[cs].visible)
			{
				shot2[cs].visible = true;

				if (shot2[cs].visible)
				{
					shot2[cs].pos.x = pPos.x;
					shot2[cs].pos.y = pPos.y;
					shot2[cs].moveDir = pDir;
					if (shot2[cs].moveDir == DIR_UP)shot2[cs].pos.y -= poffset.y;
					if (shot2[cs].moveDir == DIR_RIGHT)shot2[cs].pos.x += poffset.x;
					if (shot2[cs].moveDir == DIR_DOWN)shot2[cs].pos.y += poffset.y;
					if (shot2[cs].moveDir == DIR_LEFT)shot2[cs].pos.x -= poffset.x;
					shot2[cs].life = shot2[cs].lifeMax;
					reloadtime2--;
					break;
				}
			}
		}
	}
	/*if (shot2flag == false)
	{
		shot2flag = true;
		shot2PosX = pos.x;
		shot2PosY = pos.y;
	}*/
}

void DeleteShot2(void)
{
	for (int s = 0; s < PLAYER_SHOT2_MAX; s++)
	{
		if (shot2[s].visible)
		{
			shot2[s].visible = false;
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
