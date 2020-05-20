#include"Dxlib.h"
#include "main.h"
#include "player.h"
#include "shot.h"
#include "stage.h"

CHARACTER player3;
XY player3PosCopy;
XY player3PosOffset;
int player3Counter;

CHAR_IMAGE player3Image;

// ���̏�����
const int KeyList[DIR_MAX]
{ KEY_INPUT_DOWN, KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_UP };

void player3SystemInit(void)
{
	// �S��׸���̲Ұ��
	player3Image.faceImage = LoadGraph("image/greenface.png");

	LoadDivGraph("image/greenwalk.png", PLAYER_ANI_MAX * DIR_MAX				// �����摜�̓ǂݍ���
		, PLAYER_ANI_MAX, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, player3Image.walkImage[0]);

	player3Image.hitImage = LoadGraph("image/greenhit.png");

	LoadDivGraph("image/greenshot.png", DIR_MAX, 1, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, player3Image.shotImage);

}

void player3GameInit(void)
{
	player3.startPos = { MAP_OFFSET_X + CHIP_SIZE_X - MAP_OFFSET_X, SCREEN_SIZE_Y - CHIP_SIZE_Y * 3 - MAP_OFFSET_Y };

	player3.moveDir = DIR_DOWN;						//�����Ă������
	player3.pos = player3.startPos;							//�L�����N�^�̈ʒu�i���S�j
	player3.size = { 35, 50 };					//�L�����N�^�摜�̃T�C�Y
	player3.sizeOffset = { player3.size.x / 2 , player3.size.y / 2 };
	player3.shotFlag = false;						//�L�����N�^�̏�ԁi�e�����Ă��邩�H�j
	player3.damageFlag = false;					//�L�����N�^�̏�ԁi�_���[�W�󂯂Ă��邩�H�j
	player3.gameOverFlag = false;					//�L�����N�^�̏�ԁi����Ă��邩�H�j
	player3.moveSpeed = PLAYER_DEF_SPEED;			//�L�����N�^�̈ړ���
	player3.lifeMax = PLAYER_LIFE_MAX;			//�L�����N�^�̗͍̑ő�
	player3.life = player3.lifeMax;				//�L�����N�^�̗̑�
	player3.animCnt = 10;							//�L�����N�^�̃A�j���[�V�����p�J�E���^
	player3.imgLockCnt = 0;						//�L�����N�^�̃C���[�W�Œ�p�J�E���^
	player3.visible = true;						//�\�����

	player3Counter = 0;
}

void player3CharSelect(void)
{
	DrawGraph(0, SCREEN_SIZE_Y / 2, player3Image.faceImage, true);
	// �e�L�����̃h�b�g�G�̕`��
	DrawGraph((SCREEN_SIZE_X / 2 - FACE_SIZE_X) / 2 + FACE_SIZE_X, SCREEN_SIZE_Y / 2 + FACE_SIZE_Y / 2
		, player3Image.walkImage[DIR_DOWN][player3Counter / 20 % PLAYER_ANI_MAX], true);

	player3Counter++;
}

