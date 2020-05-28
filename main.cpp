
#include "Dxlib.h"			// Dxlib���C�u�������g�p
#include "main.h"
#include "player.h"
#include "player2.h"
#include "player3.h"
#include "player4.h"
#include "stage.h"
#include "shot.h"
#include "shot2.h"
#include "shot3.h"
#include "shot4.h"
#include "Tobitiri.h"
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
SELECT_ID selectID;
int ID;
int blend;

// �ްѵ��ް���f
bool playerGameOverFlag;
bool player2GameOverFlag;
bool player3GameOverFlag;
bool player4GameOverFlag;


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
					if (selectID == SELECT_NEXT)
					{
						sceneID = SCENE_ID_GAME;
						fadeIn = true;
						//SetDrawBright(255, 255, 255);
					}
					else if (selectID == SELECT_BACK)
					{
						sceneID = SCENE_ID_CHARASELE;
						fadeIn = true;
						//SetDrawBright(255, 255, 255);
					}
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
	playerGameOverFlag = false;
	player2GameOverFlag = false;
	player3GameOverFlag = false;
	player4GameOverFlag = false;
	sceneID = SCENE_ID_INIT;
	preSceneID = SCENE_ID_MAX;
	
	StageSystemInit();
	shotSystemInit();
	shot2SystemInit();
	shot3SystemInit();
	shot4SystemInit();
	playerSystemInit();
	player2SystemInit();
	player3SystemInit();
	player4SystemInit();
	TobiSystemInit();

	KeyInit();		// �L�[���̏�����
	EffectInit();	// �G�t�F�N�g�̏�����

	return true;
}



// �������V�[��
//--------------------------------------------------------------
void InitScene(void)
{
	fadeIn = true;
	startCounter = 0;
	
	shotGameInit();
	shot2GameInit();
	shot3GameInit();
	shot4GameInit();
	playerGameInit();
	player2GameInit();
	player3GameInit();
	player4GameInit();
	TobiGameInit();
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

		stageID = STAGE_ID_1;
		selectID = SELECT_MAIN;
		ID = 0;
		blend = 0;
	}

	CharacterSelectDraw();
}

void CharacterSelectDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "CharacterSelectScene : %d", sceneCounter);
	playerCharSelect();
	player2CharSelect();
	player3CharSelect();
	player4CharSelect();
}


// �X�e�[�W�I���V�[��
//---------------------------------------------------------------
void StageSelectScene(void)
{
	// �X�e�[�W�̕ύX
	if (selectID == SELECT_MAIN)
	{
		if (fadeOut == false)
		{
			if (keyDownTrigger[KEY_ID_DOWN])
			{
				ID++;
				blend = 0;
				if (stageID > STAGE_ID_MAX - 2)
				{
					ID = 0;
				}
			}
			if (keyDownTrigger[KEY_ID_UP])
			{
				ID--;
				blend = 0;
				if (stageID <= 0)
				{
					ID = STAGE_ID_MAX - 1;
				}
			}
			stageID = (STAGE_ID)ID;

			if (keyUpTrigger[KEY_ID_SPACE])
			{
				selectID = SELECT_NEXT;
			}
			else if (keyUpTrigger[KEY_ID_BACK])
			{
				selectID = SELECT_BACK;
				fadeOut = true;
			}
		}
	}

	// �X�e�[�W�����܂����̂ŃV�[���J��
	if (selectID == SELECT_NEXT)
	{
		// �V�[���J��
		if (keyDownTrigger[KEY_ID_SPACE])
		{
			fadeOut = true;

			StageGameInit(stageID);
		}
		else if (keyUpTrigger[KEY_ID_BACK])
		{
			selectID = SELECT_MAIN;
		}
	}

	StageSelectDraw();
	DrawFormatString(0, 50, GetColor(255, 255, 255), "stageID = %d", stageID);
	DrawFormatString(0, 70, GetColor(255, 255, 255), "selectID = %d", selectID);
}

void StageSelectDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "StageSelectScene : %d", sceneCounter);
	StageSelect(stageID,blend);
	NextBackDraw(selectID, sceneCounter);

	// �t�F�[�h�C��
	if (sceneCounter % 2 == 1)
	{
		if (blend <= 200)
		{
			blend += 3;
		}
	}
}


// �Q�[���V�[��
//----------------------------------------------------------------
void GameScene(void)
{
	// ��ʕ`��
	GameDraw();
	shotDraw();

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
			shotControl();
			shot2Control();
			shot3Control();
			shot4Control();
			if (!playerGameOver())
			{
				playerControl();
			}
			else
			{
				playerGameOverFlag = true;
			}
			if (!player2GameOver())
			{
				player2Control();
			}
			else
			{
				player2GameOverFlag = true;
			}
			if (!player3GameOver())
			{
				player3Control();
			}
			else
			{
				player3GameOverFlag = true;
			}
			if (!player4GameOver())
			{
				player4Control();
			}
			else
			{
				player4GameOverFlag = true;
			}
			TobiContlor();

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

	if (playerGameOverFlag && player2GameOverFlag && player3GameOverFlag && !player4GameOverFlag)
	{
		fadeOut = true;
	}
	if (playerGameOverFlag && player2GameOverFlag && !player3GameOverFlag && player4GameOverFlag)
	{
		fadeOut = true;
	}
	if (playerGameOverFlag && !player2GameOverFlag && player3GameOverFlag && player4GameOverFlag)
	{
		fadeOut = true;
	}
	if (!playerGameOverFlag && player2GameOverFlag && player3GameOverFlag && player4GameOverFlag)
	{
		fadeOut = true;
	}

	startCounter++;

}

void GameDraw(void)
{
	StageDraw();
	shotDraw();
	shot2Draw();
	shot3Draw();
	shot4Draw();
	playerDraw();
	player2Draw();
	player3Draw();
	player4Draw();
	TobiDraw();
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

	if (!playerGameOverFlag)
	{
		playerGameOverDraw();
	}
	if (!player2GameOverFlag)
	{
		player2GameOverDraw();
	}
	if (!player3GameOverFlag)
	{
		player3GameOverDraw();
	}
	if (!player4GameOverFlag)
	{
		player4GameOverDraw();
	}
}

void GameOverDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "GameOverScene : %d", sceneCounter);

	DrawBox(100, 100, 700, 500, GetColor(0, 0, 255), true);
}