#include <iostream>
#include <iomanip>  // std::setprecision(x)
#include <fstream>
#include <vector>

#include "RNG.h"

int main()
{
	int runTest = 0;
	std::vector<int> runTests(10);
	std::vector<int> areaTests(10);

	double n100average = 0.0;
	double n1000000average = 0.0;
	std::vector<double> randoms(1000000);

	RNG::LCG lcg;


	lcg.seed(33);

	std::ofstream rn{ "100randoms.txt" };
	for (int i = 0; i < 1000000; ++i) {
		double r = lcg.random(); // Getting the next random...
		randoms[i] = r;			 // ...and saving it


		// The firsts 100 numbers save them in a file and calculate average
		if (i < 100) {
			rn << std::setprecision(10) << r << '\n';
			n100average += r;
		}
		n1000000average += r; // Average for the first 1.000.000 numbers


		// Calculate how many times the random number was over and under 0.5
		// Save how many consecutive times that happened
		if (runTest >= 0 && r >= 0.5) ++runTest;
		else if (runTest <= 0 && r < 0.5) --runTest;
		else if (runTest > 0 && r < 0.5) {
			if (runTest > 10) runTest = 10;
			++runTests[runTest - 1];
			runTest = 1;
		}
		else if (runTest < 0 && r >= 0.5) {
			if (runTest < -10) runTest = -10;
			++runTests[-runTest - 1];
			runTest = -1;
		}


		// Calculate how many times the random number
		// is between 0.0-0.099.., 0.1-0.199.., ...
		++areaTests[(int)(r * 10)];
	}
	rn.close();						// 100numbers.txt
	n100average /= 100;				// Calculate the final average
	n1000000average /= 1000000;		// Calculate the final average


	// Calculate the standard deviation for the first 100 numbers
	// and the first 1.000.000 numbers respectively
	double sd100 = 0.0, sd1000000 = 0.0;
	for (int i = 0; i < 1000000; ++i) {
		if (i < 100) sd100 += pow(n100average - randoms[i], 2);
		sd1000000 += pow(n1000000average - randoms[i], 2);
	}
	sd100 = sqrt(sd100 / 100);
	sd1000000 = sqrt(sd1000000 / 1000000);


	// Writing the results in file results.txt
	std::ofstream res{ "results.txt" };

	res << "Average(100): " << n100average << '\n';
	res << "Standard deviation(100): " << sd100 << '\n';

	res << "Average(1000000): " << n1000000average << '\n';
	res << "Standard deviation(1000000): " << sd1000000 << '\n';

	res << "Run Tests: ";
	for (int i = 0; i < 10; ++i)
		res << runTests[i] << ' ';
	res << '\n';

	res << "Area Tests: ";
	for (int i = 0; i < 10; ++i)
		res << areaTests[i] << ' ';
	res << '\n';

	res.close(); // results.txt
}