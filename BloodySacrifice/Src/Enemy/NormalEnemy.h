#pragma once

#include "Enemy.h"
#include "../AI/AIBase.h"

#define EN_ANIM_SPD (1.0f)
#define EN_CHANGE_SPD (0.05f)	//��ԃX�s�[�h

////�A�j���Đ�
//enum {
//	ANIM_MAIN,	//���C���Đ�
//	ANIM_SUB,	//�T�u�Đ�
//
//	BLEND_NUM
//
//};

//�A�j�����
enum EN_ANIM
{
	EN_ATTACK = 0,		//�U��
	EN_DEAD = 1,		//���S
	EN_HIT_BACK = 29,	//�̂�����
	EN_WALK = 30,		//����

	EN_ANIM_NUM = 4,
};

class CNormalEnemy : public CEnemy
{
public:
	CNormalEnemy();
	~CNormalEnemy();

public:
	void Init() override;
	void Load() override;
	void Step() override;
	void Draw() override;
	void Delete() override;
	void Fin() override;
	CEnemy* Clone() override;

	int GetHandle() { return handle_; }


	//�A�j���[�V�������N�G�X�g
	void Request(int animID, float animSpd);
	//�A�j���X�V
	void AnimUpdate();
	//���ݍĐ����Ă���A�j���^�C�v���擾
	inline int GetAnimType() { return m_animType; }

private:
	void StepAI();
	void StepIdle();		//��ԁF����
	void StepCaution();
	void StepAttack();		//��ԁF�U��
	void StepBack();
	void StepHitBack();	//��ԁF�̂�����
	void StepDead();		//��ԁF���S


	// �A�j���Ɋւ���f�[�^
	float	m_animCount[BLEND_NUM];		// ���݂̃A�j���J�E���g
	float	m_animSpeed[BLEND_NUM];		// �A�j���[�V�������x
	int		m_animIdx[BLEND_NUM];		// �A�j���̃C���f�b�N�X�ԍ�
	float	m_animRate;					// �A�j���̃��[�g
	int		m_animType;					// ���ݍĐ����Ă���A�j���^�C�v

//public:
//	void Reset();

private:
	int handle_;
	CAIBase* enemy_ai_;
	float timer_;
	//int posHandle_;		//���W�p�̃��f���n���h��
	//int posID_;			//�t���[���i�{�[���j�̔ԍ�
};
