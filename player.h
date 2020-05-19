#define PLAYER_SIZE_X 35
#define PLAYER_SIZE_Y 50
#define PLAYER_FACE_SIZE_X 300
#define PLAYER_FACE_SIZE_Y 300
#define PLAYER_DEF_SPEED 3
#define PLAYER_ANI_MAX 4
#define PLAYER_LIFE_MAX 3

enum CHAR_FILE
	{
		CHAR_FILE_FACE,		// ·¬×‚ÌŠçÊ^
		CHAR_FILE_WALK,		// ·¬×‚Ì³«°¸²Ò°¼Ş
		CHAR_FILE_HIT,		// ·¬×‚ÌË¯Ä²Ò°¼Ş
		CHAR_FILE_SHOT,		// ·¬×‚Ì¼®¯Ä²Ò°¼Ş
		CHAR_FILE_MAX
	};

	struct CHAR_IMAGE
	{
		int faceImage;									// Šç²Ò°¼Ş
		int walkImage[DIR_MAX][PLAYER_ANI_MAX];			// ‘Sg²Ò°¼Ş
		int hitImage;									// ˆÚ“®²Ò°¼Ş
		int shotImage;
	};

	// ÌßÛÄÀ²ÌßéŒ¾
	void playerSystemInit(void);
	void playerGameInit(void);
	void playerCharSelect(void);
	void playerControl(void);
	void playerDraw(void);	
