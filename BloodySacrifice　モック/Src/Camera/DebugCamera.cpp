
//DebugCamera.cpp
//常時起動できるデバッグカメラ

#include <math.h>
#include "DebugCamera.h"
#include "../Input/Input.h"
#include "../Common.h"

namespace
{
	const float EYE_SPD= (0.1f);		//視点の移動速度
	const float LOOK_SPD = (0.1f);		//注視点の移動速度
	const float LOOK_LIMIT_Y = (20.0f);	//注視点の視点からの高さ限界

	const float LOOK_SPHERE_RAD = (0.5f);	//注視点描画の半径
	const int LOOK_SPHERE_DIV_NUM = (8);	//注視点描画の分割数
}

CDebugCamera::CDebugCamera()
{
	//値を初期化しておく
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vLook, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}

CDebugCamera::~CDebugCamera()
{
}

//初期化
void CDebugCamera::Init()
{
	//値を初期化しておく
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vLook, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}

void CDebugCamera::Init(VECTOR pos, VECTOR look, VECTOR up)
{
	//引数ありなら設定する
	m_vPos = pos;
	m_vLook = look;
	m_vUp = up;
}

//毎フレーム呼ぶ処理（操作）
void CDebugCamera::Step()
{
	//============================
	//注視点の操作
	//============================

	//上矢印
	if(g_input.IsCont(KEY_UP))
	{
		//注視点を上へ移動
		m_vLook.y += LOOK_SPD;

		if(m_vLook.y - m_vPos.y > LOOK_LIMIT_Y)
			m_vLook.y = m_vPos.y + LOOK_LIMIT_Y;
	}
	//下矢印
	if(g_input.IsCont(KEY_DOWN))
	{
		//注視点を下へ移動
		m_vLook.y -= LOOK_SPD;

		if(m_vLook.y - m_vPos.y < -LOOK_LIMIT_Y)
			m_vLook.y = m_vPos.y -LOOK_LIMIT_Y;
	}
	//左矢印か右矢印
	if(g_input.IsCont(KEY_LEFT) || g_input.IsCont(KEY_RIGHT))
	{
		//注視点までのベクトルを求める
		VECTOR dir = VSub(m_vLook, m_vPos);

		//注視点までのベクトルとYベクトルの外積を求める
		//横移動用のベクトルが求められる
		VECTOR side = VCross(dir, VGet(0.f, 1.f, 0.f));

		//求めたベクトルを正規化して移動速度を乗算する
		side = VNorm(side);
		side = VScale(side, LOOK_SPD);

		//右へ移動のときは反転
		if(g_input.IsCont(KEY_RIGHT))
			side = VScale(side, -1.f);

		//注視点に移動ベクトルを加算する
		m_vLook = VAdd(m_vLook, side);
	}

	//============================
	//視点の操作
	//============================

	//Wキーまたは Sキー
	if(g_input.IsCont(KEY_W) == 1 || g_input.IsCont(KEY_S))
	{
		//注視点までのベクトルを求める
		VECTOR dir = VSub(m_vLook, m_vPos);

		//求めたベクトルを正規化して移動速度を乗算する
		dir = VNorm(dir);
		dir = VScale(dir, EYE_SPD);

		//手前なら反転
		if(g_input.IsCont(KEY_S))
			dir = VScale(dir, -1.f);

		//視点に移動ベクトルを加算する
		m_vPos = VAdd(m_vPos, dir);

		//注視点に移動ベクトルを加算する
		m_vLook = VAdd(m_vLook, dir);
	}
	//Aキーまたは Dキー
	if(g_input.IsCont(KEY_A) == 1 || g_input.IsCont(KEY_D))
	{
		//注視点までのベクトルを求める
		VECTOR dir = VSub(m_vLook, m_vPos);

		//注視点までのベクトルとYベクトルの外積を求める
		VECTOR side = VCross(dir, VGet(0.f, 1.f, 0.f));

		//求めたベクトルを正規化して移動速度を乗算する
		side = VNorm(side);
		side = VScale(side, EYE_SPD);

		//右へ移動のときは反転
		if(g_input.IsCont(KEY_D))
			side = VScale(side, -1.f);
			
		//視点に移動ベクトルを加算する
		m_vPos = VAdd(m_vPos, side);

		//注視点に移動ベクトルを加算する
		m_vLook = VAdd(m_vLook, side);
	}
}

//描画
void CDebugCamera::Draw()
{
	//注視点に球体を表示する
	DrawSphere3D(m_vLook, LOOK_SPHERE_RAD, LOOK_SPHERE_DIV_NUM, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);

	DrawString(WINDOW_W - 280, 10, "デバッグカメラモード", GetColor(255, 255, 0));
	DrawFormatString(WINDOW_W - 270, 26, GetColor(255, 255, 255), "Pos  = (%.2f, %.2f, %.2f)", m_vPos.x, m_vPos.y, m_vPos.z);
	DrawFormatString(WINDOW_W - 270, 42, GetColor(255, 255, 255), "Look = (%.2f, %.2f, %.2f)", m_vLook.x, m_vLook.y, m_vLook.z);
}

//カメラ情報の更新処理
void CDebugCamera::Update()
{
	//カメラの視点（座標）・注視点・アップベクトル設定
	SetCameraPositionAndTargetAndUpVec(m_vPos, m_vLook, m_vUp);
}

//後処理
void CDebugCamera::Fin()
{
}
