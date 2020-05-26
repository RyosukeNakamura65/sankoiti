#include "DxLib.h"
#include "main.h"
#include "shot.h"
#include "player.h"
#include "player2.h"
#include "player3.h"
#include "player4.h"
#include "stage.h"
#include "Tobitiri.h"
#include "KeyCheck.h"

int shotImage[PLAYER_MAX];
CHARACTER shot[SHOT_MAX];
int shotCnt;
int reloadtime;			//リロードの時間
int reloadtimeMAX;		//リロードの最大時間
int reloadFlag;			//リロードのフラグ

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
	//shotImage[PLAYER_2] = LoadGraph("image/プレイヤー2弾.png");
	//shotImage[PLAYER_3] = LoadGraph("image/プレイヤー3弾.png");
	//shotImage[PLAYER_4] = LoadGraph("image/プレイヤー4弾.png");
}

void shotGameInit(void)
{
	for (int sh = 0; sh < PLAYER_SHOT_MAX; sh++)
	{
		shot[sh].visible = false;
		shot[sh].pos.x = 0;
		shot[sh].pos.y = 0;
		shot[sh].size.x = 32;
		shot[sh].size.y = 32;
		shot[sh].sizeOffset.x = shot[sh].size.x / 2;
		shot[sh].sizeOffset.y = shot[sh].size.y / 2;
		shot[sh].lifeMax = 100;
		shot[sh].life = 0;
		shot[sh].moveSpeed = 10;
	}
	shotCnt = 0;
	reloadtimeMAX = 15;
	reloadtime = 0;
	reloadtime = PLAYER_SHOT_MAX;
}

void shotControl(void)
{
	for (int sc = 0; sc < PLAYER_SHOT_MAX;sc++)
	{
		if (shot[sc].visible)
		{
			if (shot[sc].moveDir == DIR_UP)shot[sc].pos.y -= shot[sc].moveSpeed;
			if (shot[sc].moveDir == DIR_RIGHT)shot[sc].pos.x += shot[sc].moveSpeed;
			if (shot[sc].moveDir == DIR_DOWN)shot[sc].pos.y += shot[sc].moveSpeed;
			if (shot[sc].moveDir == DIR_LEFT)shot[sc].pos.x -= shot[sc].moveSpeed;

			if (!IsPass(shot[sc].pos))
			{
				shot[sc].visible = false;
				SetBlockEffect(shot[sc].pos, EFFECT_C_BLUE);
			}
			//if (ShotCheckHit(shot[sc].pos, shot[sc].size.x) == true)shot[sc].visible = false;
			if (Shot2CheckHit(shot[sc].pos, shot[sc].size.x) == true)shot[sc].life = 0;
			if (Shot3CheckHit(shot[sc].pos, shot[sc].size.x) == true)shot[sc].life = 0;
			if (Shot4CheckHit(shot[sc].pos, shot[sc].size.x) == true)shot[sc].life = 0;
			if (shot[sc].life < 0)
			{
				shot[sc].visible = false;
			}
		}
	}
	if (0 >= reloadtime)
	{
		reloadFlag = true;
	}
	if (reloadFlag == true)
	{
		shotCnt++;
		if (shotCnt > 100)
		{
			reloadFlag = false;
			shotCnt = 0;
			reloadtime = PLAYER_SHOT_MAX;
		}
	}

}

void shotDraw(void)
{
	for (int s = 0; s < PLAYER_SHOT_MAX; s++)
	{
		if (shot[s].visible)
		{
			DrawGraph(shot[s].pos.x - shot[s].sizeOffset.x + MAP_OFFSET_X,
				shot[s].pos.y - shot[s].sizeOffset.y + MAP_OFFSET_Y,
				shotImage[PLAYER_1],
				true);
		}

	}
	DrawFormatString(50, 50, GetColor(255, 255, 255), "shotCnt = %d", shotCnt);
	/*if (Shotflag == true)
	{
		DrawGraph(ShotPosX, ShotPosY, ShotImage, true);
	}*/
}

void CreateShot(XY pPos, XY poffset, MOVE_DIR pDir)
{
	if (reloadFlag)
	{

	}
	else
	{

	}
	if (reloadFlag == false)
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
					if (shot[cs].moveDir == DIR_UP)shot[cs].pos.y -= poffset.y;
					if (shot[cs].moveDir == DIR_RIGHT)shot[cs].pos.x += poffset.x;
					if (shot[cs].moveDir == DIR_DOWN)shot[cs].pos.y += poffset.y;
					if (shot[cs].moveDir == DIR_LEFT)shot[cs].pos.x -= poffset.x;
					shot[cs].life = shot[cs].lifeMax;
					reloadtime--;
					break;
				}
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
	for (int s = 0; s < SHOT_MAX; s++)
	{
		if (shot[s].visible)
		{
			shot[s].visible = false;
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