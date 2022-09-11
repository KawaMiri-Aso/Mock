
//SceneManager.h
//シーン管理
//各シーンへのアクセスは必ずCSceneManagerを経由
#pragma once

#include "Scene.h"

class CSceneManager
{
public:
	//シーン状態
	enum SCENE_STATE
	{
		SCENE_STATE_INIT,		//初期化
		SCENE_STATE_LOAD,		//ロード
		SCENE_STATE_LOAD_END,	//ロード終了
		SCENE_STATE_LOOP,		//ループ
		SCENE_STATE_FIN,		//後処理
	};

	//シーンID
	enum SCENE_ID
	{
		SCENE_ID_TITLE,			//タイトルシーン
		SCENE_ID_PLAY,			//プレイシーン
		SCENE_ID_CLEAR,			//クリアシーン
		SCENE_ID_GAMEOVER,		//ゲームオーバーシーン
	};

public:

	static void CreateInstance() { if (!instance_)instance_ = new CSceneManager; }
	static CSceneManager* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_)delete instance_; instance_ = nullptr; }

	CSceneManager();
	~CSceneManager();

	//初期化
	void Init();

	//ループ
	void Loop();

	//後処理
	void Fin();

	//１番最初のシーンを開始する
	void StartFirstScene(SCENE_ID sceneID);

	//引数のシーンに変更する
	void ChangeScene(SCENE_ID sceneID);

	////プレイシーンを取得
	//CPlayScene* GetPlayScene(){ return &m_PlayScene; }

private:
	//シーンを生成する
	void CreateScene(SCENE_ID sceneID);

	//次の画面に遷移させる
	void ChangeNextScene();

private:
	//インスタンス
	static CSceneManager* instance_;

	//現在のシーンID
	SCENE_ID m_eCurrentSceneID;
	SCENE_ID m_eNextSceneID;
	SCENE_STATE m_eCurrentSceneState;

	CScene* scene_;

	////各シーンの変数
	//CPlayScene m_PlayScene;		//プレイシーン
	//CTitleScene m_TitleScene;	//タイトルシーン

};