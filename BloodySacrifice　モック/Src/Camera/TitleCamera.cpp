
//TitleCamera.cpp
//タイトルシーンでのカメラ

#include <math.h>
#include "TitleCamera.h"

//コンストラクタ
CTitleCamera::CTitleCamera()
{
	//値を初期化しておく
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vLook, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}

//デストラクタ
CTitleCamera::~CTitleCamera()
{
}

//初期化（引数なし）
void CTitleCamera::Init()
{
	//引数なしならすべてゼロにする
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vLook, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}

//初期化（引数あり）
void CTitleCamera::Init(VECTOR pos, VECTOR look, VECTOR up)
{
	//引数ありなら設定する
	m_vPos = pos;
	m_vLook = look;
	m_vUp = up;
}

//毎フレーム呼ぶ処理（操作）
void CTitleCamera::Step()
{

}

//カメラ情報の更新処理
void CTitleCamera::Update()
{
	//カメラの視点（座標）・注視点・アップベクトル設定
	SetCameraPositionAndTargetAndUpVec(m_vPos, m_vLook, m_vUp);
}

//後処理
void CTitleCamera::Fin()
{
}

