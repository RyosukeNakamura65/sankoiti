#include "DxLib.h"
#include "math.h"
#include "main.h"
#include "player.h"
#include "player2.h"
#include "player3.h"
#include "player4.h"
#include "shot.h"
#include "stage.h"
#include "Tobitiri.h"

#define PI		3.141592


float TobitiriAcc;		//飛び散りの落下速度
int TobiImage[EFFECT_C_MAX][TOBI_SIZE_MAX];
EFFECT tobi[EFFECT_MAX];

//飛び散りの初期化
void TobiSystemInit(void)
{
	LoadDivGraph("image/飛び散り.png", 4, 4, 1, 16, 16, TobiImage[EFFECT_C_BLUE]);
	LoadDivGraph("image/飛び散り(ピンク).png", 4, 4, 1, 16, 16, TobiImage[EFFECT_C_PINK]);
	LoadDivGraph("image/飛び散り(緑).png", 4, 4, 1, 16, 16, TobiImage[EFFECT_C_GREEN]);
	LoadDivGraph("image/飛び散り(黄).png", 4, 4, 1, 16, 16, TobiImage[EFFECT_C_YELLOW]);
}


void TobiGameInit(void)
{
	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{
		tobi[ef].pos.x = 0;
		tobi[ef].pos.y = 0;
		/*tobi[ef].size.x = 16;
		tobi[ef].size.y = 16;*/
		tobi[ef].sizeOffset.x = 8;
		tobi[ef].sizeOffset.y = 8;
		tobi[ef].visible = false;
		tobi[ef].lifeMax = 10;
	}
}

void TobiContlor(void)
{
	TobitiriAcc = 0.07f;
	XY_F TemPos;
	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{
		if (tobi[ef].visible)
		{
			TemPos = tobi[ef].pos;
			if (tobi[ef].effectType == EFFECT_T_BLOCK)
			{
				tobi[ef].pos.y += TobitiriAcc;
			}
			tobi[ef].pos.x += tobi[ef].move.x;
			tobi[ef].pos.y += tobi[ef].move.y;
			tobi[ef].life--;
		}
		if (tobi[ef].life < 0)
		{
			tobi[ef].visible = false;
		}
	}
}

void TobiDraw(void)
{
	for (int ef = 0;ef < EFFECT_MAX; ef++)
	{
		if (tobi[ef].visible)
		{
			DrawGraph(tobi[ef].pos.x - tobi[ef].size.x + MAP_OFFSET_X
				, tobi[ef].pos.y - tobi[ef].size.y + MAP_OFFSET_Y
				, TobiImage[tobi[ef].effectColor][GetRand(4)]
				, true);
		}
	}
}

void SetBlockEffect(XY pos, EFFECT_COLOR effectColor)
{
	float rad = 0.0f;
	int effectCnt = 0;

	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{
		if (!tobi[ef].visible)
		{
			effectCnt++;
			//1°ずつ動かしながら素材を生成する
			//素材の移動速度は乱数(1〜10)を使って作る
			rad = GetRand(360)*(PI / 180.0);
			//rad += 36 * PI / 180.0;
			tobi[ef].angel = rad;
			tobi[ef].index = GetRand(3);

			tobi[ef].effectType = EFFECT_T_BLOCK;

			tobi[ef].speed = GetRand(9) + 1;

			tobi[ef].effectColor = effectColor;

			tobi[ef].pos.x = pos.x;
			tobi[ef].pos.y = pos.y;

			tobi[ef].move.x = cos(rad) * tobi[ef].speed;
			tobi[ef].move.y = sin(rad) * tobi[ef].speed;

			TobitiriAcc = 0.3f;

			tobi[ef].life = 10;

			tobi[ef].visible = true;

			if (effectCnt > TOBI_EFFECT_MAX)
			{
				break;
			}
		}


	}
}

void SetTobichiriEffect(XY pos, EFFECT_COLOR effectColor)
{
	float rad = 0.0f;
	int TobiCnt = 0;
	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{

		if (!tobi[ef].visible)
		{
			TobiCnt++;
			//1°ずつ動かしながら素材を生成する
			//素材の移動速度は乱数(1〜10)を使って作る
			rad = GetRand(360);
			rad += 1 * PI / 180.0;

			tobi[ef].angel = rad;
			tobi[ef].effectType = EFFECT_T_TOBITIRI;

			tobi[ef].speed = GetRand(500) / 75.0f;

			tobi[ef].effectColor = effectColor;

			tobi[ef].pos.x = pos.x;
			tobi[ef].pos.y = pos.y;

			TobitiriAcc = 0.8f;

			tobi[ef].move.x = cos(rad) * tobi[ef].speed;
			tobi[ef].move.y = sin(rad) * tobi[ef].speed;

			tobi[ef].life = 10;

			tobi[ef].visible = true;

			if (TobiCnt > 10)
			{
				break;
			}
		}
	}
}