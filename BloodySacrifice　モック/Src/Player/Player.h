
//Player.h
//�v���C���[�֘A

#pragma once

#include "DxLib.h"

//�v���C���[�֘A
#define PLAYER_W	(4.8f)	//�v���C���[�̉���
#define PLAYER_H	(12.8f)	//�v���C���[�̍���
#define PLAYER_D	(3.2f)	//�v���C���[�̉��s��
#define PLAYER_RAD	(6.4f)	//�v���C���[�̔��a
#define PLAYER_JUMP_VAL		(0.3f)	//�W�����v��
#define PLAYER_JUMP_TIME	(0.8f)	//�W�����v�̎���
#define PLAYER_WALK_SPEED	(0.3f)	//��������
#define PLAYER_WALK_SPEED_HALF	(0.15f)		//�≟�����̕�������
#define PLAYER_ROT_SCALING		(0.5f)		//���E���͗p�̐��l
#define PLAYER_ROT_SCALING_HALF	(0.25f)		//�΂ߓ��͗p�̐��l

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

	//�ړ����x�x�N�g�����擾
	VECTOR GetSpeed() { return m_vSpeed; }

	//�v���C���[�̉�]����
	void AngleProcess();

	//�X�e�[�W�Ƃ̓����蔻��
	void CheckCollision();

	//��������Ă��邩
	bool IsPushStone();

private:

	int				m_nHandle;		//�n���h��
	VECTOR			m_vPos;			//���W
	VECTOR			m_vSpeed;		//�ړ����x�x�N�g��
	VECTOR			m_vRot;			//�����ׂ������x�N�g��
	float			m_fAngle;		//�����Ă�������̊p�x
	PLAYER_STATE	m_eState;		//���
	float			m_fJumpTime;	//�W�����v�̎���
	
};
