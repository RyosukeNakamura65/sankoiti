//#pragma once

// 列挙型
//--------------------------------------------------------------
// 入力情報管理用
enum KEY_ID {
	KEY_ID_SPACE,		//	スペースキー
	KEY_ID_PAUSE,
	KEY_ID_SHOT,
	KEY_ID_UP,			// 上キー
	KEY_ID_RIGHT,		// 右キー
	KEY_ID_DOWN,		// 下キー
	KEY_ID_LEFT,		// 左キー
	KEY_ID_W,			// ｷｬﾗｸﾀｰ上
	KEY_ID_D,			// ｷｬﾗｸﾀｰ右
	KEY_ID_S,			// ｷｬﾗｸﾀｰ下
	KEY_ID_A,			// ｷｬﾗｸﾀｰ左
	KEY_ID_BACK,		// Zキー　戻る
	KEY_ID_MAX
};


// extern宣言
//--------------------------------------------------------------
extern bool keyOld[KEY_ID_MAX];				// 1フレーム前の入力状態
extern bool keyNew[KEY_ID_MAX];				// 現在の入力状態
extern bool keyDownTrigger[KEY_ID_MAX];		// キーダウン時のトリガー
extern bool keyUpTrigger[KEY_ID_MAX];		// キーアップ時のトリガー


// プロトタイプ宣言
//--------------------------------------------------------------
void KeyInit(void);			// 入力情報の初期化
void KeyCheck(void);		// 入力情報の確認
