#include "EnemyManager.h"

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
	
}

void CEnemyManager::Load()
{

}

void CEnemyManager::Step()
{

}

void CEnemyManager::Draw()
{

}

void CEnemyManager::Fin()
{

}