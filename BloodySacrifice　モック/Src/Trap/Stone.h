#pragma once

#include "DxLib.h"

#define STONE_W	(20.0f)
#define STONE_H	(20.0f)
#define STONE_W	(20.0f)
#define STONE_D	(20.0f)
#define STONE_RAD (10.0f)

enum STONE_TRAP_STATE
{
	STONE_TRAP_STATE_BEFORE,	//使用前
	STONE_TRAP_STATE_AFTER,		//使用後
};

class CStoneTrap
{
public:
	CStoneTrap();
	~CStoneTrap();

	void Init();
	void Init(VECTOR pos);
	void Step();
	void Draw();
	void Fin();

	void CheckCollision();

	//座標を取得
	VECTOR GetPos() { return m_vPos; }

	//回転を取得
	VECTOR GetRot() { return m_vRot; }

private:
	int m_nHandle;				//ハンドル
	VECTOR m_vPos;				//座標
	VECTOR m_vRot;				//回転
	STONE_TRAP_STATE m_eState;	//状態
};

extern CStoneTrap g_stone_trap;