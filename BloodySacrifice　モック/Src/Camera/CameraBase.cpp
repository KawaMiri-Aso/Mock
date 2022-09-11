#include "CameraBase.h"

CCameraBase::CCameraBase()
{
	pos_ = VGet(0.0f, 0.0f, 0.0f);
	look_ = VGet(0.0f, 0.0f, 0.0f);
	up_ = VGet(0.0f, 1.0f, 0.0f);
}

CCameraBase::~CCameraBase()
{
}

void CCameraBase::Update()
{
	SetCameraPositionAndTargetAndUpVec(pos_, look_, up_);
}