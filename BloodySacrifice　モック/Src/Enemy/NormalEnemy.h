#pragma once

#include "DxLib.h"
#include "Enemy.h"

class CNormalEnemy : public CEnemy
{
public:
	CNormalEnemy();
	~CNormalEnemy();

	void Init() override;
	void Init(VECTOR pos, VECTOR rot) override;
	void Load() override;
	void Step() override;
	void Draw() override;
	void Delete() override;
	void Fin()  override;
	CEnemy* Clone() override;

private:
	int handle_;
};
