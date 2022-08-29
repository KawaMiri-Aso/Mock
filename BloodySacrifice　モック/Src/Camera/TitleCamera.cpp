
//TitleCamera.cpp
//�^�C�g���V�[���ł̃J����

#include <math.h>
#include "TitleCamera.h"

//�R���X�g���N�^
CTitleCamera::CTitleCamera()
{
	//�l�����������Ă���
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vLook, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}

//�f�X�g���N�^
CTitleCamera::~CTitleCamera()
{
}

//�������i�����Ȃ��j
void CTitleCamera::Init()
{
	//�����Ȃ��Ȃ炷�ׂă[���ɂ���
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vLook, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}

//�������i��������j
void CTitleCamera::Init(VECTOR pos, VECTOR look, VECTOR up)
{
	//��������Ȃ�ݒ肷��
	m_vPos = pos;
	m_vLook = look;
	m_vUp = up;
}

//���t���[���Ăԏ����i����j
void CTitleCamera::Step()
{

}

//�J�������̍X�V����
void CTitleCamera::Update()
{
	//�J�����̎��_�i���W�j�E�����_�E�A�b�v�x�N�g���ݒ�
	SetCameraPositionAndTargetAndUpVec(m_vPos, m_vLook, m_vUp);
}

//�㏈��
void CTitleCamera::Fin()
{
}

