#include "Totem.h"
#include "../Collision/Collision.h"
#include "../Player/PlayerManager.h"

CTotem g_totem;

CTotem::CTotem()
{
}

CTotem::~CTotem()
{
}

void CTotem::Init(VECTOR pos)
{
	handle_ = MV1LoadModel("Data/Model/Totem/Totem.x");
	pos_ = pos;
	state_ = TOTEM_STATE_NONE;
	hp_ = 5000.0f;
}

void CTotem::Step()
{
	MV1SetPosition(handle_, pos_);
}

void CTotem::Draw()
{
	if (state_ != TOTEM_STATE_OUT)
	{
		MV1DrawModel(handle_);
	}
}

void CTotem::Fin()
{
	MV1DeleteModel(handle_);
}