#include "EnemyManager.h"
#include "NormalEnemy.h"

CEnemyManager* CEnemyManager::instance_ = NULL;

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

void CEnemyManager::Step()
{
	for (auto itr = enemy_list_.begin(); itr != enemy_list_.end();) {
		CEnemy* enemy = (*itr);
		enemy->Step();
		// 死亡した場合は削除
		if (!enemy->IsActive()) {
			//実体を削除
			delete enemy;
			//リストから削除。eraseが次のイデレータを返してくれる
			itr = enemy_list_.erase(itr);
			continue;
		}
		// イデレータを進める
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