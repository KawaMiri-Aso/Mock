#include "EnemyManager.h"
#include "NormalEnemy.h"

CEnemyManager* CEnemyManager::instance_ = nullptr;

CEnemyManager::CEnemyManager()
{
}

CEnemyManager::~CEnemyManager()
{
	Fin();
}

CEnemy* CEnemyManager::CreateEnemy(EnemyID id)
{
	CEnemy* enemy = org_enemy_[id]->Clone();
	enemy_list_.push_back(enemy);
	return enemy;
}

void CEnemyManager::Init()
{
	org_enemy_[ENEMY_ID_NORMAL] = new CNormalEnemy;
}

void CEnemyManager::Load()
{
	org_enemy_[ENEMY_ID_NORMAL]->Load();
}

void CEnemyManager::OnLoadEnd()
{
	CEnemy* ene;
	for (int i = 0; i < 10; i++)
	{
		ene = CreateEnemy(ENEMY_ID_NORMAL);
		ene->SetPos();
	}
}

void CEnemyManager::Step()
{
	for (auto itr = enemy_list_.begin(); itr != enemy_list_.end();) {
		CEnemy* enemy = (*itr);
		enemy->Step();
		// ���S�����ꍇ�͍폜
		if (!enemy->IsActive()) {
			//���̂��폜
			delete enemy;
			//���X�g����폜�Berase�����̃C�f���[�^��Ԃ��Ă����
			itr = enemy_list_.erase(itr);
			continue;
		}
		// �C�f���[�^��i�߂�
		itr++;
	}
}

void CEnemyManager::Draw()
{
	for (auto itr = enemy_list_.begin(); itr != enemy_list_.end(); itr++)
	{
		(*itr)->Draw();
	}
}

void CEnemyManager::Fin()
{
	for (auto itr = enemy_list_.begin(); itr != enemy_list_.end(); itr++) {
		CEnemy* enemy = (*itr);
		delete enemy;
	}
	enemy_list_.clear();
}