#include"Dxlib.h"
#include "main.h"
#include "player.h"
#include "shot.h"
#include "shot4.h"
#include "stage.h"
#include "KeyCheck.h"

CHARACTER player4;
XY player4PosCopy;
XY player4PosOffset;
int player4Counter;

CHAR_IMAGE player4Image;

// ���̏�����
const int KeyList[DIR_MAX]
{ KEY_INPUT_DOWN, KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_UP };

void player4SystemInit(void)
{
	// �S��׸���̲Ұ��
	player4Image.faceImage = LoadGraph("image/yellowface.png");

	LoadDivGraph("image/yellowwalk.png", PLAYER_ANI_MAX * DIR_MAX				// �����摜�̓ǂݍ���
		, PLAYER_ANI_MAX, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, player4Image.walkImage[0]);

	player4Image.hitImage = LoadGraph("image/yellowhit.png");

	LoadDivGraph("image/yellowshot.png", DIR_MAX, 1, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, player4Image.shotImage);

}

void player4GameInit(void)
{
	player4.moveDir = DIR_DOWN;						//�����Ă������
	player4.size = { 35, 50 };					//�L�����N�^�摜�̃T�C�Y
	player4.sizeOffset = { player4.size.x / 2 , player4.size.y / 2 };
	player4.startPos = { SCREEN_SIZE_X - MAP_OFFSET_X - CHIP_SIZE_X * 2 - MAP_OFFSET_X + player4.sizeOffset.x, SCREEN_SIZE_Y - CHIP_SIZE_Y * 3 - MAP_OFFSET_Y + player4.sizeOffset.y - 30 };
	player4.pos = player4.startPos;							//�L�����N�^�̈ʒu�i���S�j
	player4.shotFlag = false;						//�L�����N�^�̏�ԁi�e�����Ă��邩�H�j
	player4.damageFlag = false;					//�L�����N�^�̏�ԁi�_���[�W�󂯂Ă��邩�H�j
	player4.gameOverFlag = false;					//�L�����N�^�̏�ԁi����Ă��邩�H�j
	player4.moveSpeed = PLAYER_DEF_SPEED;			//�L�����N�^�̈ړ���
	player4.lifeMax = PLAYER_LIFE_MAX;			//�L�����N�^�̗͍̑ő�
	player4.life = player4.lifeMax;				//�L�����N�^�̗̑�
	player4.animCnt = 10;							//�L�����N�^�̃A�j���[�V�����p�J�E���^
	player4.imgLockCnt = 0;						//�L�����N�^�̃C���[�W�Œ�p�J�E���^
	player4.visible = true;						//�\�����

	player4Counter = 0;
}

void player4CharSelect(void)
{
	// �e�L�����̊�̕`��
	DrawGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, player4Image.faceImage, true);
	// �e�L�����̃h�b�g�G�̕`��
	DrawGraph((SCREEN_SIZE_X / 2 - FACE_SIZE_X) / 2 + SCREEN_SIZE_X / 2 + FACE_SIZE_X, SCREEN_SIZE_Y / 2 + FACE_SIZE_Y / 2
		, player4Image.walkImage[DIR_DOWN][player4Counter / 20 % PLAYER_ANI_MAX], true);

	player4Counter++;
}

