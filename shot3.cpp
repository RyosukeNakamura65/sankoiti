#include "DxLib.h"
#include "main.h"
#include "shot.h"
#include "shot3.h"
#include "player.h"
#include "player2.h"
#include "player3.h"
#include "player4.h"
#include "stage.h"
#include "Tobitiri.h"
#include "KeyCheck.h"

int shot3Image[PLAYER_MAX];
CHARACTER shot3[PLAYER_SHOT3_MAX];
int shot3Cnt;
int shot3TimeCnt;
int shot3TimeCntMax;
int shot3Sound[SHOT_MAX];
int reloadtime3;			//リロードの時間
int reloadtime3MAX;		//リロードの最大時間
int reloadFlag3;			//リロードのフラグ
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
void shot3SystemInit(void)
{
	shot3Image[PLAYER_3] = LoadGraph("image/プレイヤー3弾.png");
	shot3Sound[SHOT_3] = LoadSoundMem("効果音/laser2.mp3");
	
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
	shot3Cnt = 0;
	shot3TimeCnt = 200;
	shot3TimeCntMax = 100;
	reloadtime3MAX = 15;
	reloadtime3 = 0;
	reloadtime3 = PLAYER_SHOT3_MAX;
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
				SetBlockEffect(shot3[sc].pos, EFFECT_C_GREEN);
			}
			if (ShotCheckHit(shot3[sc].pos, shot3[sc].size.x) == true)shot3[sc].life = 0;
			if (Shot2CheckHit(shot3[sc].pos, shot3[sc].size.x) == true)shot3[sc].life = 0;
			//if (Shot3CheckHit(shot3[sc].pos, shot3[sc].size.x) == true)shot3[sc].life = 0;
			if (Shot4CheckHit(shot3[sc].pos, shot3[sc].size.x) == true)shot3[sc].life = 0;

			if (shot3[sc].life < 0)
			{
				shot3[sc].visible = false;
			}
		}
	}
	/*if (0 >= reloadtime3)
	{
		reloadFlag3 = true;
	}
	if (reloadFlag3 == true)
	{
		shot3Cnt++;
		shot3TimeCnt++;
		DrawString(0, 450, "Reload", 0x00fe00, true);
		if (shot3Cnt > 100)
		{
			reloadFlag3 = false;
			shot3Cnt = 0;
			shot3TimeCnt = 100;
			reloadtime3 = PLAYER_SHOT3_MAX;
		}
	}*/
	if (shot3TimeCnt <= 200)
	{
		shot3TimeCnt++;
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

	if (shot3TimeCnt >= 200)
	{
		DrawGraph(0, 500, shot3Image[PLAYER_3], true);
	}
	if (shot3TimeCnt >= 150)
	{
		DrawGraph(0, 550, shot3Image[PLAYER_3], true);
	}
	if (shot3TimeCnt >= 100)
	{
		DrawGraph(0, 600, shot3Image[PLAYER_3], true);
	}
	if (shot3TimeCnt >= 50)
	{
		DrawGraph(0, 650, shot3Image[PLAYER_3], true);
	}

	//DrawBox(0 //- enemy1[index].offsetSize.X
	//	, 500 //- enemy1[index].size.Y + 20 + mapPos.Y/* - enemy1[index].offsetSize.Y / 2 - mapPos.Y*/
	//	, 30 //- enemy1[index].offsetSize.X + mapPos.X + enemy1[index].lifeMax * 8
	//	, 350 + shot3TimeCntMax * 2.5//- enemy1[index].size.Y + 15 + mapPos.Y/*+ enemy1[index].size.Y - enemy1[index].offsetSize.Y - mapPos.Y*/
	//	, GetColor(28, 255, 28)
	//	, true);

	//DrawBox(0 //- enemy1[index].offsetSize.X + mapPos.X
	//	, 500  //- enemy1[index].size.Y + 20 + mapPos.Y/* - enemy1[index].offsetSize.Y / 2 - mapPos.Y*/
	//	, 30 //- enemy1[index].offsetSize.X + mapPos.X + enemy1[index].lifeMax * 8
	//	, 600 - shot3TimeCnt//- enemy1[index].size.Y + 15 + mapPos.Y/*+ enemy1[index].size.Y - enemy1[index].offsetSize.Y - mapPos.Y*/
	//	, GetColor(255, 0, 0)
	//	, true);
	DrawFormatString(200, 50, GetColor(255, 255, 255), "shot3Cnt = %d", shot3Cnt);
	/*if (shot3flag == true)
	{
		DrawGraph(shot3PosX, shot3PosY, shot3Image, true);
	}*/
}

void CreateShot3(XY pPos, XY poffset, MOVE_DIR pDir)
{
	if (reloadFlag3)
	{

	}
	else
	{

	}
	if (shot3TimeCnt > 50)
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
					PlaySoundMem(shot3Sound[SHOT_3], DX_PLAYTYPE_BACK);
					reloadtime3--;
					shot3TimeCnt -= 50;
					break;
				}
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





