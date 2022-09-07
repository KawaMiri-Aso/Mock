#pragma once

#include "DxLib.h"

#define STONE_W	(20.0f)
#define STONE_H	(20.0f)
#define STONE_D	(20.0f)
#define STONE_RAD (10.0f)
#define STONE_APP_TIME	(3.0f)	//㩂��쓮���Ă��������܂ł̎���

//�◎�Ƃ��쓮���
enum STONE_TRAP_STATE
{
	STONE_TRAP_STATE_BEFORE,	//�쓮�O
	STONE_TRAP_STATE_AFTER,		//�쓮��
	STONE_TRAP_STATE_OUT,		//�쓮��A����
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

	//���W���擾
	VECTOR GetPos() { return m_vPos; }

	//��]���擾
	VECTOR GetRot() { return m_vRot; }

	//�쓮��Ԃ��擾
	STONE_TRAP_STATE GetState() { return m_eState; }

private:
	int m_nHandle;				//�n���h��
	VECTOR m_vPos;				//���W
	VECTOR m_vRot;				//��]
	STONE_TRAP_STATE m_eState;	//���
	float m_fAppTime;			//�o������
};

extern CStoneTrap g_stone_trap;