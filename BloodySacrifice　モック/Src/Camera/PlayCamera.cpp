
//PlayCamera.cpp
//プレイシーンでのカメラ

#include <math.h>
#include "PlayCamera.h"
#include "../Player/PlayerManager.h"

//カメラ関連
#define CAMERA_OFFSET_POS		(30.0f)	//カメラのプレイヤーからのオフセット値
#define CAMERA_OFFSET_LOOK_Y	(4.0f)	//カメラの注視点のプレイヤー座標からの高さ

//コンストラクタ
CPlayCamera::CPlayCamera()
{
	//値を初期化しておく
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vLook, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}

//デストラクタ
CPlayCamera::~CPlayCamera()
{
}

//初期化（引数なし）
void CPlayCamera::Init()
{
	//引数なしならすべてゼロにする
	m_vPos.x = 15.0f; m_vPos.y = 10.0f; m_vPos.z = 15.0f;
	memset(&m_vLook, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}

//初期化（引数あり）
void CPlayCamera::Init(VECTOR pos, VECTOR look, VECTOR up)
{
	//引数ありなら設定する
	m_vPos = pos;
	m_vLook = look;
	m_vUp = up;
}

//毎フレーム呼ぶ処理（操作）
void CPlayCamera::Step()
{
	//ココでプレイヤー情報を取得して、
	//視点や注視点を決める

	CPlayer *player = g_player_manager.GetPlayer();

	//=======================
	// 視点の処理
	//=======================

	////カメラの視点をプレイヤーの後ろにする
	//VECTOR player_dir = {0};

	////プレイヤーの向きを求める
	//VECTOR player_rot = player->GetRot();
	//player_dir.x = sinf(player_rot.y);
	//player_dir.z = cosf(player_rot.y);
	//player_dir.x *= -1.0f;
	//player_dir.z *= -1.0f;

	//VECTOR offset_vec = {0};

	////プレイヤーの移動ベクトルの逆方向のベクトルを求め、
	////ずらす量を乗算する
	//offset_vec.x = player_dir.x * -CAMERA_OFFSET_POS;
	//offset_vec.z = player_dir.z * -CAMERA_OFFSET_POS;

	//プレイヤー座標にずらす量を加算し、
	//カメラの座標を求める
	VECTOR player_pos = player->GetPos();
	//m_vPos.x = player_pos.x + player_dir.x;
	//m_vPos.z = player_pos.z + player_dir.z;

	m_vPos.x = player_pos.x + 15.0f;
	m_vPos.z = player_pos.z + 15.0f;


	//=======================
	// 注視点の処理
	//=======================

	//カメラの注視点をプレイヤーの上にする
	//カメラ注視点にプレイヤー座標を代入
	m_vLook = player_pos;

	//Yだけ座標の上方にする
	m_vLook.y += CAMERA_OFFSET_LOOK_Y;

}

//カメラ情報の更新処理
void CPlayCamera::Update()
{
	//カメラの視点（座標）・注視点・アップベクトル設定
	SetCameraPositionAndTargetAndUpVec(m_vPos, m_vLook, m_vUp);
}

//後処理
void CPlayCamera::Fin()
{
}

