#include "DxLib.h"
#include "main.h"
#include "stage.h"


// 変数
int chipImage[MAP_CHIP_MAX];
int stageImage[STAGE_ID_MAX];
int stageSelectBG[STAGE_BG_MAX];
int map[MAP_Y][MAP_X];
STAGE_ID stageNo;

int stage1[MAP_Y][MAP_X] = {
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0},
	{0,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,0},
	{0,4,4,5,5, 4,4,4,4,4, 5,4,4,4,5, 4,4,4,5,4,0},
	{0,4,5,4,4, 4,5,5,4,4, 4,4,4,5,4, 4,4,4,4,5,0},
	{0,4,4,4,3, 3,3,3,3,3, 3,3,3,3,3, 5,3,4,4,4,0},
	{0,4,4,4,1, 1,1,1,1,1, 1,1,1,1,1, 4,3,4,4,4,0},
	{0,4,4,5,4, 5,4,4,4,4, 4,4,5,4,4, 4,3,4,5,4,0},
	{0,5,4,5,3, 4,4,4,4,5, 4,4,4,4,5, 4,1,4,5,4,0},
	{0,4,4,4,3, 4,4,5,5,4, 4,5,4,4,4, 5,4,4,4,5,0},
	{0,4,4,4,3, 5,3,3,3,3, 3,3,3,3,3, 3,3,5,4,4,0},
	{0,4,5,4,1, 4,1,1,1,1, 1,1,1,1,1, 1,1,4,4,4,0},
	{0,4,5,4,4, 4,4,5,4,4, 4,4,4,5,4, 4,4,4,4,5,0},
	{0,5,4,4,4, 5,5,4,4,4, 4,5,4,4,4, 4,5,5,4,4,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0},
	{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,1},
};

int stage2[MAP_Y][MAP_X] = {
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0},
	{0,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,0},
	{0,4,5,4,4, 4,5,5,4,4, 4,4,4,5,4, 4,4,4,4,5,0},
	{0,4,4,3,3, 3,3,3,3,4, 5,4,3,4,4, 5,5,4,4,4,0},
	{0,4,4,3,1, 1,1,1,1,4, 4,5,3,4,5, 4,4,4,4,4,0},
	{0,4,4,3,5, 4,4,4,4,5, 4,5,3,3,3, 3,3,3,5,4,0},
	{0,5,4,1,4, 5,5,4,4,4, 4,4,1,1,1, 1,1,1,4,5,0},
	{0,4,4,5,4, 4,4,4,5,4, 5,4,5,4,4, 4,4,4,4,4,0},
	{0,4,4,3,3, 3,3,3,3,4, 4,5,4,4,5, 5,4,3,5,4,0},
	{0,4,5,1,1, 1,1,1,3,5, 4,4,4,4,4, 4,5,3,5,4,0},
	{0,4,5,4,4, 4,4,4,3,5, 4,4,3,3,3, 3,3,3,4,5,0},
	{0,5,4,4,5, 5,4,4,1,4, 4,4,1,1,1, 1,1,1,4,4,0},
	{0,4,4,4,4, 4,5,4,4,4, 5,4,4,5,5, 4,4,5,4,4,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0},
	{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,1},
};

int stage3[MAP_Y][MAP_X] = {
	{7, 7, 7, 7, 7,  7, 7, 7, 7, 7,  7, 7, 7, 7, 7,  7, 7, 7, 7, 7,7},
	{7, 8, 8, 8, 8,  8, 8, 8, 8, 8,  8, 8, 8, 8, 8,  8, 8, 8, 8, 8,7},
	{7,12,12,12,12, 12,11,11,12,12, 12,12,12,12,12, 12,12,12,12,12,7},
	{7,12,12,12, 9,  9,12,12,11,12, 12,12,12,11,11,  9, 9,12,12,12,7},
	{7,12,12, 9,10, 10,12,12,11,11, 11,11,11, 9,11, 10,10, 9,12,12,7},
	{7,12,11,10,12, 12,11,11,11,11,  9,11,12,10,11, 11,12,10,12,12,7},
	{7,12,11,11,11, 11,11,11,12, 9,  9, 9,11,11,11, 12,11,12,12,12,7},
	{7,12,12,11,11, 12,11,11,11,10,  9,10,11,11,12, 12,11,11,12,12,7},
	{7,12,12,12,11, 12,11, 9,11,11, 10,11,11,12,11, 11,11,11,12,11,7},
	{7,12,12, 9,12, 11,11,10,12,11, 11,11,11,11,11, 12,12, 9,11,12,7},
	{7,12,12,10, 9,  9,11,11,11,11, 11,11,11,12,12,  9, 9,10,11,12,7},
	{7,12,12,12,10, 10,11,11,12,12, 12,12,11,11,12, 10,10,12,12,12,7},
	{7,12,12,12,12, 12,12,12,12,12, 12,11,12,12,12, 12,12,12,12,12,7},
	{7, 7, 7, 7, 7,  7, 7, 7, 7, 7,  7, 7, 7, 7, 7,  7, 7, 7, 7, 7,7},
	{8, 8, 8, 8, 8,  8, 8, 8, 8, 8,  8, 8, 8, 8, 8,  8, 8, 8, 8, 8,8},
};

