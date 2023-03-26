#include "CollisionManager.h"
#include "BoxCollision.h"
#include "SphereCollision.h"

CollisionManager* CollisionManager::instance_ = nullptr;

CollisionManager::CollisionManager()
{
	optimize_interval_ = 0.0f;
	optimize_timer_ = 0.0f;
}

CollisionManager::~CollisionManager()
{
	Fin();
}

void CollisionManager::Init()
{

}

void CollisionManager::Step()
{
	for (int i = 0; i < COLLISION_CATEGORY_NUM; i++)
	{
		for (auto collision : collisions_[i])
		{
			collision->Step();
		}
	}
}

void CollisionManager::Update()
{
	for (int i = 0; i < COLLISION_CATEGORY_NUM; i++)
	{
		for (auto collision : collisions_[i])
		{
			collision->Update();
		}
	}
}

void CollisionManager::Draw()
{
	for (int i = 0; i < COLLISION_CATEGORY_NUM; i++)
	{
		for (auto collision : collisions_[i])
		{
			collision->Draw();
		}
	}
}

void CollisionManager::Delete()
{
	for (int i = 0; i < COLLISION_CATEGORY_NUM; i++)
	{
		for (auto collision : collisions_[i])
		{
			delete collision;
		}
		collisions_[i].clear();
	}
}

void CollisionManager::Fin()
{
	Delete();
}

// コリジョン生成
CollisionBase* CollisionManager::CreateCollision(int shape, int category)
{
	CollisionBase* collision = nullptr;
	switch (shape)
	{
	case COLLISION_SHAPE_SPHERE:collision = new SphereCollision; break;
	case COLLISION_SHAPE_BOX:collision = new BoxCollision; break;
	}

	if (collision)
	{
		collision->SetState(COLLISION_STATE_ACTIVE);
		collisions_[category].push_back(collision);
	}
	return collision;
}

// 使用済みコリジョンの削除
void CollisionManager::DeleteEndCollision()
{
	for (int i = 0; i < COLLISION_CATEGORY_NUM; i++)
	{
		for (auto itr = collisions_[i].begin(); itr != collisions_[i].end();)
		{
			CollisionBase* collision = (*itr);
			if (!collision->IsActive())
			{
				delete collision;
				itr = collisions_[i].erase(itr);
			}
			else
			{
				itr++;
			}
		}
	}
}

// 当たり判定チェック
void CollisionManager::CheckCollision()
{
	CheckPlayerAttackAndEnemy();	// プレイヤー攻撃とエネミーの当たり判定
	CheckEnemyAttackAndPlayer();	// エネミー攻撃とプレイヤーの当たり判定
}

// プレイヤー攻撃とエネミーの当たり判定
void CollisionManager::CheckPlayerAttackAndEnemy()
{
	auto player_attack_collisions = collisions_[COLLISION_CATEGORY_PLAYER_ATTACK];
	auto enemy_collisions = collisions_[COLLISION_CATEGORY_ENEMY];
	for (auto pl_attack : player_attack_collisions)
	{
		if (!pl_attack->IsCheck()) continue;
		for (auto en_col : enemy_collisions)
		{
			if (!en_col->IsCheck()) continue;
			if (pl_attack->CheckCollision(en_col))
			{
				pl_attack->GetPlayer()->OnEnCollisionEnter(en_col->GetEnemy());
				en_col->GetEnemy()->OnPlCollisionEnter(pl_attack->GetPlayer());
			}
		}
	}
}

// エネミー攻撃とプレイヤーの当たり判定
void CollisionManager::CheckEnemyAttackAndPlayer()
{

}