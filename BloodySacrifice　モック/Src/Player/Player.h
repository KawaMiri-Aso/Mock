
//Player.h
//�v���C���[�֘A

#pragma once

#include "DxLib.h"

//�v���C���[���
enum PLAYER_STATE
{
	PLAYER_STATE_NORMAL,	//�ʏ�
	PLAYER_STATE_JUMP_UP,	//�W�����v�㏸��
};

class CPlayer
{
public:
	CPlayer();		//�R���X�g���N�^
	~CPlayer();		//�f�X�g���N�^

	//������
	void Init();
	void Init(VECTOR pos, VECTOR rot);

	//�ǂݍ���
	void Load(const char* file_path);

	//�폜
	void Delete();

	//���t���[���Ăԏ����i����j
	void Step();

	//�`��
	void Draw();

	//�㏈��
	void Fin();

	//���W���擾
	VECTOR GetPos(){ return m_vPos; }

	//��]���擾
	VECTOR GetRot(){ return m_vRot; }

	//�v���C���[�̉�]����
	void AngleProcess();

private:

	int				m_nHandle;		//�n���h��
	VECTOR			m_vPos;			//���W
	VECTOR			m_vSpeed;		//�ړ����x�x�N�g��
	VECTOR			m_vRot;			//�����ׂ������x�N�g��
	float			m_fAngle;		//�����Ă�������̊p�x
	PLAYER_STATE	m_eState;		//���
	float			m_fJumpTime;	//�W�����v�̎���
};
