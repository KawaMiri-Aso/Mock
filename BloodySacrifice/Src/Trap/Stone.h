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
	VECTOR GetPos() { return pos_; }

	//��]���擾
	VECTOR GetRot() { return rot_; }

	//�쓮��Ԃ��擾
	STONE_TRAP_STATE GetState() { return state_; }

private:
	int handle_;				//�n���h��
	VECTOR pos_;				//���W
	VECTOR rot_;				//��]
	STONE_TRAP_STATE state_;	//���
	float app_time_;			//�o������
};

extern CStoneTrap g_stone_trap;