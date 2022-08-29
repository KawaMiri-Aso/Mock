
//Player.cpp
//�v���C���[�֘A

#include <math.h>
#include "Player.h"
#include "../Common.h"
#include "../Input/Input.h"
#include "../Camera/CameraManager.h"
#include "../MyMath/MyMath.h"

CMyMath* math;

//�v���C���[�֘A
#define PLAYER_W	(2.0f)	//�v���C���[�̉���
#define PLAYER_H	(2.0f)	//�v���C���[�̍���
#define PLAYER_D	(2.0f)	//�v���C���[�̉��s��
#define PLAYER_RAD	(1.0f)	//�v���C���[�̔��a
#define PLAYER_JUMP_VAL		(0.3f)	//�W�����v��
#define PLAYER_JUMP_TIME	(0.8f)	//�W�����v�̎���
#define PLAYER_WALK_SPEED	(3.0f)	//��������

//�d��
#define GRAVITY		(0.15f)

//�R���X�g���N�^
CPlayer::CPlayer()
{
	m_nHandle = 0;
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	m_eState = PLAYER_STATE_NORMAL;
	m_fJumpTime = 0.0f;
}

//�f�X�g���N�^
CPlayer::~CPlayer()
{
}

//�������i�����Ȃ��j
void CPlayer::Init()
{
	//�����Ȃ��Ȃ炷�ׂă[���ɂ���
	m_nHandle = 0;
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	m_eState = PLAYER_STATE_NORMAL;
	m_fJumpTime = 0.0f;
}

//�������i��������j
void CPlayer::Init(VECTOR pos, VECTOR rot)
{
	//���W�Ɖ�]��ݒ�
	m_vPos = pos;
	m_vRot = rot;

	//���̓[���ɂ���
	m_nHandle = 0;
	m_eState = PLAYER_STATE_NORMAL;
	m_fJumpTime = 0.0f;

}

//�ǂݍ���
void CPlayer::Load(const char* file_path)
{
	//���f���̓ǂݍ���
	m_nHandle = MV1LoadModel(file_path);
}

//�폜
void CPlayer::Delete()
{
	//���f���j��
	MV1DeleteModel(m_nHandle);

	//�폜������0�������Ă���
	m_nHandle = 0;
}

//���t���[���Ăԏ����i����j
void CPlayer::Step()
{
	//���ӁF���ƃS�[���̓����蔻��͏����Ă��܂�

	//�ړ��O�̍��W���i�[
	VECTOR player_pre_pos = m_vPos;

	//�v���C���[�ɏ�ɏd�͂�������
	m_vPos.y -= GRAVITY;

	//�v���C���[�ʏ�
	if(m_eState == PLAYER_STATE_NORMAL)
	{
		if(g_input.IsPush(KEY_SPACE))
		{
			//��Ԃ��W�����v�㏸����
			m_eState = PLAYER_STATE_JUMP_UP;
			m_fJumpTime = 0.0f;
		}
	}

	//�v���C���[�W�����v�㏸��
	if(m_eState == PLAYER_STATE_JUMP_UP)
	{
		//�㏸
		m_vPos.y += PLAYER_JUMP_VAL;
		m_fJumpTime += 1.0f / FRAME_RATE;

		//�W�����v���Ԃ��߂�����
		if(m_fJumpTime >= PLAYER_JUMP_TIME)
		{
			m_fJumpTime = 0.0f;
			m_eState = PLAYER_STATE_NORMAL;
		}
	}

	//Y�������蔻�� =====

	//�n�ʂƓ�������
	if(m_vPos.y - PLAYER_RAD < 0.0f)
	{
		m_vPos.y = PLAYER_RAD;				//�߂荞�܂Ȃ��ʒu�ɒu��
		m_eState = PLAYER_STATE_NORMAL;	//�ʏ��Ԃɂ��Ă���
	}


	//�����Ă�������ֈړ�
	if(g_input.IsCont(KEY_UP))
	{
		//VECTOR move = {0};

		////�����x�N�g�������߂�
		//move.x = sinf(m_vRot.y);
		//move.z = cosf(m_vRot.y);

		////�����x�N�g����K�؂ȑ傫���ɕύX���č��W�ɉ��Z
		//m_vPos.x += move.x * -0.1f;
		//m_vPos.z += move.z * -0.1f;

		VECTOR move_up = { 0 };

		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		move_up = CMyMath::VecCreate(play_camera->GetLook(), play_camera->GetPos());
		move_up = CMyMath::VecNormalize(move_up);
		move_up = CMyMath::VecScale(move_up, PLAYER_WALK_SPEED);

		m_vPos.x += move_up.x * -0.1f;
		m_vPos.z += move_up.z * -0.1f;

		move_up = { 0 };
	}

	//�����Ă�������Ƃ͋t�ֈړ�
	if(g_input.IsCont(KEY_DOWN))
	{
		//VECTOR move = {0};

		////�����x�N�g�������߂�
		//move.x = sinf(m_vRot.y);
		//move.z = cosf(m_vRot.y);

		////�����x�N�g����K�؂ȑ傫���E�����ɕύX���č��W�ɉ��Z
		//m_vPos.x += move.x * 0.1f;
		//m_vPos.z += move.z * 0.1f;

		VECTOR move_down = { 0 };

		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		move_down = CMyMath::VecCreate(play_camera->GetLook(), play_camera->GetPos());
		move_down = CMyMath::VecNormalize(move_down);
		move_down = CMyMath::VecScale(move_down, PLAYER_WALK_SPEED);

		m_vPos.x += move_down.x * 0.1f;
		m_vPos.z += move_down.z * 0.1f;
	}

	//����]
	if(g_input.IsCont(KEY_LEFT))
	{
		m_vRot.y -= 0.1f;
	}
	//�E��]
	if(g_input.IsCont(KEY_RIGHT))
	{
		m_vRot.y += 0.1f;
	}

	//���W�ݒ� =====

	//�v���C���[�̉�]
	MV1SetRotationXYZ(m_nHandle, m_vRot);

	//�v���C���[�̍��W
	MV1SetPosition(m_nHandle, m_vPos);
}

//�`��
void CPlayer::Draw()
{
	//�v���C���[�̕`��
	MV1DrawModel(m_nHandle);
}

//�㏈��
void CPlayer::Fin()
{
	//Delete���Ă΂�Ă��Ȃ��Ȃ�
	if(m_nHandle != 0)
	{
		//�폜���Ă�ł���
		Delete();
	}
}

