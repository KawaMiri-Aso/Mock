
//DebugCamera.cpp
//�펞�N���ł���f�o�b�O�J����

#include <math.h>
#include "DebugCamera.h"
#include "../Input/Input.h"
#include "../Common.h"

namespace
{
	const float EYE_SPD= (0.1f);		//���_�̈ړ����x
	const float LOOK_SPD = (0.1f);		//�����_�̈ړ����x
	const float LOOK_LIMIT_Y = (20.0f);	//�����_�̎��_����̍������E

	const float LOOK_SPHERE_RAD = (0.5f);	//�����_�`��̔��a
	const int LOOK_SPHERE_DIV_NUM = (8);	//�����_�`��̕�����
}

CDebugCamera::CDebugCamera()
{
	//�l�����������Ă���
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vLook, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}

CDebugCamera::~CDebugCamera()
{
}

//������
void CDebugCamera::Init()
{
	//�l�����������Ă���
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vLook, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}

void CDebugCamera::Init(VECTOR pos, VECTOR look, VECTOR up)
{
	//��������Ȃ�ݒ肷��
	m_vPos = pos;
	m_vLook = look;
	m_vUp = up;
}

//���t���[���Ăԏ����i����j
void CDebugCamera::Step()
{
	//============================
	//�����_�̑���
	//============================

	//����
	if(g_input.IsCont(KEY_UP))
	{
		//�����_����ֈړ�
		m_vLook.y += LOOK_SPD;

		if(m_vLook.y - m_vPos.y > LOOK_LIMIT_Y)
			m_vLook.y = m_vPos.y + LOOK_LIMIT_Y;
	}
	//�����
	if(g_input.IsCont(KEY_DOWN))
	{
		//�����_�����ֈړ�
		m_vLook.y -= LOOK_SPD;

		if(m_vLook.y - m_vPos.y < -LOOK_LIMIT_Y)
			m_vLook.y = m_vPos.y -LOOK_LIMIT_Y;
	}
	//����󂩉E���
	if(g_input.IsCont(KEY_LEFT) || g_input.IsCont(KEY_RIGHT))
	{
		//�����_�܂ł̃x�N�g�������߂�
		VECTOR dir = VSub(m_vLook, m_vPos);

		//�����_�܂ł̃x�N�g����Y�x�N�g���̊O�ς����߂�
		//���ړ��p�̃x�N�g�������߂���
		VECTOR side = VCross(dir, VGet(0.f, 1.f, 0.f));

		//���߂��x�N�g���𐳋K�����Ĉړ����x����Z����
		side = VNorm(side);
		side = VScale(side, LOOK_SPD);

		//�E�ֈړ��̂Ƃ��͔��]
		if(g_input.IsCont(KEY_RIGHT))
			side = VScale(side, -1.f);

		//�����_�Ɉړ��x�N�g�������Z����
		m_vLook = VAdd(m_vLook, side);
	}

	//============================
	//���_�̑���
	//============================

	//W�L�[�܂��� S�L�[
	if(g_input.IsCont(KEY_W) == 1 || g_input.IsCont(KEY_S))
	{
		//�����_�܂ł̃x�N�g�������߂�
		VECTOR dir = VSub(m_vLook, m_vPos);

		//���߂��x�N�g���𐳋K�����Ĉړ����x����Z����
		dir = VNorm(dir);
		dir = VScale(dir, EYE_SPD);

		//��O�Ȃ甽�]
		if(g_input.IsCont(KEY_S))
			dir = VScale(dir, -1.f);

		//���_�Ɉړ��x�N�g�������Z����
		m_vPos = VAdd(m_vPos, dir);

		//�����_�Ɉړ��x�N�g�������Z����
		m_vLook = VAdd(m_vLook, dir);
	}
	//A�L�[�܂��� D�L�[
	if(g_input.IsCont(KEY_A) == 1 || g_input.IsCont(KEY_D))
	{
		//�����_�܂ł̃x�N�g�������߂�
		VECTOR dir = VSub(m_vLook, m_vPos);

		//�����_�܂ł̃x�N�g����Y�x�N�g���̊O�ς����߂�
		VECTOR side = VCross(dir, VGet(0.f, 1.f, 0.f));

		//���߂��x�N�g���𐳋K�����Ĉړ����x����Z����
		side = VNorm(side);
		side = VScale(side, EYE_SPD);

		//�E�ֈړ��̂Ƃ��͔��]
		if(g_input.IsCont(KEY_D))
			side = VScale(side, -1.f);
			
		//���_�Ɉړ��x�N�g�������Z����
		m_vPos = VAdd(m_vPos, side);

		//�����_�Ɉړ��x�N�g�������Z����
		m_vLook = VAdd(m_vLook, side);
	}
}

//�`��
void CDebugCamera::Draw()
{
	//�����_�ɋ��̂�\������
	DrawSphere3D(m_vLook, LOOK_SPHERE_RAD, LOOK_SPHERE_DIV_NUM, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);

	DrawString(WINDOW_W - 280, 10, "�f�o�b�O�J�������[�h", GetColor(255, 255, 0));
	DrawFormatString(WINDOW_W - 270, 26, GetColor(255, 255, 255), "Pos  = (%.2f, %.2f, %.2f)", m_vPos.x, m_vPos.y, m_vPos.z);
	DrawFormatString(WINDOW_W - 270, 42, GetColor(255, 255, 255), "Look = (%.2f, %.2f, %.2f)", m_vLook.x, m_vLook.y, m_vLook.z);
}

//�J�������̍X�V����
void CDebugCamera::Update()
{
	//�J�����̎��_�i���W�j�E�����_�E�A�b�v�x�N�g���ݒ�
	SetCameraPositionAndTargetAndUpVec(m_vPos, m_vLook, m_vUp);
}

//�㏈��
void CDebugCamera::Fin()
{
}
