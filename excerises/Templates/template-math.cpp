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

#include <iostream>
#include "templates.h"
using namespace std;


int main()
{
	long x = 1, y = 1;
	vector<long> z = { 1, 2, 3, 4 };
	cout << "x + y = " << add(x, y) << "\n";
	cout << "The average is " << average(z) << endl << endl;

	GrowableArray<int> a;
	a << 5.0;
	a << 12.0;
	a << 3.0;
	a << 9.0;
	a << 1.0;

	cout << a[0] << endl;
	
	return 0;
}
