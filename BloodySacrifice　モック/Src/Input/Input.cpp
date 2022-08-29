
#include "DxLib.h"
#include "Input.h"

CInput g_input;

CInput::CInput()
{
}

CInput::~CInput()
{
	m_nPreKeyState = 0;
	m_nCurrentKeyState = 0;
}

//初期化
void CInput::Init()
{
	m_nPreKeyState = 0;
	m_nCurrentKeyState = 0;
}

//ステップ
	//StepInputは他のStepより早く呼ぶ
void CInput::Step()
{
	//前回のキー状態を保存
	m_nPreKeyState = m_nCurrentKeyState;

	//今回のキー状態を判定前にfalseに
	m_nCurrentKeyState = 0;

	//必要なキーは以下に判定を書く

	if(CheckHitKey(KEY_INPUT_Z) == 1)
		m_nCurrentKeyState |= KEY_Z;

	if(CheckHitKey(KEY_INPUT_X) == 1)
		m_nCurrentKeyState |= KEY_X;

	if(CheckHitKey(KEY_INPUT_C) == 1)
		m_nCurrentKeyState |= KEY_C;

	if(CheckHitKey(KEY_INPUT_RETURN) == 1)
		m_nCurrentKeyState |= KEY_ENTER;

	if(CheckHitKey(KEY_INPUT_UP) == 1)
		m_nCurrentKeyState |= KEY_UP;

	if(CheckHitKey(KEY_INPUT_DOWN) == 1)
		m_nCurrentKeyState |= KEY_DOWN;

	if(CheckHitKey(KEY_INPUT_LEFT) == 1)
		m_nCurrentKeyState |= KEY_LEFT;

	if(CheckHitKey(KEY_INPUT_RIGHT) == 1)
		m_nCurrentKeyState |= KEY_RIGHT;

	if(CheckHitKey(KEY_INPUT_SPACE) == 1)
		m_nCurrentKeyState |= KEY_SPACE;

	if(CheckHitKey(KEY_INPUT_W) == 1)
		m_nCurrentKeyState |= KEY_W;

	if(CheckHitKey(KEY_INPUT_S) == 1)
		m_nCurrentKeyState |= KEY_S;

	if(CheckHitKey(KEY_INPUT_A) == 1)
		m_nCurrentKeyState |= KEY_A;

	if(CheckHitKey(KEY_INPUT_D) == 1)
		m_nCurrentKeyState |= KEY_D;

	if(CheckHitKey(KEY_INPUT_LSHIFT) == 1)
		m_nCurrentKeyState |= KEY_LSHIFT;

	if(CheckHitKey(KEY_INPUT_RSHIFT) == 1)
		m_nCurrentKeyState |= KEY_RSHIFT;
}

//今押された
bool CInput::IsPush(int key_bit)
{
	if((m_nCurrentKeyState & key_bit) && (m_nPreKeyState & key_bit) == false)
		return true;

	return false;
}

//押されている
bool CInput::IsCont(int key_bit)
{
	if(m_nCurrentKeyState & key_bit)
		return true;

	return false;
}

