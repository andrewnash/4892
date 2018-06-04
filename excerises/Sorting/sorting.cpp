/*
 * Copyright 2018 Jonathan Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "sorting.h"

using namespace std;


template<typename T>
ostream& operator << (ostream& o, const vector<T>& v)
{
	o << "[";
	for (const auto& x : v)
	{
		o << " " << x;
	}
	o << " ]";

	return o;
}


int main()
{
	vector<int> numbers = { 19, 82224, 42, 234, 91, 14, 83 ,85, 86, 89, 1, 22222222, 54 };
	cout << "Start vec: " << numbers << "\n";
	quickSort(numbers.begin(), numbers.end());  //, std::less<int>())
	cout << "Sorted: " << numbers << "\n";

	// vector<string> names = { "Alice", "Joe", "Eve", "Bob" };
	// cout << "Start vec: " << names << "\n";
	// bubbleSort(names.begin(), names.end(), std::less<string>());
	// cout << "Sorted: " << names << "\n";

	// vector<unique_ptr<string>> uniqueNames;
	// uniqueNames.emplace_back(new string("Beorn"));
	// uniqueNames.emplace_back(new string("Aiken"));
	// // uniqueNames.emplace_back(new string("Jesus"));
	// // uniqueNames.emplace_back(new string("Zebra"));
	// // uniqueNames.emplace_back(new string("Nathan"));
	// // uniqueNames.emplace_back(new string("Martha"));

	// insertionSort(uniqueNames.begin(), uniqueNames.end(),
	// 	//
	// 	// std::less<unique_ptr<string>>() will end up comparing pointer
	// 	// values rather than string characters, so let's implement our
	// 	// own comparison function:
	// 	//
	// 	[](const unique_ptr<string> &a, const unique_ptr<string>& b)
	// 	{
	// 		return (*a < *b);
	// 	});

	// cout << "Sorted:\n";
	// for (const auto &s : uniqueNames)
	// {
	// 	cout << " - " << *s << "\n";
	// }

	// return 0;
}
