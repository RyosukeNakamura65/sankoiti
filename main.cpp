//�@�t�@�C������p�ۑ�
//�@2019.09.09
//�@���������

#include "DxLib.h"
#include "main.h"
#include "KeyCheck1.h"
#include "effect.h"
//�ϐ��̒�`
//�V�X�e���֘A
int SceneCounter;
bool pauseFlag;		
//
SCENE_ID sceneID;
SCENE_ID preSceneID;				//�ЂƂO�̃V�[��ID
//���͏��Ǘ��p

//int TitleCouter;
//int gameCounter;		//���[�v�̓���m�F�p
//int GameOverCounter;



//�C���[�W�֘A
int TitleImage;
int gameoverImage;
int hitstartkeyImage;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//�V�X�e��������
	if (SystemInit())
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	//����������
	//if (!SystemInit())
	//{
	//	AST();
	//	return -1;
	//}

	//�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		ClsDrawScreen();

		if (sceneID != preSceneID)
		{
			SceneCounter = 0;
			preSceneID = sceneID;
		}

		KeyCheck();  //�L�[���̊m�F

		switch (sceneID)
		{
			//�Q�[���̑O�̏�����
		case SCENE_ID_INIT:
			InitScene();
			sceneID = SCENE_ID_TITLE;
			break;
			//�^�C�g��
		case SCENE_ID_TITLE:
			TitleScene();
			//fadeScene();
			/*if (bright < 1)
			{
				sceneID = SCENE_ID_GAME;
			}*/
			
			/*if (CheckHitKey(KEY_INPUT_SPACE))
			{
				bright -= 1;
			}
			if (bright != 255)
			{
				bright -= 1;
				if (bright < 0)bright = 0;
				SetDrawBright(bright, bright, bright);
			}
			if (bright < 1)
			{
				sceneID = SCENE_ID_GAME;
			}*/
			break;
			//	//�Z���N�g
			//case SCENE_ID_SELECT:
			//	SelectScene();
			//	/*sceneID = SCENE_ID_GAME;*/
			//	break;

				//�Q�[��
		case SCENE_ID_GAME:
			GameScene();
			fadeScene();
			if (bright < 1)
			{
				sceneID = SCENE_ID_GAMEOVER;
			}
			break;
			/*sceneID = SCENE_ID_GAME;*/
			//�N���A
		case SCENE_ID_GAMEOVER:
			GameOverScene();
			fadeScene();
			if (bright < 1)
			{
				sceneID = SCENE_ID_INIT;
			}
			break;


		default:
			break;
		}
		//�Q�[����Ҳݏ���
		//TitleCouter++;
		 SceneCounter++;
		//GameOverCounter++;
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}

bool SystemInit(void)
{
	//�V�X�e���̏�����
	SetWindowText("1916031_��������");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	SetDrawScreen(DX_SCREEN_BACK);
	if (DxLib_Init() == -1)				//DXײ���؏���������
	{
		return false;
	}
	int retFlag;
	//���̨���̓o�^
	//TitelImage = DrawGraph()
	TitleImage = LoadGraph("image/title.png");

		//�ϐ��̏�����
		sceneID = SCENE_ID_INIT;
		preSceneID = SCENE_ID_MAX;
		SceneCounter = 0;
		pauseFlag = true;
		//FDFlag = true;
		KeyInit();
		EffectInit();
		/*gameCounter = 0;
		TitleCouter = 0;
		GameOverCounter = 0;*/
		return false;
}

//
void InitScene(void)
{

}

//�^�C�g���̃��[�v
void TitleScene(void)
{
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		FDFlag = true;
	}
	TitleSceneDraw();
}
//�^�C�g���̕`��
void TitleSceneDraw(void)
{
	
	DrawBox(100
		, 100
		, 700
		, 500
		, 0x00FF00, true);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "SceneCounter = %d", SceneCounter);
	DrawGraph(100, 100, TitleImage, true);
	DrawGraph(500, 500, hitstartkeyImage, true);
}
//�Q�[���̃��[�v
void GameScene(void)
{
	// ========== �y��ʌ��ʇ@�z�t�F�[�h�C��
		
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		FDFlag = true;
	}

	GamemainDraw();

	/*if (pauseFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawGraph()
	}*/
}

//�Q�[���̕`��
void GamemainDraw(void)
{
	// ========== �y��ʌ��ʇA�z�t�F�[�h�A�E�g
	

	DrawBox(100
		, 100
		, 700
		, 500
		, 0xFF0000, true);

	DrawFormatString(0, 16, 0xFFFFFF, "SceneCounter : %d", SceneCounter);
}
//
void GameOverScene(void)
{
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		FDFlag = true;
	}
	GameOverSceneDraw();
}
//
void GameOverSceneDraw(void)
{
	DrawBox(100
		, 100
		, 700
		, 500
		, 0x0000FF, true);
	DrawFormatString(0, 32, 0xFFFFFF, "SceneCounter : %d", SceneCounter);
	DrawGraph(100, 100, gameoverImage, true);
}
//bool FedeInScreen(int fadeStep)
//{
//	fadeCnt += fadeStep;
//
//}

//�|�[�Y�̋@�\
void pauseScene(void)
{
	if (keyDownTrigger[KEY_ID_PAUSE])
	{
		//
		pauseFlag = !pauseFlag;
	}
	//�|�[�Y��
	if (pauseFlag)
	{
		SetDrawBright(128, 128, 128);
	}
	else
	{
		//�e�폈��
		aaaaCounter++;
	}

}