void player3Control(void)
{
	// �L�[����
	// ��߰�ނ�ς���

	player3PosCopy = player3.pos;		// ���W���ޯ�����
	player3PosOffset = player3PosCopy;

	player3.shotFlag = false;
	player3.moveFlag = false;

	// ��ڲ԰�̕���
	for (int dir = 0; dir < DIR_MAX; dir++)
	{
		if (CheckHitKey(KeyList[dir]) == 1)
		{
			player3.moveDir = (MOVE_DIR)dir;
			player3.moveFlag = true;
		}
	}

	// player���ړ�������
	if (player3.moveFlag == true)
	{
		if (player3.moveDir == DIR_RIGHT)	// �E�ړ�
		{
			player3PosCopy.x += player3.moveSpeed;
			player3PosOffset.x = player3PosCopy.x + player3.size.x / 2;
			if (IsPass(player3PosOffset))
			{
				player3.pos = player3PosCopy;
			}
		}
		if (player3.moveDir == DIR_LEFT)	// ���ړ�
		{
			player3PosCopy.x -= player3.moveSpeed;
			player3PosOffset.x = player3PosCopy.x - player3.size.x / 2;
			if (IsPass(player3PosOffset))
			{
				player3.pos = player3PosCopy;
			}
		}
		if (player3.moveDir == DIR_UP)		// ��ړ�
		{
			player3PosCopy.y -= player3.moveSpeed;
			player3PosOffset.y = player3PosCopy.y - player3.size.y / 2;
			if (IsPass(player3PosOffset))
			{
				player3.pos = player3PosCopy;
			}
		}
		if (player3.moveDir == DIR_DOWN)		// ���ړ�
		{
			player3PosCopy.y += player3.moveSpeed;
			player3PosOffset.y = player3PosCopy.y + player3.size.y / 2;
			if (IsPass(player3PosOffset))
			{
				player3.pos = player3PosCopy;
			}
		}
		player3.animCnt++;
	}
	// ��ڲ԰��ײ̂�0�ɂȂ�����
	if (player3.life == 0)
	{
		player3.gameOverFlag = true;
	}

	// ��ڲ԰�̔�e��
	if (player3.damageFlag)
	{
		if (player3.imgLockCnt < 50)
		{
			player3.imgLockCnt++;
		}
		else
		{
			player3.damageFlag = false;
			player3.imgLockCnt = 0;
		}
	}
	// �e�̔���
	if (CheckHitKey(KEY_INPUT_LCONTROL))
	{
		CreateShot(player3.pos, player3.moveDir);
		player3.shotFlag = true;
	}

}

bool player3GameOver(void)
{
	if (player3.gameOverFlag)
	{
		return true;
	}
	return false;
}

	//�e�Ƃ̓����蔻��
bool Shot3CheckHit(XY sPos, int ssize)
{
	if (!player3.damageFlag)
	{
		if (player3.pos.y - player3.sizeOffset.y <= sPos.y
			&& player3.pos.y + player3.sizeOffset.y >= sPos.y
			&& player3.pos.x - player3.sizeOffset.x <= sPos.x
			&& player3.pos.x + player3.sizeOffset.x >= sPos.x)
		{
			if (player3.life > 0)
			{
				player3.life -= 1;
				player3.damageFlag = true;
			}
			return true;
		}
	}
}

void player3Draw(void)
{
	// ��ڲ԰�̕\��
	// �����̕\��

	DrawFormatString(0, 0, 0xffffff, "Speed:%d", player3.moveSpeed);
	DrawFormatString(0, 16, GetColor(255, 255, 255), "Count:%d", player3.animCnt);
	DrawFormatString(300, 0, GetColor(255, 255, 255), "3Life%d", player3.life);

	if (player3.shotFlag)
	{
		DrawGraph(player3.pos.x - player3.sizeOffset.x + MAP_OFFSET_X
			, player3.pos.y - player3.sizeOffset.y + MAP_OFFSET_Y, player3Image.shotImage[player3.moveDir], true);
	}
	else
	{
		if (player3.gameOverFlag)
		{
			DrawGraph(player3.pos.x, player3.pos.y, player3Image.hitImage, true);
		}
		else
		{
			if (player3.damageFlag)
			{
				if (player3.animCnt % 1 == 0)
				{
					DrawGraph(player3.pos.x - player3.sizeOffset.x + MAP_OFFSET_X, player3.pos.y - player3.sizeOffset.y + MAP_OFFSET_Y
						, player3Image.walkImage[player3.moveDir][player3.animCnt / 10 % PLAYER_ANI_MAX], true);
				}
				else
				{
				}
			}
			else
			{
				DrawGraph(player3.pos.x - player3.sizeOffset.x + MAP_OFFSET_X, player3.pos.y - player3.sizeOffset.y + MAP_OFFSET_Y
					, player3Image.walkImage[player3.moveDir][player3.animCnt / 10 % PLAYER_ANI_MAX], true);
			}
		}
	}
}