int stage4[MAP_Y][MAP_X] = {
	{7, 7, 7, 7, 7,  7, 7, 7, 7, 7,  7, 7, 7, 7, 7,  7, 7, 7, 7, 7,7},
	{7, 8, 8, 8, 8,  8, 8, 8, 8, 8,  8, 8, 8, 8, 8,  8, 8, 8, 8, 8,7},
	{7,11,11,11,11, 11,11,11,11,11, 11,12,12,12,12, 12,12,12,12,12,7},
	{7,11,11,11,11, 11,11, 9,11,12, 11,11,12, 9,12, 12,12,12,12,12,7},
	{7, 9, 9,11, 9,  9, 9, 9, 9, 9, 12, 9, 9, 9, 9,  9, 9,12, 9, 9,7},
	{7,10,10,11,10, 10,10, 9,10,10, 11,10,10, 9,10, 10,10,12,10,10,7},
	{7,12,11,11,12, 11,11,10,11,11, 11,11,11,10,11, 11,12,12,12,12,7},
	{7,12,12,11,11, 12,11,11,11,11, 11,11,11,11,11, 12,11,11,12,12,7},
	{7,12,12,12,12, 11,11, 9,11,11, 11,11,11, 9,11, 11,11,11,11,12,7},
	{7, 9, 9,12, 9,  9, 9, 9, 9, 9, 11, 9, 9, 9, 9,  9, 9,11, 9, 9,7},
	{7,10,10,12,10, 10,10, 9,10,10, 12,10,10, 9,10, 10,10,11,10,10,7},
	{7,12,12,12,12, 12,12,10,11,11, 11,12,11,10,11, 11,11,11,11,11,7},
	{7,12,12,12,12, 12,12,12,12,12, 11,11,11,11,11, 11,11,11,11,11,7},
	{7, 7, 7, 7, 7,  7, 7, 7, 7, 7,  7, 7, 7, 7, 7,  7, 7, 7, 7, 7,7},
	{8, 8, 8, 8, 8,  8, 8, 8, 8, 8,  8, 8, 8, 8, 8,  8, 8, 8, 8, 8,8},
};

int stage5[MAP_Y][MAP_X] = {
	{16,16,16,16,16, 16,16,16,16,16, 16,16,16,16,16, 16,16,16,16,16,16},
	{16,14,14,14,14, 14,14,14,14,16, 16,14,14,14,14, 19,19,14,14,14,16},
	{16,14,14,14,17, 17,17,17,14,21, 21,14,14,14,14, 14,14,14,14,14,16},
	{16,14,17,14,14, 14,14,17,14,16, 16,20,20,20,14, 14,14,14,20,20,16},
	{16,14,17,14,14, 14,14,17,14,16, 16,15,15,15,15, 15,15,18,15,15,16},
	{16,14,17,14,14, 14,14,17,14,16, 16,16,16,16,16, 16,16,18,16,16,16},
	{16,14,17,17,17, 17,14,14,14,21, 14,16,14,14,14, 14,14,14,14,14,16},
	{16,14,14,14,14, 14,14,14,14,16, 14,21,14,17,17, 17,17,14,14,14,16},
	{16,15,15,18,15, 15,15,15,15,16, 15,16,14,17,14, 14,14,14,17,14,16},
	{16,16,16,18,16, 16,16,16,16,16, 16,16,14,17,14, 14,14,14,17,14,16},
	{16,20,20,14,14, 14,14,20,20,20, 16,16,14,17,14, 14,14,14,17,14,16},
	{16,14,14,14,14, 14,14,14,14,14, 21,21,14,14,14, 17,17,17,17,14,16},
	{16,14,14,14,19, 19,14,14,14,14, 16,16,14,14,14, 14,14,14,14,14,16},
	{16,15,15,15,15, 15,15,15,15,15, 16,16,15,15,15, 15,15,15,15,15,16},
	{16,16,16,16,16, 16,16,16,16,16, 16,16,16,16,16, 16,16,16,16,16,16},
};


