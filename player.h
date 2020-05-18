#define PLAYER_SIZE_X 35
#define PLAYER_SIZE_Y 50
#define PLAYER_DEF_SPEED 3
#define PLAYER_ANI_MAX 4

class Player
{
	// privateとして処理されている
	char playerName;

	enum DIR
	{
		DIR_UP,				// ﾌﾟﾚｲﾔｰの後ろ姿
		DIR_RIGHT,			// ﾌﾟﾚｲﾔｰの右姿	
		DIR_DOWN,			// ﾌﾟﾚｲﾔｰの前姿
		DIR_LEFT,			// ﾌﾟﾚｲﾔｰの左姿
		DIR_MAX
	};

private:
	const int START_POS_X;	// プレイヤーの初期位置X座標
	const int START_POS_Y;	// プレイヤーの初期位置Y座標

	// メンバ変数
	int playerImage[PLAYER_ANI_MAX][DIR_MAX];
	int playerFaceImage;
	int playerHitImage;
	int playerShotImage[DIR_MAX];
	XY playerPos;
	int playerSpeed;
	int playerCounter;
	int playerDir;
	bool playerFlag;
	bool playerShotFlag;
	bool playerMoveFlag;

	int playerNo;
	KEY_LIST keyList;

public:
	//Player(int no);
	Player(int no, int posX, int posY, const char walkImage[], const char faceImage[]
		, const char hitImage[], const char shotImage[], KEY_LIST key);
	~Player();

public:
	// メンバ関数
	void SystemInit(void);
	void GameInit(void);
	void Control(void);
	void Draw(void);

	XY GetPos(void);
	XY GetSize(void);
	
	void DeletePlayer(void);
};