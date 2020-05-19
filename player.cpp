#include"Dxlib.h"
#include "main.h"
#include "player.h"
#include "shot.h"
#include "stage.h"

CHARACTER player[PLAYER_MAX];
XY playerPosOffset;
int playerCounter;

CHAR_IMAGE charImage[PLAYER_MAX];

// ｷｰの初期化
const int KeyList[DIR_MAX]
{ KEY_INPUT_DOWN, KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_UP };

void playerSystemInit(void)
{
	// ｷｬﾗの画像格納
	const char* charFileList[PLAYER_MAX][CHAR_FILE_MAX] = {
	{ "image/blueface.png", "image/bluewalk.png", "image/bluehit.png", "image/blueshot.png" },
	{ "image/pinkface.png", "image/pinkwalk.png", "image/pinkhit.png", "image/pinkshot.png"  },
	{ "image/greenface.png", "image/greenwalk.png", "image/greenhit.png", "image/greenshot.png"  },
	{ "image/yellowface.png", "image/yellowwalk.png", "image/yellowhit.png", "image/yellowshot.png"  },
	};

	// 全ｷｬﾗｸﾀｰのｲﾒｰｼﾞ
	for (int charID = 0; charID < PLAYER_MAX; charID++)
	{

		charImage[charID].faceImage = LoadGraph(charFileList[charID][CHAR_FILE_FACE]);

		LoadDivGraph(charFileList[charID][CHAR_FILE_WALK], PLAYER_ANI_MAX * DIR_MAX				// 歩く画像の読み込み
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
		player[i].moveDir = DIR_DOWN;						//向いている方向
		player[i].pos = player[i].startPos;							//キャラクタの位置（中心）
		player[i].size = { 35, 50 };					//キャラクタ画像のサイズ
		player[i].shotFlag = false;						//キャラクタの状態（弾撃っているか？）
		player[i].damageFlag = false;					//キャラクタの状態（ダメージ受けているか？）
		player[i].moveSpeed = PLAYER_DEF_SPEED;			//キャラクタの移動量
		player[i].lifeMax = PLAYER_LIFE_MAX;			//キャラクタの体力最大
		player[i].life = player[i].lifeMax;				//キャラクタの体力
		player[i].animCnt = 10;							//キャラクタのアニメーション用カウンタ
		player[i].imgLockCnt = 0;						//キャラクタのイメージ固定用カウンタ
		player[i].visible = true;						//表示状態
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
	// キー操作
	// ｽﾋﾟｰﾄﾞを変える

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		player[i].shotFlag = false;
		player[i].moveFlag = false;

		// ﾌﾟﾚｲﾔｰの方向
		for (int dir = 0; dir < DIR_MAX; dir++)
		{
			if (CheckHitKey(KeyList[dir]) == 1)
			{
				player[i].moveDir = (MOVE_DIR)dir;
				player[i].moveFlag = true;
			}
		}

		// playerを移動させる
		if (player[i].moveFlag == true)
		{
			if (player[i].moveDir == DIR_RIGHT)	// 右移動
			{
				if (player[i].pos.x < SCREEN_SIZE_X - PLAYER_SIZE_X)
				{
					player[i].pos.x += player[i].moveSpeed;
				}
			}
			if (player[i].moveDir == DIR_LEFT)	// 左移動
			{
				if (player[i].pos.x > 0)
				{
					player[i].pos.x -= player[i].moveSpeed;
				}
			}
			if (player[i].moveDir == DIR_UP)		// 上移動
			{
				if (player[i].pos.y > 0)
				{
					player[i].pos.y -= player[i].moveSpeed;
				}
			}
			if (player[i].moveDir == DIR_DOWN)		// 下移動
			{
				if (player[i].pos.y < SCREEN_SIZE_Y - PLAYER_SIZE_Y)
				{
					player[i].pos.y += player[i].moveSpeed;
				}
			}
			player[i].animCnt++;
		}

		// 弾の発射
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
		// ﾌﾟﾚｲﾔｰの表示
		if (player[i].visible == true)
		{
			DrawBox(player[i].pos.x, player[i].pos.y, player[i].pos.x + PLAYER_SIZE_X, player[i].pos.y + PLAYER_SIZE_Y, 0xffffff, false);
		}
		// 文字の表示
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