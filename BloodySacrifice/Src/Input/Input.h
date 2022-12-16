
#pragma once

//����p�r�b�g
#define KEY_Z		(1 << 0)	// Z�L�[
#define KEY_X		(1 << 1)	// X�L�[
#define KEY_ENTER	(1 << 2)	// ENTER�L�[
#define KEY_UP		(1 << 3)	// ��
#define KEY_DOWN	(1 << 4)	// ��
#define KEY_LEFT	(1 << 5)	// ��
#define KEY_RIGHT	(1 << 6)	// ��
#define KEY_SPACE	(1 << 7)	// SPACE
#define KEY_C		(1 << 8)	// C�L�[
#define KEY_W		(1 << 9)	// W�L�[
#define KEY_S		(1 << 10)	// S�L�[
#define KEY_A		(1 << 11)	// A�L�[
#define KEY_D		(1 << 12)	// D�L�[
#define KEY_LSHIFT	(1 << 13)	// ��SHIFT
#define KEY_RSHIFT	(1 << 14)	// �ESHIFT
#define KEY_J		(1 << 15)	// J�L�[
#define KEY_K		(1 << 16)	// K�L�[
#define KEY_L		(1 << 17)	// L�L�[

class CInput
{
public:

	CInput();
	~CInput();

	//������
	void Init();

	//�X�e�b�v
	//StepInput�͑���Step��葁���Ă�
	void Step();

	//�������ꂽ
	bool IsPush(int key_bit);

	//������Ă���
	bool IsCont(int key_bit);

private:

	int m_nPreKeyState;		//�O��̃L�[���
	int m_nCurrentKeyState;	//����̃L�[���

};

extern CInput g_input;
