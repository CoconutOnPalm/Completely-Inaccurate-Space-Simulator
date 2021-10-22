#include "RandomGenerator.hpp"

namespace ke
{

	Random::Random()
	{

	}


	Random& Random::Get()
	{
		static Random instance;
		return instance;
	}


	void Random::getnerateSeed(unsigned int seed)
	{
		srand(seed);
		Get().m_seed = seed;
	}



	////////////////////////////////////////////////////////////////



	void Random::geterateRandomSeed()
	{
		Get().m_seed = static_cast<unsigned int>(std::time(nullptr));
		srand(Get().m_seed);
	}


	void Random::setSeed(unsigned int seed)
	{
		Get().m_seed = seed;
		srand(seed);
	}


	unsigned int Random::getSeed()
	{
		return Get().m_seed;
	}



	////////////////////////////////////////////////////////////////



	bool Random::Chance(float prc)
	{
		return Float(0.0f, 100.0f) < prc;
	}



	////////////////



	int Random::Int(int min, int max)
	{
		return rand() % (max - min + 1) + min;
	}



	////////////////



	float Random::Float(float min, float max)
	{
		return ((max - min) * ((static_cast<float>(rand()) / RAND_MAX))) + min;
	}



	////////////////



	double Random::Double(double min, double max)
	{
		return ((max - min) * ((static_cast<double>(rand()) / RAND_MAX))) + min;
	}



	////////////////



	char Random::Char(char min, char max)
	{
		return Int(static_cast<int>(min), static_cast<int>(max));
	}



	////////////////////////////////



	int Random::Unique(int min, int max)
	{
		if (min == max && min == Get().m_last) return min;

		int rv; // return value

		do {
			rv = Int(min, max);
		} while (rv == Get().m_last);

		Get().m_last = rv;
		return rv;
	}

} // namespace ke