// �萔
//------------------------------------------------------------------
#define SCREEN_SIZE_X 960		// ��ʃT�C�Y��
#define SCREEN_SIZE_Y 750		// ��ʃT�C�Y�c
#define START_MSG_1_CNT 120					// ����ү����1�̕\������
#define START_MSG_2_CNT 60					// ����ү����2�̕\������
#define START_MSG_SIZE_X 500
#define START_MSG_SIZE_Y 300
#define FACE_SIZE_X 300
#define FACE_SIZE_Y 300


// �񋓌^
//------------------------------------------------------------------
// �V�[���Ǘ��p
enum SCENE_ID {
	SCENE_ID_INIT,			// �������V�[��
	SCENE_ID_TITLE,			// �^�C�g���V�[��
	SCENE_ID_CHARASELE,		// �L�����N�^�I���V�[��
	SCENE_ID_STAGESELE,		// �X�e�[�W�I���V�[��
	SCENE_ID_GAME,			// �Q�[���V�[��
	SCENE_ID_GAMEOVER,		// �Q�[���I�[�o�[�V�[��
	SCENE_ID_MAX
};

enum PLAYER {
	PLAYER_1,			// ��
	PLAYER_2,			// ��ݸ
	PLAYER_3,			// ��
	PLAYER_4,			// ���F
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

// �\����
//------------------------------------------------------------------

struct KEY_LIST {
	int Up;
	int Right;
	int Down;
	int Left;
	int Shot;
};

// �\����
struct XY
{
	// public�Ƃ��ď�������Ă���
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
	MOVE_DIR moveDir;	//�����Ă������
	XY pos;			//�L�����N�^�̈ʒu�i���S�j
	XY startPos;	//�X�^�[�g�̈ʒu
	XY size;		//�L�����N�^�摜�̃T�C�Y
	XY sizeOffset;		//�L�����N�^��������̍���ʒu
	XY hitPosS;		//�����蔻��p�̍���
	XY hitPosE;		//�����蔻��p�̉E��
	bool runFlag;		//�L�����N�^�̏�ԁi�����Ă��邩�H�j
	bool jumpFlag;		//�L�����N�^�̏�ԁi�W�����v���Ă��邩�H�j
	bool shotFlag;		//�L�����N�^�̏�ԁi�e�����Ă��邩�H�j
	bool damageFlag;	//�L�����N�^�̏�ԁi�_���[�W�󂯂Ă��邩�H�j
	bool moveFlag;		//�L�����N�^�̏�ԁi�����Ă��邩�H�j
	int moveSpeed;		//�L�����N�^�̈ړ���
	XY_F velocity;
	int life;		//�L�����N�^�̗̑�
	int lifeMax;		//�L�����N�^�̗͍̑ő�
	int animCnt;		//�L�����N�^�̃A�j���[�V�����p�J�E���^
	int imgLockCnt;		//�L�����N�^�̃C���[�W�Œ�p�J�E���^
	bool visible;		//�\�����
	int type;			//���炩�̑������i�[�ł���B
};



// �v���g�^�C�v�錾
//------------------------------------------------------------------
bool SystemInit(void);				// �V�X�e���n������

void InitScene(void);				// �������V�[���p

void TitleScene(void);				// �^�C�g���V�[���p
void TitleDraw(void);				// �^�C�g���V�[���`��

void CharacterSelectScene(void);	// �L�����N�^�I���V�[���p
void CharacterSelectDraw(void);		// �L�����N�^�I���V�[���`��

void StageSelectScene(void);		// �X�e�[�W�I���V�[���p
void StageSelectDraw(void);			// �X�e�[�W�I���V�[���`��

void GameScene(void);				// �Q�[���V�[���p
void GameDraw(void);				// �Q�[���V�[���`��

void GameOverScene(void);			// �Q�[���I�[�o�[�V�[���p
void GameOverDraw(void);			// �Q�[���I�[�o�[�V�[���`��
