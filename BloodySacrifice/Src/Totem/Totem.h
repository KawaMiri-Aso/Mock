#include "DxLib.h"

#define TOTEM_W		(13.0f)
#define TOTEM_H		(12.2f)
#define TOTEM_D		(13.0f)
#define TOTEM_RAD	(6.5f)

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

private:
	int handle_;
	VECTOR pos_;
	TOTEM_STATE state_;
	float hp_;
};

extern CTotem g_totem;