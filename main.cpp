
#include "Dxlib.h"			// Dxlibライブラリを使用
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


// 変数
//-------------------------------------------------------------
// シーン管理用
int gameCounter;		// gameLoop動作確認用
int sceneCounter;		// シーンカウンター
int startCounter;		// ｹﾞｰﾑ開始の時間設定
SCENE_ID sceneID;
SCENE_ID preSceneID;

// スタートメッセージ
int startMsg[2];

// タイトル
int titleImage;
int titleWordImage;

// ステージ
STAGE_ID stageID;
SELECT_ID selectID;
int ID;
int blend;

// ｹﾞｰﾑｵｰﾊﾞｰ判断
bool playerGameOverFlag;
bool player2GameOverFlag;
bool player3GameOverFlag;
bool player4GameOverFlag;


// WinMain関数
//-------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// システムの初期化
	if (!SystemInit())
	{
		return -1;
	}

	// ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		ClsDrawScreen();

		// シーンカウンタを制御
		if (sceneID != preSceneID)
		{
			preSceneID = sceneID;
			sceneCounter = 0;
		}


		// 入力情報の取得
		KeyCheck();


		// シーン選択
		switch (sceneID)
		{
		// 初期化シーン
		case SCENE_ID_INIT:
			InitScene();
			break;

		// タイトルシーン
		case SCENE_ID_TITLE:
			// 画面切り替えエフェクト
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					// エフェクト終了後の処理
				}
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// エフェクト終了後の処理
					sceneID = SCENE_ID_CHARASELE;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);
				}
			}
			TitleScene();
			break;

			// キャラクタ選択シーン
		case SCENE_ID_CHARASELE:
			// 画面切り替えエフェクト
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					// エフェクト終了後の処理
				}
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// エフェクト終了後の処理
					sceneID = SCENE_ID_STAGESELE;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);
				}
			}
			CharacterSelectScene();
			break;

			// ステージ選択シーン
		case SCENE_ID_STAGESELE:
			// 画面切り替えエフェクト
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					// エフェクト終了後の処理
				}
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// エフェクト終了後の処理
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

		// ゲームシーン
		case SCENE_ID_GAME:
			// 画面切り替えエフェクト
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					// エフェクト終了後の処理
				}
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// エフェクト終了後の処理
					sceneID = SCENE_ID_GAMEOVER;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);
				}
			}
			GameScene();
			break;

		// ゲームオーバーシーン
		case SCENE_ID_GAMEOVER:
			// 画面切り替えエフェクト
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					// エフェクト終了後の処理
				}
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// エフェクト終了後の処理
					sceneID = SCENE_ID_INIT;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);
				}
			}
			GameOverScene();
			break;

		// その他
		default:
			return -1;
			break;
		}


		gameCounter++;
		sceneCounter++;

		ScreenFlip();
	}

	DxLib_End();		// DXライブラリの終了処理
	return 0;
}


//システム系初期化
//--------------------------------------------------------------
bool SystemInit(void)
{
	// システムの初期化
	SetWindowText("SanCo壱");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	
	// グラフィックの登録
	//---------------------------------
	startMsg[0] = LoadGraph("image/start1.png");
	startMsg[1] = LoadGraph("image/start2.png");

	// 変数の初期化
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

	KeyInit();		// キー情報の初期化
	EffectInit();	// エフェクトの初期化

	return true;
}



// 初期化シーン
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


// タイトルシーン
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


// キャラクタ選択シーン
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


// ステージ選択シーン
//---------------------------------------------------------------
void StageSelectScene(void)
{
	// ステージの変更
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

	// ステージが決まったのでシーン遷移
	if (selectID == SELECT_NEXT)
	{
		// シーン遷移
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

	// フェードイン
	if (sceneCounter % 2 == 1)
	{
		if (blend <= 200)
		{
			blend += 3;
		}
	}
}


// ゲームシーン
//----------------------------------------------------------------
void GameScene(void)
{
	// 画面描画
	GameDraw();
	shotDraw();

	if (startCounter <= START_MSG_1_CNT)
	{
		DrawGraph((SCREEN_SIZE_X - START_MSG_SIZE_X) / 2
			, (SCREEN_SIZE_Y - START_MSG_SIZE_Y) / 2 + 60
			, startMsg[0], true);
		/*DrawFormatString(SCREEN_SIZE_X / 2
			, SCREEN_SIZE_Y / 2
			, GetColor(255,255,255), "よーい");*/
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
				, GetColor(255, 255, 255), "スタート");*/
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

			// Pause機能
			if (keyDownTrigger[KEY_ID_PAUSE])
			{
				pauseFlag = !pauseFlag;
			}

			// Pause時
			if (pauseFlag)
			{
				SetDrawBright(100, 100, 100);
			}
			// 通常動作時
			else
			{
				// 各種処理
				a++;
			}

			// Pauseメッセージを描画
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
	DrawFormatString(0, 64, GetColor(255, 255, 255), "動作確認 : (%d)", a);

	//DrawBox(100, 100, 700, 500, GetColor(255, 0, 0), true);
}


// ゲームオーバーシーン
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