void StageSystemInit(void)
{
	// マップチップ画像
	LoadDivGraph("image/mapChip.png", MAP_CHIP_MAX, MAP_CHIP_MAX, 1, CHIP_SIZE_X, CHIP_SIZE_Y, chipImage);

	// ステージ選択シーン用画像
	stageImage[STAGE_ID_1] = LoadGraph("image/stage1.png");
	stageImage[STAGE_ID_2] = LoadGraph("image/stage2.png");
	stageImage[STAGE_ID_3] = LoadGraph("image/stage3.png");
	stageImage[STAGE_ID_4] = LoadGraph("image/stage4.png");
	stageImage[STAGE_ID_5] = LoadGraph("image/stage5.png");
	stageImage[STAGE_ID_RANDOM] = LoadGraph("image/stageR.png");

	// ステージ選択シーン用背景画像
	stageSelectBG[STAGE_BG_1] = LoadGraph("image/砂漠.jpg");
	stageSelectBG[STAGE_BG_2] = LoadGraph("image/遺跡.jpg");
	stageSelectBG[STAGE_BG_3] = LoadGraph("image/無人島.png");
}


void StageGameInit(STAGE_ID no)
{
	// ステージ選択（ランダム）
	if (no == STAGE_ID_RANDOM)
	{
		no = (STAGE_ID)GetRand(STAGE_ID_MAX - 2);
	}
	stageNo = no;

	SetMapData(stageNo);
}


void StageDraw(void)
{
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			DrawGraph(x * CHIP_SIZE_X + MAP_OFFSET_X
				, y * CHIP_SIZE_Y + MAP_OFFSET_Y
				, chipImage[map[y][x]]
				, true);
		}
	}
}


// ピクセル座標系からマップ配列座標系に変換
XY PosToIndex(XY pos)
{
	XY tmp;

	tmp.x = pos.x / CHIP_SIZE_X;	// posのx座標を変換
	tmp.y = pos.y / CHIP_SIZE_Y;	// posのy座標を変換

	return tmp;
}


// マップ配列座標系からピクセル座標系に変換
XY IndexToPos(XY index)
{
	XY tmp;

	tmp.x = index.x * CHIP_SIZE_X;
	tmp.y = index.y * CHIP_SIZE_Y;

	return tmp;
}


// 指定した座標が通過可能かを返す　true:通過可能
bool IsPass(XY pos)
{
	XY indexPos;
	indexPos = PosToIndex(pos);

	switch (map[indexPos.y][indexPos.x])
	{
	case S1_ROOF:
	case S1_WALL:
	case S1_UNBREAK_WALL:
	case S3_ROOF:
	case S3_WALL:
	case S3_UNBREAK_WALL:
	case S3_UNBREAK_WALL2:
	case S5_UNBREAK_OBJ:
	case S5_UNBREAK_OBJ2:
		return false;
		break;

	default:
		return true;
		break;
	}
}

// プレイヤーが指定した座標が通過可能かを返す
bool PIsPass(XY pos)
{
	XY indexPos;
	indexPos = PosToIndex(pos);

	switch (map[indexPos.y][indexPos.x])
	{
	case S1_ROOF:
	case S1_WALL:
	case S1_UNBREAK_WALL:
	case S3_ROOF:
	case S3_WALL:
	case S3_UNBREAK_WALL:
	case S3_UNBREAK_WALL2:
	case S5_WALL:
	case S5_WATER:
	case S5_WATER2:
	case S5_UNBREAK_OBJ:		
	case S5_UNBREAK_OBJ2:	
		return false;
		break;

	default:
		return true;
		break;
	}
}


// 指定した座標が特別にイベントを起こすかを確認する　戻り値：イベントID
//EVENT_ID GetEvent(XY pos)
//{
//	XY indexPos;
//	indexPos = PosToIndex(pos);
//
//	switch (map[indexPos.y][indexPos.x])
//	{
//	
//		return;
//		break;
//
//	default:
//		break;
//	}
//}


