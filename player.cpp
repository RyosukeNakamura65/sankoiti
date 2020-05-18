#include"Dxlib.h"
#include "main.h"
#include "stage.h"
#include "player.h"
#include "shot.h"

// �ݽ�׸�
Player::Player(int no, int posX, int posY, const char walkImage[], const char faceImage[]
	, const char hitImage[], const char shotImage[], KEY_LIST key) : START_POS_X(posX), START_POS_Y(posY)
{
	playerNo = no;				// ���삷����ڲ԰���ް
	keyList = key;				// ����L�[�̐ݒ�
	playerImage[DIR_MAX][PLAYER_ANI_MAX] = LoadDivGraph(walkImage, PLAYER_ANI_MAX * DIR_MAX				// �����摜�̓ǂݍ���
		, PLAYER_ANI_MAX, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, playerImage[0]);
	playerFaceImage = LoadGraph(faceImage);				// ��̉摜�ǂݍ���
	playerHitImage = LoadGraph(hitImage);				// ����摜�̓ǂݍ���
	playerShotImage[DIR_MAX] = LoadDivGraph(shotImage, DIR_MAX, 1, DIR_MAX
		, PLAYER_SIZE_X, PLAYER_SIZE_Y, playerShotImage);				// ���Ď��摜�̓ǂݍ���


	// �ϐ��̏�����
	playerPos.x = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;			// ��ڲ԰��X���W
	playerPos.y = (SCREEN_SIZE_Y - PLAYER_SIZE_Y);				// ��ڲ԰��Y���W
	playerSpeed = PLAYER_DEF_SPEED;								// ��ڲ԰�̈ړ���߰��
	playerFlag = true;											// ��ڲ԰�������Ă�Ȃ�true�A����ł���Ȃ�false
	playerShotFlag = false;										// ��ڲ԰���e�������Ă���Ȃ�true�A�����Ă��Ȃ��Ȃ�false
	playerMoveFlag = false;										// �ړ��������͂���Ă���Ȃ�true,����Ă��Ȃ��Ȃ�false
	playerCounter = 10;											// ��ڲ԰��Ұ��݂𓮂��������
	playerDir = DIR_UP;												// ��ڲ԰�̌������L��
}

// �޽�׸�
Player::~Player()
{
	//DeleteGraph(playerImage);
}


void Player::SystemInit(void)
{
	//LoadDivGraph("image/bulewalke.png", PLAYER_ANI_MAX, PLAYER_ANI_MAX, 1, 35, 52.5, playerImage);
}

void Player::GameInit(void)
{
	playerPos.x = START_POS_X;
	playerPos.y = START_POS_Y;
	playerSpeed = PLAYER_DEF_SPEED;
}

void Player::Control(void)
{
	// �L�[����
	// ��߰�ނ�ς���

	XY playerPosCopy = playerPos;		// ���W���ޯ�����
	XY playerPosOffset = playerPos;
	playerShotFlag = false;
	playerMoveFlag = false;
		// ��ڲ԰�̕���
	// player���ړ�������
	if (CheckHitKey(keyList.Right))		// �E�ړ��̏��
	{
		playerDir = DIR_DOWN;
	}
	if (CheckHitKey(keyList.Left))		// ���ړ��̏��
	{
		playerDir = DIR_RIGHT;
	}
	if (CheckHitKey(keyList.Up))		// ��ړ��̏��
	{
		playerDir = DIR_LEFT;
	}
	if (CheckHitKey(keyList.Down))		// ���ړ��̏��
	{
		playerDir = DIR_UP;
	}
	if (CheckHitKey(keyList.Right) || CheckHitKey(keyList.Left) || CheckHitKey(keyList.Up) || CheckHitKey(keyList.Down))
	{
		playerMoveFlag = true;
	}

	if (playerMoveFlag == true)
	{
		if (playerDir == DIR_DOWN)	// �E�ړ�
		{
			if (playerPos.x < SCREEN_SIZE_X - PLAYER_SIZE_X)
			{
				playerPos.x += playerSpeed;
				//if (IsPass(playerPosOffset))
				//{
				//	playerPos = playerPosCopy;
				//}
			}
			playerCounter++;
		}
		if (playerDir == DIR_RIGHT)	// ���ړ�
		{
			if (playerPos.x > 0)
			{
				playerPos.x -= playerSpeed;
			}
			playerCounter++;
		}
		if (playerDir == DIR_LEFT)		// ��ړ�
		{
			if (playerPos.y > 0)
			{
				playerPos.y -= playerSpeed;
			}
			playerCounter++;
		}
		if (playerDir == DIR_UP)		// ���ړ�
		{
			if (playerPos.y < SCREEN_SIZE_Y - PLAYER_SIZE_Y)
			{
				playerPos.y += playerSpeed;
			}
		}
	}

	// �e�̔���
	if (CheckHitKey(keyList.Shot))
	{
		//CreateMainShot(GetPos());
		playerShotFlag = true;
	}


	//// ���@���|���ꂽ�珉���ʒu�ɍĕ\��
	//if (playerFlag == false)
	//{
	//	playerPosX = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
	//	playerPosY = (SCREEN_SIZE_Y - PLAYER_SIZE_Y);
	//	playerFlag = true;
	//}
}

XY Player::GetPos(void)
{
	return { playerPos.x,playerPos.y };
}

XY Player::GetSize(void)
{
	return { PLAYER_SIZE_X,PLAYER_SIZE_Y };
}

void Player::Draw(void)
{
	// ��ڲ԰�̕\��
	if (playerFlag == true)
	{
		DrawBox(playerPos.x, playerPos.y, playerPos.x + PLAYER_SIZE_X, playerPos.y + PLAYER_SIZE_Y, 0xffffff, false);
	}

	// �����̕\��
	DrawFormatString(0, 0, 0xffffff, "Speed:%d", playerSpeed);
	DrawFormatString(0, 16, GetColor(255, 255, 255), "Count:%d", playerCounter);

	if (playerShotFlag)
	{
		DrawGraph(playerPos.x, playerPos.y, playerShotImage[playerDir], true);
	}
	else
	{
		DrawGraph(playerPos.x, playerPos.y, playerImage[playerDir][playerCounter / 10 % PLAYER_ANI_MAX], true);
	}
}

void Player::DeletePlayer(void)
{
	playerFlag = false;
}