#pragma once

#include "DxLib.h"
#include "Enemy.h"
#include <assert.h>

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

private:
	int handle_;
};
