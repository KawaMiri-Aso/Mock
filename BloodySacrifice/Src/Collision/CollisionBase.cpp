#include "CollisionBase.h"

CollisionBase::CollisionBase()
{
	shape_ = 0;
	state_ = 0;
	pos_ = { 0.0f };
}

CollisionBase::~CollisionBase()
{
	Fin();
}

void CollisionBase::Init()
{
}

void CollisionBase::Step()
{
	if (player_)
	{
		pos_ = player_->GetPos();
	}
	if (enemy_)
	{
		pos_ = enemy_->GetPos();
	}
}

void CollisionBase::Update()
{
}

void CollisionBase::Draw()
{
}

void CollisionBase::Fin()
{
}
