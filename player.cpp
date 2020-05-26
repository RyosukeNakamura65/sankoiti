#include"Dxlib.h"
#include "main.h"
#include "player.h"
#include "shot.h"
#include "stage.h"
#include "KeyCheck.h"

CHARACTER player;
XY playerPosCopy;
XY playerPosOffset;
int playerCounter;

CHAR_IMAGE playerImage;

// ���̏�����
const int KeyList[DIR_MAX]
{ KEY_INPUT_DOWN, KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_UP };

void playerSystemInit(void)
{
	// ��׸���̉摜�i�[

	playerImage.faceImage = LoadGraph("image/blueface.png");				// ��̉摜�ǂݍ���

	LoadDivGraph("image/bluewalk.png", PLAYER_ANI_MAX * DIR_MAX				
		, PLAYER_ANI_MAX, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, playerImage.walkImage[0]);				// ���s�摜�ǂݍ���

	playerImage.hitImage = LoadGraph("image/bluehit.png");					// ����摜�ǂݍ���

	LoadDivGraph("image/blueshot.png", DIR_MAX, 1, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, playerImage.shotImage);			// ���ĉ摜�ǂݍ���

	playerImage.standImage = LoadGraph("image/buleup.png");
}

void playerGameInit(void)
{
	player.moveDir = DIR_DOWN;														//�����Ă������
	player.size = { 35, 50 };														//�L�����N�^�摜�̃T�C�Y
	player.sizeOffset = { player.size.x / 2 , player.size.y / 2 };					// ��׸���̵̾�Ļ���
	player.startPos = { MAP_OFFSET_X + CHIP_SIZE_X - MAP_OFFSET_X + player.sizeOffset.x				
		, MAP_OFFSET_Y + CHIP_SIZE_Y * 2 - MAP_OFFSET_Y + player.sizeOffset.y };				// �L�����N�^�̃X�^�[�g�̈ʒu
	player.pos = player.startPos;													//�L�����N�^�̈ʒu�i���S�j
	player.shotFlag = false;														//�L�����N�^�̏�ԁi�e�����Ă��邩�H�j
	player.damageFlag = false;														//�L�����N�^�̏�ԁi�_���[�W�󂯂Ă��邩�H�j
	player.gameOverFlag = false;													//�L�����N�^�̏�ԁi����Ă��邩�H�j
	player.moveSpeed = PLAYER_DEF_SPEED;											//�L�����N�^�̈ړ���
	player.lifeMax = PLAYER_LIFE_MAX;												//�L�����N�^�̗͍̑ő�
	player.life = player.lifeMax;													//�L�����N�^�̗̑�
	player.animCnt = 10;															//�L�����N�^�̃A�j���[�V�����p�J�E���^
	player.imgLockCnt = 0;															//�L�����N�^�̃C���[�W�Œ�p�J�E���^
	player.visible = true;															//�\�����

	playerCounter = 0;																// ��ڲ԰�I����ʂł̱�Ұ��ݶ���														
}

void playerCharSelect(void)
{
	// �w�i�̕`��
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(255, 255, 255), true);
	// �e�L�����̊�̕`��
	DrawGraph(0, 0, playerImage.faceImage, true);
	// �e�L�����̃h�b�g�G�̕`��
	DrawGraph((SCREEN_SIZE_X / 2 - FACE_SIZE_X) / 2 + FACE_SIZE_X, FACE_SIZE_Y / 2
		, playerImage.walkImage[DIR_DOWN][playerCounter / 20 % PLAYER_ANI_MAX], true);

	playerCounter++;			// ��Ұ��݂𓮂���
}

