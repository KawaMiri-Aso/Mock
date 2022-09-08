
//TitleCamera.h
//�^�C�g���V�[���ł̃J����

#pragma once

#include "DxLib.h"

class CTitleCamera
{

public:
	CTitleCamera();	//�R���X�g���N�^
	~CTitleCamera();	//�f�X�g���N�^

	//������
	void Init();
	void Init(VECTOR pos, VECTOR look, VECTOR up);

	//���t���[���Ăԏ����i����j
	void Step();

	//�J�������̍X�V����
	void Update();

	//�㏈��
	void Fin();

	//���_���擾
	VECTOR GetPos(){ return pos_; }

	//�����_���擾
	VECTOR GetLook(){ return look_; }

private:
	
	VECTOR	pos_;		//���_
	VECTOR	look_;		//�����_
	VECTOR	up_;		//�A�b�v�x�N�g��

};

