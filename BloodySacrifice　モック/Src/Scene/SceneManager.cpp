
//SceneManager.cpp
//シーン管理
//各シーンへのアクセスは必ずCSceneManagerを経由

#include "SceneManager.h"
#include "PlayScene.h"

CSceneManager* CSceneManager::instance_ = nullptr;

CSceneManager::CSceneManager()
{
	scene_ = nullptr;
	m_eCurrentSceneState = SCENE_STATE_INIT;
}

CSceneManager::~CSceneManager()
{
}

//初期化
void CSceneManager::Init()
{
	//ここはシーン管理の初期化であって、
	//各シーンの初期化ではない
}

//ループ
void CSceneManager::Loop()
{
	switch(m_eCurrentSceneState)
	{

	//シーン初期化
	case SCENE_STATE_INIT:
		scene_->Init();
		m_eCurrentSceneState = SCENE_STATE_LOAD;
		break;

	//シーン繰り返し
	case SCENE_STATE_LOAD:
		scene_->Load();
		m_eCurrentSceneState = SCENE_STATE_LOAD_END;
		break;

	//シーンロード完了
	case SCENE_STATE_LOAD_END:
		scene_->OnLoadEnd();
		m_eCurrentSceneState = SCENE_STATE_LOOP;
		break;

	//シーン繰り返し
	case SCENE_STATE_LOOP:
		scene_->Step();
		scene_->Draw();	//描画はステップの後に呼ぶ
		break;

	//タイトルシーン後処理
	case SCENE_STATE_FIN:
		scene_->Fin();
		ChangeNextScene();
		break;

	}

}


//後処理
void CSceneManager::Fin()
{
	if (scene_)
	{
		delete scene_;
	}
}

//１番最初のシーンを開始する
void CSceneManager::StartFirstScene(SCENE_ID sceneID)
{
	//既に何かシーンが動いてるのであれば即終了
	if (scene_) return;

	//シーンを生成して初期化から開始する
	CreateScene(sceneID);
	m_eCurrentSceneID = sceneID;
	m_eCurrentSceneState = SCENE_STATE_INIT;
}

//引数のシーンに変更する
void CSceneManager::ChangeScene(SCENE_ID sceneID)
{
	//次に遷移するシーンを覚えておき、終了処理へ
	m_eNextSceneID = sceneID;
	m_eCurrentSceneState = SCENE_STATE_FIN;
}

//シーンを生成する
void CSceneManager::CreateScene(SCENE_ID sceneID)
{
	//シーンを生成
	switch (sceneID) {
	case SCENE_ID_PLAY: scene_ = new CPlayScene; break;
	}
}

//次の画面に遷移させる
void CSceneManager::ChangeNextScene()
{
}
