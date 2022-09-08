#include "Map.h"

CMap g_map;

CMap::CMap()
{
	// モデル
	handle_ = -1;
	// 当たり判定用モデル
	col_handle_ = -1;
	pos_ = { 0 };
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
	col_handle_ = MV1LoadModel("Data/Model/Field/coll_Field.x");
	// 当たり判定用モデルのポリゴン情報をセットアップ
	MV1SetupCollInfo(col_handle_);
	pos_ = { 0 };
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
}

//後処理();
void CMap::Fin()
{
	MV1DeleteModel(handle_);
	MV1DeleteModel(col_handle_);
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