#include"Dxlib.h"
#include "main.h"
#include "player.h"
#include "shot.h"
#include "shot4.h"
#include "stage.h"
#include "KeyCheck.h"

CHARACTER player4;
XY player4PosCopy;
XY player4PosOffset;
int player4Counter;

CHAR_IMAGE player4Image;

// ｷｰの初期化
const int KeyList[DIR_MAX]
{ KEY_INPUT_DOWN, KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_UP };

void player4SystemInit(void)
{
	// 全ｷｬﾗｸﾀｰのｲﾒｰｼﾞ
	player4Image.faceImage = LoadGraph("image/yellowface.png");

	LoadDivGraph("image/yellowwalk.png", PLAYER_ANI_MAX * DIR_MAX				// 歩く画像の読み込み
		, PLAYER_ANI_MAX, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, player4Image.walkImage[0]);

	player4Image.hitImage = LoadGraph("image/yellowhit.png");

	LoadDivGraph("image/yellowshot.png", DIR_MAX, 1, DIR_MAX, PLAYER_SIZE_X, PLAYER_SIZE_Y, player4Image.shotImage);

}

void player4GameInit(void)
{
	player4.moveDir = DIR_DOWN;						//向いている方向
	player4.size = { 35, 50 };					//キャラクタ画像のサイズ
	player4.sizeOffset = { player4.size.x / 2 , player4.size.y / 2 };
	player4.startPos = { SCREEN_SIZE_X - MAP_OFFSET_X - CHIP_SIZE_X * 2 - MAP_OFFSET_X + player4.sizeOffset.x, SCREEN_SIZE_Y - CHIP_SIZE_Y * 3 - MAP_OFFSET_Y + player4.sizeOffset.y - 30 };
	player4.pos = player4.startPos;							//キャラクタの位置（中心）
	player4.shotFlag = false;						//キャラクタの状態（弾撃っているか？）
	player4.damageFlag = false;					//キャラクタの状態（ダメージ受けているか？）
	player4.gameOverFlag = false;					//キャラクタの状態（やられているか？）
	player4.moveSpeed = PLAYER_DEF_SPEED;			//キャラクタの移動量
	player4.lifeMax = PLAYER_LIFE_MAX;			//キャラクタの体力最大
	player4.life = player4.lifeMax;				//キャラクタの体力
	player4.animCnt = 10;							//キャラクタのアニメーション用カウンタ
	player4.imgLockCnt = 0;						//キャラクタのイメージ固定用カウンタ
	player4.visible = true;						//表示状態

	player4Counter = 0;
}

void player4CharSelect(void)
{
	// 各キャラの顔の描画
	DrawGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, player4Image.faceImage, true);
	// 各キャラのドット絵の描画
	DrawGraph((SCREEN_SIZE_X / 2 - FACE_SIZE_X) / 2 + SCREEN_SIZE_X / 2 + FACE_SIZE_X, SCREEN_SIZE_Y / 2 + FACE_SIZE_Y / 2
		, player4Image.walkImage[DIR_DOWN][player4Counter / 20 % PLAYER_ANI_MAX], true);

	player4Counter++;
}

