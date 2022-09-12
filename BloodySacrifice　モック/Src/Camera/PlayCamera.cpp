
//PlayCamera.cpp
//プレイシーンでのカメラ

#include <math.h>
#include "CameraBase.h"
#include "PlayCamera.h"
#include "../Player/PlayerManager.h"

//カメラ関連
#define CAMERA_OFFSET_POS		(30.0f)	//カメラのプレイヤーからのオフセット値
#define CAMERA_OFFSET_LOOK_Y	(4.0f)	//カメラの注視点のプレイヤー座標からの高さ

//コンストラクタ
CPlayCamera::CPlayCamera()// : CCameraBase()
{
	//値を初期化しておく
	//memset(&pos_, 0, sizeof(VECTOR));
	//memset(&look_, 0, sizeof(VECTOR));
	//memset(&up_, 0, sizeof(VECTOR));
}

//デストラクタ
CPlayCamera::~CPlayCamera()
{
	Fin();
}

//初期化（引数なし）
void CPlayCamera::Init()
{
	//引数なしならすべてゼロにする
	//pos_ = VGet(45.0f, 50.0f, 45.0f);
	//memset(&look_, 0, sizeof(VECTOR));
	//memset(&up_, 0, sizeof(VECTOR));

	SetCameraNearFar(0.1f, 150.0f);
}

//初期化（引数あり）
void CPlayCamera::Init(VECTOR pos, VECTOR look, VECTOR up)
{
	//引数ありなら設定する
	pos_ = pos;
	look_ = look;
	up_ = up;
}

//毎フレーム呼ぶ処理（操作）
void CPlayCamera::Step()
{
	//ココでプレイヤー情報を取得して、
	//視点や注視点を決める

	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//=======================
	// 視点の処理
	//=======================

	//カメラの座標を求める
	VECTOR player_pos = player->GetPos();

	//カメラは常に斜め上からプレイヤーを見る
	pos_.x = player_pos.x + 45.0f;
	pos_.y = player_pos.y + 50.0f;
	pos_.z = player_pos.z + 45.0f;


	//=======================
	// 注視点の処理
	//=======================

	//カメラの注視点をプレイヤーの上にする
	//カメラ注視点にプレイヤー座標を代入
	look_ = player_pos;

	//Yだけ座標の上方にする
	look_.y += CAMERA_OFFSET_LOOK_Y;

}

//カメラ情報の更新処理
void CPlayCamera::Update()
{
	//カメラの視点（座標）・注視点・アップベクトル設定
	SetCameraPositionAndTargetAndUpVec(pos_, look_, up_);
}

void CPlayCamera::Draw()
{
}

//後処理
void CPlayCamera::Fin()
{
}

