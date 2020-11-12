//---------------------------------------------------------------------------

#include "RNG.h"

//---------------------------------------------------------------------------

#include <chrono>

//---------------------------------------------------------------------------

namespace RNG {

	// The constractror sets the initial value for the generator
	// A specific initial value can be defined using LCG::seed()
	//
	LCG::LCG()
	{
		using namespace std::chrono;

		z = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch()).count();
	}

//---------------------------------------------------------------------------

	// Returns a random float number from 0 to 1
	//
	double LCG::random()
	{
		z = random_integer();
		return z / (double)m;
	}

//---------------------------------------------------------------------------

	// Returns a random integer number from 0 to MAXINT
	//
	int LCG::randint()
	{
		return random() * INT_MAX;
	}

//---------------------------------------------------------------------------

	// Returns a random integer number from low to high - 1 
	//
	int LCG::randint(int low, int high)
	{
		if (low > high) throw errors::invalid_range;

		return (high - low) * random() + low;
	}

//---------------------------------------------------------------------------

	// Set a specific seed for the generator
	// An initial value is also set by the constractor LCG::LCG()
	//
	void LCG::seed(long long s)
	{
		z = s;
	}

//---------------------------------------------------------------------------

	// Generates the next pseudo-random value and sets the seed for the next one
	//
	long long LCG::random_integer()
	{
		return (a * z + c) % m;
	}

//---------------------------------------------------------------------------

} // of namespace RNG