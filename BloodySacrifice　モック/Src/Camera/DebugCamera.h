
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
	void SetPos(VECTOR pos){ pos_ = pos; }
	
	//�����_��ݒ�
	void SetLook(VECTOR look){ look_ = look; }

private:

	VECTOR	pos_;		//���_
	VECTOR	look_;	//�����_
	VECTOR	up_;		//�A�b�v�x�N�g��
};