// Copyright 2020 Ben Howenstein. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <array>


constexpr auto MaxPrime = 100000;

int FoundPrimes[MaxPrime];

int CountPrimesSlow(const int n)
{
	if (n <= 0)
	{
		return 0;
	}

    int* foundPrimes = FoundPrimes;
    auto numFoundPrimes = 0;

    auto i = 0, j = 0;

    auto numComparisons = 0;
    for (i = 2; i < n; ++i)
    {
        for (j = 2; j < i; ++j)
        {
            ++numComparisons;
            if (i % j == 0)
            {
                break;
            }
        }

        if (i == j)
        {
            foundPrimes[numFoundPrimes++] = i;
        }
    }

    std::cout << "(comparisons: " << numComparisons << ") ";
    return numFoundPrimes + 1;
}

int CountPrimesFast(const int n)
{
    if (n <= 0)
    {
        return 0;
    }

    int* foundPrimes = FoundPrimes;
    foundPrimes[0] = 2;
    auto numFoundPrimes = 1;

    auto numComparisons = 0;
    for (auto testValue = 2; testValue < n; ++testValue)
    {
		auto primeIndex = 0;
		for (; primeIndex < numFoundPrimes; ++primeIndex)
		{
            ++numComparisons;
			if ( testValue % foundPrimes[primeIndex] == 0)
			{
				break;
			}
		}
		if (primeIndex == numFoundPrimes)
		{
			foundPrimes[numFoundPrimes++] = testValue;
		}
    }

    std::cout << "(comparisons:  " << numComparisons << ") ";
    return numFoundPrimes + 1;
}


int main()
{

    auto runTest = [](const int n)
    {
        {
            const auto startTime = std::chrono::high_resolution_clock::now();
            const auto numPrimes = CountPrimesSlow(n);
            const auto endTime = std::chrono::high_resolution_clock::now();
            const auto timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
            std::cout << "(time: " << timeTaken << ") There are " << numPrimes << " primes less than or equal to " << n << "\n";
        }
        {
            const auto startTime = std::chrono::high_resolution_clock::now();
            const auto numPrimes = CountPrimesFast(n);
            const auto endTime = std::chrono::high_resolution_clock::now();
            const auto timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
            std::cout << "(time: " << timeTaken << ") There are " << numPrimes << " primes less than or equal to " << n << "\n";
        }
    };

    runTest(100);
    std::cout << "\n\n";
    runTest(1000);
    std::cout << "\n\n";
    runTest(10000);
    std::cout << "\n\n";
	runTest(100000);
	std::cout << "\n\n";
}
