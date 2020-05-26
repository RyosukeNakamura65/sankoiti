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

// ｷｰの初期化
const int KeyList[DIR_MAX]
{ KEY_INPUT_DOWN, KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_UP };

void playerSystemInit(void)
{
	// ｷｬﾗｸﾀｰの画像格納

	playerImage.faceImage = LoadGraph("image/blueface.png");				// 顔の画像読み込み

	LoadDivGraph("image/bluewalk.png", PLAYER_ANI_MAX * DIR_MAX				
		, PLAYER_ANI_MAX, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, playerImage.walkImage[0]);				// 歩行画像読み込み

	playerImage.hitImage = LoadGraph("image/bluehit.png");					// やられ画像読み込み

	LoadDivGraph("image/blueshot.png", DIR_MAX, 1, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, playerImage.shotImage);			// ｼｮｯﾄ画像読み込み

	playerImage.standImage = LoadGraph("image/buleup.png");
}

void playerGameInit(void)
{
	player.moveDir = DIR_DOWN;														//向いている方向
	player.size = { 35, 50 };														//キャラクタ画像のサイズ
	player.sizeOffset = { player.size.x / 2 , player.size.y / 2 };					// ｷｬﾗｸﾀｰのｵﾌｾｯﾄｻｲｽﾞ
	player.startPos = { MAP_OFFSET_X + CHIP_SIZE_X - MAP_OFFSET_X + player.sizeOffset.x				
		, MAP_OFFSET_Y + CHIP_SIZE_Y * 2 - MAP_OFFSET_Y + player.sizeOffset.y };				// キャラクタのスタートの位置
	player.pos = player.startPos;													//キャラクタの位置（中心）
	player.shotFlag = false;														//キャラクタの状態（弾撃っているか？）
	player.damageFlag = false;														//キャラクタの状態（ダメージ受けているか？）
	player.gameOverFlag = false;													//キャラクタの状態（やられているか？）
	player.moveSpeed = PLAYER_DEF_SPEED;											//キャラクタの移動量
	player.lifeMax = PLAYER_LIFE_MAX;												//キャラクタの体力最大
	player.life = player.lifeMax;													//キャラクタの体力
	player.animCnt = 10;															//キャラクタのアニメーション用カウンタ
	player.imgLockCnt = 0;															//キャラクタのイメージ固定用カウンタ
	player.visible = true;															//表示状態

	playerCounter = 0;																// ﾌﾟﾚｲﾔｰ選択画面でのｱﾆﾒｰｼｮﾝｶｳﾝﾄ														
}

void playerCharSelect(void)
{
	// 背景の描画
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(255, 255, 255), true);
	// 各キャラの顔の描画
	DrawGraph(0, 0, playerImage.faceImage, true);
	// 各キャラのドット絵の描画
	DrawGraph((SCREEN_SIZE_X / 2 - FACE_SIZE_X) / 2 + FACE_SIZE_X, FACE_SIZE_Y / 2
		, playerImage.walkImage[DIR_DOWN][playerCounter / 20 % PLAYER_ANI_MAX], true);

	playerCounter++;			// ｱﾆﾒｰｼｮﾝを動かす
}

