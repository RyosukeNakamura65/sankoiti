#include "DxLib.h"
#include "main.h"
#include "stage.h"


// 変数
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


// コンストラクタ
Stage::Stage(STAGE_ID no, const char filename[])
{
	stageNo = no;
	LoadDivGraph(filename, 6, 6, 1, CHIP_SIZE_X, CHIP_SIZE_Y,chipImage);

	SetMapData(no);
}

// デストラクタ
Stage::~Stage()
{
	
}


void Stage::SystemInit(void)
{

}


void Stage::GameInit(void)
{

}


void Stage::Draw(void)
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
XY Stage::PosToIndex(XY pos)
{
	XY tmp;

	tmp.x = pos.x / CHIP_SIZE_X;	// posのx座標を変換
	tmp.y = pos.y / CHIP_SIZE_Y;	// posのy座標を変換

	return tmp;
}


// マップ配列座標系からピクセル座標系に変換
XY Stage::IndexToPos(XY index)
{
	XY tmp;

	tmp.x = index.x * CHIP_SIZE_X;
	tmp.y = index.y * CHIP_SIZE_Y;

	return tmp;
}


// 指定した座標が通過可能かを返す　true:通過可能
bool Stage::IsPass(XY pos)
{
	XY indexPos;
	indexPos = PosToIndex(pos);

	switch (map[indexPos.y][indexPos.x])
	{
	case S1_ROOF:
	case S1_WALL:
	case S1_UNBREAK_WALL:
		return false;
		break;

	default:
		return true;
		break;
	}
}


// 指定した座標が特別にイベントを起こすかを確認する　戻り値：イベントID
//EVENT_ID Stage::GetEvent(XY pos)
//{
//	XY indexPos;
//	indexPos = PosToIndex(pos);
//
//	switch (map[indexPos.y][indexPos.x])
//	{
//		return ;
//
//	default:
//		break;
//	}
//}


// ステージデータをマップ配列にコピーする
void Stage::SetMapData(STAGE_ID stageID)
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
		//stageID = STAGE_ID_1;
	}
}
