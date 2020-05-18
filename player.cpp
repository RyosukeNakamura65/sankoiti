#include"Dxlib.h"
#include "main.h"
#include "player.h"
#include "shot.h"
#include "stage.h"

XY playerPos;
int playerSpeed;
int playerCounter;
int playerDir;
bool playerFlag;
bool playerShotFlag;
bool playerMoveFlag;
XY playerPosOffset;

CHAR_IMAGE charImage[PLAYER_MAX];

void playerSystemInit(void)
{
	// ��ׂ̉摜�i�[
	const char* charFileList[PLAYER_MAX][CHAR_FILE_MAX] = {
	{ "image/blueface.png", "image/bluewalk.png", "image/bluehit.png", "image/blueshot.png" },
	{ "image/pinkface.png", "image/pinkwalk.png", "image/pinkhit.png", "image/pinkshot.png"  },
	{ "image/greenface.png", "image/greenwalk.png", "image/greenhit.png", "image/greenshot.png"  },
	{ "image/yellowface.png", "image/yellowwalk.png", "image/yellowhit.png", "image/yellowshot.png"  },
	};

	// �S��׸���̲Ұ��
	for (int charID = 0; charID < PLAYER_MAX; charID++)
	{

		charImage[charID].faceImage = LoadGraph(charFileList[charID][CHAR_FILE_FACE]);

		LoadDivGraph(charFileList[charID][CHAR_FILE_WALK], PLAYER_ANI_MAX * DIR_MAX				// �����摜�̓ǂݍ���
			, PLAYER_ANI_MAX, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, charImage[charID].walkImage[0]);

		charImage[charID].hitImage = LoadGraph(charFileList[charID][CHAR_FILE_HIT]);

		charImage[charID].shotImage = LoadGraph(charFileList[charID][CHAR_FILE_SHOT]);

	}
}

void playerGameInit(void)
{
	playerPos.x = 0;
	playerPos.y = 0;
	playerSpeed = PLAYER_DEF_SPEED;
	playerPos.x = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;			// ��ڲ԰��X���W
	playerPos.y = (SCREEN_SIZE_Y - PLAYER_SIZE_Y);				// ��ڲ԰��Y���W
	playerSpeed = PLAYER_DEF_SPEED;								// ��ڲ԰�̈ړ���߰��
	playerFlag = true;											// ��ڲ԰�������Ă�Ȃ�true�A����ł���Ȃ�false
	playerShotFlag = false;										// ��ڲ԰���e�������Ă���Ȃ�true�A�����Ă��Ȃ��Ȃ�false
	playerMoveFlag = false;										// �ړ��������͂���Ă���Ȃ�true,����Ă��Ȃ��Ȃ�false
	playerCounter = 10;											// ��ڲ԰��Ұ��݂𓮂��������
	playerDir = DIR_UP;												// ��ڲ԰�̌������L��

}

void playerControl(void)
{
	// �L�[����
	// ��߰�ނ�ς���

	XY playerPosCopy = playerPos;		// ���W���ޯ�����
	playerPosOffset = playerPosCopy;
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
				//playerPosCopy.x += playerSpeed;
				//playerPosOffset.x = playerPosCopy.x + PLAYER_SIZE_X / 2;
				//if (IsPass(GetPosOffset))
				//{
				//	playerPos = playerPosCopy;
				//}
			}
		}
		if (playerDir == DIR_RIGHT)	// ���ړ�
		{
			if (playerPos.x > 0)
			{
				playerPos.x -= playerSpeed;
			}
		}
		if (playerDir == DIR_LEFT)		// ��ړ�
		{
			if (playerPos.y > 0)
			{
				playerPos.y -= playerSpeed;
			}
		}
		if (playerDir == DIR_UP)		// ���ړ�
		{
			if (playerPos.y < SCREEN_SIZE_Y - PLAYER_SIZE_Y)
			{
				playerPos.y += playerSpeed;
			}
		}
		playerCounter++;
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

void playerDraw(void)
{
	// ��ڲ԰�̕\��
	if (playerFlag == true)
	{
		DrawBox(playerPos.x, playerPos.y, playerPos.x + PLAYER_SIZE_X, playerPos.y + PLAYER_SIZE_Y, 0xffffff, false);
	}

	// �����̕\��
	DrawFormatString(0, 0, 0xffffff, "Speed:%d", playerSpeed);
	DrawFormatString(0, 16, GetColor(255, 255, 255), "Count:%d", playerCounter);


	for (int charID = 0; charID < PLAYER_MAX; charID++)
	{
		if (playerShotFlag)
		{
			DrawGraph(playerPos.x, playerPos.y, charImage[charID].shotImage, true);
		}
		else
		{
			DrawGraph(playerPos.x, playerPos.y, charImage[charID].walkImage[playerDir][playerCounter / 10 % PLAYER_ANI_MAX], true);
		}
	}
}