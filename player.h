#define PLAYER_SIZE_X 35
#define PLAYER_SIZE_Y 50
#define PLAYER_DEF_SPEED 3
#define PLAYER_ANI_MAX 4

	enum DIR
	{
		DIR_UP,				// ��ڲ԰�̌��p
		DIR_RIGHT,			// ��ڲ԰�̉E�p	
		DIR_DOWN,			// ��ڲ԰�̑O�p
		DIR_LEFT,			// ��ڲ԰�̍��p
		DIR_MAX
	};

	enum CHAR_FILE
	{
		CHAR_FILE_FACE,		// ��ׂ̊�ʐ^
		CHAR_FILE_WALK,		// ��ׂ̳����Ұ��
		CHAR_FILE_HIT,		// ��ׂ�˯ĲҰ��
		CHAR_FILE_SHOT,		// ��ׂ̼��ĲҰ��
		CHAR_FILE_MAX
	};

	struct CHAR_IMAGE
	{
		int faceImage;									// ��Ұ��
		int walkImage[DIR_MAX][PLAYER_ANI_MAX];			// �S�g�Ұ��
		int hitImage;									// �ړ��Ұ��
		int shotImage;
	};

	int playerNo;
	KEY_LIST keyList;

	// �������ߐ錾
	void playerSystemInit(void);
	void playerGameInit(void);
	void playerControl(void);
	void playerDraw(void);	
