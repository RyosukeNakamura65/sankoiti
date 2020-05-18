
#include "Dxlib.h"			// Dxlib���C�u�������g�p
#include "main.h"
#include "player.h"
#include "stage.h"
#include "shot.h"
#include "KeyCheck.h"
#include "Effect.h"


// �ϐ�
//-------------------------------------------------------------
// �V�[���Ǘ��p
int gameCounter;		// gameLoop����m�F�p
int sceneCounter;		// �V�[���J�E���^�[
int startCounter;		// �ްъJ�n�̎��Ԑݒ�
int faceImage[PLAYER_MAX];
SCENE_ID sceneID;
SCENE_ID preSceneID;

// �^�C�g��
int titleImage;
int titleWordImage;

// �X�e�[�W
STAGE_ID stageID;
int ID;

// �N���X����C���X�^���X�𐶐�����
Player* player1;
Player* player2;
Player* player3;
Player* player4;
Stage* stage;
Shot* shot1;
Shot* shot2;
Shot* shot3;
Shot* shot4;

// WinMain�֐�
//-------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// �V�X�e���̏�����
	if (!SystemInit())
	{
		return -1;
	}

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		ClsDrawScreen();

		// �V�[���J�E���^�𐧌�
		if (sceneID != preSceneID)
		{
			preSceneID = sceneID;
			sceneCounter = 0;
		}


		// ���͏��̎擾
		KeyCheck();


		// �V�[���I��
		switch (sceneID)
		{
		// �������V�[��
		case SCENE_ID_INIT:
			InitScene();
			break;

		// �^�C�g���V�[��
		case SCENE_ID_TITLE:
			// ��ʐ؂�ւ��G�t�F�N�g
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					// �G�t�F�N�g�I����̏���
				}
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// �G�t�F�N�g�I����̏���
					sceneID = SCENE_ID_CHARASELE;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);
				}
			}
			TitleScene();
			break;

			// �L�����N�^�I���V�[��
		case SCENE_ID_CHARASELE:
			// ��ʐ؂�ւ��G�t�F�N�g
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					// �G�t�F�N�g�I����̏���
				}
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// �G�t�F�N�g�I����̏���
					sceneID = SCENE_ID_STAGESELE;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);
				}
			}
			CharacterSelectScene();
			break;

			// �X�e�[�W�I���V�[��
		case SCENE_ID_STAGESELE:
			// ��ʐ؂�ւ��G�t�F�N�g
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					// �G�t�F�N�g�I����̏���
				}
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// �G�t�F�N�g�I����̏���
					sceneID = SCENE_ID_GAME;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);
				}
			}
			StageSelectScene();
			break;

		// �Q�[���V�[��
		case SCENE_ID_GAME:
			// ��ʐ؂�ւ��G�t�F�N�g
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					// �G�t�F�N�g�I����̏���
				}
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// �G�t�F�N�g�I����̏���
					sceneID = SCENE_ID_GAMEOVER;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);
				}
			}
			GameScene();
			break;

		// �Q�[���I�[�o�[�V�[��
		case SCENE_ID_GAMEOVER:
			// ��ʐ؂�ւ��G�t�F�N�g
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					// �G�t�F�N�g�I����̏���
				}
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// �G�t�F�N�g�I����̏���
					sceneID = SCENE_ID_INIT;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);
				}
			}
			GameOverScene();
			break;

		// ���̑�
		default:
			return -1;
			break;
		}


		gameCounter++;
		sceneCounter++;

		ScreenFlip();
	}

	DxLib_End();		// DX���C�u�����̏I������
	return 0;
}


