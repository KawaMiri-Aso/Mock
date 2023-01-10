#pragma once

#include "Enemy.h"
#include <list>
using EnemyList = std::list<CEnemy*>;

class CEnemyManager
{
public:
	enum EnemyID
	{
		ENEMY_ID_NORMAL,	//�ʏ�G
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

	//�G�l�~�[�N���X���擾
	CEnemy* GetEnemy()const { return org_enemy_[ENEMY_ID_NORMAL]; }

private:
	static CEnemyManager* instance_;
	CEnemy* org_enemy_[ENEMY_ID_MAX];	//�G�N���X
	EnemyList enemy_list_;
	int norm_pos_hndl;		//���W�p�̃��f���n���h��
	int norm_pos_ID_;		//�t���[���i�{�[���j�̔ԍ�
};
