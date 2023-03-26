#pragma once
//コリジョン管理クラス

#include "CollisionBase.h"
#include <list>

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	static void CreateInstance() { if (!instance_) instance_ = new CollisionManager; }
	static CollisionManager* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

	void Init();
	void Step();
	void Update();
	void Draw();
	void Delete();
	void Fin();

	CollisionBase* CreateCollision(int shape, int category);
	void DeleteEndCollision();	// 使用済みコリジョンの削除

	void CheckCollision();	// 当たり判定チェック

	void CheckPlayerAttackAndEnemy();	// プレイヤー攻撃とエネミーの当たり判定
	void CheckEnemyAttackAndPlayer();	// エネミー攻撃とプレイヤーの当たり判定

private:
	static CollisionManager* instance_;
	std::list<CollisionBase*>collisions_[COLLISION_CATEGORY_NUM];
	float optimize_interval_;
	float optimize_timer_;
};