void playerControl(void)
{
	// �L�[����
	// ��߰�ނ�ς���

	playerPosCopy = player.pos;				// ���W���ޯ�����
	playerPosOffset = playerPosCopy;			// �̾�ĕ���̍��W
	XY playerHitRight = player.pos;
	XY playerHitLeft = player.pos;
	XY playerHitDown = player.pos;
	XY playerHitUp = player.pos;

	player.shotFlag = false;
	player.moveFlag = false;

	// ��ڲ԰�̕���
	for (int dir = 0; dir < DIR_MAX; dir++)
	{
		if (CheckHitKey(KeyList[dir]) == 1)
		{
			player.moveDir = (MOVE_DIR)dir;
			player.moveFlag = true;
		}
	}

	playerPosOffset.y = playerPosCopy.y - player.hitPosS.y;

	// player���ړ�������
	if (player.moveFlag == true)
	{
		if (player.moveDir == DIR_RIGHT)	// �E�ړ�
		{
			playerPosCopy.x += player.moveSpeed;
			playerPosOffset.x = playerPosCopy.x + player.sizeOffset.x - 5;
			playerPosOffset.y += 6;

			playerHitUp.x = playerPosOffset.x;
			playerHitUp.y -= player.sizeOffset.y - 50;

			playerHitDown = playerPosOffset;
			playerHitDown.y += player.sizeOffset.y - 20;

			if (PIsPass(playerPosOffset) && PIsPass(playerHitUp) && PIsPass(playerHitDown))
			{
				player.pos = playerPosCopy;
			}
		}
		if (player.moveDir == DIR_LEFT)	// ���ړ�
		{
			playerPosCopy.x -= player.moveSpeed;
			playerPosOffset.x = playerPosCopy.x - player.sizeOffset.x + 5;
			playerPosOffset.y += 6;

			playerHitUp.x = playerPosOffset.x;
			playerHitUp.y -= player.sizeOffset.y - 50;

			playerHitDown = playerPosOffset;
			playerHitDown.y += player.sizeOffset.y - 20;

			if (PIsPass(playerPosOffset) && PIsPass(playerHitUp) && PIsPass(playerHitDown))
			{
				player.pos = playerPosCopy;
			}
		}
		if (player.moveDir == DIR_UP)		// ��ړ�
		{
			playerPosCopy.y -= player.moveSpeed;
			playerPosOffset.y = playerPosCopy.y - player.sizeOffset.y + 30;

			//�E�̓���Ƀu���b�N�����邩
			playerHitLeft = playerPosOffset;
			playerHitLeft.x -= player.sizeOffset.x - 5;

			//���̓���Ƀu���b�N�����邩
			playerHitRight = playerPosOffset;
			playerHitRight.x += player.sizeOffset.x - 5;

			if (PIsPass(playerPosOffset) && PIsPass(playerHitLeft) && PIsPass(playerHitRight))
			{
				player.pos = playerPosCopy;
			}
		}
		if (player.moveDir == DIR_DOWN)		// ���ړ�
		{
			playerPosCopy.y += player.moveSpeed;
			playerPosOffset.y = playerPosCopy.y + player.sizeOffset.y;

			//�E�̑����Ƀu���b�N�����邩
			playerHitLeft = playerPosOffset;
			playerHitLeft.x -= player.sizeOffset.x - 5;

			//���̑����Ƀu���b�N�����邩
			playerHitRight = playerPosOffset;
			playerHitRight.x += player.sizeOffset.x - 5;

			if (PIsPass(playerPosOffset) && PIsPass(playerHitLeft) && PIsPass(playerHitRight))
			{
				player.pos = playerPosCopy;
			}
		}
		player.animCnt++;
	}

	// ��ڲ԰��ײ̂�0�ɂȂ�����
	if (player.life == 0)
	{
		player.gameOverFlag = true;
	}

	// ��ڲ԰�̔�e��
	if (player.damageFlag)
	{
		if (player.imgLockCnt < 50)					// ���b�����Ȃ��Ȃ�
		{
			player.imgLockCnt++;
		}
		else
		{
			player.damageFlag = false;				// ������
			player.imgLockCnt = 0;
		}
	}

	// �e�̔��ˎ�
	if (player.shotFlag)
	{
		if (player.imgLockCnt < 10)					// ���b�����Ȃ��Ȃ�
		{
			player.imgLockCnt++;
		}
		else
		{
			player.shotFlag = false;				// ������
			player.imgLockCnt = 0;
		}

	}

	// �e�̔���
	if (keyDownTrigger[KEY_ID_A])
	{
		CreateShot(player.pos, player.sizeOffset, player.moveDir);				// �e�̐���
		player.shotFlag = true;
	}

	playerCounter++;			// ��Ұ��݂𓮂���
}