// ステージデータをマップ配列にコピーする
void SetMapData(STAGE_ID stageID)
{
	// マップ配列の初期化
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			map[y][x] = 0;
		}
	}

	// stage1
	//------------------------------------------
	if (stageID == STAGE_ID_1)
	{
		// ステージデータをマップ配列にコピー
		for (int y = 0; y < MAP_Y; y++)
		{
			for (int x = 0; x < MAP_X; x++)
			{
				// コピー
				map[y][x] = stage1[y][x];
			}
		}
	}
	// stage2
	//------------------------------------------
	if (stageID == STAGE_ID_2)
	{
		// ステージデータをマップ配列にコピー
		for (int y = 0; y < MAP_Y; y++)
		{
			for (int x = 0; x < MAP_X; x++)
			{
				// コピー
				map[y][x] = stage2[y][x];
			}
		}
	}
	// stage3
	//------------------------------------------
	if (stageID == STAGE_ID_3)
	{
		// ステージデータをマップ配列にコピー
		for (int y = 0; y < MAP_Y; y++)
		{
			for (int x = 0; x < MAP_X; x++)
			{
				// コピー
				map[y][x] = stage3[y][x];
			}
		}
	}
	// stage4
	//------------------------------------------
	if (stageID == STAGE_ID_4)
	{
		// ステージデータをマップ配列にコピー
		for (int y = 0; y < MAP_Y; y++)
		{
			for (int x = 0; x < MAP_X; x++)
			{
				// コピー
				map[y][x] = stage4[y][x];
			}
		}
	}
	// stage5
	//------------------------------------------
	if (stageID == STAGE_ID_5)
	{
		// ステージデータをマップ配列にコピー
		for (int y = 0; y < MAP_Y; y++)
		{
			for (int x = 0; x < MAP_X; x++)
			{
				// コピー
				map[y][x] = stage5[y][x];
			}
		}
	}
}


