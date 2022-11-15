#pragma once

#include "Enemy.h"
#include <list>
using EnemyList = std::list<CEnemy*>;

class CEnemyManager
{
public:
	enum EnemyID
	{
		ENEMY_ID_NORMAL,	//通常敵
		ENEMY_ID_MAX
	};

public:
	CEnemyManager();
	~CEnemyManager();

	static void CreateInstance() { if (!instance_)instance_ = new CEnemyManager; }
	static CEnemyManager* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_)delete instance_; instance_ = NULL; }

	CEnemy* CreateEnemy(EnemyID id);

	void Init();
	void Load();
	void OnLoadEnd();
	void Step();
	void Draw();
	void Fin();

private:
	static CEnemyManager* instance_;
	CEnemy* org_enemy_[ENEMY_ID_MAX];
	EnemyList enemy_list_;
	int norm_pos_hndl;		//座標用のモデルハンドル
	int norm_pos_ID_;		//フレーム（ボーン）の番号
};
