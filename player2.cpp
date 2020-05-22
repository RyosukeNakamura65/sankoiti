#include"Dxlib.h"
#include "main.h"
#include "player.h"
#include "shot.h"
#include "shot2.h"
#include "stage.h"
#include "KeyCheck.h"

CHARACTER player2;
XY player2PosCopy;
XY player2PosOffset;
int player2Counter;

CHAR_IMAGE player2Image;

// ���̏�����
const int KeyList[DIR_MAX]
{ KEY_INPUT_DOWN, KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_UP };

void player2SystemInit(void)
{
	// �S��׸���̲Ұ��
	player2Image.faceImage = LoadGraph("image/pinkface.png");

	LoadDivGraph("image/pinkwalk.png", PLAYER_ANI_MAX * DIR_MAX				// �����摜�̓ǂݍ���
		, PLAYER_ANI_MAX, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, player2Image.walkImage[0]);

	player2Image.hitImage = LoadGraph("image/pinkhit.png");

	LoadDivGraph("image/pinkshot.png", DIR_MAX, 1, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, player2Image.shotImage);

}

void player2GameInit(void)
{
	player2.moveDir = DIR_DOWN;						//�����Ă������
	player2.size = { 35, 50 };					//�L�����N�^�摜�̃T�C�Y
	player2.sizeOffset = { player2.size.x / 2 , player2.size.y / 2 };
	player2.startPos = { SCREEN_SIZE_X - MAP_OFFSET_X - CHIP_SIZE_X * 2 - MAP_OFFSET_X + player2.sizeOffset.x, MAP_OFFSET_Y + CHIP_SIZE_Y * 2 - MAP_OFFSET_Y + player2.sizeOffset.y  };
	player2.pos = player2.startPos;							//�L�����N�^�̈ʒu�i���S�j
	player2.shotFlag = false;						//�L�����N�^�̏�ԁi�e�����Ă��邩�H�j
	player2.damageFlag = false;					//�L�����N�^�̏�ԁi�_���[�W�󂯂Ă��邩�H�j
	player2.gameOverFlag = false;					//�L�����N�^�̏�ԁi����Ă��邩�H�j
	player2.moveSpeed = PLAYER_DEF_SPEED;			//�L�����N�^�̈ړ���
	player2.lifeMax = PLAYER_LIFE_MAX;			//�L�����N�^�̗͍̑ő�
	player2.life = player2.lifeMax;				//�L�����N�^�̗̑�
	player2.animCnt = 10;							//�L�����N�^�̃A�j���[�V�����p�J�E���^
	player2.imgLockCnt = 0;						//�L�����N�^�̃C���[�W�Œ�p�J�E���^
	player2.visible = true;						//�\�����

	player2Counter = 0;
}

void player2CharSelect(void)
{
	// �e�L�����̊�̕`��
	DrawGraph(SCREEN_SIZE_X / 2, 0, player2Image.faceImage, true);
	// �e�L�����̃h�b�g�G�̕`��
	DrawGraph((SCREEN_SIZE_X / 2 - FACE_SIZE_X) / 2 + SCREEN_SIZE_X / 2 + FACE_SIZE_X, FACE_SIZE_Y / 2
		, player2Image.walkImage[DIR_DOWN][player2Counter / 20 % PLAYER_ANI_MAX], true);

	player2Counter++;
}

