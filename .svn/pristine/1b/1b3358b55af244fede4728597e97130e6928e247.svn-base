#include <chrono>
#include <cstdlib>
#include <functional>
#include <iostream>
#include "windows.h"
using namespace std;


/**
 * Time the execution of a factorial function.
 *
 * Students using g++ on Windows should modify this function as shown in
 * https://www.engr.mun.ca/~anderson/teaching/4892/exercises/0-intarray/windows-time.
 */
void timeFactorialFunction(std::function<long (int)>, int n);


//! Calculate the factorial of a number, recursively.
long recursive(int n);

//! Calculate the factorial of a number, iteratively.
long iterative(int n);


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cerr << "Usage:  " << argv[0] << " <n>\n";
		return 1;
	}

	char *end;
	int n = strtol(argv[1], &end, 10);
	if (*end != '\0')
	{
		cerr << "Invalid value of n: '" << argv[1] << "'\n";
		return 1;
	}

	cout << "Recursive: ";
	timeFactorialFunction(recursive, n);

	cout << "Iterative: ";
	timeFactorialFunction(iterative, n);

	return 0;
}


void timeFactorialFunction(std::function<long (int)> f, int n)
{
	long result;
	LARGE_INTEGER start, end;

	QueryPerformanceCounter(&start);
	result = f(n);
	QueryPerformanceCounter(&end);

	// cout << "Calculated " << n << "! = " << result << " the difference: " << (end.QuadPart - start.QuadPart) << "\n";
	
	// auto start = chrono::high_resolution_clock::now();
	// result = f(n);
	// auto end = chrono::high_resolution_clock::now();

	cout << "Calculated " << n << "! = " << result
		<< " in " << (end.QuadPart - start.QuadPart) << " ns\n";
}

long recursive(int n)
{
	if(n >= 1)
	{
		return n*recursive(n-1);
	}
}

long iterative(int n)
{
	auto answer = 1; 
	for(int i = 1; i < n+1; i++)
	{
		answer = answer*i;
	}
	return answer;
}