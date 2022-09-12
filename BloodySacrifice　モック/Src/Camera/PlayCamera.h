
//PlayCamera.h
//�v���C�V�[���ł̃J����

#pragma once

#include "DxLib.h"
#include "CameraBase.h"

class CPlayCamera :public CCameraBase
{
public:
	CPlayCamera();	//�R���X�g���N�^
	~CPlayCamera();	//�f�X�g���N�^

	////������
	//void Init();
	//void Init(VECTOR pos, VECTOR look, VECTOR up);

	////���t���[���Ăԏ����i����j
	//void Step();

	////�J�������̍X�V����
	//void Update();

	////�㏈��
	//void Fin();

	void Init() override;
	void Init(VECTOR pos, VECTOR look, VECTOR up) override;
	void Step() override;
	void Update();
	void Draw() override;
	void Fin() override;

	//���_���擾
	VECTOR GetPos(){ return pos_; }

	//�����_���擾
	VECTOR GetLook(){ return look_; }

private:

	//VECTOR	pos_;		//���_
	//VECTOR	look_;		//�����_
	//VECTOR	up_;		//�A�b�v�x�N�g��

};

