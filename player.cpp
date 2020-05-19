#include"Dxlib.h"
#include "main.h"
#include "player.h"
#include "shot.h"
#include "stage.h"

CHARACTER player[PLAYER_MAX];
XY playerPosOffset;
int playerCounter;

CHAR_IMAGE charImage[PLAYER_MAX];

// ���̏�����
const int KeyList[DIR_MAX]
{ KEY_INPUT_DOWN, KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_UP };

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
	player[PLAYER_1].startPos = { MAP_OFFSET_X + CHIP_SIZE_X, MAP_OFFSET_Y + CHIP_SIZE_Y * 2 };
	player[PLAYER_2].startPos = { SCREEN_SIZE_X - MAP_OFFSET_X - CHIP_SIZE_X * 2, MAP_OFFSET_Y + CHIP_SIZE_Y * 2 };
	player[PLAYER_3].startPos = { MAP_OFFSET_X + CHIP_SIZE_X, SCREEN_SIZE_Y - CHIP_SIZE_Y * 3 };
	player[PLAYER_4].startPos = { SCREEN_SIZE_X - MAP_OFFSET_X - CHIP_SIZE_X * 2, SCREEN_SIZE_Y - CHIP_SIZE_Y * 3 };

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		player[i].moveDir = DIR_DOWN;						//�����Ă������
		player[i].pos = player[i].startPos;							//�L�����N�^�̈ʒu�i���S�j
		player[i].size = { 35, 50 };					//�L�����N�^�摜�̃T�C�Y
		player[i].shotFlag = false;						//�L�����N�^�̏�ԁi�e�����Ă��邩�H�j
		player[i].damageFlag = false;					//�L�����N�^�̏�ԁi�_���[�W�󂯂Ă��邩�H�j
		player[i].moveSpeed = PLAYER_DEF_SPEED;			//�L�����N�^�̈ړ���
		player[i].lifeMax = PLAYER_LIFE_MAX;			//�L�����N�^�̗͍̑ő�
		player[i].life = player[i].lifeMax;				//�L�����N�^�̗̑�
		player[i].animCnt = 10;							//�L�����N�^�̃A�j���[�V�����p�J�E���^
		player[i].imgLockCnt = 0;						//�L�����N�^�̃C���[�W�Œ�p�J�E���^
		player[i].visible = true;						//�\�����
	}

	playerCounter = 0;
}

void playerCharSelect(void)
{
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(255, 255, 255), true);
	DrawGraph(0, 0, charImage[PLAYER_1].faceImage, true);
	DrawGraph(SCREEN_SIZE_X / 2, 0, charImage[PLAYER_2].faceImage, true);
	DrawGraph(0, SCREEN_SIZE_Y / 2, charImage[PLAYER_3].faceImage, true);
	DrawGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, charImage[PLAYER_4].faceImage, true);
	DrawGraph((SCREEN_SIZE_X / 2 - FACE_SIZE_X) / 2 + FACE_SIZE_X, FACE_SIZE_Y / 2, charImage[PLAYER_1].walkImage[DIR_DOWN][playerCounter / 20 % PLAYER_ANI_MAX], true);
	DrawGraph((SCREEN_SIZE_X / 2 - FACE_SIZE_X) / 2 + SCREEN_SIZE_X / 2 + FACE_SIZE_X, FACE_SIZE_Y / 2, charImage[PLAYER_2].walkImage[DIR_DOWN][playerCounter / 20 % PLAYER_ANI_MAX], true);
	DrawGraph((SCREEN_SIZE_X / 2 - FACE_SIZE_X) / 2 + FACE_SIZE_X, SCREEN_SIZE_Y / 2 + FACE_SIZE_Y / 2, charImage[PLAYER_3].walkImage[DIR_DOWN][playerCounter / 20 % PLAYER_ANI_MAX], true);
	DrawGraph((SCREEN_SIZE_X / 2 - FACE_SIZE_X) / 2 + SCREEN_SIZE_X / 2 + FACE_SIZE_X, SCREEN_SIZE_Y / 2 + FACE_SIZE_Y / 2, charImage[PLAYER_4].walkImage[DIR_DOWN][playerCounter / 20 % PLAYER_ANI_MAX], true);

	playerCounter++;
}

void playerControl(void)
{
	// �L�[����
	// ��߰�ނ�ς���

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		player[i].shotFlag = false;
		player[i].moveFlag = false;

		// ��ڲ԰�̕���
		for (int dir = 0; dir < DIR_MAX; dir++)
		{
			if (CheckHitKey(KeyList[dir]) == 1)
			{
				player[i].moveDir = (MOVE_DIR)dir;
				player[i].moveFlag = true;
			}
		}

		// player���ړ�������
		if (player[i].moveFlag == true)
		{
			if (player[i].moveDir == DIR_RIGHT)	// �E�ړ�
			{
				if (player[i].pos.x < SCREEN_SIZE_X - PLAYER_SIZE_X)
				{
					player[i].pos.x += player[i].moveSpeed;
				}
			}
			if (player[i].moveDir == DIR_LEFT)	// ���ړ�
			{
				if (player[i].pos.x > 0)
				{
					player[i].pos.x -= player[i].moveSpeed;
				}
			}
			if (player[i].moveDir == DIR_UP)		// ��ړ�
			{
				if (player[i].pos.y > 0)
				{
					player[i].pos.y -= player[i].moveSpeed;
				}
			}
			if (player[i].moveDir == DIR_DOWN)		// ���ړ�
			{
				if (player[i].pos.y < SCREEN_SIZE_Y - PLAYER_SIZE_Y)
				{
					player[i].pos.y += player[i].moveSpeed;
				}
			}
			player[i].animCnt++;
		}

		// �e�̔���
		//if (CheckHitKey(KEY_INPUT_CONTROL))
		//{
		//	//CreateMainShot(GetPos());
		//	playerShotFlag = true;
		//}

	}
}

void playerDraw(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		// ��ڲ԰�̕\��
		if (player[i].visible == true)
		{
			DrawBox(player[i].pos.x, player[i].pos.y, player[i].pos.x + PLAYER_SIZE_X, player[i].pos.y + PLAYER_SIZE_Y, 0xffffff, false);
		}
		// �����̕\��
		DrawFormatString(0, 0, 0xffffff, "Speed:%d", player[i].moveSpeed);
		DrawFormatString(0, 16, GetColor(255, 255, 255), "Count:%d", player[i].animCnt);
	}

	for (int charID = 0; charID < PLAYER_MAX; charID++)
	{
		if (player[charID].shotFlag)
		{
			DrawGraph(player[charID].pos.x, player[charID].pos.y, charImage[charID].shotImage, true);
		}
		else
		{
			DrawGraph(player[charID].pos.x, player[charID].pos.y
			, charImage[charID].walkImage[player[charID].moveDir][player[charID].animCnt / 10 % PLAYER_ANI_MAX], true);
		}
	}
}