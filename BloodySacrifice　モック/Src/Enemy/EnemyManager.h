#pragma once

#include "Enemy.h"
#include <list>
using EnemyList = std::list<CEnemy*>;

class CEnemyManager
{
public:
	enum EnemyID
	{
		ENEMY_ID_NORMAL,	//í èÌìG
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
	void Step();
	void Draw();
	void Fin();

private:
	static CEnemyManager* instance_;
	CEnemy* org_enemy_[ENEMY_ID_MAX];
	EnemyList enemy_list_;
};
