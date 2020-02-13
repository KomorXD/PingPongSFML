#include "Random.hpp"

#include <ctime>

Random::Random() {
	m_Gen.seed(static_cast<unsigned int>(std::time(0)));
}

int Random::IntInRange(int left, int right) {
	std::uniform_int_distribution<int> dist(left, right);

	return dist(m_Gen);
}

float Random::FloatInRange(float left, float right) {
	std::uniform_real_distribution<float> dist(left, right);

	return dist(m_Gen);
}

Random& Random::Get() {
	// Return always the same instance of the class
	static Random instance;

	return instance;
}
