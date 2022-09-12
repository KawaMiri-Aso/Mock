
//CameraManager.cpp
//カメラ管理
//各カメラへのアクセスは必ずCCameraManagerを経由

#include "CameraManager.h"
#include "PlayCamera.h"
#include "DebugCamera.h"
#include "CameraBase.h"


CCameraManager* CCameraManager::instance_ = nullptr;

CCameraManager::CCameraManager()
//: camera_(nullptr)
{
	Init();
}

CCameraManager::~CCameraManager()
{
}

//初期化
void CCameraManager::Init()
{
	////全てのカメラの初期化
	
	//m_DebugCamera.Init(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f));

	m_PlayCamera = new CPlayCamera();

	m_PlayCamera->Init(VGet(15.0f, 40.0f, 15.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f));
}

//ステップ
void CCameraManager::Step()

{
	////現在のカメラIDによってステップ処理を振り分ける
	//switch (m_eCurrentCameraID)
	//{
	//	//プレイカメラの処理
	//	case CAMERA_ID_PLAY:
	//		camera_->Step();
	//		break;

	//	//デバッグカメラの処理
	//	case CAMERA_ID_DEBUG:
	//		camera_->Step();
	//		break;
	//}

	m_PlayCamera->Step();
}

//更新
void CCameraManager::Update()
{
	////現在のカメラIDによって更新処理を振り分ける
	//switch (m_eCurrentCameraID)
	//{
	//	//プレイカメラの処理
	//case CAMERA_ID_PLAY:
	//	camera_->Update();
	//	break;

	//	//デバッグカメラの処理
	//case CAMERA_ID_DEBUG:
	//	camera_->Update();
	//	break;
	//}
	m_PlayCamera->Update();
}

//描画
void CCameraManager::Draw()
{
	////現在のカメラIDによってステップ処理を振り分ける
	//switch (m_eCurrentCameraID)
	//{
	//	//デバッグカメラの処理
	//	case CAMERA_ID_DEBUG:
	//		camera_->Draw();
	//		break;
	//}
}

//後処理
void CCameraManager::Fin()
{
	////全てのカメラの後処理
	//m_PlayCamera.Fin();
	//m_DebugCamera.Fin();

	delete m_PlayCamera;
}


void CCameraManager::StartCamera(CAMERA_ID id)
{
	//if (camera_) delete camera_;

	//
	//switch (id) {
	//case CAMERA_ID_PLAY: 
	//	camera_ = new CPlayCamera; 
	//	break;
	//}
	//camera_->Init();
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

