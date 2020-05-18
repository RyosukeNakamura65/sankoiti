
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
SCENE_ID sceneID;
SCENE_ID preSceneID;

// �X�^�[�g���b�Z�[�W
int startMsg[2];

// �^�C�g��
int titleImage;
int titleWordImage;

// �X�e�[�W
STAGE_ID stageID;
int ID;

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
	
	// �O���t�B�b�N�̓o�^
	//---------------------------------
	startMsg[0] = LoadGraph("image/start1.png");
	startMsg[1] = LoadGraph("image/start2.png");

	// �ϐ��̏�����
	//---------------------------------
	gameCounter = 0;
	sceneCounter = 0;
	startCounter = 0;
	sceneID = SCENE_ID_INIT;
	preSceneID = SCENE_ID_MAX;

	stageID = STAGE_ID_1;
	ID = 0;
	
	StageSystemInit();
	shotSystemInit();
	playerSystemInit();


	KeyInit();		// �L�[���̏�����
	EffectInit();	// �G�t�F�N�g�̏�����

	return true;
}



// �������V�[��
//--------------------------------------------------------------
void InitScene(void)
{
	fadeIn = true;
	shotGameInit();
	playerGameInit();

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

		StageGameInit(stageID);
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
	shotDraw();

	shotControl();
	playerControl();

	if (startCounter <= START_MSG_1_CNT)
	{
		DrawGraph((SCREEN_SIZE_X - START_MSG_SIZE_X) / 2
			, (SCREEN_SIZE_Y - START_MSG_SIZE_Y) / 2 + 60
			, startMsg[0], true);
		/*DrawFormatString(SCREEN_SIZE_X / 2
			, SCREEN_SIZE_Y / 2
			, GetColor(255,255,255), "��[��");*/
	}
	else
	{
		if (startCounter <= START_MSG_1_CNT + START_MSG_2_CNT)
		{
			DrawGraph((SCREEN_SIZE_X - START_MSG_SIZE_X) / 2
				, (SCREEN_SIZE_Y - START_MSG_SIZE_Y) / 2 + 65
				, startMsg[1], true);
			/*DrawFormatString(SCREEN_SIZE_X / 2
				, SCREEN_SIZE_Y / 2
				, GetColor(255, 255, 255), "�X�^�[�g");*/
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

			}
		}
	}

	startCounter++;

}

void GameDraw(void)
{
	StageDraw();
	playerDraw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "GameScene : %d", sceneCounter);
	DrawFormatString(0, 64, GetColor(255, 255, 255), "����m�F : (%d)", a);

	//DrawBox(100, 100, 700, 500, GetColor(255, 0, 0), true);
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