
//CameraManager.cpp
//カメラ管理
//各カメラへのアクセスは必ずCCameraManagerを経由

#include "CameraManager.h"

CCameraManager g_camera_manager;

CCameraManager::CCameraManager()
{
}

CCameraManager::~CCameraManager()
{
}

//初期化
void CCameraManager::Init()
{
	//全てのカメラの初期化
	m_PlayCamera.Init(VGet(15.0f, 30.0f, 15.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f));
	m_TitleCamera.Init(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f));
	m_DebugCamera.Init(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f));
}

//ステップ
void CCameraManager::Step()
{
	//現在のカメラIDによってステップ処理を振り分ける
	switch (m_eCurrentCameraID)
	{
		//プレイカメラの処理
		case CAMERA_ID_PLAY:
			m_PlayCamera.Step();
			break;

		//タイトルカメラの処理
		case CAMERA_ID_TITLE:
			m_TitleCamera.Step();
			break;

		//デバッグカメラの処理
		case CAMERA_ID_DEBUG:
			m_DebugCamera.Step();
			break;
	}
}

//描画
void CCameraManager::Draw()
{
	//現在のカメラIDによってステップ処理を振り分ける
	switch (m_eCurrentCameraID)
	{
		//デバッグカメラの処理
		case CAMERA_ID_DEBUG:
			m_DebugCamera.Draw();
			break;
	}
}

//更新
void CCameraManager::Update()
{
	//現在のカメラIDによって更新処理を振り分ける
	switch (m_eCurrentCameraID)
	{
		//プレイカメラの処理
		case CAMERA_ID_PLAY:
			m_PlayCamera.Update();
			break;

		//タイトルカメラの処理
		case CAMERA_ID_TITLE:
			m_TitleCamera.Update();
			break;

		//デバッグカメラの処理
		case CAMERA_ID_DEBUG:
			m_DebugCamera.Update();
			break;
	}
}

//後処理
void CCameraManager::Fin()
{
	//全てのカメラの後処理
	m_PlayCamera.Fin();
	m_TitleCamera.Fin();
	m_DebugCamera.Fin();
}

//引数のカメラに変更する
void CCameraManager::ChangeCamera(CAMERA_ID cameraID)
{
	//現在のカメラIDを変更する
	m_eCurrentCameraID = cameraID;
}

//ニアクリップ・ファークリップの設定
void CCameraManager::SetNearFar(float near_val, float far_val)
{
	SetCameraNearFar(near_val, far_val);
}

