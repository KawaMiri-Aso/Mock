#include "SphereCollision.h"

SphereCollision::SphereCollision() : CollisionBase()
{
	shape_ = COLLISION_SHAPE_SPHERE;
	radius_ = 0.0f;
}

SphereCollision::~SphereCollision()
{
	Fin();
}

void SphereCollision::Init()
{
}

void SphereCollision::Update()
{
}

void SphereCollision::Draw()
{
#ifdef _DEBUG
	// “–‚½‚è”»’è‰ÂŽ‹‰»
	DrawSphere3D(pos_, radius_, 16, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);
#endif
}

void SphereCollision::Fin()
{
}

CollisionBase* SphereCollision::Clone()
{
	CollisionBase* clone = new SphereCollision;
	*clone = *this;
	return clone;
}

bool SphereCollision::CheckCollision(CollisionBase* another)
{
	// Œ»óA‹…“¯Žm‚Ì“–‚½‚è”»’è‚µ‚©‚Æ‚ç‚È‚¢
	if (another->GetShape() != COLLISION_SHAPE_SPHERE) {
		return false;
	}

	SphereCollision* another_collision = static_cast<SphereCollision*>(another);
	VECTOR another_pos = another->GetPos();
	float another_radius = another_collision->GetRadius();

	if ((pos_.x - another_pos.x) * (pos_.x - another_pos.x) +
		(pos_.y - another_pos.y) * (pos_.y - another_pos.y) +
		(pos_.z - another_pos.z) * (pos_.z - another_pos.z) <=
		(radius_ + another_radius) * (radius_ + another_radius)) {
		return true;
	}

	return false;
}
