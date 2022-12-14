
#include <math.h>
#include "DxLib.h"
#include "Common.h"
#include "Input/Input.h"
#include "Player/PlayerManager.h"
#include "Camera/CameraManager.h"
#include "Scene/SceneManager.h"
#include "Enemy/EnemyManager.h"
#include "Map/Map.h"

//------------------------------
// 定数
//------------------------------

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

	//必要なマネージャークラスを生成、初期化
	CSceneManager::CreateInstance();
	CCameraManager::CreateInstance();

	CSceneManager* scene_manager = CSceneManager::GetInstance();
	scene_manager->StartFirstScene(CSceneManager::SCENE_ID_PLAY);

	//シャドウマップ初期設定
	g_map.ShadowSet();

	//キー入力初期化
	g_input.Init();

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

			//シーン管理のループ
			scene_manager->Loop();

			////箱の座標
			//for(int box_index = 0; box_index < BOX_NUM; box_index++)
			//{
			//	MV1SetPosition(box_info[box_index].handle, box_info[box_index].pos);
			//}

			//Cキー押された
			//if(g_input.IsPush(KEY_C))
			//{
			//	//プレイカメラ中なら
			//	if(g_camera_manager.GetCameraID() == CCameraManager::CAMERA_ID_PLAY)
			//	{
			//		//デバッグカメラに変更
			//		g_camera_manager.ChangeCamera(CCameraManager::CAMERA_ID_DEBUG);

			//		//デバッグカメラにプレイカメラの情報を設定
			//		CPlayCamera *play_camera = g_camera_manager.GetPlayCamera();
			//		CDebugCamera *debug_camera = g_camera_manager.GetDebugCamera();

			//		debug_camera->SetPos(play_camera->GetPos());
			//		debug_camera->SetLook(play_camera->GetLook());
			//	}
			//	//デバッグカメラ中なら
			//	else
			//	{
			//		//プレイカメラに変更
			//		g_camera_manager.ChangeCamera(CCameraManager::CAMERA_ID_PLAY);
			//	}
			//}


			////箱の描画
			//for(int box_index = 0; box_index < BOX_NUM; box_index++)
			//{
			//	MV1DrawModel(box_info[box_index].handle);
			//}

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
	CSceneManager::DeleteInstance();
	CCameraManager::DeleteInstance();

	////箱の削除
	//for(int box_index = 0; box_index < BOX_NUM; box_index++)
	//{
	//	MV1DeleteModel(box_info[box_index].handle);
	//}
	
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
	DrawFormatString(1815, 1060, GetColor(255, 30, 30), "FPS[%.2f]", g_fFrameRate);	
}
