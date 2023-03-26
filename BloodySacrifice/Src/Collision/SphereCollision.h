#pragma once

#include "CollisionBase.h"

class SphereCollision : public CollisionBase {
public:
	SphereCollision();
	virtual ~SphereCollision();

public:
	void Init();
	void Update();
	virtual void Draw() override;
	void Fin();
	virtual CollisionBase* Clone() override;

	virtual bool CheckCollision(CollisionBase* another) override;

public:
	void SetRadius(float radius) { radius_ = radius; }

	float GetRadius() const { return radius_; }

private:
	float radius_;
};
