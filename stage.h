//#pragma once

// �萔�̒�`
//---------------------------------------------------------------------------------
#define CHIP_SIZE_X  40
#define CHIP_SIZE_Y  40
#define MAP_X		 21
#define MAP_Y		 15
#define MAP_OFFSET_X 60
#define MAP_OFFSET_Y 150


// �񋓌^
//---------------------------------------------------------------------------------
// �}�b�v�`�b�v�Ǘ��p
enum MAP_CHIP {
	// �X�e�[�W�P�A�Q�f��
	S1_ROOF,			// ����
	S1_WALL,			// ��
	S1_ROAD,			// ��
	S1_UNBREAK_WALL,	// �󂹂Ȃ���
	S1_DESERT,			// �����i���j
	S1_KUSAMITI,		// �������i���j

	MAP_CHIP_NON,		// �}�b�v�`�b�v����
	// �X�e�[�W�R�f��
	S3_ROOF,			// ����
	S3_WALL,			// ��
	S3_UNBREAK_WALL,	// �󂹂Ȃ���
	S3_UNBREAK_WALL2,	// �󂹂Ȃ��ǁi�e�j
	S3_TILE,			// �^�C���i���j
	S3_ROAD,			// �����i���j
	S3,ROAD2,			// �����y�Z�z�i���j

	MAP_CHIP_MAX
};

// �C�x���g�Ǘ��p
enum EVENT_ID {
	EVENT_ID_MAX
};


// �v���g�^�C�v�錾
//---------------------------------------------------------------------------------
void StageSystemInit(void);
void StageGameInit(STAGE_ID no);
void StageDraw(void);

XY PosToIndex(XY pos);				// �s�N�Z�����W�n����}�b�v�z����W�n�ɕϊ�
XY IndexToPos(XY index);			// �}�b�v�z����W�n����s�N�Z�����W�n�ɕϊ�
bool IsPass(XY pos);				// �w�肵�����W���ʉ߉\����Ԃ��@true:�ʉ߉\
EVENT_ID GetEvent(XY pos);			// �w�肵�����W�����ʂɃC�x���g���N���������m�F����@�߂�l�F�C�x���gID

void SetMapData(STAGE_ID stageID);	// �X�e�[�W�f�[�^���}�b�v�z��ɃR�s�[����