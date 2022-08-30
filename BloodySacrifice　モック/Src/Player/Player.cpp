
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
#define PLAYER_WALK_SPEED	(0.3f)	//��������
#define PLAYER_WALK_SPEED_HALF	(0.15f)		//�΂ߕ����p�̑���
#define PLAYER_ROT_SCALING		(0.5f)		//���E���͗p�̐��l
#define PLAYER_ROT_SCALING_HALF	(0.25f)		//�΂ߓ��͗p�̐��l

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

	//�΂߈ړ�
	if (g_input.IsCont(KEY_UP) && g_input.IsCont(KEY_LEFT) || g_input.IsCont(KEY_UP) && g_input.IsCont(KEY_RIGHT))
	{
		VECTOR move_up_sidle = { 0 };

		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_up_sidle = CMyMath::VecCreate(play_camera->GetLook(), play_camera->GetPos());
		//Y�����͏�����
		move_up_sidle.y = 0;
		//���K��
		move_up_sidle = CMyMath::VecNormalize(move_up_sidle);
		//�����������|���Z
		move_up_sidle = CMyMath::VecScale(move_up_sidle, -PLAYER_WALK_SPEED);

		MATRIX m_dir = MGetTranslate(move_up_sidle);
		MATRIX m_rotY;
		if (!g_input.IsCont(KEY_RIGHT))
		{
			m_rotY = MGetRotY(DX_PI_F * -PLAYER_ROT_SCALING_HALF);
		}
		else
		{
			m_rotY = MGetRotY(DX_PI_F * PLAYER_ROT_SCALING_HALF);
		}
		MATRIX m_result = MMult(m_dir, m_rotY);

		VECTOR v_Res;
		v_Res.x = m_result.m[3][0];
		v_Res.y = m_result.m[3][1];
		v_Res.z = m_result.m[3][2];

		m_vPos = VAdd(m_vPos, v_Res);

	}
	else if (g_input.IsCont(KEY_DOWN) && g_input.IsCont(KEY_LEFT) || g_input.IsCont(KEY_DOWN) && g_input.IsCont(KEY_RIGHT))
	{
		VECTOR move_up_sidle = { 0 };

		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_up_sidle = CMyMath::VecCreate(play_camera->GetLook(), play_camera->GetPos());
		//Y�����͏�����
		move_up_sidle.y = 0;
		//���K��
		move_up_sidle = CMyMath::VecNormalize(move_up_sidle);
		//�����������|���Z
		move_up_sidle = CMyMath::VecScale(move_up_sidle, PLAYER_WALK_SPEED);

		MATRIX m_dir = MGetTranslate(move_up_sidle);
		MATRIX m_rotY;
		if (!g_input.IsCont(KEY_RIGHT))
		{
			m_rotY = MGetRotY(DX_PI_F * PLAYER_ROT_SCALING_HALF);
		}
		else
		{
			m_rotY = MGetRotY(DX_PI_F * -PLAYER_ROT_SCALING_HALF);
		}
		MATRIX m_result = MMult(m_dir, m_rotY);

		VECTOR v_Res;
		v_Res.x = m_result.m[3][0];
		v_Res.y = m_result.m[3][1];
		v_Res.z = m_result.m[3][2];

		m_vPos = VAdd(m_vPos, v_Res);

	}
	//�J�����������Ă�������ֈړ�
	else if(g_input.IsCont(KEY_UP))
	{
		VECTOR move_up = { 0 };

		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_up = CMyMath::VecCreate(play_camera->GetLook(), play_camera->GetPos());
		//���K��
		move_up = CMyMath::VecNormalize(move_up);
		//�����������|���Z
		move_up = CMyMath::VecScale(move_up, -PLAYER_WALK_SPEED);

		m_vPos.x += move_up.x;
		m_vPos.z += move_up.z;

		AngleProcess();
	}
	//�J�����������Ă�������Ƃ͋t�ֈړ�
	else if(g_input.IsCont(KEY_DOWN))
	{
		VECTOR move_down = { 0 };

		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_down = CMyMath::VecCreate(play_camera->GetLook(), play_camera->GetPos());
		//���K��
		move_down = CMyMath::VecNormalize(move_down);
		//�����������|���Z
		move_down = CMyMath::VecScale(move_down, PLAYER_WALK_SPEED);

		m_vPos.x += move_down.x;
		m_vPos.z += move_down.z;

		AngleProcess();
	}
	//���ֈړ�
	else if(g_input.IsCont(KEY_LEFT))
	{
		VECTOR move_left = { 0 };

		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_left = CMyMath::VecCreate(play_camera->GetLook(), play_camera->GetPos());
		//Y�����͏�����
		move_left.y = 0;
		//���K��
		move_left = CMyMath::VecNormalize(move_left);
		//�����������|���Z
		move_left = CMyMath::VecScale(move_left, PLAYER_WALK_SPEED);
		

		MATRIX m_dir = MGetTranslate(move_left);
		MATRIX m_rotY = MGetRotY(DX_PI_F * PLAYER_ROT_SCALING);
		MATRIX m_result = MMult(m_dir, m_rotY);

		VECTOR v_Res;
		v_Res.x = m_result.m[3][0];
		v_Res.y = m_result.m[3][1];
		v_Res.z = m_result.m[3][2];

		m_vPos = CMyMath::VecAdd(m_vPos, v_Res);

		AngleProcess();
	}
	//�E�ֈړ�
	else if(g_input.IsCont(KEY_RIGHT))
	{
		VECTOR move_right = { 0 };

		CPlayCamera* play_camera = g_camera_manager.GetPlayCamera();

		//�J�����̎��_�A�����_����x�N�g�����쐬
		move_right = CMyMath::VecCreate(play_camera->GetLook(), play_camera->GetPos());
		//Y�����͏�����
		move_right.y = 0;
		//���K��
		move_right = CMyMath::VecNormalize(move_right);
		//�����������|���Z
		move_right = CMyMath::VecScale(move_right, PLAYER_WALK_SPEED);

		MATRIX m_dir = MGetTranslate(move_right);
		MATRIX m_rotY = MGetRotY(DX_PI_F * -PLAYER_ROT_SCALING);
		MATRIX m_result = MMult(m_dir, m_rotY);

		VECTOR v_Res;
		v_Res.x = m_result.m[3][0];
		v_Res.y = m_result.m[3][1];
		v_Res.z = m_result.m[3][2];

		m_vPos = CMyMath::VecAdd(m_vPos, v_Res);

		AngleProcess();
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

//�v���C���[�̉�]����
void CPlayer::AngleProcess()
{
	//�ڕW�p�x
	float TargetAngle;
	//�ڕW�p�x�ƌ��݂̊p�x�Ƃ̍�
	float SaAngle;

	TargetAngle = atan2f(m_vPos.x, m_vPos.z);

	SaAngle = TargetAngle - m_vRot.y;

	if (SaAngle < -DX_PI_F)
	{
		SaAngle += DX_TWO_PI_F;
	}
	else if (SaAngle > DX_PI_F)
	{
		SaAngle -= DX_TWO_PI_F;
	}

	// �p�x�̍����O�ɋ߂Â���
	if (SaAngle > 0.0f)
	{
		// �����v���X�̏ꍇ�͈���
		SaAngle -= PLAYER_WALK_SPEED;
		if (SaAngle < 0.0f)
		{
			SaAngle = 0.0f;
		}
	}
	else
	{
		// �����}�C�i�X�̏ꍇ�͑���
		SaAngle += PLAYER_WALK_SPEED;
		if (SaAngle > 0.0f)
		{
			SaAngle = 0.0f;
		}
	}

	m_vRot.y = TargetAngle - SaAngle;
}