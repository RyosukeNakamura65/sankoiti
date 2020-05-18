#include"Dxlib.h"
#include "main.h"
#include "stage.h"
#include "player.h"
#include "shot.h"

// ｺﾝｽﾄﾗｸﾀ
Player::Player(int no, int posX, int posY, const char walkImage[], const char faceImage[]
	, const char hitImage[], const char shotImage[], KEY_LIST key) : START_POS_X(posX), START_POS_Y(posY)
{
	playerNo = no;				// 操作するﾌﾟﾚｲﾔｰﾅﾝﾊﾞｰ
	keyList = key;				// 操作キーの設定
	playerImage[DIR_MAX][PLAYER_ANI_MAX] = LoadDivGraph(walkImage, PLAYER_ANI_MAX * DIR_MAX				// 歩く画像の読み込み
		, PLAYER_ANI_MAX, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, playerImage[0]);
	playerFaceImage = LoadGraph(faceImage);				// 顔の画像読み込み
	playerHitImage = LoadGraph(hitImage);				// やられ画像の読み込み
	playerShotImage[DIR_MAX] = LoadDivGraph(shotImage, DIR_MAX, 1, DIR_MAX
		, PLAYER_SIZE_X, PLAYER_SIZE_Y, playerShotImage);				// ｼｮｯﾄ時画像の読み込み


	// 変数の初期化
	playerPos.x = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;			// ﾌﾟﾚｲﾔｰのX座標
	playerPos.y = (SCREEN_SIZE_Y - PLAYER_SIZE_Y);				// ﾌﾟﾚｲﾔｰのY座標
	playerSpeed = PLAYER_DEF_SPEED;								// ﾌﾟﾚｲﾔｰの移動ｽﾋﾟｰﾄﾞ
	playerFlag = true;											// ﾌﾟﾚｲﾔｰが生きてるならtrue、死んでいるならfalse
	playerShotFlag = false;										// ﾌﾟﾚｲﾔｰが弾を撃っているならtrue、撃っていないならfalse
	playerMoveFlag = false;										// 移動ｷｰが入力されているならtrue,されていないならfalse
	playerCounter = 10;											// ﾌﾟﾚｲﾔｰｱﾆﾒｰｼｮﾝを動かすｶｳﾝﾀｰ
	playerDir = DIR_UP;												// ﾌﾟﾚｲﾔｰの向きを記憶
}

// ﾃﾞｽﾄﾗｸﾀ
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
	// キー操作
	// ｽﾋﾟｰﾄﾞを変える

	XY playerPosCopy = playerPos;		// 座標のﾊﾞｯｸｱｯﾌﾟ
	XY playerPosOffset = playerPos;
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
				playerPos.x += playerSpeed;
				//if (IsPass(playerPosOffset))
				//{
				//	playerPos = playerPosCopy;
				//}
			}
			playerCounter++;
		}
		if (playerDir == DIR_RIGHT)	// 左移動
		{
			if (playerPos.x > 0)
			{
				playerPos.x -= playerSpeed;
			}
			playerCounter++;
		}
		if (playerDir == DIR_LEFT)		// 上移動
		{
			if (playerPos.y > 0)
			{
				playerPos.y -= playerSpeed;
			}
			playerCounter++;
		}
		if (playerDir == DIR_UP)		// 下移動
		{
			if (playerPos.y < SCREEN_SIZE_Y - PLAYER_SIZE_Y)
			{
				playerPos.y += playerSpeed;
			}
		}
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
	// ﾌﾟﾚｲﾔｰの表示
	if (playerFlag == true)
	{
		DrawBox(playerPos.x, playerPos.y, playerPos.x + PLAYER_SIZE_X, playerPos.y + PLAYER_SIZE_Y, 0xffffff, false);
	}

	// 文字の表示
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