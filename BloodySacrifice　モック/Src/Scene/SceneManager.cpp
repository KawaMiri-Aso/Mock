
//SceneManager.cpp
//シーン管理
//各シーンへのアクセスは必ずCSceneManagerを経由

#include "SceneManager.h"

CSceneManager g_scene_manager;

CSceneManager::CSceneManager()
{
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
	switch(m_eCurrentSceneID)
	{

	//プレイシーン初期化
	case SCENE_ID_PLAY_INIT:
		m_PlayScene.Init();
		break;

	//プレイシーン繰り返し
	case SCENE_ID_PLAY_LOOP:
		m_PlayScene.Step();
		m_PlayScene.Draw();	//描画はステップの後に呼ぶ
		break;

	//プレイシーン後処理
	case SCENE_ID_PLAY_FIN:
		m_PlayScene.Fin();
		break;

	//タイトルシーン初期化
	case SCENE_ID_TITLE_INIT:
		m_TitleScene.Init();
		break;

	//タイトルシーン繰り返し
	case SCENE_ID_TITLE_LOOP:
		m_TitleScene.Step();
		m_TitleScene.Draw();
		break;

	//タイトルシーン後処理
	case SCENE_ID_TITLE_FIN:
		m_TitleScene.Fin();
		break;

	}

}


//後処理
void CSceneManager::Fin()
{
}

//引数のシーンに変更する
void CSceneManager::ChangeScene(SCENE_ID sceneID)
{
	//シーンIDを変更
	m_eCurrentSceneID = sceneID;
}
