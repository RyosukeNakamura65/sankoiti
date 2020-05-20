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


float TobitiriAcc;		//”ò‚ÑU‚è‚Ì—‰º‘¬“x
int TobiImage[EFFECT_C_MAX][TOBI_SIZE_MAX];
EFFECT tobi[EFFECT_MAX];

//”ò‚ÑU‚è‚Ì‰Šú‰»
void TobiSystemInit(void)
{
	LoadDivGraph("image/”ò‚ÑU‚è.png", 4, 4, 1, 16, 16, TobiImage[EFFECT_C_BLUE]);
	LoadDivGraph("image/”ò‚ÑU‚è(ƒsƒ“ƒN).png", 4, 4, 1, 16, 16, TobiImage[EFFECT_C_PINK]);
	LoadDivGraph("image/”ò‚ÑU‚è(—Î).png", 4, 4, 1, 16, 16, TobiImage[EFFECT_C_GREEN]);
	LoadDivGraph("image/”ò‚ÑU‚è(‰©),png", 4, 4, 1, 16, 16, TobiImage[EFFECT_C_YELLOW]);
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

	}
}

void SetBlockEffect(XY pos, EFFECT_COLOR effectColor)
{

}

void SetTobichiriEffect(XY pos, EFFECT_COLOR effectColor)
{

}