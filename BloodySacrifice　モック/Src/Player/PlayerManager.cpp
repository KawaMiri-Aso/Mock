
//PlayerManager.cpp
//�v���C���[�Ǘ�
//CPlayer�ւ̃A�N�Z�X�͕K��CPlayerManager���o�R

#include "PlayerManager.h"

//CPlayerManager�̎��̐錾
CPlayerManager g_player_manager;

CPlayerManager::CPlayerManager()
{
	//CPlayer�̃R���X�g���N�^�͎����ŌĂ΂�܂�
}

CPlayerManager::~CPlayerManager()
{
	//CPlayer�̃f�X�g���N�^�͎����ŌĂ΂�܂�
}

//������
void CPlayerManager::Init()
{
	//�v���C���[�̏��������Ă�
	m_player.Init(VGet(0.0f, 1.0f, 0.0f));
}

//�X�e�b�v
void CPlayerManager::Step()
{
	//�v���C���[�̃X�e�b�v
	m_player.Step();
}

//�`��
void CPlayerManager::Draw()
{
	//�v���C���[�̕`��
	m_player.Draw();
}

//�폜
void CPlayerManager::Delete()
{
	//�v���C���[�폜
	m_player.Delete();
}

//�㏈��();
void CPlayerManager::Fin()
{
	//�v���C���[�̌㏈�����Ă�
	m_player.Fin();
}
