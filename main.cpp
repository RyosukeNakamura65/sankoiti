
#include "Dxlib.h"			// Dxlibライブラリを使用
#include "main.h"
#include "player.h"
#include "stage.h"
#include "shot.h"
#include "KeyCheck.h"
#include "Effect.h"


// 変数
//-------------------------------------------------------------
// シーン管理用
int gameCounter;		// gameLoop動作確認用
int sceneCounter;		// シーンカウンター
int startCounter;		// ｹﾞｰﾑ開始の時間設定
int faceImage[PLAYER_MAX];
SCENE_ID sceneID;
SCENE_ID preSceneID;

// タイトル
int titleImage;
int titleWordImage;

// ステージ
STAGE_ID stageID;
int ID;

// クラスからインスタンスを生成する
Player* player1;
Player* player2;
Player* player3;
Player* player4;
Stage* stage;
Shot* shot1;
Shot* shot2;
Shot* shot3;
Shot* shot4;

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
					sceneID = SCENE_ID_GAME;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);
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

	faceImage[PLAYER_1] = LoadGraph("image/blueface.png");
	faceImage[PLAYER_2] = LoadGraph("image/pinkface.png");
	faceImage[PLAYER_3] = LoadGraph("image/greenface.png");
	faceImage[PLAYER_4] = LoadGraph("image/yellowface.png");

	// ｲﾝｽﾀﾝｽの生成
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
		, "image/プレイヤー1弾.png");

	shot2 = new Shot(PLAYER_2
		, SCREEN_SIZE_X - 100
		, SCREEN_SIZE_Y - 650
		, "image/プレイヤー2弾.png");

	shot3 = new Shot(PLAYER_3
		, 100
		, SCREEN_SIZE_Y - 100
		, "image/プレイヤー3弾.png");

	shot4 = new Shot(PLAYER_4
		, SCREEN_SIZE_X - 100
		, SCREEN_SIZE_Y - 100
		, "image/プレイヤー4弾.png");


	// グラフィックの登録
	//---------------------------------
	
	// 変数の初期化
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

	KeyInit();		// キー情報の初期化
	EffectInit();	// エフェクトの初期化

	return true;
}



// 初期化シーン
//--------------------------------------------------------------
void InitScene(void)
{
	fadeIn = true;
	
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


// ステージ選択シーン
//---------------------------------------------------------------
void StageSelectScene(void)
{
	// ステージの変更
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

	// シーン遷移
	if (keyUpTrigger[KEY_ID_SPACE])
	{
		fadeOut = true;

		// ステージのインスタンスの生成
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


// ゲームシーン
//----------------------------------------------------------------
void GameScene(void)
{
	// 画面描画
	GameDraw();

	if (startCounter <= START_MSG_1_CNT)
	{
		DrawFormatString(SCREEN_SIZE_X / 2
			, SCREEN_SIZE_Y / 2
			, GetColor(255,255,255), "よーい");
	}
	else
	{
		if (startCounter <= START_MSG_1_CNT + START_MSG_2_CNT)
		{

			DrawFormatString(SCREEN_SIZE_X / 2
				, SCREEN_SIZE_Y / 2
				, GetColor(255, 255, 255), "スタート");
		}
		else
		{
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
	DrawFormatString(0, 64, GetColor(255, 255, 255), "動作確認 : (%d)", a);

	//DrawBox(100, 100, 700, 500, GetColor(255, 0, 0), true);
	player1->Draw();
	player2->Draw();
	player3->Draw();
	player4->Draw();
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
}

void GameOverDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "GameOverScene : %d", sceneCounter);

	DrawBox(100, 100, 700, 500, GetColor(0, 0, 255), true);
}