void playerControl(void)
{
	// キー操作
	// ｽﾋﾟｰﾄﾞを変える

	playerPosCopy = player.pos;				// 座標のﾊﾞｯｸｱｯﾌﾟ
	playerPosOffset = playerPosCopy;			// ｵﾌｾｯﾄ分先の座標
	XY playerHitRight = player.pos;
	XY playerHitLeft = player.pos;
	XY playerHitDown = player.pos;
	XY playerHitUp = player.pos;

	player.shotFlag = false;
	player.moveFlag = false;

	// ﾌﾟﾚｲﾔｰの方向
	for (int dir = 0; dir < DIR_MAX; dir++)
	{
		if (CheckHitKey(KeyList[dir]) == 1)
		{
			player.moveDir = (MOVE_DIR)dir;
			player.moveFlag = true;
		}
	}

	playerPosOffset.y = playerPosCopy.y - player.hitPosS.y;

	// playerを移動させる
	if (player.moveFlag == true)
	{
		if (player.moveDir == DIR_RIGHT)	// 右移動
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
		if (player.moveDir == DIR_LEFT)	// 左移動
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
		if (player.moveDir == DIR_UP)		// 上移動
		{
			playerPosCopy.y -= player.moveSpeed;
			playerPosOffset.y = playerPosCopy.y - player.sizeOffset.y + 30;

			//右の頭上にブロックがあるか
			playerHitLeft = playerPosOffset;
			playerHitLeft.x -= player.sizeOffset.x - 5;

			//左の頭上にブロックがあるか
			playerHitRight = playerPosOffset;
			playerHitRight.x += player.sizeOffset.x - 5;

			if (PIsPass(playerPosOffset) && PIsPass(playerHitLeft) && PIsPass(playerHitRight))
			{
				player.pos = playerPosCopy;
			}
		}
		if (player.moveDir == DIR_DOWN)		// 下移動
		{
			playerPosCopy.y += player.moveSpeed;
			playerPosOffset.y = playerPosCopy.y + player.sizeOffset.y;

			//右の足元にブロックがあるか
			playerHitLeft = playerPosOffset;
			playerHitLeft.x -= player.sizeOffset.x - 5;

			//左の足元にブロックがあるか
			playerHitRight = playerPosOffset;
			playerHitRight.x += player.sizeOffset.x - 5;

			if (PIsPass(playerPosOffset) && PIsPass(playerHitLeft) && PIsPass(playerHitRight))
			{
				player.pos = playerPosCopy;
			}
		}
		player.animCnt++;
	}

	// ﾌﾟﾚｲﾔｰのﾗｲﾌが0になった時
	if (player.life == 0)
	{
		player.gameOverFlag = true;
	}

	// ﾌﾟﾚｲﾔｰの被弾時
	if (player.damageFlag)
	{
		if (player.imgLockCnt < 50)					// 数秒動けなくなる
		{
			player.imgLockCnt++;
		}
		else
		{
			player.damageFlag = false;				// 初期化
			player.imgLockCnt = 0;
		}
	}

	// 弾の発射時
	if (player.shotFlag)
	{
		if (player.imgLockCnt < 10)					// 数秒動けなくなる
		{
			player.imgLockCnt++;
		}
		else
		{
			player.shotFlag = false;				// 初期化
			player.imgLockCnt = 0;
		}

	}

	// 弾の発射
	if (keyDownTrigger[KEY_ID_A])
	{
		CreateShot(player.pos, player.sizeOffset, player.moveDir);				// 弾の生成
		player.shotFlag = true;
	}

	playerCounter++;			// ｱﾆﾒｰｼｮﾝを動かす
}

bool playerGameOver(void)
{
	// ﾌﾟﾚｲﾔｰのｺﾝﾄﾛｰﾙを中止
	if (player.gameOverFlag)
	{
		return true;
	}
	return false;
}

void playerGameOverDraw(void)
{
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(255, 255, 255), true);
	DrawFormatString(100, SCREEN_SIZE_Y / 2, GetColor(0, 0, 0), "プレイヤー1のしょうり！！");
	DrawGraph(SCREEN_SIZE_X - PLAYER_STAND_X, SCREEN_SIZE_Y - PLAYER_STAND_Y, playerImage.standImage, true);
}

//弾との当たり判定
bool ShotCheckHit(XY sPos, int ssize)
{
	if (!player.damageFlag)				// 弾が当たってないとき
	{
		// 弾とｷｬﾗｸﾀｰの当たり判定
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
	// ﾌﾟﾚｲﾔｰの表示
	// 文字の表示

	DrawFormatString(0, 0, 0xffffff, "Speed:%d", player.moveSpeed);
	DrawFormatString(0, 16, GetColor(255, 255, 255), "Count:%d", player.animCnt);
	DrawFormatString(100, 0, GetColor(255, 255, 255), "1Life%d", player.life);

	// やられの描画(ﾗｲﾌが0:true、ﾗｲﾌが1以上:false)
	if (player.gameOverFlag)
	{
		DrawGraph(player.pos.x - player.sizeOffset.x + MAP_OFFSET_X, player.pos.y - player.sizeOffset.y + MAP_OFFSET_Y, playerImage.hitImage, true);
	}
	else
	{
		// ﾌﾟﾚｲﾔｰの被弾の描画（点滅させる）
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
			// ｼｮｯﾄｲﾒｰｼﾞの描画(弾を撃っている:true、弾を撃っていない:false)
			if (player.shotFlag)
			{
				DrawGraph(player.pos.x - player.sizeOffset.x + MAP_OFFSET_X
					, player.pos.y - player.sizeOffset.y + MAP_OFFSET_Y, playerImage.shotImage[player.moveDir], true);
			}
			else
			{
				// 通常時の描画
				DrawGraph(player.pos.x - player.sizeOffset.x + MAP_OFFSET_X, player.pos.y - player.sizeOffset.y + MAP_OFFSET_Y
					, playerImage.walkImage[player.moveDir][player.animCnt / 10 % PLAYER_ANI_MAX], true);
			}
		}
	}
}