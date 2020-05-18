// 定数
//------------------------------------------------------------------
#define SCREEN_SIZE_X 960		// 画面サイズ横
#define SCREEN_SIZE_Y 750		// 画面サイズ縦
#define START_MSG_1_CNT 120					// ｽﾀｰﾄﾒｯｾｰｼﾞ1の表示時間
#define START_MSG_2_CNT 60					// ｽﾀｰﾄﾒｯｾｰｼﾞ2の表示時間



// 列挙型
//------------------------------------------------------------------
// シーン管理用
enum SCENE_ID {
	SCENE_ID_INIT,			// 初期化シーン
	SCENE_ID_TITLE,			// タイトルシーン
	SCENE_ID_CHARASELE,		// キャラクタ選択シーン
	SCENE_ID_STAGESELE,		// ステージ選択シーン
	SCENE_ID_GAME,			// ゲームシーン
	SCENE_ID_GAMEOVER,		// ゲームオーバーシーン
	SCENE_ID_MAX
};

enum PLAYER {
	PLAYER_1,			// 青
	PLAYER_2,			// ﾋﾟﾝｸ
	PLAYER_3,			// 緑
	PLAYER_4,			// 黄色
	PLAYER_MAX
};

enum STAGE_ID {
	STAGE_ID_1,
	STAGE_ID_2,
	STAGE_ID_RANDOM,
	STAGE_ID_MAX
};

// 構造体
//------------------------------------------------------------------

struct KEY_LIST {
	int Up;
	int Right;
	int Down;
	int Left;
	int Shot;
};

// 構造体
struct XY
{
	// publicとして処理されている
	int x;
	int y;
};


// プロトタイプ宣言
//------------------------------------------------------------------
bool SystemInit(void);				// システム系初期化

void InitScene(void);				// 初期化シーン用

void TitleScene(void);				// タイトルシーン用
void TitleDraw(void);				// タイトルシーン描画

void CharacterSelectScene(void);	// キャラクタ選択シーン用
void CharacterSelectDraw(void);		// キャラクタ選択シーン描画

void StageSelectScene(void);		// ステージ選択シーン用
void StageSelectDraw(void);			// ステージ選択シーン描画

void GameScene(void);				// ゲームシーン用
void GameDraw(void);				// ゲームシーン描画

void GameOverScene(void);			// ゲームオーバーシーン用
void GameOverDraw(void);			// ゲームオーバーシーン描画
