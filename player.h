#define PLAYER_SIZE_X 35
#define PLAYER_SIZE_Y 50
#define PLAYER_DEF_SPEED 3
#define PLAYER_ANI_MAX 4

	enum DIR
	{
		DIR_UP,				// ﾌﾟﾚｲﾔｰの後ろ姿
		DIR_RIGHT,			// ﾌﾟﾚｲﾔｰの右姿	
		DIR_DOWN,			// ﾌﾟﾚｲﾔｰの前姿
		DIR_LEFT,			// ﾌﾟﾚｲﾔｰの左姿
		DIR_MAX
	};

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
		int shotImage;
	};

	int playerNo;
	KEY_LIST keyList;

	// ﾌﾟﾛﾄﾀｲﾌﾟ宣言
	void playerSystemInit(void);
	void playerGameInit(void);
	void playerControl(void);
	void playerDraw(void);	
