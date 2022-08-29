
//TitleScene.cpp
//タイトルシーン

#include "TitleScene.h"
#include "SceneManager.h"
#include "../Camera/CameraManager.h"
#include "../Player/PlayerManager.h"
#include "../Input/Input.h"

CTitleScene::CTitleScene()
{
}

CTitleScene::~CTitleScene()
{
}

//初期化
void CTitleScene::Init()
{
	//タイトルカメラに変更
	g_camera_manager.ChangeCamera(CCameraManager::CAMERA_ID_TITLE);

	//次はタイトルシーンの繰り返しへ
	g_scene_manager.ChangeScene(CSceneManager::SCENE_ID_TITLE_LOOP);
}

//毎フレーム呼ぶ処理
void CTitleScene::Step()
{
	//ENTER押された
	if(g_input.IsPush(KEY_ENTER))
	{
		g_scene_manager.ChangeScene(CSceneManager::SCENE_ID_TITLE_FIN);
	}

	//カメラ視点・注視点の操作
	g_camera_manager.Step();

	//カメラ視点・注視点の反映
	g_camera_manager.Update();

}

//描画
void CTitleScene::Draw()
{
	//カメラの描画
	g_camera_manager.Draw();

	//文字列描画
	DrawString(10, 10, "タイトル画面", GetColor(255, 255, 255));
	DrawString(10, 26, "Enter押したらプレイへ", GetColor(255, 255, 0));
}

//後処理
void CTitleScene::Fin()
{
	//次はプレイシーンの初期化へ
	g_scene_manager.ChangeScene(CSceneManager::SCENE_ID_PLAY_INIT);
}

