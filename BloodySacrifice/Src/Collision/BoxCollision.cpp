#include "BoxCollision.h"

BoxCollision::BoxCollision() : CollisionBase()
{
	shape_ = COLLISION_SHAPE_BOX;
	size_ = { 0.0f };
}

BoxCollision::~BoxCollision()
{
	Fin();
}

void BoxCollision::Init()
{
}

void BoxCollision::Update()
{
}

void BoxCollision::Draw()
{
#ifdef	_DEBUG
	// 当たり判定の可視化
	VECTOR posA = VGet(pos_.x - size_.x / 2.0f, pos_.y - size_.y / 2.0f, pos_.z - size_.z / 2.0f);
	VECTOR posB = VGet(pos_.x + size_.x / 2.0f, pos_.y + size_.y / 2.0f, pos_.z + size_.z / 2.0f);

	DrawCube3D(posA, posB, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);
#endif
}

void BoxCollision::Fin()
{
}

CollisionBase* BoxCollision::Clone()
{
	CollisionBase* clone = new BoxCollision;
	*clone = *this;
	return clone;
}

bool BoxCollision::CheckCollision(CollisionBase* another)
{
	// 現状、ボックス同士の当たり判定しかとらない
	if (another->GetShape() != COLLISION_SHAPE_BOX) {
		return false;
	}

	BoxCollision* another_box = static_cast<BoxCollision*>(another);
	VECTOR another_size = another_box->GetSize();

	float w1_half = (size_.x / 2);		//対象Aの横幅の半分（中心から端までの長さ）
	float h1_half = (size_.y / 2);		//対象Aの高さの半分（中心から端までの長さ）
	float d1_half = (size_.z / 2);		//対象Aの奥行きの半分（中心から端までの長さ）

	float x1min = pos_.x - w1_half;	//対象Aの最小X
	float x1max = pos_.x + w1_half;	//対象Aの最大X
	float y1min = pos_.y - h1_half;	//対象Aの最小Y
	float y1max = pos_.y + h1_half;	//対象Aの最大Y
	float z1min = pos_.z - d1_half;	//対象Aの最小Z
	float z1max = pos_.z + d1_half;	//対象Aの最大Z

	float w2_half = (another_size.x / 2);		//対象Bの横幅の半分（中心から端までの長さ）
	float h2_half = (another_size.y / 2);		//対象Bの高さの半分（中心から端までの長さ）
	float d2_half = (another_size.z / 2);		//対象Bの奥行きの半分（中心から端までの長さ）

	float x2min = another_box->pos_.x - w2_half;		//対象Bの最小X
	float x2max = another_box->pos_.x + w2_half;		//対象Bの最大X
	float y2min = another_box->pos_.y - h2_half;		//対象Bの最小Y
	float y2max = another_box->pos_.y + h2_half;		//対象Bの最大Y
	float z2min = another_box->pos_.z - d2_half;		//対象Bの最小Z
	float z2max = another_box->pos_.z + d2_half;		//対象Bの最大Z

	if (x1min < x2max && x1max > x2min &&
		y1min < y2max && y1max > y2min &&
		z1min < z2max && z1max > z2min)
		return true;

	return false;
}
