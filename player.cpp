#include"Dxlib.h"
#include "main.h"
#include "player.h"

Player::Player(int no, int posX, int posY, const char filename[], KEY_LIST key) : START_POS_X(posX), START_POS_Y(posY)
{
	playerNo = no;
	keyList = key;
	playerImage[DIR_MAX][PLAYER_ANI_MAX] = LoadDivGraph(filename, PLAYER_ANI_MAX * DIR_MAX, PLAYER_ANI_MAX, DIR_MAX, 35, 52.5, playerImage[0]);

	// �ϐ��̏�����
	playerPosX = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
	playerPosY = (SCREEN_SIZE_Y - PLAYER_SIZE_Y);
	playerSpeed = PLAYER_DEF_SPEED;
	playerFlag = true;
	playerCounter = 0;
	playerDir = 0;
}

//�f�X�g���N�^
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
	playerPosX = START_POS_X;
	playerPosY = START_POS_Y;
	playerSpeed = PLAYER_DEF_SPEED;
}

void Player::Control(void)
{
	// �L�[����
	// ��߰�ނ�ς���

	// player���ړ�������
	if (CheckHitKey(keyList.Right))	// �E�ړ�
	{
		if (playerPosX < SCREEN_SIZE_X - PLAYER_SIZE_X)
		{
			playerPosX = playerPosX + playerSpeed;
			playerDir = DIR_DOWN;
		}
	}
	if (CheckHitKey(keyList.Left))	// ���ړ�
	{
		if (playerPosX > 0)
		{
			playerPosX = playerPosX - playerSpeed;
			playerDir = DIR_RIGHT;
		}
	}
	if (CheckHitKey(keyList.Up))		// ��ړ�
	{
		if (playerPosY > 0)
		{
			playerPosY = playerPosY - playerSpeed;
			playerDir = DIR_LEFT;
		}
	}
	if (CheckHitKey(keyList.Down))		// ���ړ�
	{
		if (playerPosY < SCREEN_SIZE_Y - PLAYER_SIZE_Y)
		{
			playerPosY = playerPosY + playerSpeed;
			playerDir = DIR_UP;
		}
	}

	//// �e�̔���
	//if (CheckHitKey(keyList.Shot))
	//{
	//	CreateMainShot(GetPos());
	//}


	// ���@���|���ꂽ�珉���ʒu�ɍĕ\��
	if (playerFlag == false)
	{
		playerPosX = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
		playerPosY = (SCREEN_SIZE_Y - PLAYER_SIZE_Y);
		playerFlag = true;
	}
	playerCounter++;
}


XY Player::GetPos(void)
{
	return { playerPosX,playerPosY };
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
		DrawBox(playerPosX, playerPosY, playerPosX + PLAYER_SIZE_X, playerPosY + PLAYER_SIZE_Y, 0xffffff, false);
	}

	// �����̕\��
	DrawFormatString(0, 0, 0xffffff, "Speed:%d", playerSpeed);
	DrawFormatString(0, 16, GetColor(255, 255, 255), "Count:%d", playerCounter);

	DrawGraph(playerPosX, playerPosY, playerImage[playerDir][playerCounter / 5 % PLAYER_ANI_MAX], true);
}

void Player::DeletePlayer(void)
{
	playerFlag = false;
}