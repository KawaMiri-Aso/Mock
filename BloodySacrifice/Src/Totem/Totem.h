#include "DxLib.h"

#define TOTEM_W		(26.0f)
#define TOTEM_H		(24.4f)
#define TOTEM_D		(26.0f)
#define TOTEM_RAD	(13.0f)

enum TOTEM_STATE
{
	TOTEM_STATE_NONE,	//�������
	TOTEM_STATE_ACTIVE,	//�A�N�e�B�u���
	TOTEM_STATE_BREAK,	//�󂳂ꂽ���
	TOTEM_STATE_OUT,	//�󂳂�ď��ŏ��
};

class CTotem
{
public:
	CTotem();
	~CTotem();

	void Init(VECTOR pos);
	void Step();
	void Draw();
	void Fin();

	VECTOR GetPos() { return pos_; }
	TOTEM_STATE GetState() { return state_; }
	float GetHp() { return hp_; }

	void Damage(int damage) { hp_ -= damage; }

private:
	int handle_;
	VECTOR pos_;
	TOTEM_STATE state_;
	float hp_;
};

extern CTotem g_totem;