void player4Control(void)
{
	// �L�[����
	// ��߰�ނ�ς���

	player4PosCopy = player4.pos;		// ���W���ޯ�����
	player4PosOffset = player4PosCopy;
	XY playerHitRight = player4.pos;
	XY playerHitLeft = player4.pos;
	XY playerHitDown = player4.pos;
	XY playerHitUp = player4.pos;

	player4.shotFlag = false;
	player4.moveFlag = false;

	// ��ڲ԰�̕���
	for (int dir = 0; dir < DIR_MAX; dir++)
	{
		if (CheckHitKey(KeyList[dir]) == 1)
		{
			player4.moveDir = (MOVE_DIR)dir;
			player4.moveFlag = true;
		}
	}

	// player���ړ�������
	if (player4.moveFlag == true)
	{
		if (player4.moveDir == DIR_RIGHT)	// �E�ړ�
		{
			player4PosCopy.x += player4.moveSpeed;
			player4PosOffset.x = player4PosCopy.x + player4.sizeOffset.x - 5;
			player4PosOffset.y += 6;

			playerHitUp.x = player4PosOffset.x;
			playerHitUp.y -= player4.sizeOffset.y - 50;

			playerHitDown = player4PosOffset;
			playerHitDown.y += player4.sizeOffset.y - 20;

			if (PIsPass(player4PosOffset) && PIsPass(playerHitUp) && PIsPass(playerHitDown))
			{
				player4.pos = player4PosCopy;
			}
		}
		if (player4.moveDir == DIR_LEFT)	// ���ړ�
		{
			player4PosCopy.x -= player4.moveSpeed;
			player4PosOffset.x = player4PosCopy.x - player4.sizeOffset.x + 5;
			player4PosOffset.y += 6;

			playerHitUp.x = player4PosOffset.x;
			playerHitUp.y -= player4.sizeOffset.y - 50;

			playerHitDown = player4PosOffset;
			playerHitDown.y += player4.sizeOffset.y - 20;

			if (PIsPass(player4PosOffset) && PIsPass(playerHitUp) && PIsPass(playerHitDown))
			{
				player4.pos = player4PosCopy;
			}
		}
		if (player4.moveDir == DIR_UP)		// ��ړ�
		{
			player4PosCopy.y -= player4.moveSpeed;
			player4PosOffset.y = player4PosCopy.y - player4.sizeOffset.y + 30;

			//�E�̓���Ƀu���b�N�����邩
			playerHitLeft = player4PosOffset;
			playerHitLeft.x -= player4.sizeOffset.x - 5;

			//���̓���Ƀu���b�N�����邩
			playerHitRight = player4PosOffset;
			playerHitRight.x += player4.sizeOffset.x - 5;

			if (PIsPass(player4PosOffset) && PIsPass(playerHitLeft) && PIsPass(playerHitRight))
			{
				player4.pos = player4PosCopy;
			}
		}
		if (player4.moveDir == DIR_DOWN)		// ���ړ�
		{
			player4PosCopy.y += player4.moveSpeed;
			player4PosOffset.y = player4PosCopy.y + player4.sizeOffset.y;

			//�E�̑����Ƀu���b�N�����邩
			playerHitLeft = player4PosOffset;
			playerHitLeft.x -= player4.sizeOffset.x - 5;

			//���̑����Ƀu���b�N�����邩
			playerHitRight = player4PosOffset;
			playerHitRight.x += player4.sizeOffset.x - 5;

			if (PIsPass(player4PosOffset) && PIsPass(playerHitLeft) && PIsPass(playerHitRight))
			{
				player4.pos = player4PosCopy;
			}
		}
		player4.animCnt++;
	}
	// ��ڲ԰��ײ̂�0�ɂȂ�����
	if (player4.life == 0)
	{
		player4.gameOverFlag = true;
	}

	// ��ڲ԰�̔�e��
	if (player4.damageFlag)
	{
		if (player4.imgLockCnt < 50)
		{
			player4.imgLockCnt++;
		}
		else
		{
			player4.damageFlag = false;
			player4.imgLockCnt = 0;
		}
	}

	// �e�̔���
	if (keyDownTrigger[KEY_ID_D])
	{
		CreateShot4(player4.pos, player4.sizeOffset, player4.moveDir);
		player4.shotFlag = true;
	}
}

bool player4GameOver(void)
{
	if (player4.gameOverFlag)
	{
		return true;
	}
	return false;
}

//�e�Ƃ̓����蔻��
bool Shot4CheckHit(XY sPos, int ssize)
{
	if (!player4.damageFlag)
	{
		if (player4.pos.y - player4.sizeOffset.y <= sPos.y
			&& player4.pos.y + player4.sizeOffset.y >= sPos.y
			&& player4.pos.x - player4.sizeOffset.x <= sPos.x
			&& player4.pos.x + player4.sizeOffset.x >= sPos.x)
		{
			if (player4.life > 0)
			{
				player4.life -= 1;
				player4.damageFlag = true;
				DeleteShot();
			}
			return true;
		}
	}
}

void player4Draw(void)
{
	// ��ڲ԰�̕\��
	// �����̕\��

	DrawFormatString(0, 0, 0xffffff, "Speed:%d", player4.moveSpeed);
	DrawFormatString(0, 16, GetColor(255, 255, 255), "Count:%d", player4.animCnt);
	DrawFormatString(400, 0, GetColor(255, 255, 255), "4Life%d", player4.life);

	// ����̕`��(ײ̂�0:true�Aײ̂�1�ȏ�:false)
	if (player4.gameOverFlag)
	{
		DrawGraph(player4.pos.x - player4.sizeOffset.x + MAP_OFFSET_X, player4.pos.y - player4.sizeOffset.y + MAP_OFFSET_Y, player4Image.hitImage, true);
	}
	else
	{
		// ��ڲ԰�̔�e�̕`��i�_�ł�����j
		if (player4.damageFlag)
		{
			if (player4.animCnt % 2 == 0)
			{
				DrawGraph(player4.pos.x - player4.sizeOffset.x + MAP_OFFSET_X, player4.pos.y - player4.sizeOffset.y + MAP_OFFSET_Y
					, player4Image.walkImage[player4.moveDir][player4.animCnt / 10 % PLAYER_ANI_MAX], true);
			}
			else
			{
			}
		}
		else
		{
			// ���ĲҰ�ނ̕`��(�e�������Ă���:true�A�e�������Ă��Ȃ�:false)
			if (player4.shotFlag)
			{
				DrawGraph(player4.pos.x - player4.sizeOffset.x + MAP_OFFSET_X
					, player4.pos.y - player4.sizeOffset.y + MAP_OFFSET_Y, player4Image.shotImage[player4.moveDir], true);
			}
			else
			{
				// �ʏ펞�̕`��
				DrawGraph(player4.pos.x - player4.sizeOffset.x + MAP_OFFSET_X, player4.pos.y - player4.sizeOffset.y + MAP_OFFSET_Y
					, player4Image.walkImage[player4.moveDir][player4.animCnt / 10 % PLAYER_ANI_MAX], true);
			}
		}
	}
}