#pragma once

// A namespace that holds all the generators for random numbers
//
namespace RNG {

	// An enumeration of the possible errors that can be caused
	// using the in namespace RNG
	//
	enum class errors {
		invalid_range
	};

	// Linear Congruential Generator
	class LCG {
	public:
		// Linear Congruential Generator
		LCG();

		// Returns a random number from 0 to 1
		double random();

		// Returns a random integer from 0 to MAXINT - 1
		int randint();

		// Returns a random integer from low to high - 1
		int randint(int low, int high);

		// Sets the seed for the generator
		void seed(long long s);

	private:
		const long long a = 314156269; // the multiplier
		const long long c = 453806243; // the increment
		const long long m = 2147483648; // 2^31 the modulus
		long long z; // start value or the seed

		// Generates the next value for the generator
		long long random_integer(); 

	}; // of class LCG

} // of namespace RNG