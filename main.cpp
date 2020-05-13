//　ファイル操作用課題
//　2019.09.09
//　中村亮介うんこ

#include "DxLib.h"
#include "main.h"
#include "KeyCheck1.h"
#include "effect.h"
//変数の定義
//システム関連
int SceneCounter;
bool pauseFlag;		
//
SCENE_ID sceneID;
SCENE_ID preSceneID;				//ひとつ前のシーンID
//入力情報管理用

//int TitleCouter;
//int gameCounter;		//ループの動作確認用
//int GameOverCounter;



//イメージ関連
int TitleImage;
int gameoverImage;
int hitstartkeyImage;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//システム初期化
	if (SystemInit())
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	//初期化処理
	//if (!SystemInit())
	//{
	//	AST();
	//	return -1;
	//}

	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		ClsDrawScreen();

		if (sceneID != preSceneID)
		{
			SceneCounter = 0;
			preSceneID = sceneID;
		}

		KeyCheck();  //キー情報の確認

		switch (sceneID)
		{
			//ゲームの前の初期化
		case SCENE_ID_INIT:
			InitScene();
			sceneID = SCENE_ID_TITLE;
			break;
			//タイトル
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
			//	//セレクト
			//case SCENE_ID_SELECT:
			//	SelectScene();
			//	/*sceneID = SCENE_ID_GAME;*/
			//	break;

				//ゲーム
		case SCENE_ID_GAME:
			GameScene();
			fadeScene();
			if (bright < 1)
			{
				sceneID = SCENE_ID_GAMEOVER;
			}
			break;
			/*sceneID = SCENE_ID_GAME;*/
			//クリア
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
		//ゲームのﾒｲﾝ処理
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
	//システムの初期化
	SetWindowText("1916031_中村亮介");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	SetDrawScreen(DX_SCREEN_BACK);
	if (DxLib_Init() == -1)				//DXﾗｲﾌﾞﾗﾘ初期化処理
	{
		return false;
	}
	int retFlag;
	//ｸﾞﾗﾌｨｯｸの登録
	//TitelImage = DrawGraph()
	TitleImage = LoadGraph("image/title.png");

		//変数の初期化
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

//タイトルのループ
void TitleScene(void)
{
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		FDFlag = true;
	}
	TitleSceneDraw();
}
//タイトルの描画
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
//ゲームのループ
void GameScene(void)
{
	// ========== 【画面効果①】フェードイン
		
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

//ゲームの描画
void GamemainDraw(void)
{
	// ========== 【画面効果②】フェードアウト
	

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

//ポーズの機能
void pauseScene(void)
{
	if (keyDownTrigger[KEY_ID_PAUSE])
	{
		//
		pauseFlag = !pauseFlag;
	}
	//ポーズ中
	if (pauseFlag)
	{
		SetDrawBright(128, 128, 128);
	}
	else
	{
		//各種処理
		aaaaCounter++;
	}

}