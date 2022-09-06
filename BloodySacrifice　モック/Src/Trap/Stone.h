#pragma once

#include "DxLib.h"

#define STONE_W	(20.0f)
#define STONE_H	(20.0f)
#define STONE_W	(20.0f)
#define STONE_D	(20.0f)
#define STONE_RAD (10.0f)

enum STONE_TRAP_STATE
{
	STONE_TRAP_STATE_BEFORE,	//�g�p�O
	STONE_TRAP_STATE_AFTER,		//�g�p��
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

	//���W���擾
	VECTOR GetPos() { return m_vPos; }

	//��]���擾
	VECTOR GetRot() { return m_vRot; }

private:
	int m_nHandle;				//�n���h��
	VECTOR m_vPos;				//���W
	VECTOR m_vRot;				//��]
	STONE_TRAP_STATE m_eState;	//���
};

extern CStoneTrap g_stone_trap;