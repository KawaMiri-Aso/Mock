
//TitleCamera.cpp
//�^�C�g���V�[���ł̃J����

#include <math.h>
#include "TitleCamera.h"

//�R���X�g���N�^
CTitleCamera::CTitleCamera()
{
	//�l�����������Ă���
	memset(&pos_, 0, sizeof(VECTOR));
	memset(&look_, 0, sizeof(VECTOR));
	memset(&up_, 0, sizeof(VECTOR));
}

//�f�X�g���N�^
CTitleCamera::~CTitleCamera()
{
}

//�������i�����Ȃ��j
void CTitleCamera::Init()
{
	//�����Ȃ��Ȃ炷�ׂă[���ɂ���
	memset(&pos_, 0, sizeof(VECTOR));
	memset(&look_, 0, sizeof(VECTOR));
	memset(&up_, 0, sizeof(VECTOR));
}

//�������i��������j
void CTitleCamera::Init(VECTOR pos, VECTOR look, VECTOR up)
{
	//��������Ȃ�ݒ肷��
	pos_ = pos;
	look_ = look;
	up_ = up;
}

//���t���[���Ăԏ����i����j
void CTitleCamera::Step()
{

}

//�J�������̍X�V����
void CTitleCamera::Update()
{
	//�J�����̎��_�i���W�j�E�����_�E�A�b�v�x�N�g���ݒ�
	SetCameraPositionAndTargetAndUpVec(pos_, look_, up_);
}

//�㏈��
void CTitleCamera::Fin()
{
}

