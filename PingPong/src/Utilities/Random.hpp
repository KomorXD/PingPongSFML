#pragma once

#include <random>

class Random {
	private:
		std::minstd_rand m_Gen;

		Random();
	public:
		int IntInRange(int left, int right);
		float FloatInRange(float left, float right);

		static Random& Get();
};