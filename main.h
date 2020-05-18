// �萔
//------------------------------------------------------------------
#define SCREEN_SIZE_X 960		// ��ʃT�C�Y��
#define SCREEN_SIZE_Y 750		// ��ʃT�C�Y�c
#define START_MSG_1_CNT 120					// ����ү����1�̕\������
#define START_MSG_2_CNT 60					// ����ү����2�̕\������



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

enum STAGE_ID {
	STAGE_ID_1,
	STAGE_ID_2,
	STAGE_ID_RANDOM,
	STAGE_ID_MAX
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
