#include"Dxlib.h"
#include "main.h"
#include "player.h"
#include "shot.h"
#include "shot3.h"
#include "stage.h"
#include "KeyCheck.h"

CHARACTER player3;
XY player3PosCopy;
XY player3PosOffset;
int player3Counter;
int player3Win;

CHAR_IMAGE player3Image;

// ｷｰの初期化
const int KeyList[DIR_MAX]
{ KEY_INPUT_DOWN, KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_UP };

void player3SystemInit(void)
{
	// 全ｷｬﾗｸﾀｰのｲﾒｰｼﾞ
	player3Image.faceImage = LoadGraph("image/greenface.png");

	LoadDivGraph("image/greenwalk.png", PLAYER_ANI_MAX * DIR_MAX				// 歩く画像の読み込み
		, PLAYER_ANI_MAX, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, player3Image.walkImage[0]);

	player3Image.hitImage = LoadGraph("image/greenhit.png");

	LoadDivGraph("image/greenshot.png", DIR_MAX, 1, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, player3Image.shotImage);

	player3Image.standImage = LoadGraph("image/greenup.png");

	player3Win = LoadGraph("image/player3win.png");
}

void player3GameInit(void)
{
	player3.moveDir = DIR_DOWN;						//向いている方向
	player3.size = { 35, 50 };					//キャラクタ画像のサイズ
	player3.sizeOffset = { player3.size.x / 2 , player3.size.y / 2 };
	player3.startPos = { MAP_OFFSET_X + CHIP_SIZE_X - MAP_OFFSET_X + player3.sizeOffset.x, SCREEN_SIZE_Y - CHIP_SIZE_Y * 3 - MAP_OFFSET_Y + player3.sizeOffset.y - 30 };
	player3.pos = player3.startPos;							//キャラクタの位置（中心）
	player3.shotFlag = false;						//キャラクタの状態（弾撃っているか？）
	player3.damageFlag = false;					//キャラクタの状態（ダメージ受けているか？）
	player3.gameOverFlag = false;					//キャラクタの状態（やられているか？）
	player3.moveSpeed = PLAYER_DEF_SPEED;			//キャラクタの移動量
	player3.lifeMax = PLAYER_LIFE_MAX;			//キャラクタの体力最大
	player3.life = player3.lifeMax;				//キャラクタの体力
	player3.animCnt = 10;							//キャラクタのアニメーション用カウンタ
	player3.imgLockCnt = 0;						//キャラクタのイメージ固定用カウンタ
	player3.visible = true;						//表示状態

	player3Counter = 0;
}

void player3CharSelect(void)
{
	DrawGraph(0, SCREEN_SIZE_Y / 2, player3Image.faceImage, true);
	// 各キャラのドット絵の描画
	DrawGraph((SCREEN_SIZE_X / 2 - FACE_SIZE_X) / 2 + FACE_SIZE_X, SCREEN_SIZE_Y / 2 + FACE_SIZE_Y / 2
		, player3Image.walkImage[DIR_DOWN][player3Counter / 20 % PLAYER_ANI_MAX], true);

	player3Counter++;
}

void player3Control(void)
{
	// キー操作
	// ｽﾋﾟｰﾄﾞを変える

	player3PosCopy = player3.pos;		// 座標のﾊﾞｯｸｱｯﾌﾟ
	player3PosOffset = player3PosCopy;
	XY playerHitRight = player3.pos;
	XY playerHitLeft = player3.pos;
	XY playerHitDown = player3.pos;
	XY playerHitUp = player3.pos;

	player3.shotFlag = false;
	player3.moveFlag = false;

	// ﾌﾟﾚｲﾔｰの方向
	for (int dir = 0; dir < DIR_MAX; dir++)
	{
		if (CheckHitKey(KeyList[dir]) == 1)
		{
			player3.moveDir = (MOVE_DIR)dir;
			player3.moveFlag = true;
		}
	}

	// playerを移動させる
	if (player3.moveFlag == true)
	{
		if (player3.moveDir == DIR_RIGHT)	// 右移動
		{
			player3PosCopy.x += player3.moveSpeed;
			player3PosOffset.x = player3PosCopy.x + player3.sizeOffset.x - 5;
			player3PosOffset.y += 6;

			playerHitUp.x = player3PosOffset.x;
			playerHitUp.y -= player3.sizeOffset.y - 50;

			playerHitDown = player3PosOffset;
			playerHitDown.y += player3.sizeOffset.y - 20;

			if (PIsPass(player3PosOffset) && PIsPass(playerHitUp) && PIsPass(playerHitDown))
			{
				player3.pos = player3PosCopy;
			}
		}
		if (player3.moveDir == DIR_LEFT)	// 左移動
		{
			player3PosCopy.x -= player3.moveSpeed;
			player3PosOffset.x = player3PosCopy.x - player3.sizeOffset.x + 5;
			player3PosOffset.y += 6;

			playerHitUp.x = player3PosOffset.x;
			playerHitUp.y -= player3.sizeOffset.y - 50;

			playerHitDown = player3PosOffset;
			playerHitDown.y += player3.sizeOffset.y - 20;

			if (PIsPass(player3PosOffset) && PIsPass(playerHitUp) && PIsPass(playerHitDown))
			{
				player3.pos = player3PosCopy;
			}
		}
		if (player3.moveDir == DIR_UP)		// 上移動
		{
			player3PosCopy.y -= player3.moveSpeed;
			player3PosOffset.y = player3PosCopy.y - player3.sizeOffset.y + 30;

			//右の頭上にブロックがあるか
			playerHitLeft = player3PosOffset;
			playerHitLeft.x -= player3.sizeOffset.x - 5;

			//左の頭上にブロックがあるか
			playerHitRight = player3PosOffset;
			playerHitRight.x += player3.sizeOffset.x - 5;

			if (PIsPass(player3PosOffset) && PIsPass(playerHitLeft) && PIsPass(playerHitRight))
			{
				player3.pos = player3PosCopy;
			}
		}
		if (player3.moveDir == DIR_DOWN)		// 下移動
		{
			player3PosCopy.y += player3.moveSpeed;
			player3PosOffset.y = player3PosCopy.y + player3.sizeOffset.y;

			//右の足元にブロックがあるか
			playerHitLeft = player3PosOffset;
			playerHitLeft.x -= player3.sizeOffset.x - 5;

			//左の足元にブロックがあるか
			playerHitRight = player3PosOffset;
			playerHitRight.x += player3.sizeOffset.x - 5;

			if (PIsPass(player3PosOffset) && PIsPass(playerHitLeft) && PIsPass(playerHitRight))
			{
				player3.pos = player3PosCopy;
			}
		}
		player3.animCnt++;
	}
	// ﾌﾟﾚｲﾔｰのﾗｲﾌが0になった時
	if (player3.life == 0)
	{
		player3.gameOverFlag = true;
	}

	// ﾌﾟﾚｲﾔｰの被弾時
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
	// 弾の発射
	if (keyDownTrigger[KEY_ID_S])
	{
		CreateShot3(player3.pos, player3.sizeOffset, player3.moveDir);
		player3.shotFlag = true;
	}

	player3Counter++;
}

bool player3GameOver(void)
{
	if (player3.gameOverFlag)
	{
		return true;
	}
	return false;
}

void player3GameOverDraw(void)
{
	DrawGraph(80, 250, player3Win, true);
	DrawGraph(SCREEN_SIZE_X - PLAYER_STAND_X - 50, SCREEN_SIZE_Y - PLAYER_STAND_Y, player3Image.standImage, true);
}

	//弾との当たり判定
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
				DeleteShot3();
			}
			return true;
		}
	}
}

void player3Draw(void)
{
	// ﾌﾟﾚｲﾔｰの表示
	// 文字の表示

	DrawFormatString(0, 0, 0xffffff, "Speed:%d", player3.moveSpeed);
	DrawFormatString(0, 16, GetColor(255, 255, 255), "Count:%d", player3.animCnt);
	DrawFormatString(300, 0, GetColor(255, 255, 255), "3Life%d", player3.life);

	// やられの描画(ﾗｲﾌが0:true、ﾗｲﾌが1以上:false)
	if (player3.gameOverFlag)
	{
		DrawGraph(player3.pos.x - player3.sizeOffset.x + MAP_OFFSET_X, player3.pos.y - player3.sizeOffset.y + MAP_OFFSET_Y, player3Image.hitImage, true);
	}
	else
	{
		// ﾌﾟﾚｲﾔｰの被弾の描画（点滅させる）
		if (player3.damageFlag)
		{
			if (player3Counter % 2 == 0)
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
			// ｼｮｯﾄｲﾒｰｼﾞの描画(弾を撃っている:true、弾を撃っていない:false)
			if (player3.shotFlag)
			{
				DrawGraph(player3.pos.x - player3.sizeOffset.x + MAP_OFFSET_X
					, player3.pos.y - player3.sizeOffset.y + MAP_OFFSET_Y, player3Image.shotImage[player3.moveDir], true);
			}
			else
			{
				// 通常時の描画
				DrawGraph(player3.pos.x - player3.sizeOffset.x + MAP_OFFSET_X, player3.pos.y - player3.sizeOffset.y + MAP_OFFSET_Y
					, player3Image.walkImage[player3.moveDir][player3.animCnt / 10 % PLAYER_ANI_MAX], true);
			}
		}
	}
}