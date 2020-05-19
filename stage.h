//#pragma once

// 定数の定義
//---------------------------------------------------------------------------------
#define CHIP_SIZE_X  40
#define CHIP_SIZE_Y  40
#define MAP_X		 21
#define MAP_Y		 15
#define MAP_OFFSET_X 60
#define MAP_OFFSET_Y 150


// 列挙型
//---------------------------------------------------------------------------------
// マップチップ管理用
enum MAP_CHIP {
	// ステージ１、２素材
	S1_ROOF,			// 屋根
	S1_WALL,			// 壁
	S1_ROAD,			// 道
	S1_UNBREAK_WALL,	// 壊せない壁
	S1_DESERT,			// 砂漠（床）
	S1_KUSAMITI,		// 砂漠草（床）

	MAP_CHIP_NON,		// マップチップ無し
	// ステージ３素材
	S3_ROOF,			// 屋根
	S3_WALL,			// 壁
	S3_UNBREAK_WALL,	// 壊せない壁
	S3_UNBREAK_WALL2,	// 壊せない壁（影）
	S3_TILE,			// タイル（床）
	S3_ROAD,			// 草道（床）
	S3,ROAD2,			// 草道【濃】（床）

	MAP_CHIP_MAX
};

// イベント管理用
enum EVENT_ID {
	EVENT_ID_MAX
};


// プロトタイプ宣言
//---------------------------------------------------------------------------------
void StageSystemInit(void);
void StageGameInit(STAGE_ID no);
void StageDraw(void);

XY PosToIndex(XY pos);				// ピクセル座標系からマップ配列座標系に変換
XY IndexToPos(XY index);			// マップ配列座標系からピクセル座標系に変換
bool IsPass(XY pos);				// 指定した座標が通過可能かを返す　true:通過可能
EVENT_ID GetEvent(XY pos);			// 指定した座標が特別にイベントを起こすかを確認する　戻り値：イベントID

void SetMapData(STAGE_ID stageID);	// ステージデータをマップ配列にコピーする