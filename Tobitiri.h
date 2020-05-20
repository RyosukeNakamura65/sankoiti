//#pragma once

#define EFFECT_MAX 100
#define TOBI_EFFECT_MAX 10
#define TOBI_SIZE_MAX 6


enum EFFECT_COLOR {
	EFFECT_C_BLUE,
	EFFECT_C_PINK,
	EFFECT_C_GREEN,
	EFFECT_C_YELLOW,
	EFFECT_C_MAX
};

enum EFFECT_TYPE {
	EFFECT_T_BLOCK,
	EFFECT_T_TOBITIRI,
	EFFECT_T_MAX,
};

struct EFFECT {
	int index;
	EFFECT_COLOR effectColor;		//エフェクトの色
	XY_F pos;			//座標
	XY_F move;			//移動量

	float speed;		//移動スピード
	float angel;		//移動角度
	XY	size;			//画像サイズ
	XY	sizeOffset;		//画像補正量
	int life;			//エフェクトの寿命
	int lifeMax;		//寿命の最大
	bool visible;		//表示フラグ(true:表示)
	EFFECT_TYPE effectType;		//エフェクトの種別
};

void TobiSystemInit(void);

void TobiInit(void);

void TobiContlor(void);

void TobiDraw(void);

void SetBlockEffect(XY pos, EFFECT_COLOR effectColor);

void SetTobichiriEffect(XY pos, EFFECT_COLOR effectColor);
