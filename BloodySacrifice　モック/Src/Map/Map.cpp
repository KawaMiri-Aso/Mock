#include "Map.h"

CMap g_map;

CMap::CMap()
{
	// モデル
	handle = -1;
	// 当たり判定用モデル
	col_handle = -1;
	pos = { 0 };
}

CMap::~CMap()
{
}

//初期化
void CMap::Init()
{
	// モデル読み込み
	handle = MV1LoadModel("Data/Model/Field/Field.x");
	// 当たり判定用モデル読み込み
	col_handle = MV1LoadModel("Data/Model/Field/coll_Field.x");
	// 当たり判定用モデルのポリゴン情報をセットアップ
	MV1SetupReferenceMesh(col_handle, -1, TRUE);
	pos = { 0 };
}

//ステップ
void CMap::Step()
{

}

//更新
void CMap::Update()
{
	//マップの座標
	MV1SetPosition(handle, pos);
	// ポリゴン情報を更新する
	MV1RefreshReferenceMesh(col_handle, -1, TRUE);
}

//描画
void CMap::Draw()
{
	MV1DrawModel(handle);
}

//後処理();
void CMap::Fin()
{
	MV1DeleteModel(handle);
	MV1DeleteModel(col_handle);
}