//#pragma once

// 定数の定義
//---------------------------------------------------------------------------------
#define CHIP_SIZE_X 40
#define CHIP_SIZE_Y 40
#define MAP_X		19
#define MAP_Y		15
#define CHIP_MAX	6


// 列挙型
//---------------------------------------------------------------------------------
enum EVENT_ID {

};


class Stage {
	// メンバ変数
private:
	int chipImage[CHIP_MAX];
	int map[MAP_Y][MAP_X];
	STAGE_ID stageNo;
	
public:
	Stage(STAGE_ID no,const char filename[]);
	~Stage();

	// メンバ関数
public:
	void SystemInit(void);
	void GameInit(void);
	void Draw(void);

	XY PosToIndex(XY pos);				// ピクセル座標系からマップ配列座標系に変換
	XY IndexToPos(XY index);			// マップ配列座標系からピクセル座標系に変換
	bool IsPass(XY pos);				// 指定した座標が通過可能かを返す　true:通過可能
	EVENT_ID GetEvent(XY pos);			// 指定した座標が特別にイベントを起こすかを確認する　戻り値：イベントID

	void SetMapData(STAGE_ID stageID);	// ステージデータをマップ配列にコピーする
};