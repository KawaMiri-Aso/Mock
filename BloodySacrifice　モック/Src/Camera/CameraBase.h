#pragma once

#include "DxLib.h"

class CCameraBase {
public:
	CCameraBase();
	~CCameraBase();

public:
	virtual void Init() = 0;
	virtual void Step() = 0;
	void Update();
	virtual void Draw() = 0;
	virtual void Fin() = 0;

	VECTOR GetPos() const { return pos_; }
	VECTOR GetLook() const { return look_; }

	void SetPos(VECTOR pos) { pos_ = pos; }
	void SetLook(VECTOR look) { look_ = look; }

protected:
	VECTOR pos_;
	VECTOR look_;
	VECTOR up_;
};
