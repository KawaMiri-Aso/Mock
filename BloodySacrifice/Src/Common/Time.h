#pragma once
#include <random>

#define GAME_FPS 60

class Comn {
public:
	static void Init();
	static void Step();

	static int GetGameDeltaFrame();

	static void InitRandom();
	static int  GetRandom(int min_value, int max_value);
	static float GetRandom(float min_value, float max_value, int digit);

private:
	static int old_time_;
	static int delta_frame_;
	static std::mt19937 mt_;
};
