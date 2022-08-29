
//CameraManager.h
//カメラ管理
//各カメラへのアクセスは必ずCCameraManagerを経由

#include "PlayCamera.h"
#include "TitleCamera.h"
#include "DebugCamera.h"

class CCameraManager
{
public:

	//enumもclassの定義内に書くことが出来る
	enum CAMERA_ID
	{
		CAMERA_ID_PLAY,		//CPlayCamera
		CAMERA_ID_TITLE,	//CTitleCamera
		CAMERA_ID_DEBUG,	//今後作るCDebugCamera
	};

public:

	CCameraManager();
	~CCameraManager();

	//初期化
	void Init();

	//ステップ
	void Step();

	//描画
	void Draw();

	//更新
	void Update();

	//後処理
	void Fin();

	//引数のカメラに変更する
	void ChangeCamera(CAMERA_ID cameraID);

	//現在のカメラID取得
	CAMERA_ID GetCameraID(){ return m_eCurrentCameraID; }

	//ニアクリップ・ファークリップの設定
	void SetNearFar(float near_val, float far_val);

	//プレイカメラを取得
	CPlayCamera* GetPlayCamera(){ return &m_PlayCamera; }

	//デバッグカメラを取得
	CDebugCamera* GetDebugCamera(){ return &m_DebugCamera; }

private:

	//現在のカメラID
	CAMERA_ID m_eCurrentCameraID;

	//各カメラの変数
	CPlayCamera m_PlayCamera;	//プレイカメラ
	CTitleCamera m_TitleCamera;	//タイトルカメラ
	CDebugCamera m_DebugCamera;	//デバッグカメラ

};

extern CCameraManager g_camera_manager;