//�V�X�e���n������
//--------------------------------------------------------------
bool SystemInit(void)
{
	// �V�X�e���̏�����
	SetWindowText("SanCo��");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	faceImage[PLAYER_1] = LoadGraph("image/blueface.png");
	faceImage[PLAYER_2] = LoadGraph("image/pinkface.png");
	faceImage[PLAYER_3] = LoadGraph("image/greenface.png");
	faceImage[PLAYER_4] = LoadGraph("image/yellowface.png");

	// �ݽ�ݽ�̐���
	player1 = new Player(PLAYER_1
		, MAP_OFFSET_X + CHIP_SIZE_X
		, MAP_OFFSET_Y + CHIP_SIZE_Y * 2
		, "image/bluewalk.png"
		, "image/blueface.pnh"
		, "image/bluehit.png"
		, "image/blueshot.png"
		, { KEY_INPUT_W
		,	KEY_INPUT_D
		,	KEY_INPUT_S
		,	KEY_INPUT_A
		,   KEY_INPUT_LCONTROL });
	player2 = new Player(PLAYER_2
		, SCREEN_SIZE_X - MAP_OFFSET_X - CHIP_SIZE_X * 2
		, MAP_OFFSET_Y + CHIP_SIZE_Y * 2
		, "image/pinkwalk.png"
		, "image/pinkface.pnh"
		, "image/pinkhit.png"
		, "image/pinkshot.png"
		, { KEY_INPUT_T
		,	KEY_INPUT_H
		,	KEY_INPUT_G
		,	KEY_INPUT_F
		,   KEY_INPUT_LCONTROL });
	player3 = new Player(PLAYER_3
		, MAP_OFFSET_X + CHIP_SIZE_X
		, SCREEN_SIZE_Y - CHIP_SIZE_Y * 3 - 10
		, "image/greenwalk.png"
		, "image/greenface.pnh"
		, "image/greenhit.png"
		, "image/greenshot.png"
		, { KEY_INPUT_U
		,	KEY_INPUT_K
		,	KEY_INPUT_J
		,	KEY_INPUT_H
		,   KEY_INPUT_LCONTROL });
	player4 = new Player(PLAYER_4
		, SCREEN_SIZE_X - MAP_OFFSET_X - CHIP_SIZE_X * 2
		, SCREEN_SIZE_Y - CHIP_SIZE_Y * 3 - 10
		, "image/yellowwalk.png"
		, "image/yellowface.pnh"
		, "image/yellowhit.png"
		, "image/yellowshot.png"
		, { KEY_INPUT_O
		,	KEY_INPUT_P
		,	KEY_INPUT_L
		,	KEY_INPUT_K
		,   KEY_INPUT_LCONTROL });

	shot1 = new Shot(PLAYER_1
		, 100
		, 100
		, "image/�v���C���[1�e.png");

	shot2 = new Shot(PLAYER_2
		, SCREEN_SIZE_X - 100
		, SCREEN_SIZE_Y - 650
		, "image/�v���C���[2�e.png");

	shot3 = new Shot(PLAYER_3
		, 100
		, SCREEN_SIZE_Y - 100
		, "image/�v���C���[3�e.png");

	shot4 = new Shot(PLAYER_4
		, SCREEN_SIZE_X - 100
		, SCREEN_SIZE_Y - 100
		, "image/�v���C���[4�e.png");


	// �O���t�B�b�N�̓o�^
	//---------------------------------
	
	// �ϐ��̏�����
	//---------------------------------
	gameCounter = 0;
	sceneCounter = 0;
	startCounter = 0;
	sceneID = SCENE_ID_INIT;
	preSceneID = SCENE_ID_MAX;

	stageID = STAGE_ID_1;
	ID = 0;
	
	player1->GameInit();
	player2->GameInit();
	player3->GameInit();
	player4->GameInit();

	KeyInit();		// �L�[���̏�����
	EffectInit();	// �G�t�F�N�g�̏�����

	return true;
}



// �������V�[��
//--------------------------------------------------------------
void InitScene(void)
{
	fadeIn = true;
	
	sceneID = SCENE_ID_TITLE;

}


// �^�C�g���V�[��
//---------------------------------------------------------------
void TitleScene(void)
{
	if (keyUpTrigger[KEY_ID_SPACE])
	{
		fadeOut = true;
	}

	TitleDraw();
}

void TitleDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "TitleScene : %d", sceneCounter);

	DrawBox(100, 100, 700, 500, GetColor(0, 255, 0), true);
}


// �L�����N�^�I���V�[��
//---------------------------------------------------------------
void CharacterSelectScene(void)
{
	if (keyUpTrigger[KEY_ID_SPACE])
	{
		fadeOut = true;
	}

	CharacterSelectDraw();
}