void player2Control(void)
{
	// �L�[����
	// ��߰�ނ�ς���

	player2PosCopy = player2.pos;		// ���W���ޯ�����
	player2PosOffset = player2PosCopy;
	XY playerHitRight = player2.pos;
	XY playerHitLeft = player2.pos;
	XY playerHitDown = player2.pos;
	XY playerHitUp = player2.pos;

	player2.shotFlag = false;
	player2.moveFlag = false;

	// ��ڲ԰�̕���
	for (int dir = 0; dir < DIR_MAX; dir++)
	{
		if (CheckHitKey(KeyList[dir]) == 1)
		{
			player2.moveDir = (MOVE_DIR)dir;
			player2.moveFlag = true;
		}
	}

	// player���ړ�������
	if (player2.moveFlag == true)
	{
		if (player2.moveDir == DIR_RIGHT)	// �E�ړ�
		{
			player2PosCopy.x += player2.moveSpeed;
			player2PosOffset.x = player2PosCopy.x + player2.sizeOffset.x - 5;
			player2PosOffset.y += 6;

			playerHitUp.x = player2PosOffset.x;
			playerHitUp.y -= player2.sizeOffset.y - 50;

			playerHitDown = player2PosOffset;
			playerHitDown.y += player2.sizeOffset.y - 20;

			if (PIsPass(player2PosOffset) && PIsPass(playerHitUp) && PIsPass(playerHitDown))
			{
				player2.pos = player2PosCopy;
			}
		}
		if (player2.moveDir == DIR_LEFT)	// ���ړ�
		{
			player2PosCopy.x -= player2.moveSpeed;
			player2PosOffset.x = player2PosCopy.x - player2.sizeOffset.x + 5;
			player2PosOffset.y += 6;

			playerHitUp.x = player2PosOffset.x;
			playerHitUp.y -= player2.sizeOffset.y - 50;

			playerHitDown = player2PosOffset;
			playerHitDown.y += player2.sizeOffset.y - 20;

			if (PIsPass(player2PosOffset) && PIsPass(playerHitUp) && PIsPass(playerHitDown))
			{
				player2.pos = player2PosCopy;
			}
		}
		if (player2.moveDir == DIR_UP)		// ��ړ�
		{
			player2PosCopy.y -= player2.moveSpeed;
			player2PosOffset.y = player2PosCopy.y - player2.sizeOffset.y + 30;

			//�E�̓���Ƀu���b�N�����邩
			playerHitLeft = player2PosOffset;
			playerHitLeft.x -= player2.sizeOffset.x - 5;

			//���̓���Ƀu���b�N�����邩
			playerHitRight = player2PosOffset;
			playerHitRight.x += player2.sizeOffset.x - 5;

			if (PIsPass(player2PosOffset) && PIsPass(playerHitLeft) && PIsPass(playerHitRight))
			{
				player2.pos = player2PosCopy;
			}
		}
		if (player2.moveDir == DIR_DOWN)		// ���ړ�
		{
			player2PosCopy.y += player2.moveSpeed;
			player2PosOffset.y = player2PosCopy.y + player2.sizeOffset.y;

			//�E�̑����Ƀu���b�N�����邩
			playerHitLeft = player2PosOffset;
			playerHitLeft.x -= player2.sizeOffset.x - 5;

			//���̑����Ƀu���b�N�����邩
			playerHitRight = player2PosOffset;
			playerHitRight.x += player2.sizeOffset.x - 5;

			if (PIsPass(player2PosOffset) && PIsPass(playerHitLeft) && PIsPass(playerHitRight))
			{
				player2.pos = player2PosCopy;
			}
		}
		player2.animCnt++;
	}
	// ��ڲ԰��ײ̂�0�ɂȂ�����
	if (player2.life == 0)
	{
		player2.gameOverFlag = true;
	}

	// ��ڲ԰�̔�e��
	if (player2.damageFlag)
	{
		if (player2.imgLockCnt < 50)
		{
			player2.imgLockCnt++;
		}
		else
		{
			player2.damageFlag = false;
			player2.imgLockCnt = 0;
		}
	}

	// �e�̔���
	if (keyDownTrigger[KEY_ID_W])
	{
		CreateShot2(player2.pos, player2.sizeOffset, player2.moveDir);
		player2.shotFlag = true;
	}
}

bool player2GameOver(void)
{
	if (player2.gameOverFlag)
	{
		return true;
	}
	return false;
}

//�e�Ƃ̓����蔻��
bool Shot2CheckHit(XY sPos, int ssize)
{
	if (!player2.damageFlag)
	{
		if (player2.pos.y - player2.sizeOffset.y <= sPos.y
			&& player2.pos.y + player2.sizeOffset.y >= sPos.y
			&& player2.pos.x - player2.sizeOffset.x <= sPos.x
			&& player2.pos.x + player2.sizeOffset.x >= sPos.x)
		{
			if (player2.life > 0)
			{
				player2.life -= 1;
				player2.damageFlag = true;
				DeleteShot();
			}
			return true;
		}
	}
}

void player2Draw(void)
{
	// ��ڲ԰�̕\��
	// �����̕\��

	DrawFormatString(0, 0, 0xffffff, "Speed:%d", player2.moveSpeed);
	DrawFormatString(0, 16, GetColor(255, 255, 255), "Count:%d", player2.animCnt);
	DrawFormatString(200, 0, GetColor(255, 255, 255), "2Life%d", player2.life);

	// ����̕`��(ײ̂�0:true�Aײ̂�1�ȏ�:false)
	if (player2.gameOverFlag)
	{
		DrawGraph(player2.pos.x - player2.sizeOffset.x + MAP_OFFSET_X, player2.pos.y - player2.sizeOffset.y + MAP_OFFSET_Y, player2Image.hitImage, true);
	}
	else
	{
		// ��ڲ԰�̔�e�̕`��i�_�ł�����j
		if (player2.damageFlag)
		{
			if (player2.animCnt % 2 == 0)
			{
				DrawGraph(player2.pos.x - player2.sizeOffset.x + MAP_OFFSET_X, player2.pos.y - player2.sizeOffset.y + MAP_OFFSET_Y
					, player2Image.walkImage[player2.moveDir][player2.animCnt / 10 % PLAYER_ANI_MAX], true);
			}
			else
			{
			}
		}
		else
		{
			// ���ĲҰ�ނ̕`��(�e�������Ă���:true�A�e�������Ă��Ȃ�:false)
			if (player2.shotFlag)
			{
				DrawGraph(player2.pos.x - player2.sizeOffset.x + MAP_OFFSET_X
					, player2.pos.y - player2.sizeOffset.y + MAP_OFFSET_Y, player2Image.shotImage[player2.moveDir], true);
			}
			else
			{
				// �ʏ펞�̕`��
				DrawGraph(player2.pos.x - player2.sizeOffset.x + MAP_OFFSET_X, player2.pos.y - player2.sizeOffset.y + MAP_OFFSET_Y
					, player2Image.walkImage[player2.moveDir][player2.animCnt / 10 % PLAYER_ANI_MAX], true);
			}
		}
	}
}