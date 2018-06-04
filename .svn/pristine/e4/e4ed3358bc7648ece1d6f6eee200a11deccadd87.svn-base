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
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

template<typename Iter, typename Comparator>
void bubbleSort(const Iter& begin, const Iter& end, Comparator compareFn)
{
	for(auto i = begin; i != end; i++)
	{
		for(auto j = begin; j != end - 1; j++)
		{
			if(compareFn(*(j+1),*j))
			{
				std::iter_swap(j + 1, j);
			}
		}
	}
}

template<typename Iter, typename Comparator>
void insertionSort(const Iter& begin, const Iter& end, Comparator compareFn)
{
	for(auto i = begin; i != end; i++)
	{
		auto j = i;
		while(j > begin and compareFn(*j, *(j-1)))
		{
			std::iter_swap(j - 1, j);
			j--;
		}
	}
}

template<typename Iter, typename Comparator>
void radixSort(const Iter& begin, const Iter& end, Comparator compareFn)
{
	auto biggest = *max_element(begin, end); //Find most num with most digits so we know how many times to sort 
	int digits = log10(biggest) + 1;
	int base = 1;
	for(int i = 0; i != digits; i++)
	{
		std::vector<std::vector<int> > bucket; //make bucket 
		bucket.resize(10);
		for(auto j = begin; j != end; j++) //put numbers into buckets
		{
			bucket[*j/base%10].push_back(*j); // num/base%10 = digit at base
		}
		auto num = begin;
		for (int j = 0; j != 10; j++) //take numbers out of buckets
		{
		    int bucketSize = bucket[j].size(); //find size of each bucket to empty
		    for (int k = 0; k < bucketSize; k++) 
		    { 
		        *num = bucket[j].front(); //update to new order
		        bucket[j].erase(bucket[j].begin()); //empty bucket
		        num++;
		    }
		}
		base *= 10; 
	}
}

template<typename Iter>
void quickSort(const Iter& begin, const Iter& end)
{
	if(std::distance(begin, end) > 1)
	{
		auto pivot = partition(begin, end);
		quickSort(begin, pivot - 1);
		quickSort(pivot, end);
	}
}

template<typename Iter>
Iter partition(const Iter& begin, const Iter& end)
{
	auto pivot = *end;
	auto i = begin;
	for(auto j = begin; j != end; j++)
	{
		if(*j < pivot)
		{
			std::iter_swap(j, i);
			i++;
		}
	}
	std::iter_swap(begin, i - 1);
	return i;
}
