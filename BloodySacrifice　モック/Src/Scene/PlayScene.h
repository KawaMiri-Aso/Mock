
//PlayScene.h
//�v���C�V�[��

#pragma once

#include "DxLib.h"

class CPlayScene
{

public:
	CPlayScene();
	~CPlayScene();

	//������
	void Init();

	//���t���[���Ăԏ���
	void Step();

	//�`��
	void Draw();

	//�㏈��
	void Fin();

private:

	//�V��
	int m_sky_handle;

};
