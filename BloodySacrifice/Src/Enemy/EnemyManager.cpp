#include "EnemyManager.h"
#include "NormalEnemy.h"

CEnemyManager* CEnemyManager::instance_ = nullptr;

//���W�ԍ�
static const int NORM_POS_ID[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//���W�̌�
static const int NORM_POS_NUM = 10;

CEnemyManager::CEnemyManager()
{
	norm_pos_hndl = -1;
	norm_pos_ID_ = 0;
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
	if (norm_pos_hndl == -1)
	{
		norm_pos_hndl = MV1LoadModel("Data/Model/Enemy/Pos_Bone/Enemy_Bone.x");
	}
}

void CEnemyManager::OnLoadEnd()
{
	CEnemy* ene = new CNormalEnemy;
	for (int i = 0; i < NORM_POS_NUM; i++)
	{
		ene = CreateEnemy(ENEMY_ID_NORMAL);
		VECTOR pos = MV1GetFramePosition(norm_pos_hndl, NORM_POS_ID[i]);
		ene->SetPos(pos);
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