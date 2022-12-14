#include "DxLib.h"
#include "Time.h"
#include <time.h>

using namespace std;

int Comn::old_time_ = 0;
int Comn::delta_frame_ = 0;
mt19937 Comn::mt_;

void Comn::Init()
{
	old_time_ = GetNowCount();
}

void Comn::Step()
{
	int now_time = GetNowCount();
	delta_frame_ = (now_time - old_time_) / (1000 / GAME_FPS);

	old_time_ = now_time;
}

// �f���^�t���[���擾�i1���[�v�Ɋ|���������Ԃ�FPS��ŉ��t���[���|����������Ԃ��j
int Comn::GetGameDeltaFrame()
{
#ifdef _DEBUG
	// �f�o�b�O���͕K���P�i�u���[�N���ɂ��Q�[�����i�ނ��߁j
	return 1;
#else
	return delta_frame_;
#endif
}

void Comn::InitRandom()
{
	// �����V�[�h�ݒ�
	random_device rand;
	mt_.seed(rand());
}

// �����擾
int Comn::GetRandom(int min_value, int max_value)
{
	int range = max_value - min_value + 1;
	return (mt_() % range) + min_value;
}

// �����_��5�ʂ܂ł̗���
float Comn::GetRandom(float min_value, float max_value, int digit)
{
	int coe = 1;
	for (int i = 0; i < digit - 1; i++) {
		coe *= 10;
	}

	float min = (min_value) * coe;
	float max = (max_value) * coe;
	int range = static_cast<int>(max - min);

	// �����_���͈͂������ꍇ�͍ŏ��l��Ԃ�
	if (range == 0) return min;

	return ((mt_() % range) + min) / coe;
}