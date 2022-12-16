
#pragma once

//判定用ビット
#define KEY_Z		(1 << 0)	// Zキー
#define KEY_X		(1 << 1)	// Xキー
#define KEY_ENTER	(1 << 2)	// ENTERキー
#define KEY_UP		(1 << 3)	// ↑
#define KEY_DOWN	(1 << 4)	// ↓
#define KEY_LEFT	(1 << 5)	// ←
#define KEY_RIGHT	(1 << 6)	// →
#define KEY_SPACE	(1 << 7)	// SPACE
#define KEY_C		(1 << 8)	// Cキー
#define KEY_W		(1 << 9)	// Wキー
#define KEY_S		(1 << 10)	// Sキー
#define KEY_A		(1 << 11)	// Aキー
#define KEY_D		(1 << 12)	// Dキー
#define KEY_LSHIFT	(1 << 13)	// 左SHIFT
#define KEY_RSHIFT	(1 << 14)	// 右SHIFT
#define KEY_J		(1 << 15)	// Jキー
#define KEY_K		(1 << 16)	// Kキー
#define KEY_L		(1 << 17)	// Lキー

class CInput
{
public:

	CInput();
	~CInput();

	//初期化
	void Init();

	//ステップ
	//StepInputは他のStepより早く呼ぶ
	void Step();

	//今押された
	bool IsPush(int key_bit);

	//押されている
	bool IsCont(int key_bit);

private:

	int m_nPreKeyState;		//前回のキー状態
	int m_nCurrentKeyState;	//今回のキー状態

};

extern CInput g_input;
