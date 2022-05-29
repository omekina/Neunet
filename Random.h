#pragma once
#include <cstdlib>
#include <ctime>


namespace random
{
	void start()
	{
		srand(time(NULL));
	}
	float random()
	{
		int randint = rand() % 200;
		float randfloat = (float(randint) / 100) - 1;
		return randfloat;
	}
}
