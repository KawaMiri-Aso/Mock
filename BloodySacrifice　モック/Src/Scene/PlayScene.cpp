
//PlayScene.cpp
//プレイシーン

#include "PlayScene.h"
#include "SceneManager.h"
#include "../Camera/CameraManager.h"
#include "../Player/PlayerManager.h"
#include "../Map/Map.h"
#include "../Collision/Collision.h"
#include "../Trap/Stone.h"

CPlayScene::CPlayScene()
{
}

CPlayScene::~CPlayScene()
{
}

//初期化
void CPlayScene::Init()
{
	//天球読み込み
	m_sky_handle = MV1LoadModel("Data/Model/Sky/Sky.x");

	//フィールド初期化
	g_map.Init();

	//岩罠初期化
	g_stone_trap.Init(VGet(-30.0f, 12.0f, 0.0f));

	//天球のサイズを大きくする
	MV1SetScale(m_sky_handle, VGet(150.0f, 150.0f, 150.0f));

	//プレイカメラに変更
	g_camera_manager.ChangeCamera(CCameraManager::CAMERA_ID_PLAY);

	//次はプレイシーンの繰り返しへ
	g_scene_manager.ChangeScene(CSceneManager::SCENE_ID_PLAY_LOOP);
}

//毎フレーム呼ぶ処理
void CPlayScene::Step()
{
	// マップステップ
	g_map.Step();
	// プレイヤーの当たり判定を取るため更新も呼ぶ
	g_map.Update();

	g_stone_trap.Step();

	//プレイカメラ中なら
	if(g_camera_manager.GetCameraID() == CCameraManager::CAMERA_ID_PLAY)
	{
		//プレイヤー管理ステップ
		g_player_manager.Step();

	}

	//カメラ視点・注視点の操作
	g_camera_manager.Step();

	//カメラの座標が終わった後に天球の処理
	//プレイカメラを取得して、カメラの座標に天球を置く
	CPlayCamera *play_camera = g_camera_manager.GetPlayCamera();
	MV1SetPosition(m_sky_handle, play_camera->GetPos());

	//カメラ視点・注視点の反映
	g_camera_manager.Update();

}

//描画
void CPlayScene::Draw()
{	
	//フィールドの描画
	g_map.Draw();

	g_stone_trap.Draw();

	//プレイヤー管理描画
	g_player_manager.Draw();

	//天球描画
	MV1DrawModel(m_sky_handle);

	//カメラの描画
	g_camera_manager.Draw();

	//文字列描画
	DrawString(10, 10, "上下左右で移動", GetColor(255, 255, 255));
	DrawString(10, 26, "スペースでジャンプ", GetColor(255, 255, 255));
	DrawString(10, 42, " <箱とは直方体の当たり判定>", GetColor(255, 255, 128));
}

//後処理
void CPlayScene::Fin()
{
	//フィールド削除
	g_map.Fin();

	g_stone_trap.Fin();

	MV1DeleteModel(m_sky_handle);
}

