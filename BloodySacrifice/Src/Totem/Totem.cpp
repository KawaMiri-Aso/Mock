#include "Totem.h"
#include "../Collision/Collision.h"
#include "../Player/PlayerManager.h"

#define DEBUG

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
	MV1SetScale(handle_, VGet(2.0f, 2.0f, 2.0f));
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

#ifdef DEBUG
	DrawFormatString(10, 90, GetColor(255, 128, 0), "トーテムHP：%.f", hp_);
#endif // DEBUG

}

void CTotem::Fin()
{
	MV1DeleteModel(handle_);
}