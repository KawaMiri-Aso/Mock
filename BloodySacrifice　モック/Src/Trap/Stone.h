#pragma once

#include "DxLib.h"

#define STONE_W	(20.0f)
#define STONE_H	(20.0f)
#define STONE_D	(20.0f)
#define STONE_RAD (10.0f)
#define STONE_APP_TIME	(3.0f)	//罠が作動してから消えるまでの時間

//岩落とし作動状態
enum STONE_TRAP_STATE
{
	STONE_TRAP_STATE_BEFORE,	//作動前
	STONE_TRAP_STATE_AFTER,		//作動後
	STONE_TRAP_STATE_OUT,		//作動後、消滅
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

	//座標を取得
	VECTOR GetPos() { return m_vPos; }

	//回転を取得
	VECTOR GetRot() { return m_vRot; }

	//作動状態を取得
	STONE_TRAP_STATE GetState() { return m_eState; }

private:
	int m_nHandle;				//ハンドル
	VECTOR m_vPos;				//座標
	VECTOR m_vRot;				//回転
	STONE_TRAP_STATE m_eState;	//状態
	float m_fAppTime;			//出現時間
};

extern CStoneTrap g_stone_trap;