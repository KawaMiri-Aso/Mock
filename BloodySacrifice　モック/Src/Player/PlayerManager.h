
//PlayerManager.h
//�v���C���[�Ǘ�
//CPlayer�ւ̃A�N�Z�X�͕K��CPlayerManager���o�R

#pragma once

#include "Player.h"

class CPlayerManager
{
public:

	CPlayerManager();
	~CPlayerManager();

	static void CreateInstance() { if (!instance_)instance_ = new CPlayerManager; }
	static CPlayerManager* GetInstance(){return instance_; }
	static void DeleteInstance() { if (instance_)delete instance_; instance_ = nullptr; }

	//������
	void Init();
	//���[�h
	void Load();
	//�X�e�b�v
	void Step();
	//�`��
	void Draw();
	//�폜
	void Delete();
	//�㏈��();
	void Fin();

	//�v���C���[�N���X���擾
	CPlayer* GetPlayer()const { return m_player; }

private:
	static CPlayerManager* instance_;
	CPlayer* m_player;	//�v���C���[�N���X

};
