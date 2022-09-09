
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

	//������
	void Init();

	//�X�e�b�v
	void Step();

	//���[�h
	void Load();

	//�`��
	void Draw();

	//�폜
	void Delete();

	//�㏈��();
	void Fin();

	//�v���C���[�N���X���擾
	CPlayer* GetPlayer(){ return &m_player; }

private:

	CPlayer	m_player;	//�v���C���[�N���X

};

//PlayerManager.h���C���N���[�h������Ŏg����悤��
extern CPlayerManager g_player_manager;
