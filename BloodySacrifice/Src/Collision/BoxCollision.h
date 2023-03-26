#pragma once
// ボックスの当たり判定（AABB）
#include "DxLib.h"
#include "CollisionBase.h"

class BoxCollision : public CollisionBase {
public:
	BoxCollision();
	virtual ~BoxCollision();

public:
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Fin();
	virtual CollisionBase* Clone() override;

	virtual bool CheckCollision(CollisionBase* another) override;

public:
	VECTOR GetSize() const { return size_; }

	void SetSize(VECTOR size) { size_ = size; }
	void SetSize(float width, float height, float depth) { size_ = VGet(width, height, depth); }

private:
	VECTOR size_;
};
