#include "DxLib.h"
#include "main.h"
#include "stage.h"


// �ϐ�
int chipImage[MAP_CHIP_MAX];
int map[MAP_Y][MAP_X];
STAGE_ID stageNo;

int stage1[MAP_Y][MAP_X] = {
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0},
	{0,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,0},
	{0,4,4,5,5, 4,4,4,4,4, 5,4,4,4,5, 4,4,4,5,4,0},
	{0,4,5,4,4, 4,5,5,4,4, 4,4,4,5,4, 4,4,4,4,5,0},
	{0,4,4,4,3, 3,3,3,3,3, 3,3,3,3,3, 5,3,4,4,4,0},
	{0,4,4,4,1, 1,1,1,1,1, 1,1,1,1,1, 4,3,4,4,4,0},
	{0,4,4,5,4, 5,4,4,4,4, 4,4,5,4,4, 4,3,4,5,4,0},
	{0,5,4,5,3, 4,4,4,4,5, 4,4,4,4,5, 4,1,4,5,4,0},
	{0,4,4,4,3, 4,4,5,5,4, 4,5,4,4,4, 5,4,4,4,5,0},
	{0,4,4,4,3, 5,3,3,3,3, 3,3,3,3,3, 3,3,5,4,4,0},
	{0,4,5,4,1, 4,1,1,1,1, 1,1,1,1,1, 1,1,4,4,4,0},
	{0,4,5,4,4, 4,4,5,4,4, 4,4,4,5,4, 4,4,4,4,5,0},
	{0,5,4,4,4, 5,5,4,4,4, 4,5,4,4,4, 4,5,5,4,4,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0},
	{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,1},
};

int stage2[MAP_Y][MAP_X] = {
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0},
	{0,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,0},
	{0,4,5,4,4, 4,5,5,4,4, 4,4,4,5,4, 4,4,4,4,5,0},
	{0,4,4,3,3, 3,3,3,3,4, 5,4,3,4,4, 5,5,4,4,4,0},
	{0,4,4,3,1, 1,1,1,1,4, 4,5,3,4,5, 4,4,4,4,4,0},
	{0,4,4,3,5, 4,4,4,4,5, 4,5,3,3,3, 3,3,3,5,4,0},
	{0,5,4,1,4, 5,5,4,4,4, 4,4,1,1,1, 1,1,1,4,5,0},
	{0,4,4,5,4, 4,4,4,5,4, 5,4,5,4,4, 4,4,4,4,4,0},
	{0,4,4,3,3, 3,3,3,3,4, 4,5,4,4,5, 5,4,3,5,4,0},
	{0,4,5,1,1, 1,1,1,3,5, 4,4,4,4,4, 4,5,3,5,4,0},
	{0,4,5,4,4, 4,4,4,3,5, 4,4,3,3,3, 3,3,3,4,5,0},
	{0,5,4,4,5, 5,4,4,1,4, 4,4,1,1,1, 1,1,1,4,4,0},
	{0,4,4,4,4, 4,5,4,4,4, 5,4,4,5,5, 4,4,5,4,4,0},
	{0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0},
	{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,1},
};


void StageSystemInit(void)
{
	LoadDivGraph("image/mapChip.png", 6, 6, 1, CHIP_SIZE_X, CHIP_SIZE_Y, chipImage);
}


void StageGameInit(STAGE_ID no)
{
	// �X�e�[�W�I���i�����_���j
	if (no == STAGE_ID_RANDOM)
	{
		no = (STAGE_ID)GetRand(STAGE_ID_MAX - 2);
	}
	stageNo = no;

	SetMapData(stageNo);
}


void StageDraw(void)
{
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			DrawGraph(x * CHIP_SIZE_X + MAP_OFFSET_X
				, y * CHIP_SIZE_Y + MAP_OFFSET_Y
				, chipImage[map[y][x]]
				, true);
		}
	}
}


// �s�N�Z�����W�n����}�b�v�z����W�n�ɕϊ�
XY PosToIndex(XY pos)
{
	XY tmp;

	tmp.x = pos.x / CHIP_SIZE_X;	// pos��x���W��ϊ�
	tmp.y = pos.y / CHIP_SIZE_Y;	// pos��y���W��ϊ�

	return tmp;
}


// �}�b�v�z����W�n����s�N�Z�����W�n�ɕϊ�
XY IndexToPos(XY index)
{
	XY tmp;

	tmp.x = index.x * CHIP_SIZE_X;
	tmp.y = index.y * CHIP_SIZE_Y;

	return tmp;
}


// �w�肵�����W���ʉ߉\����Ԃ��@true:�ʉ߉\
bool IsPass(XY pos)
{
	XY indexPos;
	indexPos = PosToIndex(pos);

	switch (map[indexPos.y][indexPos.x])
	{
	case S1_ROOF:
	case S1_WALL:
	case S1_UNBREAK_WALL:
		return false;
		break;

	default:
		return true;
		break;
	}
}


// �w�肵�����W�����ʂɃC�x���g���N���������m�F����@�߂�l�F�C�x���gID
//EVENT_ID GetEvent(XY pos)
//{
//	XY indexPos;
//	indexPos = PosToIndex(pos);
//
//	switch (map[indexPos.y][indexPos.x])
//	{
//		return ;
//
//	default:
//		break;
//	}
//}


// �X�e�[�W�f�[�^���}�b�v�z��ɃR�s�[����
void SetMapData(STAGE_ID stageID)
{
	// �}�b�v�z��̏�����
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			map[y][x] = 0;
		}
	}

	// stage1
	//------------------------------------------
	if (stageID == STAGE_ID_1)
	{
		// �X�e�[�W�f�[�^���}�b�v�z��ɃR�s�[
		for (int y = 0; y < MAP_Y; y++)
		{
			for (int x = 0; x < MAP_X; x++)
			{
				// �R�s�[
				map[y][x] = stage1[y][x];
			}
		}
	}
	// stage2
	//------------------------------------------
	if (stageID == STAGE_ID_2)
	{
		// �X�e�[�W�f�[�^���}�b�v�z��ɃR�s�[
		for (int y = 0; y < MAP_Y; y++)
		{
			for (int x = 0; x < MAP_X; x++)
			{
				// �R�s�[
				map[y][x] = stage2[y][x];
			}
		}
	}
}
