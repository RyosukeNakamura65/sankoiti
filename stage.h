//#pragma once

// �萔�̒�`
//---------------------------------------------------------------------------------
#define CHIP_SIZE_X  40
#define CHIP_SIZE_Y  40
#define MAP_X		 21
#define MAP_Y		 15
#define MAP_OFFSET_X 60
#define MAP_OFFSET_Y 130


// �񋓌^
//---------------------------------------------------------------------------------
// �}�b�v�`�b�v�Ǘ��p
enum MAP_CHIP {
	// �X�e�[�W�P�f��
	S1_ROOF,			// ����
	S1_WALL,			// ��
	S1_ROAD,			// ��
	S1_UNBREAK_WALL,	// �󂹂Ȃ���
	S1_DESERT,			// �����i���j
	S1_KUSAMITI,		// �����i���j

	MAP_CHIP_MAX
};

// �C�x���g�Ǘ��p
enum EVENT_ID {
	EVENT_ID_MAX
};


class Stage {
	// �����o�ϐ�
private:
	int chipImage[MAP_CHIP_MAX];
	int map[MAP_Y][MAP_X];
	STAGE_ID stageNo;
	
public:
	Stage(STAGE_ID no,const char filename[]);
	~Stage();

	// �����o�֐�
public:
	void SystemInit(void);
	void GameInit(void);
	void Draw(void);

	XY PosToIndex(XY pos);				// �s�N�Z�����W�n����}�b�v�z����W�n�ɕϊ�
	XY IndexToPos(XY index);			// �}�b�v�z����W�n����s�N�Z�����W�n�ɕϊ�
	bool IsPass(XY pos);				// �w�肵�����W���ʉ߉\����Ԃ��@true:�ʉ߉\
	EVENT_ID GetEvent(XY pos);			// �w�肵�����W�����ʂɃC�x���g���N���������m�F����@�߂�l�F�C�x���gID

	void SetMapData(STAGE_ID stageID);	// �X�e�[�W�f�[�^���}�b�v�z��ɃR�s�[����
};