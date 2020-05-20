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
	EFFECT_COLOR effectColor;		//�G�t�F�N�g�̐F
	XY_F pos;			//���W
	XY_F move;			//�ړ���

	float speed;		//�ړ��X�s�[�h
	float angel;		//�ړ��p�x
	XY	size;			//�摜�T�C�Y
	XY	sizeOffset;		//�摜�␳��
	int life;			//�G�t�F�N�g�̎���
	int lifeMax;		//�����̍ő�
	bool visible;		//�\���t���O(true:�\��)
	EFFECT_TYPE effectType;		//�G�t�F�N�g�̎��
};

void TobiSystemInit(void);

void TobiInit(void);

void TobiContlor(void);

void TobiDraw(void);

void SetBlockEffect(XY pos, EFFECT_COLOR effectColor);

void SetTobichiriEffect(XY pos, EFFECT_COLOR effectColor);
