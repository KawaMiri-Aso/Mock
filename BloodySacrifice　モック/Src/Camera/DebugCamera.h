
//DebugCamera.h
//�펞�N���ł���f�o�b�O�J����

#pragma once

#include "DxLib.h"

class CDebugCamera
{

public:
	CDebugCamera();
	~CDebugCamera();

	//������
	void Init();
	void Init(VECTOR pos, VECTOR look, VECTOR up);

	//���t���[���Ăԏ����i����j
	void Step();

	//�`��
	void Draw();

	//�J�������̍X�V����
	void Update();

	//�㏈��
	void Fin();

	//���_��ݒ�
	void SetPos(VECTOR pos){ m_vPos = pos; }
	
	//�����_��ݒ�
	void SetLook(VECTOR look){ m_vLook = look; }

private:

	VECTOR	m_vPos;		//���_
	VECTOR	m_vLook;	//�����_
	VECTOR	m_vUp;		//�A�b�v�x�N�g��
};