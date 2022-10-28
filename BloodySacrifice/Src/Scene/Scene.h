#pragma once

class CScene
{

public:
	CScene();
	virtual ~CScene();

	//������
	virtual void Init() = 0;

	//���[�h
	virtual void Load() = 0;

	//���[�h����
	virtual void OnLoadEnd() = 0;

	//���t���[���Ăԏ���
	virtual void Step() = 0;

	//�`��
	virtual void Draw() = 0;

	//�㏈��
	virtual void Fin() = 0;
};
