#include "NormalEnemy.h"
#include "../Common.h"
#include "../Player/PlayerManager.h"
#include "../MyMath/MyMath.h"

namespace {
	int NORMAL_ENEMY_HP = 10;
	float NORMAL_ENEMY_RAD = 10.0f;
}


CNormalEnemy::CNormalEnemy() : CEnemy()
{
	handle_ = 0;
}

CNormalEnemy::~CNormalEnemy()
{
	Fin();
}

void CNormalEnemy::Init()
{
	is_active_ = true;
	hp_ = NORMAL_ENEMY_HP;
	rad_ = NORMAL_ENEMY_RAD;
}

void CNormalEnemy::Load()
{
	handle_ = MV1LoadModel("Data/Model/Enemy/enemy-mock.x");
}

void CNormalEnemy::Step()
{
	//��ɏd�͂�������
	move_.y -= GRAVITY;
	//�ړ�����
	pos_ = MyMath::VecAdd(pos_, move_);

	//�}�b�v�Ƃ̓����蔻��
	HitMap();

	MV1SetRotationXYZ(handle_, rot_);
	MV1SetPosition(handle_, pos_);
}

void CNormalEnemy::Draw()
{
	MV1DrawModel(handle_);
}

void CNormalEnemy::Delete()
{
	MV1DeleteModel(handle_);
}

void CNormalEnemy::Fin()
{
	Delete();
}

CEnemy* CNormalEnemy::Clone()
{
	CNormalEnemy* clone =  new CNormalEnemy;
	*clone = *this;
	clone->handle_ = MV1DuplicateModel(handle_);
	return clone;
}