bool playerGameOver(void)
{
	// ��ڲ԰�̺��۰ق𒆎~
	if (player.gameOverFlag)
	{
		return true;
	}
	return false;
}

void playerGameOverDraw(void)
{
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(255, 255, 255), true);
	DrawFormatString(100, SCREEN_SIZE_Y / 2, GetColor(0, 0, 0), "�v���C���[1�̂��傤��I�I");
	DrawGraph(SCREEN_SIZE_X - PLAYER_STAND_X, SCREEN_SIZE_Y - PLAYER_STAND_Y, playerImage.standImage, true);
}

//�e�Ƃ̓����蔻��
bool ShotCheckHit(XY sPos, int ssize)
{
	if (!player.damageFlag)				// �e���������ĂȂ��Ƃ�
	{
		// �e�Ʒ�׸���̓����蔻��
		if (player.pos.y - player.sizeOffset.y <= sPos.y
			&& player.pos.y + player.sizeOffset.y >= sPos.y
			&& player.pos.x - player.sizeOffset.x <= sPos.x
			&& player.pos.x + player.sizeOffset.x >= sPos.x)
		{
			if (player.life > 0)
			{
				player.life -= 1;
				player.damageFlag = true;
				DeleteShot();
			}
			return true;
		}
	}
}

void playerDraw(void)
{
	// ��ڲ԰�̕\��
	// �����̕\��

	DrawFormatString(0, 0, 0xffffff, "Speed:%d", player.moveSpeed);
	DrawFormatString(0, 16, GetColor(255, 255, 255), "Count:%d", player.animCnt);
	DrawFormatString(100, 0, GetColor(255, 255, 255), "1Life%d", player.life);

	// ����̕`��(ײ̂�0:true�Aײ̂�1�ȏ�:false)
	if (player.gameOverFlag)
	{
		DrawGraph(player.pos.x - player.sizeOffset.x + MAP_OFFSET_X, player.pos.y - player.sizeOffset.y + MAP_OFFSET_Y, playerImage.hitImage, true);
	}
	else
	{
		// ��ڲ԰�̔�e�̕`��i�_�ł�����j
		if (player.damageFlag)
		{
			if (playerCounter % 2 == 0)
			{
				DrawGraph(player.pos.x - player.sizeOffset.x + MAP_OFFSET_X, player.pos.y - player.sizeOffset.y + MAP_OFFSET_Y
					, playerImage.walkImage[player.moveDir][(player.animCnt / 10 % PLAYER_ANI_MAX)], true);
			}
			else
			{
			}
		}
		else
		{
			// ���ĲҰ�ނ̕`��(�e�������Ă���:true�A�e�������Ă��Ȃ�:false)
			if (player.shotFlag)
			{
				DrawGraph(player.pos.x - player.sizeOffset.x + MAP_OFFSET_X
					, player.pos.y - player.sizeOffset.y + MAP_OFFSET_Y, playerImage.shotImage[player.moveDir], true);
			}
			else
			{
				// �ʏ펞�̕`��
				DrawGraph(player.pos.x - player.sizeOffset.x + MAP_OFFSET_X, player.pos.y - player.sizeOffset.y + MAP_OFFSET_Y
					, playerImage.walkImage[player.moveDir][player.animCnt / 10 % PLAYER_ANI_MAX], true);
			}
		}
	}
}