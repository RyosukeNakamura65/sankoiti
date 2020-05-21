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


float TobitiriAcc;		//��юU��̗������x
int TobiImage[EFFECT_C_MAX][TOBI_SIZE_MAX];
EFFECT tobi[EFFECT_MAX];

//��юU��̏�����
void TobiSystemInit(void)
{
	LoadDivGraph("image/��юU��.png", 4, 4, 1, 16, 16, TobiImage[EFFECT_C_BLUE]);
	LoadDivGraph("image/��юU��(�s���N).png", 4, 4, 1, 16, 16, TobiImage[EFFECT_C_PINK]);
	LoadDivGraph("image/��юU��(��).png", 4, 4, 1, 16, 16, TobiImage[EFFECT_C_GREEN]);
	LoadDivGraph("image/��юU��(��),png", 4, 4, 1, 16, 16, TobiImage[EFFECT_C_YELLOW]);
}


void TobiInit(void)
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
			if (tobi[ef].effectType == EFFECT_T_TOBITIRI)
			{
				tobi[ef].pos.y += TobitiriAcc;
			}
			tobi[ef].pos.x += tobi[ef].move.x;
			tobi[ef].pos.x += tobi[ef].move.y;
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
				, TobiImage[tobi[ef].effectColor][GetRand(3)]
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
		//if (!tobi[ef].visible)
		//{
		//	effectCnt++;
		//	//1�����������Ȃ���f�ނ𐶐�����
		//	//�f�ނ̈ړ����x�͗���(1�`10)���g���č��
		//	rad = GetRand(360);
		//	rad = 36 * PI
		//}


	}
}

void SetTobichiriEffect(XY pos, EFFECT_COLOR effectColor)
{

}