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

	// ステージ裏の背景　〜フェードイン〜
	if (stageID != STAGE_ID_RANDOM)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
		DrawGraph(0, 0, stageSelectBG[bgID], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// ステージ画像
	DrawGraph((SCREEN_SIZE_X - STAGE_SIZE_X) / 2 - 150
		, (SCREEN_SIZE_Y - STAGE_SIZE_Y) / 2
		, stageImage[stageID], true);

	// ステージの名前
	for (int st = 0; st < STAGE_ID_MAX; st++)
	{
		if (st == stageID)
		{
			DrawFormatString(740, 250 + 50 * st, GetColor(255, 0, 0), "stage[%d]", st + 1);
		}
		else
		{
			DrawFormatString(740,250 + 50 * st, GetColor(255, 255, 255), "stage[%d]", st + 1);
		}
	}
	
}