void CharacterSelectDraw(void)
{
	DrawGraph(0, 0, faceImage[PLAYER_1], true);
	DrawGraph(SCREEN_SIZE_X / 2, 0, faceImage[PLAYER_2], true);
	DrawGraph(0, SCREEN_SIZE_Y - FACE_SIZE_Y, faceImage[PLAYER_3], true);
	DrawGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y - FACE_SIZE_Y, faceImage[PLAYER_4], true);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "CharacterSelectScene : %d", sceneCounter);
}


// �X�e�[�W�I���V�[��
//---------------------------------------------------------------
void StageSelectScene(void)
{
	// �X�e�[�W�̕ύX
	if (keyDownTrigger[KEY_ID_RIGHT])
	{
		ID++;
		if (stageID > STAGE_ID_MAX - 2)
		{
			ID = 0;
		}
	}
	if (keyDownTrigger[KEY_ID_LEFT])
	{
		ID--;
		if (stageID <= 0)
		{
			ID = STAGE_ID_MAX - 1;
		}
	}
	stageID = (STAGE_ID)ID;

	// �V�[���J��
	if (keyUpTrigger[KEY_ID_SPACE])
	{
		fadeOut = true;

		// �X�e�[�W�̃C���X�^���X�̐���
		stage = new Stage(stageID
			, "image/mapChip.png");
	}

	StageSelectDraw();
	DrawFormatString(0, 50, GetColor(255, 255, 255), "stageID = %d", stageID);
}

void StageSelectDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "StageSelectScene : %d", sceneCounter);
}


// �Q�[���V�[��
//----------------------------------------------------------------
void GameScene(void)
{
	// ��ʕ`��
	GameDraw();

	if (startCounter <= START_MSG_1_CNT)
	{
		DrawFormatString(SCREEN_SIZE_X / 2
			, SCREEN_SIZE_Y / 2
			, GetColor(255,255,255), "��[��");
	}
	else
	{
		if (startCounter <= START_MSG_1_CNT + START_MSG_2_CNT)
		{

			DrawFormatString(SCREEN_SIZE_X / 2
				, SCREEN_SIZE_Y / 2
				, GetColor(255, 255, 255), "�X�^�[�g");
		}
		else
		{
			if (keyUpTrigger[KEY_ID_SPACE])
			{
				fadeOut = true;
			}

			// Pause�@�\
			if (keyDownTrigger[KEY_ID_PAUSE])
			{
				pauseFlag = !pauseFlag;
			}

			// Pause��
			if (pauseFlag)
			{
				SetDrawBright(100, 100, 100);
			}
			// �ʏ퓮�쎞
			else
			{
				// �e�폈��
				a++;
			}

			// Pause���b�Z�[�W��`��
			if (pauseFlag)
			{
				SetDrawBright(255, 255, 255);
				DrawFormatString((SCREEN_SIZE_X - 9 * 8) / 2
					, (SCREEN_SIZE_Y - 16) / 2
					, GetColor(255, 255, 255)
					, "P A U S E");
			}
			else
			{
				shot1->Control();
				shot2->Control();
				shot3->Control();
				shot4->Control();

				player1->Control();
				player2->Control();
				player3->Control();
				player4->Control();
			}
		}
	}

	startCounter++;

}

void GameDraw(void)
{
	stage->Draw();

	shot1->Draw();
	shot2->Draw();
	shot3->Draw();
	shot4->Draw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "GameScene : %d", sceneCounter);
	DrawFormatString(0, 64, GetColor(255, 255, 255), "����m�F : (%d)", a);

	//DrawBox(100, 100, 700, 500, GetColor(255, 0, 0), true);
	player1->Draw();
	player2->Draw();
	player3->Draw();
	player4->Draw();
}


// �Q�[���I�[�o�[�V�[��
//-----------------------------------------------------------------
void GameOverScene(void)
{
	if (keyUpTrigger[KEY_ID_SPACE])
	{
		fadeOut = true;
	}

	GameOverDraw();
}

void GameOverDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "GameOverScene : %d", sceneCounter);

	DrawBox(100, 100, 700, 500, GetColor(0, 0, 255), true);
}