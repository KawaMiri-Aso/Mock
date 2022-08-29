
//PlayCamera.cpp
//�v���C�V�[���ł̃J����

#include <math.h>
#include "PlayCamera.h"
#include "../Player/PlayerManager.h"

//�J�����֘A
#define CAMERA_OFFSET_POS		(30.0f)	//�J�����̃v���C���[����̃I�t�Z�b�g�l
#define CAMERA_OFFSET_LOOK_Y	(4.0f)	//�J�����̒����_�̃v���C���[���W����̍���

//�R���X�g���N�^
CPlayCamera::CPlayCamera()
{
	//�l�����������Ă���
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vLook, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}

//�f�X�g���N�^
CPlayCamera::~CPlayCamera()
{
}

//�������i�����Ȃ��j
void CPlayCamera::Init()
{
	//�����Ȃ��Ȃ炷�ׂă[���ɂ���
	m_vPos.x = 15.0f; m_vPos.y = 10.0f; m_vPos.z = 15.0f;
	memset(&m_vLook, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}

//�������i��������j
void CPlayCamera::Init(VECTOR pos, VECTOR look, VECTOR up)
{
	//��������Ȃ�ݒ肷��
	m_vPos = pos;
	m_vLook = look;
	m_vUp = up;
}

//���t���[���Ăԏ����i����j
void CPlayCamera::Step()
{
	//�R�R�Ńv���C���[�����擾���āA
	//���_�⒍���_�����߂�

	CPlayer *player = g_player_manager.GetPlayer();

	//=======================
	// ���_�̏���
	//=======================

	////�J�����̎��_���v���C���[�̌��ɂ���
	//VECTOR player_dir = {0};

	////�v���C���[�̌��������߂�
	//VECTOR player_rot = player->GetRot();
	//player_dir.x = sinf(player_rot.y);
	//player_dir.z = cosf(player_rot.y);
	//player_dir.x *= -1.0f;
	//player_dir.z *= -1.0f;

	//VECTOR offset_vec = {0};

	////�v���C���[�̈ړ��x�N�g���̋t�����̃x�N�g�������߁A
	////���炷�ʂ���Z����
	//offset_vec.x = player_dir.x * -CAMERA_OFFSET_POS;
	//offset_vec.z = player_dir.z * -CAMERA_OFFSET_POS;

	//�v���C���[���W�ɂ��炷�ʂ����Z���A
	//�J�����̍��W�����߂�
	VECTOR player_pos = player->GetPos();
	//m_vPos.x = player_pos.x + player_dir.x;
	//m_vPos.z = player_pos.z + player_dir.z;

	m_vPos.x = player_pos.x + 15.0f;
	m_vPos.z = player_pos.z + 15.0f;


	//=======================
	// �����_�̏���
	//=======================

	//�J�����̒����_���v���C���[�̏�ɂ���
	//�J���������_�Ƀv���C���[���W����
	m_vLook = player_pos;

	//Y�������W�̏���ɂ���
	m_vLook.y += CAMERA_OFFSET_LOOK_Y;

}

//�J�������̍X�V����
void CPlayCamera::Update()
{
	//�J�����̎��_�i���W�j�E�����_�E�A�b�v�x�N�g���ݒ�
	SetCameraPositionAndTargetAndUpVec(m_vPos, m_vLook, m_vUp);
}

//�㏈��
void CPlayCamera::Fin()
{
}

