#pragma once

#include "DxLib.h"

//�}�b�v�֘A
#define MAP_FLOOR_NORM_Y (0.1f)	//�@����Y������Βl�����̒l�ȏ�ł���Ώ�
#define MAP_WALL_NORM_Z (0.5f)	//�@����Z������Βl�����̒l�ȏ�ł����XY���ʂ̕�
#define MAP_CEIL_NORM_Y	(-0.9f)	//�@����Y������Βl�����̒l�ȉ��ł���ΓV��

class CMap
{
public:
	CMap();
	~CMap();

	//������
	void Init();

	//�X�e�b�v
	void Step();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�㏈��();
	void Fin();

	int GetCol_handle() { return col_handle; }

private:
	int handle;						//�摜�n���h��
	int col_handle;					//�����蔻��p���f���n���h��
	VECTOR pos;						//���W
};

extern CMap g_map;