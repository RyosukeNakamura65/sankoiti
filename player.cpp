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
	playerPos.x = 0;
	playerPos.y = 0;
	playerSpeed = PLAYER_DEF_SPEED;
	playerPos.x = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;			// ﾌﾟﾚｲﾔｰのX座標
	playerPos.y = (SCREEN_SIZE_Y - PLAYER_SIZE_Y);				// ﾌﾟﾚｲﾔｰのY座標
	playerSpeed = PLAYER_DEF_SPEED;								// ﾌﾟﾚｲﾔｰの移動ｽﾋﾟｰﾄﾞ
	playerFlag = true;											// ﾌﾟﾚｲﾔｰが生きてるならtrue、死んでいるならfalse
	playerShotFlag = false;										// ﾌﾟﾚｲﾔｰが弾を撃っているならtrue、撃っていないならfalse
	playerMoveFlag = false;										// 移動ｷｰが入力されているならtrue,されていないならfalse
	playerCounter = 10;											// ﾌﾟﾚｲﾔｰｱﾆﾒｰｼｮﾝを動かすｶｳﾝﾀｰ
	playerDir = DIR_UP;												// ﾌﾟﾚｲﾔｰの向きを記憶

}

void playerControl(void)
{
	// キー操作
	// ｽﾋﾟｰﾄﾞを変える

	XY playerPosCopy = playerPos;		// 座標のﾊﾞｯｸｱｯﾌﾟ
	playerPosOffset = playerPosCopy;
	playerShotFlag = false;
	playerMoveFlag = false;
		// ﾌﾟﾚｲﾔｰの方向
	// playerを移動させる
	if (CheckHitKey(keyList.Right))		// 右移動の情報
	{
		playerDir = DIR_DOWN;
	}
	if (CheckHitKey(keyList.Left))		// 左移動の情報
	{
		playerDir = DIR_RIGHT;
	}
	if (CheckHitKey(keyList.Up))		// 上移動の情報
	{
		playerDir = DIR_LEFT;
	}
	if (CheckHitKey(keyList.Down))		// 下移動の情報
	{
		playerDir = DIR_UP;
	}
	if (CheckHitKey(keyList.Right) || CheckHitKey(keyList.Left) || CheckHitKey(keyList.Up) || CheckHitKey(keyList.Down))
	{
		playerMoveFlag = true;
	}

	if (playerMoveFlag == true)
	{
		if (playerDir == DIR_DOWN)	// 右移動
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
		if (playerDir == DIR_RIGHT)	// 左移動
		{
			if (playerPos.x > 0)
			{
				playerPos.x -= playerSpeed;
			}
		}
		if (playerDir == DIR_LEFT)		// 上移動
		{
			if (playerPos.y > 0)
			{
				playerPos.y -= playerSpeed;
			}
		}
		if (playerDir == DIR_UP)		// 下移動
		{
			if (playerPos.y < SCREEN_SIZE_Y - PLAYER_SIZE_Y)
			{
				playerPos.y += playerSpeed;
			}
		}
		playerCounter++;
	}

	// 弾の発射
	if (CheckHitKey(keyList.Shot))
	{
		//CreateMainShot(GetPos());
		playerShotFlag = true;
	}


	//// 自機が倒されたら初期位置に再表示
	//if (playerFlag == false)
	//{
	//	playerPosX = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
	//	playerPosY = (SCREEN_SIZE_Y - PLAYER_SIZE_Y);
	//	playerFlag = true;
	//}
}

void playerDraw(void)
{
	// ﾌﾟﾚｲﾔｰの表示
	if (playerFlag == true)
	{
		DrawBox(playerPos.x, playerPos.y, playerPos.x + PLAYER_SIZE_X, playerPos.y + PLAYER_SIZE_Y, 0xffffff, false);
	}

	// 文字の表示
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