#pragma once
//�R���W�����Ǘ��N���X

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
	void DeleteEndCollision();	// �g�p�ς݃R���W�����̍폜

	void CheckCollision();	// �����蔻��`�F�b�N

	void CheckPlayerAttackAndEnemy();	// �v���C���[�U���ƃG�l�~�[�̓����蔻��
	void CheckEnemyAttackAndPlayer();	// �G�l�~�[�U���ƃv���C���[�̓����蔻��

private:
	static CollisionManager* instance_;
	std::list<CollisionBase*>collisions_[COLLISION_CATEGORY_NUM];
	float optimize_interval_;
	float optimize_timer_;
};