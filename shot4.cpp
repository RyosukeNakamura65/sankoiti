#include "DxLib.h"
#include "main.h"
#include "shot.h"
#include "shot4.h"
#include "player.h"
#include "player2.h"
#include "player3.h"
#include "player4.h"
#include "stage.h"
#include "Tobitiri.h"
#include "KeyCheck.h"

int shot4Image[PLAYER_MAX];
CHARACTER shot4[PLAYER_SHOT4_MAX];
int shot4Cnt;
int shot4TimeCnt;
int shot4TimeCntMax;
int reloadtime4;			//リロードの時間
int reloadtime4MAX;		//リロードの最大時間
int reloadFlag4;			//リロードのフラグ
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
	shot4Cnt = 0;
	shot4TimeCnt = 100;
	shot4TimeCntMax = 100;
	reloadtime4MAX = 15;
	reloadtime4 = 0;
	reloadtime4 = PLAYER_SHOT4_MAX;
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
				SetBlockEffect(shot4[sc].pos, EFFECT_C_YELLOW);
			}
			if (ShotCheckHit(shot4[sc].pos, shot4[sc].size.x) == true)shot4[sc].life = 0;
			if (Shot2CheckHit(shot4[sc].pos, shot4[sc].size.x) == true)shot4[sc].life = 0;
			if (Shot3CheckHit(shot4[sc].pos, shot4[sc].size.x) == true)shot4[sc].life = 0;
			//if (Shot4CheckHit(shot4[sc].pos, shot4[sc].size.x) == true)shot4[sc].life = 0;

			if (shot4[sc].life < 0)
			{
				shot4[sc].visible = false;
			}
		}
	}
	if (0 >= reloadtime4)
	{
		reloadFlag4 = true;
	}
	if (reloadFlag4 == true)
	{
		shot4Cnt++;
		shot4TimeCnt++;
		if (shot4Cnt > 100)
		{
			reloadFlag4 = false;
			shot4Cnt = 0;
			reloadtime4 = PLAYER_SHOT4_MAX;
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
	DrawBox(930 //- enemy1[index].offsetSize.X
		, 500 //- enemy1[index].size.Y + 20 + mapPos.Y/* - enemy1[index].offsetSize.Y / 2 - mapPos.Y*/
		, 960 //- enemy1[index].offsetSize.X + mapPos.X + enemy1[index].lifeMax * 8
		, 350 + shot4TimeCntMax * 2.5//- enemy1[index].size.Y + 15 + mapPos.Y/*+ enemy1[index].size.Y - enemy1[index].offsetSize.Y - mapPos.Y*/
		, GetColor(255, 255, 28)
		, true);

	DrawBox(930 //- enemy1[index].offsetSize.X + mapPos.X
		, 500  //- enemy1[index].size.Y + 20 + mapPos.Y/* - enemy1[index].offsetSize.Y / 2 - mapPos.Y*/
		, 960 //- enemy1[index].offsetSize.X + mapPos.X + enemy1[index].lifeMax * 8
		, 600 - shot4TimeCnt//- enemy1[index].size.Y + 15 + mapPos.Y/*+ enemy1[index].size.Y - enemy1[index].offsetSize.Y - mapPos.Y*/
		, GetColor(255, 0, 0)
		, true);
	DrawFormatString(300, 50, GetColor(255, 255, 255), "shot4Cnt = %d", shot4Cnt);
	/*if (shot4flag == true)
	{
		DrawGraph(shot4PosX, shot4PosY, shot4Image, true);
	}*/
}

void CreateShot4(XY pPos, XY poffset, MOVE_DIR pDir)
{
	if (reloadFlag4)
	{

	}
	else
	{

	}
	if (reloadFlag4 == false)
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
					reloadtime4--;
					shot4TimeCnt -= 25;
					break;
				}
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

void DeleteShot4(void)
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