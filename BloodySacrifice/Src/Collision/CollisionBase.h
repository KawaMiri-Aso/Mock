#pragma once
//�R���W�������N���X

#include "../Player/PlayerManager.h"
#include "../Enemy/EnemyManager.h"

// �R���W�����̌`��
enum CollisionShape {
	COLLISION_SHAPE_SPHERE,	// ���̓����蔻��
	COLLISION_SHAPE_BOX,	// �{�b�N�X�̓����蔻��iAABB�j
	COLLISION_SHAPE_NUM
};

// �R���W�����̃J�e�S���[
enum CollisionCategory {
	COLLISION_CATEGORY_PLAYER,			//�v���C���[
	COLLISION_CATEGORY_ENEMY,			//�G�l�~�[
	COLLISION_CATEGORY_PLAYER_ATTACK,	//�v���C���[�̍U��
	COLLISION_CATEGORY_ENEMY_ATTACK,	//�G�l�~�[�̍U��
	COLLISION_CATEGORY_NUM
};

// �R���W�����̏��
enum CollisionState {
	COLLISION_STATE_ACTIVE,	// �L��
	COLLISION_STATE_UNUSE,	// ����
	COLLISION_STATE_NONE,	// �g�p�ς�
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

	//�R���W�����̔���֐�
	virtual bool CheckCollision(CollisionBase* another) = 0;

	//�ݒ�֐�
	void SetPlayer(CPlayer* player) { player_ = player; }
	void SetEnemy(CEnemy* enemy) { enemy_ = enemy; }
	void SetState(int state) { state_ = state; }

	//�擾�֐�
	CPlayer* GetPlayer() const { return player_; }
	CEnemy* GetEnemy() const { return enemy_; }
	int GetState() const { return state_; }
	int GetShape() const { return shape_; }
	VECTOR GetPos() const { return pos_; }
	bool IsActive() const { return state_ != COLLISION_STATE_NONE; }
	bool IsCheck() const { return state_ == COLLISION_STATE_ACTIVE; }

protected:
	int shape_;		//�`��
	int state_;		//���
	VECTOR pos_;	//���W
	CPlayer* player_;
	CEnemy* enemy_;
};
