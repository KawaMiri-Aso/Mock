#pragma once

#include "DxLib.h"

//マップ関連
#define MAP_FLOOR_NORM_Y (0.1f)	//法線のY成分絶対値がこの値以上であれば床
#define MAP_WALL_NORM_Z (0.5f)	//法線のZ成分絶対値がこの値以上であればXY平面の壁
#define MAP_CEIL_NORM_Y	(-0.9f)	//法線のY成分絶対値がこの値以下であれば天井

class CMap
{
public:
	CMap();
	~CMap();

	//初期化
	void Init();

	//ステップ
	void Step();

	//更新
	void Update();

	//描画
	void Draw();

	//後処理();
	void Fin();

	int GetCol_handle() { return col_handle; }

private:
	int handle;						//画像ハンドル
	int col_handle;					//当たり判定用モデルハンドル
	VECTOR pos;						//座標
};

extern CMap g_map;