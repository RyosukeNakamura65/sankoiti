#define PLAYER_SIZE_X 35
#define PLAYER_SIZE_Y 50
#define PLAYER_FACE_SIZE_X 300
#define PLAYER_FACE_SIZE_Y 300
#define PLAYER_STAND_X 300
#define PLAYER_STAND_Y 700
#define PLAYER_DEF_SPEED 3
#define PLAYER_ANI_MAX 4
#define PLAYER_LIFE_MAX 3

enum CHAR_FILE
	{
		CHAR_FILE_FACE,		// ｷｬﾗの顔写真
		CHAR_FILE_WALK,		// ｷｬﾗのｳｫｰｸｲﾒｰｼﾞ
		CHAR_FILE_HIT,		// ｷｬﾗのﾋｯﾄｲﾒｰｼﾞ
		CHAR_FILE_SHOT,		// ｷｬﾗのｼｮｯﾄｲﾒｰｼﾞ
		CHAR_FILE_MAX
	};

	struct CHAR_IMAGE
	{
		int faceImage;									// 顔ｲﾒｰｼﾞ
		int walkImage[DIR_MAX][PLAYER_ANI_MAX];			// 全身ｲﾒｰｼﾞ
		int hitImage;									// 移動ｲﾒｰｼﾞ
		int standImage;									// 立ち絵ｲﾒｰｼﾞ
		int shotImage[DIR_MAX];
	};

	// ﾌﾟﾛﾄﾀｲﾌﾟ宣言
	void playerSystemInit(void);
	void playerGameInit(void);
	void playerCharSelect(void);
	void playerControl(void);
	bool playerGameOver(void);
	void playerGameOverDraw(void);
	bool ShotCheckHit(XY sPos, int ssize);
	void playerDraw(void);	
