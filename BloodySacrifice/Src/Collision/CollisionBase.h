#pragma once
//コリジョン基底クラス

#include "../Player/PlayerManager.h"
#include "../Enemy/EnemyManager.h"

// コリジョンの形状
enum CollisionShape {
	COLLISION_SHAPE_SPHERE,	// 球の当たり判定
	COLLISION_SHAPE_BOX,	// ボックスの当たり判定（AABB）
	COLLISION_SHAPE_NUM
};

// コリジョンのカテゴリー
enum CollisionCategory {
	COLLISION_CATEGORY_PLAYER,			//プレイヤー
	COLLISION_CATEGORY_ENEMY,			//エネミー
	COLLISION_CATEGORY_PLAYER_ATTACK,	//プレイヤーの攻撃
	COLLISION_CATEGORY_ENEMY_ATTACK,	//エネミーの攻撃
	COLLISION_CATEGORY_NUM
};

// コリジョンの状態
enum CollisionState {
	COLLISION_STATE_ACTIVE,	// 有効
	COLLISION_STATE_UNUSE,	// 無効
	COLLISION_STATE_NONE,	// 使用済み
};

class CollisionBase
{
public:
	CollisionBase();
	~CollisionBase();

	virtual void Init();
	virtual void Step();
	virtual void Update();
	virtual void Draw();
	virtual void Fin();
	virtual CollisionBase* Clone() = 0;

	//コリジョンの判定関数
	virtual bool CheckCollision(CollisionBase* another) = 0;

	//設定関数
	void SetPlayer(CPlayer* player) { player_ = player; }
	void SetEnemy(CEnemy* enemy) { enemy_ = enemy; }
	void SetState(int state) { state_ = state; }

	//取得関数
	CPlayer* GetPlayer() const { return player_; }
	CEnemy* GetEnemy() const { return enemy_; }
	int GetState() const { return state_; }
	int GetShape() const { return shape_; }
	VECTOR GetPos() const { return pos_; }
	bool IsActive() const { return state_ != COLLISION_STATE_NONE; }
	bool IsCheck() const { return state_ == COLLISION_STATE_ACTIVE; }

protected:
	int shape_;		//形状
	int state_;		//状態
	VECTOR pos_;	//座標
	CPlayer* player_;
	CEnemy* enemy_;
};
