
//PlayerManager.cpp
//�v���C���[�Ǘ�
//CPlayer�ւ̃A�N�Z�X�͕K��CPlayerManager���o�R
#pragma once

#include "PlayerManager.h"

CPlayerManager* CPlayerManager::instance_ = nullptr;

CPlayerManager::CPlayerManager()
{
	m_player = nullptr;
}

CPlayerManager::~CPlayerManager()
{
	Fin();
}

//������
void CPlayerManager::Init()
{
	//�v���C���[�̏��������Ă�
	m_player = new CPlayer;
	m_player->Init(VGet(-41.0f, 1.0f, 41.0f));
}

//���[�h
void CPlayerManager::Load()
{
	m_player->Load();
}

//�X�e�b�v
void CPlayerManager::Step()
{
	//�v���C���[�̃X�e�b�v
	m_player->Step();
}

//�`��
void CPlayerManager::Draw()
{
	//�v���C���[�̕`��
	m_player->Draw();
}

//�폜
void CPlayerManager::Delete()
{
	//�v���C���[�폜
	m_player->Delete();
}

//�㏈��();
void CPlayerManager::Fin()
{
	//�v���C���[�̌㏈�����Ă�
	m_player->Fin();
}
