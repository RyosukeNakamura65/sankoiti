#include "DxLib.h"
#include "main.h"
#include "stage.h"


// �ϐ�
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


// �R���X�g���N�^
Stage::Stage(STAGE_ID no, const char filename[])
{
	stageNo = no;
	LoadDivGraph(filename, 6, 6, 1, CHIP_SIZE_X, CHIP_SIZE_Y,chipImage);

	SetMapData(no);
}

// �f�X�g���N�^
Stage::~Stage()
{
	
}


void Stage::SystemInit(void)
{

}


void Stage::GameInit(void)
{

}


void Stage::Draw(void)
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
XY Stage::PosToIndex(XY pos)
{
	XY tmp;

	tmp.x = pos.x / CHIP_SIZE_X;	// pos��x���W��ϊ�
	tmp.y = pos.y / CHIP_SIZE_Y;	// pos��y���W��ϊ�

	return tmp;
}


// �}�b�v�z����W�n����s�N�Z�����W�n�ɕϊ�
XY Stage::IndexToPos(XY index)
{
	XY tmp;

	tmp.x = index.x * CHIP_SIZE_X;
	tmp.y = index.y * CHIP_SIZE_Y;

	return tmp;
}


// �w�肵�����W���ʉ߉\����Ԃ��@true:�ʉ߉\
bool Stage::IsPass(XY pos)
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
//EVENT_ID Stage::GetEvent(XY pos)
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
void Stage::SetMapData(STAGE_ID stageID)
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
		//stageID = STAGE_ID_1;
	}
}
