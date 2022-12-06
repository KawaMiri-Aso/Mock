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

	//後処理
	void Fin();

	VECTOR HitCheck(VECTOR vCenter, float fRadius);

	int GetCol_handle() { return col_handle_; }

	//シャドウマップ関連
	void ShadowSet();
	int GetShadowHandle() { return shadow_handle_; }

private:
	int handle_;						//画像ハンドル
	int col_handle_;					//当たり判定用モデルハンドル
	VECTOR pos_;						//座標

	int m_sky_handle;					//天球
	int shadow_handle_;					//シャドウハンドル
};

extern CMap g_map;