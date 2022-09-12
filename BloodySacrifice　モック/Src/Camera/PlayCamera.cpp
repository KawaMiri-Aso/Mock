
//PlayCamera.cpp
//�v���C�V�[���ł̃J����

#include <math.h>
#include "CameraBase.h"
#include "PlayCamera.h"
#include "../Player/PlayerManager.h"

//�J�����֘A
#define CAMERA_OFFSET_POS		(30.0f)	//�J�����̃v���C���[����̃I�t�Z�b�g�l
#define CAMERA_OFFSET_LOOK_Y	(4.0f)	//�J�����̒����_�̃v���C���[���W����̍���

//�R���X�g���N�^
CPlayCamera::CPlayCamera()// : CCameraBase()
{
	//�l�����������Ă���
	//memset(&pos_, 0, sizeof(VECTOR));
	//memset(&look_, 0, sizeof(VECTOR));
	//memset(&up_, 0, sizeof(VECTOR));
}

//�f�X�g���N�^
CPlayCamera::~CPlayCamera()
{
	Fin();
}

//�������i�����Ȃ��j
void CPlayCamera::Init()
{
	//�����Ȃ��Ȃ炷�ׂă[���ɂ���
	//pos_ = VGet(45.0f, 50.0f, 45.0f);
	//memset(&look_, 0, sizeof(VECTOR));
	//memset(&up_, 0, sizeof(VECTOR));

	SetCameraNearFar(0.1f, 150.0f);
}

//�������i��������j
void CPlayCamera::Init(VECTOR pos, VECTOR look, VECTOR up)
{
	//��������Ȃ�ݒ肷��
	pos_ = pos;
	look_ = look;
	up_ = up;
}

//���t���[���Ăԏ����i����j
void CPlayCamera::Step()
{
	//�R�R�Ńv���C���[�����擾���āA
	//���_�⒍���_�����߂�

	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//=======================
	// ���_�̏���
	//=======================

	//�J�����̍��W�����߂�
	VECTOR player_pos = player->GetPos();

	//�J�����͏�Ɏ΂ߏォ��v���C���[������
	pos_.x = player_pos.x + 45.0f;
	pos_.y = player_pos.y + 50.0f;
	pos_.z = player_pos.z + 45.0f;


	//=======================
	// �����_�̏���
	//=======================

	//�J�����̒����_���v���C���[�̏�ɂ���
	//�J���������_�Ƀv���C���[���W����
	look_ = player_pos;

	//Y�������W�̏���ɂ���
	look_.y += CAMERA_OFFSET_LOOK_Y;

}

//�J�������̍X�V����
void CPlayCamera::Update()
{
	//�J�����̎��_�i���W�j�E�����_�E�A�b�v�x�N�g���ݒ�
	SetCameraPositionAndTargetAndUpVec(pos_, look_, up_);
}

void CPlayCamera::Draw()
{
}

//�㏈��
void CPlayCamera::Fin()
{
}

