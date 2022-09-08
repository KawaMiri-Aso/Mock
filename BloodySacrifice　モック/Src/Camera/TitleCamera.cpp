
//TitleCamera.cpp
//タイトルシーンでのカメラ

#include <math.h>
#include "TitleCamera.h"

//コンストラクタ
CTitleCamera::CTitleCamera()
{
	//値を初期化しておく
	memset(&pos_, 0, sizeof(VECTOR));
	memset(&look_, 0, sizeof(VECTOR));
	memset(&up_, 0, sizeof(VECTOR));
}

//デストラクタ
CTitleCamera::~CTitleCamera()
{
}

//初期化（引数なし）
void CTitleCamera::Init()
{
	//引数なしならすべてゼロにする
	memset(&pos_, 0, sizeof(VECTOR));
	memset(&look_, 0, sizeof(VECTOR));
	memset(&up_, 0, sizeof(VECTOR));
}

//初期化（引数あり）
void CTitleCamera::Init(VECTOR pos, VECTOR look, VECTOR up)
{
	//引数ありなら設定する
	pos_ = pos;
	look_ = look;
	up_ = up;
}

//毎フレーム呼ぶ処理（操作）
void CTitleCamera::Step()
{

}

//カメラ情報の更新処理
void CTitleCamera::Update()
{
	//カメラの視点（座標）・注視点・アップベクトル設定
	SetCameraPositionAndTargetAndUpVec(pos_, look_, up_);
}

//後処理
void CTitleCamera::Fin()
{
}

