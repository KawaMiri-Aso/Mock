#pragma once

#include "DxLib.h"
#include "../Player/PlayerManager.h"

//�G�̍s���^�C�v
enum
{	
	STATE_WALK,		//������
	STATE_BACK,		//�m�b�N�o�b�N��

	STATE_NUM
};

class CEnemy
{
public:
	CEnemy();
	virtual ~CEnemy();

	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Step() = 0;
	virtual void Draw() = 0;
	virtual void Delete() = 0;
	virtual void Fin() = 0;
	virtual CEnemy* Clone() = 0;

public:
	void SetPos(VECTOR pos) { pos_ = pos; }
	void SetBackPos(VECTOR pos) { back_pos_ = pos; }

	bool IsActive() const { return active_; }
	int  GetHP() const { return hp_; }
	VECTOR GetPos() const { return pos_; }
	VECTOR GetBackPos() const { return back_pos_; }
	int GetEnemyAIState() const { return ai_state_; }
	void Damage(int damage) { hp_ -= damage; }
	void Dead();

	//���݈ʒu�ɍ��W���Z
	void ReflectCollision(VECTOR addVec);

	//�v���C���[�̍U�����q�b�g������̏���
	void HitCalc(VECTOR move);

	//�v���C���[�ƓG�̓����蔻��
	void HitCheckEnemyToPlayer(CPlayer* player, CEnemy* enemy);
	//�v���C���[�̍U���ƓG�̓����蔻��
	void HitCheckEnemyToPlayerAttack(CPlayer* player, CEnemy* enemy);

protected:
	void HitMap();

protected:
	bool active_;	// �����t���O
	int hp_;			// HP
	int ai_state_;		// AI���
	VECTOR pos_;		// ���W
	VECTOR rot_;		// ��]
	VECTOR move_;		// �ړ���
	VECTOR back_pos_;	// �A�ҍ��W
	float rad_;			// ���a
	int damage;			//�󂯂��_���[�W�i�����HP��������Ă����j

	/*bool is_hit_stonetrap;*/
};
