
#include <math.h>
#include "DxLib.h"
#include "Common.h"
#include "Input/Input.h"
#include "Player/PlayerManager.h"
#include "Camera/CameraManager.h"
#include "Scene/SceneManager.h"
#include "Enemy/EnemyManager.h"

//------------------------------
// 定数
//------------------------------

//箱関連
#define BOX_NUM		(4)		//箱の数
#define BOX_W		(2.0f)	//箱の横幅
#define BOX_H		(2.0f)	//箱の高さ
#define BOX_D		(2.0f)	//箱の奥行き

//箱情報
struct BoxInfo
{
	int		handle;		//ハンドル
	VECTOR	pos;		//座標
};

//------------------------------
// グローバル変数
//------------------------------

//フレームレート関連
int g_nCurrentTime = 0;			//現在の時間
int g_nLastFrameTime = 0;		//前回のフレーム実行時の時間
int g_nFrameCnt = 0;			//フレームカウント用
int g_nUpdateFrameRateTime = 0;	//フレームレートを更新した時間
float g_fFrameRate = 0.f;		//フレームレート（表示用）


//------------------------------
// グローバル関数
//------------------------------

//フレームレート計算
void CalcFrameRate();

//フレームレート表示（デバッグ用）
void DrawFrameRate();

//プログラムは WinMain から始まる
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
#ifdef _DEBUG
	SetUseDirectInputFlag(FALSE);