// ステージ選択シーン用描画
void StageSelect(STAGE_ID stageID,int blend)
{
	STAGE_BG bgID;
	int posX = 720;
	int posY = 280;
	int color;
	int fontHandle = CreateFontToHandle(NULL, 21, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	int fontHandleTitle = CreateFontToHandle(NULL, 90, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	// ステージIDをもとに背景画像を決める
	if (stageID == STAGE_ID_1 || stageID == STAGE_ID_2)
	{
		bgID = STAGE_BG_1;
	}
	else if (stageID == STAGE_ID_3 || stageID == STAGE_ID_4)
	{
		bgID = STAGE_BG_2;
	}
	else if (stageID == STAGE_ID_5)
	{
		bgID = STAGE_BG_3;
	}
	else if (stageID == STAGE_ID_RANDOM)
	{
		color = GetColor(150, 150, 150);
	}

	// ステージ裏の背景　〜フェードイン〜
	if (stageID == STAGE_ID_RANDOM)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
		DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, color, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
		DrawGraph(0, 0, stageSelectBG[bgID], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// 枠
	// 透過無し
	// ステージ裏
	DrawBox((SCREEN_SIZE_X - STAGE_SIZE_X) / 2 - 185
		, (SCREEN_SIZE_Y - STAGE_SIZE_Y) / 2 + 15
		, (SCREEN_SIZE_X - STAGE_SIZE_X) / 2 + 385
		, (SCREEN_SIZE_Y - STAGE_SIZE_Y) / 2 + 435
		, GetColor(0, 0, 255), false);
	// ステージ名
	DrawBox(SCREEN_SIZE_X / 2 + 210
		, (SCREEN_SIZE_Y - STAGE_SIZE_Y) / 2 + 20
		, SCREEN_SIZE_X / 2 + 410
		, (SCREEN_SIZE_Y - STAGE_SIZE_Y) / 2 + 430
		, GetColor(0, 0, 255), false);
	// ステージセレクト（タイトル）
	DrawBox(0 - 1
		, 50
		, SCREEN_SIZE_X + 1
		, 150
		, GetColor(0, 0, 0), false);

	// 透過あり
	// ステージ裏
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox((SCREEN_SIZE_X - STAGE_SIZE_X) / 2 - 185
		, (SCREEN_SIZE_Y - STAGE_SIZE_Y) / 2 + 15
		, (SCREEN_SIZE_X - STAGE_SIZE_X) / 2 + 385
		, (SCREEN_SIZE_Y - STAGE_SIZE_Y) / 2 + 435
		, GetColor(0, 0, 0), true);
	// ステージ名
	DrawBox(SCREEN_SIZE_X / 2 + 210
		, (SCREEN_SIZE_Y - STAGE_SIZE_Y) / 2 + 20
		, SCREEN_SIZE_X / 2 + 410
		, (SCREEN_SIZE_Y - STAGE_SIZE_Y) / 2 + 430
		, GetColor(0, 0, 0), true);
	// ステージセレクト（タイトル）
	DrawBox(0
		, 50
		, SCREEN_SIZE_X
		, 150
		, GetColor(0, 0, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	

	// ステージ画像
	DrawGraph((SCREEN_SIZE_X - STAGE_SIZE_X) / 2 - 150
		, (SCREEN_SIZE_Y - STAGE_SIZE_Y) / 2 + 50
		, stageImage[stageID], true);

	// ステージの名前
	for (int st = 0; st < STAGE_ID_MAX; st++)
	{
		// 選択されているかどうかで色の変更
		if (st == stageID)
		{
			// 選択されている
			color = GetColor(255, 255, 0);
		}
		else
		{
			// 選択されていない
			color = GetColor(255, 255, 255);
		}

		// ステージIDをもとにステージ名の描画
		switch (st)
		{
		case STAGE_ID_1:
			DrawFormatStringToHandle(posX, posY + 50 * st, color, fontHandle, "%d. 砂漠�T", st + 1);
			break;

		case STAGE_ID_2:
			DrawFormatStringToHandle(posX, posY + 50 * st, color, fontHandle, "%d. 砂漠�U", st + 1);
			break;

		case STAGE_ID_3:
			DrawFormatStringToHandle(posX, posY + 50 * st, color, fontHandle, "%d. 遺跡�T", st + 1);
			break;

		case STAGE_ID_4:
			DrawFormatStringToHandle(posX, posY + 50 * st, color, fontHandle, "%d. 遺跡�U", st + 1);
			break;

		case STAGE_ID_5:
			DrawFormatStringToHandle(posX, posY + 50 * st, color, fontHandle, "%d. 無人島", st + 1);
			break;

		case STAGE_ID_RANDOM:
			DrawFormatStringToHandle(posX, posY + 50 * st, color, fontHandle, "%d. ランダム", st + 1);
			break;

		default:
			break;
		}
	}

	// ステージセレクト（タイトル）
	DrawFormatStringToHandle(50, 55, GetColor(255,255,255), fontHandleTitle, "SELECT STAGE");

	DeleteFontToHandle(fontHandle);
	DeleteFontToHandle(fontHandleTitle);
}


// ステージ選択シーン用描画（NEXT,BACK）
void NextBackDraw(SELECT_ID selectID,int cnt)
{
	int color = GetColor(255,255,255);
	int fontHandle = CreateFontToHandle(NULL, 21, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	// 枠
	//透過無し
	// 準備完了 
	DrawBox(SCREEN_SIZE_X / 2 + 210
		, 670
		, SCREEN_SIZE_X / 2 + 410
		, 730
		, GetColor(0, 0, 255), false);
	// 戻る
	DrawBox((SCREEN_SIZE_X - STAGE_SIZE_X) / 2 - 185
		, 670
		, (SCREEN_SIZE_X - STAGE_SIZE_X) / 2 + 100
		, 730
		, GetColor(0, 0, 255), false);

	// 透過あり
	// 準備完了
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(SCREEN_SIZE_X / 2 + 210
		, 670
		, SCREEN_SIZE_X / 2 + 410
		, 730
		, GetColor(0, 0, 0), true);
	// 戻る
	DrawBox((SCREEN_SIZE_X - STAGE_SIZE_X) / 2 - 185
		, 670
		, (SCREEN_SIZE_X - STAGE_SIZE_X) / 2 + 100
		, 730
		, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	

	for (int sl = 0; sl < SELECT_MAX; sl++)
	{
		// 準備完了（スタート）
		if (selectID == SELECT_NEXT)
		{
			if (cnt / 40 % 2 == 1)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
				DrawBox(SCREEN_SIZE_X / 2 + 215
					, 675
					, SCREEN_SIZE_X / 2 + 405
					, 725
					, GetColor(255, 255, 0), true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
		
		// selectIDをもとに各情報の描画
		switch (sl)
		{
		case SELECT_BACK:
			if (selectID == SELECT_NEXT)
			{
				DrawFormatStringToHandle(100, 690, GetColor(255,255,255), fontHandle, "キャンセル（Z）");
			}
			else
			{
				DrawFormatStringToHandle(70, 690, GetColor(255,255,255), fontHandle, "キャラクタ選択へ（Z）");
			}
			break;

		case SELECT_MAIN:
			break;

		case SELECT_NEXT:
			if (selectID == SELECT_NEXT)
			{
				DrawFormatStringToHandle(SCREEN_SIZE_X - 255, 690, color, fontHandle, "START(スペース)");
			}
			else
			{
				DrawFormatStringToHandle(SCREEN_SIZE_X - 250, 690, color, fontHandle, "決定(スペース)");
			}
			break;
		}
	}

	DeleteFontToHandle(fontHandle);
}
