#include "Map.h"

CMap g_map;

CMap::CMap()
{
	// モデル
	handle_ = -1;
	// 当たり判定用モデル
	col_handle_ = -1;
	pos_ = { 0 };

	//天球モデル
	m_sky_handle = -1;
}

CMap::~CMap()
{
}

//初期化
void CMap::Init()
{
	// モデル読み込み
	handle_ = MV1LoadModel("Data/Model/Field/Field.x");
	// 当たり判定用モデル読み込み
	col_handle_ = MV1LoadModel("Data/Model/Field/Col_Field.x");
	// 当たり判定用モデルのポリゴン情報をセットアップ
	MV1SetupCollInfo(col_handle_);
	pos_ = { 0 };

	//天球読み込み
	m_sky_handle = MV1LoadModel("Data/Model/Sky/Sky.x");
	//天球のサイズを大きくする
	MV1SetScale(m_sky_handle, VGet(2000.0f, 2000.0f, 2000.0f));
}

//ステップ
void CMap::Step()
{

}

//更新
void CMap::Update()
{
	//マップの座標
	MV1SetPosition(handle_, pos_);
	// ポリゴン情報を更新する
	MV1RefreshReferenceMesh(col_handle_, -1, TRUE);
}

//描画
void CMap::Draw()
{
	MV1DrawModel(handle_);

	//天球描画
	MV1DrawModel(m_sky_handle);
}

//後処理();
void CMap::Fin()
{
	MV1DeleteModel(handle_);
	MV1DeleteModel(col_handle_);
	MV1DeleteModel(m_sky_handle);
}

VECTOR CMap::HitCheck(VECTOR vCenter, float fRadius)
{
	VECTOR	vOut = { 0 };	//　物体が背景にめり込んだ距離

	MV1_COLL_RESULT_POLY_DIM	res;	// 当たり判定結果格納構造体
	res = MV1CollCheck_Sphere(col_handle_, -1, vCenter, fRadius);	// 球の当たり判定結果格納

	// 当たったポリゴンの数だけ繰返す
	for (int i = 0; i < res.HitNum; i++)
	{
		//	ヒットしたポリゴンとヒットした物体のめり込んだ距離を求める
		VECTOR	vSub = VSub(res.Dim[i].HitPosition, vCenter);
		float	fLen = VSize(vSub);
		fLen = fRadius - fLen;
		// めり込んだ距離分だけ外に押し出す　押し出す方向は法線の方向
		VECTOR	vLine = VScale(res.Dim[i].Normal, fLen);
		
		vOut = VAdd(vOut, vLine);
	}
	//当たってるポリゴン数だけ法線を掛けてるので、その分割る
	if (res.HitNum >= 2)
	{
		vOut.x /= res.HitNum;
		vOut.y /= res.HitNum;
		vOut.z /= res.HitNum;
	}
	// 当たり判定結果を破棄する
	MV1CollResultPolyDimTerminate(res);

	return vOut;
}

//シャドウマップ関連
void CMap::ShadowSet()
{
	shadow_handle_ = MakeShadowMap(2048, 2048);
	//光の方向を設定
	SetShadowMapLightDirection(shadow_handle_, VGet(1.0f, -1.0f, 0.0f));
	//影を描画する範囲を設定
	SetShadowMapDrawArea(shadow_handle_,
		VGet(-500.0f, -1.0f, -500.0f),	//範囲の最小値
		VGet(500.0f, 180.0f, 500.0f));		//範囲の最大値
}