void player4Control(void)
{
	// キー操作
	// ｽﾋﾟｰﾄﾞを変える

	player4PosCopy = player4.pos;		// 座標のﾊﾞｯｸｱｯﾌﾟ
	player4PosOffset = player4PosCopy;
	XY playerHitRight = player4.pos;
	XY playerHitLeft = player4.pos;
	XY playerHitDown = player4.pos;
	XY playerHitUp = player4.pos;

	player4.shotFlag = false;
	player4.moveFlag = false;

	// ﾌﾟﾚｲﾔｰの方向
	for (int dir = 0; dir < DIR_MAX; dir++)
	{
		if (CheckHitKey(KeyList[dir]) == 1)
		{
			player4.moveDir = (MOVE_DIR)dir;
			player4.moveFlag = true;
		}
	}

	// playerを移動させる
	if (player4.moveFlag == true)
	{
		if (player4.moveDir == DIR_RIGHT)	// 右移動
		{
			player4PosCopy.x += player4.moveSpeed;
			player4PosOffset.x = player4PosCopy.x + player4.sizeOffset.x - 5;
			player4PosOffset.y += 6;

			playerHitUp.x = player4PosOffset.x;
			playerHitUp.y -= player4.sizeOffset.y - 50;

			playerHitDown = player4PosOffset;
			playerHitDown.y += player4.sizeOffset.y - 20;

			if (PIsPass(player4PosOffset) && PIsPass(playerHitUp) && PIsPass(playerHitDown))
			{
				player4.pos = player4PosCopy;
			}
		}
		if (player4.moveDir == DIR_LEFT)	// 左移動
		{
			player4PosCopy.x -= player4.moveSpeed;
			player4PosOffset.x = player4PosCopy.x - player4.sizeOffset.x + 5;
			player4PosOffset.y += 6;

			playerHitUp.x = player4PosOffset.x;
			playerHitUp.y -= player4.sizeOffset.y - 50;

			playerHitDown = player4PosOffset;
			playerHitDown.y += player4.sizeOffset.y - 20;

			if (PIsPass(player4PosOffset) && PIsPass(playerHitUp) && PIsPass(playerHitDown))
			{
				player4.pos = player4PosCopy;
			}
		}
		if (player4.moveDir == DIR_UP)		// 上移動
		{
			player4PosCopy.y -= player4.moveSpeed;
			player4PosOffset.y = player4PosCopy.y - player4.sizeOffset.y + 30;

			//右の頭上にブロックがあるか
			playerHitLeft = player4PosOffset;
			playerHitLeft.x -= player4.sizeOffset.x - 5;

			//左の頭上にブロックがあるか
			playerHitRight = player4PosOffset;
			playerHitRight.x += player4.sizeOffset.x - 5;

			if (PIsPass(player4PosOffset) && PIsPass(playerHitLeft) && PIsPass(playerHitRight))
			{
				player4.pos = player4PosCopy;
			}
		}
		if (player4.moveDir == DIR_DOWN)		// 下移動
		{
			player4PosCopy.y += player4.moveSpeed;
			player4PosOffset.y = player4PosCopy.y + player4.sizeOffset.y;

			//右の足元にブロックがあるか
			playerHitLeft = player4PosOffset;
			playerHitLeft.x -= player4.sizeOffset.x - 5;

			//左の足元にブロックがあるか
			playerHitRight = player4PosOffset;
			playerHitRight.x += player4.sizeOffset.x - 5;

			if (PIsPass(player4PosOffset) && PIsPass(playerHitLeft) && PIsPass(playerHitRight))
			{
				player4.pos = player4PosCopy;
			}
		}
		player4.animCnt++;
	}
	// ﾌﾟﾚｲﾔｰのﾗｲﾌが0になった時
	if (player4.life == 0)
	{
		player4.gameOverFlag = true;
	}

	// ﾌﾟﾚｲﾔｰの被弾時
	if (player4.damageFlag)
	{
		if (player4.imgLockCnt < 50)
		{
			player4.imgLockCnt++;
		}
		else
		{
			player4.damageFlag = false;
			player4.imgLockCnt = 0;
		}
	}

	// 弾の発射
	if (keyDownTrigger[KEY_ID_D])
	{
		CreateShot4(player4.pos, player4.sizeOffset, player4.moveDir);
		player4.shotFlag = true;
	}
}

bool player4GameOver(void)
{
	if (player4.gameOverFlag)
	{
		return true;
	}
	return false;
}

//弾との当たり判定
bool Shot4CheckHit(XY sPos, int ssize)
{
	if (!player4.damageFlag)
	{
		if (player4.pos.y - player4.sizeOffset.y <= sPos.y
			&& player4.pos.y + player4.sizeOffset.y >= sPos.y
			&& player4.pos.x - player4.sizeOffset.x <= sPos.x
			&& player4.pos.x + player4.sizeOffset.x >= sPos.x)
		{
			if (player4.life > 0)
			{
				player4.life -= 1;
				player4.damageFlag = true;
				DeleteShot();
			}
			return true;
		}
	}
}

void player4Draw(void)
{
	// ﾌﾟﾚｲﾔｰの表示
	// 文字の表示

	DrawFormatString(0, 0, 0xffffff, "Speed:%d", player4.moveSpeed);
	DrawFormatString(0, 16, GetColor(255, 255, 255), "Count:%d", player4.animCnt);
	DrawFormatString(400, 0, GetColor(255, 255, 255), "4Life%d", player4.life);

	// やられの描画(ﾗｲﾌが0:true、ﾗｲﾌが1以上:false)
	if (player4.gameOverFlag)
	{
		DrawGraph(player4.pos.x - player4.sizeOffset.x + MAP_OFFSET_X, player4.pos.y - player4.sizeOffset.y + MAP_OFFSET_Y, player4Image.hitImage, true);
	}
	else
	{
		// ﾌﾟﾚｲﾔｰの被弾の描画（点滅させる）
		if (player4.damageFlag)
		{
			if (player4.animCnt % 2 == 0)
			{
				DrawGraph(player4.pos.x - player4.sizeOffset.x + MAP_OFFSET_X, player4.pos.y - player4.sizeOffset.y + MAP_OFFSET_Y
					, player4Image.walkImage[player4.moveDir][player4.animCnt / 10 % PLAYER_ANI_MAX], true);
			}
			else
			{
			}
		}
		else
		{
			// ｼｮｯﾄｲﾒｰｼﾞの描画(弾を撃っている:true、弾を撃っていない:false)
			if (player4.shotFlag)
			{
				DrawGraph(player4.pos.x - player4.sizeOffset.x + MAP_OFFSET_X
					, player4.pos.y - player4.sizeOffset.y + MAP_OFFSET_Y, player4Image.shotImage[player4.moveDir], true);
			}
			else
			{
				// 通常時の描画
				DrawGraph(player4.pos.x - player4.sizeOffset.x + MAP_OFFSET_X, player4.pos.y - player4.sizeOffset.y + MAP_OFFSET_Y
					, player4Image.walkImage[player4.moveDir][player4.animCnt / 10 % PLAYER_ANI_MAX], true);
			}
		}
	}
}