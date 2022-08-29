
//SceneManager.h
//シーン管理
//各シーンへのアクセスは必ずCSceneManagerを経由

#include "PlayScene.h"
#include "TitleScene.h"

class CSceneManager
{
public:

	//シーンID
	enum SCENE_ID
	{
		SCENE_ID_PLAY_INIT,		//プレイシーン初期化
		SCENE_ID_PLAY_LOOP,		//プレイシーン繰り返し
		SCENE_ID_PLAY_FIN,		//プレイシーン後処理

		SCENE_ID_TITLE_INIT,	//タイトルシーン初期化
		SCENE_ID_TITLE_LOOP,	//タイトルシーン繰り返し
		SCENE_ID_TITLE_FIN,		//タイトルシーン後処理
	};

public:

	CSceneManager();
	~CSceneManager();

	//初期化
	void Init();

	//ループ
	void Loop();

	//後処理
	void Fin();

	//引数のシーンに変更する
	void ChangeScene(SCENE_ID sceneID);

	//プレイシーンを取得
	CPlayScene* GetPlayScene(){ return &m_PlayScene; }

private:

	//現在のシーンID
	SCENE_ID m_eCurrentSceneID;

	//各シーンの変数
	CPlayScene m_PlayScene;		//プレイシーン
	CTitleScene m_TitleScene;	//タイトルシーン

};

extern CSceneManager g_scene_manager;
