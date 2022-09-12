
//CameraManager.h
//カメラ管理
//各カメラへのアクセスは必ずCCameraManagerを経由
#pragma once

class CCameraBase;
class CPlayCamera;
class CDebugCamera;

class CCameraManager
{
public:

	//enumもclassの定義内に書くことが出来る
	enum CAMERA_ID
	{
		CAMERA_ID_PLAY,		//CPlayCamera
		CAMERA_ID_DEBUG,	//今後作るCDebugCamera
	};

public:

	CCameraManager();
	~CCameraManager();

	static void CreateInstance() { if (!instance_) instance_ = new CCameraManager; }
	static CCameraManager* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

	//初期化
	void Init();
	//ステップ
	void Step();
	//更新
	void Update();
	//描画
	void Draw();
	//後処理
	void Fin();

	void StartCamera(CAMERA_ID id);

	//引数のカメラに変更する
	void ChangeCamera(CAMERA_ID cameraID);

	//ニアクリップ・ファークリップの設定
	void SetNearFar(float near_val, float far_val);

	//プレイカメラを取得
	CPlayCamera* GetPlayCamera() { return m_PlayCamera; }

	//デバッグカメラを取得
	CDebugCamera* GetDebugCamera() { return m_DebugCamera; }

private:

	//各カメラの変数
	CPlayCamera* m_PlayCamera;	//プレイカメラ
	CDebugCamera* m_DebugCamera;	//デバッグカメラ

	//現在のカメラID
	CAMERA_ID m_eCurrentCameraID;

	static CCameraManager* instance_;
	//CCameraBase* camera_;
};