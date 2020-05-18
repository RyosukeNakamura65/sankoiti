#define PLAYER_SIZE_X 35
#define PLAYER_SIZE_Y 50
#define PLAYER_DEF_SPEED 3
#define PLAYER_ANI_MAX 4

class Player
{
	// private�Ƃ��ď�������Ă���
	char playerName;

	enum DIR
	{
		DIR_UP,				// ��ڲ԰�̌��p
		DIR_RIGHT,			// ��ڲ԰�̉E�p	
		DIR_DOWN,			// ��ڲ԰�̑O�p
		DIR_LEFT,			// ��ڲ԰�̍��p
		DIR_MAX
	};

private:
	const int START_POS_X;	// �v���C���[�̏����ʒuX���W
	const int START_POS_Y;	// �v���C���[�̏����ʒuY���W

	// �����o�ϐ�
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
	// �����o�֐�
	void SystemInit(void);
	void GameInit(void);
	void Control(void);
	void Draw(void);

	XY GetPos(void);
	XY GetSize(void);
	
	void DeletePlayer(void);
};