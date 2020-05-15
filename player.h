#define PLAYER_SIZE_X 35
#define PLAYER_SIZE_Y 50
#define PLAYER_DEF_SPEED 4
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
	int playerPosX;
	int playerPosY;
	int playerSpeed;
	int playerCounter;
	int playerDir;
	bool playerFlag;

	int playerNo;
	KEY_LIST keyList;

public:
	//Player(int no);
	Player(int no, int posX, int posY, const char filename[], KEY_LIST key);
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