#include "Enemy.h"
#include "../Map/Map.h"
#include "../Common.h"
#include "../MyMath/MyMath.h"

CEnemy::CEnemy()
{
	active_ = false;
	hp_ = 0;
	pos_ = { 0 };
	rot_ = { 0 };
	move_ = { 0 };
	rad_ = 0.0f;
	/*is_hit_stonetrap = false;*/
}

CEnemy::~CEnemy()
{
}

void CEnemy::HitMap()
{
	VECTOR vVec;
	vVec = g_map.HitCheck(pos_, rad_);
	if (vVec.y > 0)
	{
		move_.y = 0.0f;
	}
	pos_ = VAdd(pos_, vVec);
}

void CEnemy::Dead()
{
	active_ = false;
}

//���݈ʒu�ɍ��W���Z
void CEnemy::ReflectCollision(VECTOR addVec)
{
	// �I�[���[���Ȃ牽�����Ȃ�
	if (addVec.x == 0.0f && addVec.y == 0.0f && addVec.z == 0.0f) return;

	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR	pos = player->GetPos();
	pos = VAdd(pos, addVec);
	//m_gravity = 0.0f;
	SetPos(pos);
}

//�v���C���[�̍U�����q�b�g������̏���
void CEnemy::HitCalc(VECTOR move)
{
	move_ = move;
	
}

////�v���C���[�ƓG�̓����蔻��
//bool CEnemy::HitCheckEnemyToPlayer(CPlayer* player, CEnemy* enemy)
//{
//	VECTOR plPos = player->GetPos();
//	VECTOR enPos = GetPos();
//
//	//�Q�_�Ԃ̋������擾
//	VECTOR vec = VSub(enPos, plPos);
//	float len = VSize(vec);
//
//	//���͈͂��Z����΃q�b�g
//	if (len < 10.0f)
//	{
//		//�G�������Ԃ�
//		vec = VNorm(vec);
//		vec = VScale(vec, 10.0f - len);
//		ReflectCollision(vec);
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
////�v���C���[�̍U���ƓG�̓����蔻��
//bool CEnemy::HitCheckEnemyToPlayerAttack(CPlayer* player, CEnemy* enemy)
//{
//	//�U�����łȂ���ΏI��
//	if (!player->IsAttack())
//	{
//		return false;
//	}
//
//	//�G�̍��W�ƃv���C���[�̍U���������W���擾
//	VECTOR plAttackPos = player->GetAttackPos();
//	VECTOR enPos = GetPos();
//
//	//2�_�Ԃ̋������擾
//	VECTOR vec = MyMath::VecSubtract(enPos, plAttackPos);
//	float len = VSize(vec);
//
//	//���͈͂��Z����΃q�b�g
//	if (len < 50.0f)
//	{
//		//vec = MyMath::VecNormalize(vec);
//		//vec.y = 5.0f;						//������ɔ�΂���
//		//vec = MyMath::VecScale(vec, 3.0f);	//�S�̂̐�����΂���
//
//		////�G�ɐ�����ԕ�����^����
//		//HitCalc(vec);
//
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

void CEnemy::OnPlCollisionEnter(CPlayer* another)
{

}