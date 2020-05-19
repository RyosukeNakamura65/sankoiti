// 定数
//------------------------------------------------------------------
#define SCREEN_SIZE_X 960		// 画面サイズ横
#define SCREEN_SIZE_Y 750		// 画面サイズ縦
#define START_MSG_1_CNT 120					// ｽﾀｰﾄﾒｯｾｰｼﾞ1の表示時間
#define START_MSG_2_CNT 60					// ｽﾀｰﾄﾒｯｾｰｼﾞ2の表示時間
#define START_MSG_SIZE_X 500
#define START_MSG_SIZE_Y 300
#define FACE_SIZE_X 300
#define FACE_SIZE_Y 300


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

enum SHOT {
	SHOT_1,
	SHOT_2,
	SHOT_3,
	SHOT_4,
	SHOT_MAX
};

enum STAGE_ID {
	STAGE_ID_1,
	STAGE_ID_2,
	STAGE_ID_3,
	STAGE_ID_4,
	STAGE_ID_5,
	STAGE_ID_RANDOM,
	STAGE_ID_MAX
};

enum MOVE_DIR
{
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_MAX
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

struct XY_F
{
	float x;
	float y;
};

struct CHARACTER
{
	MOVE_DIR moveDir;	//向いている方向
	XY pos;			//キャラクタの位置（中心）
	XY startPos;	//スタートの位置
	XY size;		//キャラクタ画像のサイズ
	XY sizeOffset;		//キャラクタ中央からの左上位置
	XY hitPosS;		//当たり判定用の左上
	XY hitPosE;		//当たり判定用の右下
	bool runFlag;		//キャラクタの状態（走っているか？）
	bool jumpFlag;		//キャラクタの状態（ジャンプしているか？）
	bool shotFlag;		//キャラクタの状態（弾撃っているか？）
	bool damageFlag;	//キャラクタの状態（ダメージ受けているか？）
	bool moveFlag;		//キャラクタの状態（動いているか？）
	int moveSpeed;		//キャラクタの移動量
	XY_F velocity;
	int life;		//キャラクタの体力
	int lifeMax;		//キャラクタの体力最大
	int animCnt;		//キャラクタのアニメーション用カウンタ
	int imgLockCnt;		//キャラクタのイメージ固定用カウンタ
	bool visible;		//表示状態
	int type;			//何らかの属性を格納できる。
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