#endif

	ChangeWindowMode(true);	//ウィンドウの状態を設定する

	//-----------------------------------------
	//一番最初に１回だけやる処理をここに書く

	//DXライブラリの初期化
	if(DxLib_Init() == -1)
	{
		return -1;
	}

	//ウィンドウサイズを変更
	SetGraphMode(WINDOW_W, WINDOW_H, 32);
	
	//描画するスクリーンを設定
	SetDrawScreen(DX_SCREEN_BACK);

	//透過色を設定
	SetTransColor(0, 127, 127);

	//キー入力初期化
	g_input.Init();

	//モデル関連 =====

	//プレイヤー管理初期化
	g_player_manager.Init();

	//プレイヤー読み込み
	CPlayer *player = g_player_manager.GetPlayer();
	player->Load("Data/Model/Player/player-mock.x");

	CEnemy* enemy = CEnemyManager::GetInstance()->CreateEnemy(CEnemyManager::ENEMY_ID_NORMAL);
	enemy->Init();
	enemy->Load();
	enemy->SetPos(VGet(0.0f, 1.0f, 0.0f));
	enemy->SetBackPos(VGet(0.0f, 1.0f, 0.0f));

	//箱初期化
	BoxInfo box_info[BOX_NUM];

	{
		VECTOR box_pos[BOX_NUM] = {
			{ -7.0f, 1.0f, 7.0f },
			{ 7.0f, 1.0f, 7.0f },
			{ -7.0f, 1.0f, -7.0f },
			{ 7.0f, 1.0f, -7.0f }
		};

		int box_original_handle = MV1LoadModel("Data/Model/Box/Box.x");

		for(int box_index = 0; box_index < BOX_NUM; box_index++)
		{
			box_info[box_index].handle = MV1DuplicateModel(box_original_handle);
			box_info[box_index].pos = box_pos[box_index];
		}

		//コピー元モデルは削除
		MV1DeleteModel(box_original_handle);
	} 

	//シーン管理初期化
	g_scene_manager.Init();

	//最初はタイトルシーンへ
	g_scene_manager.ChangeScene(CSceneManager::SCENE_ID_TITLE_INIT);

	//カメラ管理初期化
	g_camera_manager.Init();
	g_camera_manager.SetNearFar(0.1f, 150.0f);

	//-----------------------------------------

	//=====================================
	//ゲームメインループ
	while(ProcessMessage() != -1)
	{
		Sleep(1);	//システムに処理を返す

		//現在の時刻を取得
		g_nCurrentTime = GetNowCount();

		// 現在の時刻が、前回のフレーム時より
		// 1/60秒経過していたら処理を実行する

		if(g_nCurrentTime - g_nLastFrameTime >= 1000 / FRAME_RATE)
		{
			//フレーム実行時の時間を更新
			g_nLastFrameTime = g_nCurrentTime;

			//フレーム数をカウント
			g_nFrameCnt++;

			if(CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				//エスケープキーが押されたら終了
				break;
			}

			//画面に表示されたものを初期化
			ClearDrawScreen();

			//キー入力ステップ
			g_input.Step();

			//====================
			//モデル関連
			//====================

			//シーン管理のループ
			g_scene_manager.Loop();

			//フィールドの座標
			/*MV1SetPosition(field_info.handle, field_info.pos);*/

			//箱の座標
			for(int box_index = 0; box_index < BOX_NUM; box_index++)
			{
				MV1SetPosition(box_info[box_index].handle, box_info[box_index].pos);
			}

			//カメラ関連 =====

			//Cキー押された
			if(g_input.IsPush(KEY_C))
			{
				//プレイカメラ中なら
				if(g_camera_manager.GetCameraID() == CCameraManager::CAMERA_ID_PLAY)
				{
					//デバッグカメラに変更
					g_camera_manager.ChangeCamera(CCameraManager::CAMERA_ID_DEBUG);

					//デバッグカメラにプレイカメラの情報を設定
					CPlayCamera *play_camera = g_camera_manager.GetPlayCamera();
					CDebugCamera *debug_camera = g_camera_manager.GetDebugCamera();

					debug_camera->SetPos(play_camera->GetPos());
					debug_camera->SetLook(play_camera->GetLook());
				}
				//デバッグカメラ中なら
				else
				{
					//プレイカメラに変更
					g_camera_manager.ChangeCamera(CCameraManager::CAMERA_ID_PLAY);
				}
			}

			//描画 =====

			//フィールドの描画
			/*MV1DrawModel(field_info.handle);*/
		

			//箱の描画
			for(int box_index = 0; box_index < BOX_NUM; box_index++)
			{
				MV1DrawModel(box_info[box_index].handle);
			}

			//フレームレート計算
			CalcFrameRate();

			//フレームレート表示（デバッグ用）
			DrawFrameRate();

			//フリップ関数（ループの終わりに１度だけ行う）
			ScreenFlip();
		}
	}

	//-----------------------------------------
	//最後に１回だけやる処理をここに書く

	//カメラの後処理
	g_camera_manager.Fin();

	//プレイヤー管理の後処理
	g_player_manager.Delete();	//明示的に削除を呼ぶ
	g_player_manager.Fin();		//後処理

	//シーン管理の後処理
	g_scene_manager.Fin();

	//フィールド削除
	/*MV1DeleteModel(field_info.handle);*/
	

	//箱の削除
	for(int box_index = 0; box_index < BOX_NUM; box_index++)
	{
		MV1DeleteModel(box_info[box_index].handle);
	}
	
	//使用したすべての画像を破棄
	InitGraph();

	//DXライブラリの後処理
	DxLib_End();

	//-----------------------------------------

	return 0;
}

//フレームレート計算
void CalcFrameRate()
{
	//前回のフレームレート更新からの経過時間を求める
	int nDifTime = g_nCurrentTime - g_nUpdateFrameRateTime;

	//前回のフレームレート更新から
	//１秒以上経過していたらフレームレートを更新する
	if(nDifTime > 1000)
	{
		//フレーム回数をミリ秒に合わせる
		//小数まで出したいのでfloatにキャスト
		float fFrameCnt = (float)(g_nFrameCnt * 1000);

		//フレームレートを求める
		//理想どおりなら 60000 / 1000 で 60 となる
		g_fFrameRate = fFrameCnt / nDifTime;

		//フレームカウントをクリア
		g_nFrameCnt = 0;

		//フレームレート更新時間を更新
		g_nUpdateFrameRateTime = g_nCurrentTime;
	}
}

//フレームレート表示（デバッグ用）
void DrawFrameRate()
{
	DrawFormatString(695, 580, GetColor(255, 30, 30), "FPS[%.2f]", g_fFrameRate);	
}
