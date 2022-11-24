
//PlayScene.cpp
//プレイシーン

#include "PlayScene.h"
#include "SceneManager.h"
#include "../Camera/CameraManager.h"
#include "../Player/PlayerManager.h"
#include "../Map/Map.h"
#include "../Collision/Collision.h"
#include "../Trap/Stone.h"
#include "../Enemy/EnemyManager.h"
#include "../Totem/Totem.h"

CTotem* totem = new CTotem;

CPlayScene::CPlayScene()
{
	state_ = PLAY_STATE_NONE;
}

CPlayScene::~CPlayScene()
{
}

//初期化
void CPlayScene::Init()
{
	////プレイカメラに変更
	//g_camera_manager.ChangeCamera(CCameraManager::CAMERA_ID_PLAY);

	////次はプレイシーンの繰り返しへ
	//g_scene_manager.ChangeScene(CSceneManager::SCENE_ID_PLAY_LOOP);

	InitPlayer();
	InitMap();
	InitEnemy();
	InitCamera();
	InitStoneTrap();
	InitTotem();

}

//ロード
void CPlayScene::Load()
{
	LoadPlayer();
	LoadMap();
	LoadEnemy();
	LoadCamera();
	LoadStoneTrap();
	LoadTotem();
}

//ロード完了
void CPlayScene::OnLoadEnd()
{
	/*CEnemy* enemy = CEnemyManager::GetInstance()->CreateEnemy(CEnemyManager::ENEMY_ID_NORMAL);
	enemy->Init();
	enemy->SetPos(VGet(30.0f, 1.0f, 25.0f));
	enemy->SetBackPos(VGet(30.0f, 1.0f, 25.0f));*/

	CEnemyManager::GetInstance()->OnLoadEnd();
}

//毎フレーム呼ぶ処理
void CPlayScene::Step()
{
	// マップステップ
	g_map.Step();
	// プレイヤーとの当たり判定を取るため更新も呼ぶ
	g_map.Update();
	//トーテム
	g_totem.Step();
	//岩落とし
	g_stone_trap.Step();


	////プレイカメラ中なら
	//if(g_camera_manager.GetCameraID() == CCameraManager::CAMERA_ID_PLAY)
	//{
	//	//プレイヤー管理ステップ
	//	g_player_manager.Step();

	//}

	////カメラ視点・注視点の操作
	//g_camera_manager.Step();

	////カメラの座標が終わった後に天球の処理
	////プレイカメラを取得して、カメラの座標に天球を置く
	//CPlayCamera *play_camera = g_camera_manager.GetPlayCamera();
	//MV1SetPosition(m_sky_handle, play_camera->GetPos());

	////カメラ視点・注視点の反映
	//g_camera_manager.Update();

	CPlayerManager::GetInstance()->Step();
	CEnemyManager::GetInstance()->Step();
	//CMapをゲットインスタンスでStep
	CCameraManager::GetInstance()->Step();
	CCameraManager::GetInstance()->Update();
}

//描画
void CPlayScene::Draw()
{	
	//フィールドの描画
	g_map.Draw();
	g_totem.Draw();
	//g_stone_trap.Draw();

	////プレイヤー管理描画
	//g_player_manager.Draw();

	////カメラの描画
	//g_camera_manager.Draw();

	CPlayerManager::GetInstance()->Draw();
	CEnemyManager::GetInstance()->Draw();
	CCameraManager::GetInstance()->Draw();

	//文字列描画
	DrawString(10, 10, "上下左右で移動", GetColor(255, 255, 255));
	DrawString(10, 26, "スペースでジャンプ", GetColor(255, 255, 255));

}

//後処理
void CPlayScene::Fin()
{
	//フィールド削除
	g_map.Fin();
	g_totem.Fin();
	g_stone_trap.Fin();

	CPlayerManager::DeleteInstance();
	CEnemyManager::DeleteInstance();
	CCameraManager::DeleteInstance();
}

void CPlayScene::InitPlayer()
{
	CPlayerManager::CreateInstance();
	CPlayerManager::GetInstance()->Init();
}
void CPlayScene::InitMap()
{
	//フィールド初期化
	g_map.Init();
}
void CPlayScene::InitEnemy()
{
	CEnemyManager::CreateInstance();
	CEnemyManager::GetInstance()->Init();
}
void CPlayScene::InitCamera()
{
	CCameraManager::GetInstance()->ChangeCamera(CCameraManager::CAMERA_ID_PLAY);
}
void CPlayScene::InitStoneTrap()
{
	//岩罠初期化
	g_stone_trap.Init(VGet(-30.0f, 12.0f, 0.0f));
}

void CPlayScene::InitTotem()
{
	g_totem.Init(VGet(0.0f, 12.2f, 0.0f));
}

void CPlayScene::LoadPlayer()
{
	CPlayerManager::GetInstance()->Load();
}
void CPlayScene::LoadMap()
{

}
void CPlayScene::LoadEnemy()
{
	CEnemyManager::GetInstance()->Load();
}
void CPlayScene::LoadCamera()
{

}
void CPlayScene::LoadStoneTrap()
{

}
void CPlayScene::LoadTotem()
{

}

void CPlayScene::StepPlayState()
{

}
