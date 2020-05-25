//#pragma once

// �萔�̒�`
//---------------------------------------------------------------------------------
#define CHIP_SIZE_X  40
#define CHIP_SIZE_Y  40
#define MAP_X		 21
#define MAP_Y		 15
#define MAP_OFFSET_X 60
#define MAP_OFFSET_Y 150
#define STAGE_SIZE_X 500
#define STAGE_SIZE_Y 356


// �񋓌^
//---------------------------------------------------------------------------------
// �}�b�v�`�b�v�Ǘ��p
enum MAP_CHIP {
	// �X�e�[�W�P�A�Q�f��
	S1_ROOF,			// ����
	S1_WALL,			// ��
	S1_WALL_ROAD,		// �Ǔ�
	S1_UNBREAK_WALL,	// �󂹂Ȃ���
	S1_ROAD,			// �����i���j
	S1_ROAD2,			// �������i���j

	MAP_CHIP_NON,		// �}�b�v�`�b�v����

	// �X�e�[�W�R�A�S�f��
	S3_ROOF,			// ����
	S3_WALL,			// ��
	S3_UNBREAK_WALL,	// �󂹂Ȃ���
	S3_UNBREAK_WALL2,	// �󂹂Ȃ��ǁi�e�j
	S3_TILE,			// �^�C���i���j
	S3_ROAD,			// �����i���j
	S3_ROAD2,			// �����y�Z�z�i���j

	// �X�e�[�W�T�f��
	S5_ROAD,			// �����i���j
	S5_WALL,			// ��
	S5_WATER,			// ��
	S5_WATER2,			// �����܂�
	S5_ROAD2,			// ���i���j
	S5_UNBREAK_OBJ,		// �󂹂Ȃ��I�u�W�F�N�g�i��j
	S5_UNBREAK_OBJ2,	// �󂹂Ȃ��I�u�W�F�N�g�i���j
	S5_ROAD3,			// ���i���j

	MAP_CHIP_MAX
};

// �C�x���g�Ǘ��p
enum EVENT_ID {
	EVENT_ID_MAX
};

// �X�e�[�W�I��w�i�Ǘ��p
enum STAGE_BG {
	STAGE_BG_1,		// ����
	STAGE_BG_2,		// ���
	STAGE_BG_3,		// ���l��
	STAGE_BG_MAX
};


// �v���g�^�C�v�錾
//---------------------------------------------------------------------------------
void StageSystemInit(void);
void StageGameInit(STAGE_ID no);
void StageDraw(void);

XY PosToIndex(XY pos);							// �s�N�Z�����W�n����}�b�v�z����W�n�ɕϊ�
XY IndexToPos(XY index);						// �}�b�v�z����W�n����s�N�Z�����W�n�ɕϊ�
bool IsPass(XY pos);							// �w�肵�����W���ʉ߉\����Ԃ��@true:�ʉ߉\
bool PIsPass(XY pos);							// �v���C���[�݂̂��w�肵�����W���ʉ߉\����Ԃ��@true:�ʉ߉\
EVENT_ID GetEvent(XY pos);						// �w�肵�����W�����ʂɃC�x���g���N���������m�F����@�߂�l�F�C�x���gID

void SetMapData(STAGE_ID stageID);				// �X�e�[�W�f�[�^���}�b�v�z��ɃR�s�[����

void StageSelect(STAGE_ID stageID,int blend);	// �X�e�[�W�I���V�[���p�`��