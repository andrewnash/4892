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

#include <libgrading.h>

#include "BST.h"

using namespace grading;
using namespace std;
using namespace std::placeholders;


//! Check that a BST traversal yields expected elements
template<typename T, class Iter, typename Checker, typename Printer>
void CheckTraversal(Iter begin, Iter end, const vector<T> &expected,
                    Checker check, Printer print)
{
	size_t count = 0;
	cout << "Traversal order:";

	for (auto i = begin; i != end; i++)
	{
		print(cout, *i);

		Check(count < expected.size(),
			"traversal has more elements than expected")
			<< "expected " << expected.size()
			<< " elements but have at least " << (count + 1);

		check(expected[count], *i)
			<< "(element " << count << " in traversal)";

		count++;
	}

	cout << "\n";

	CheckInt(expected.size(), count)
		<< "Incorrect number of traversed nodes";
}

// Bind a version of CheckFloat that takes only two arguments
static const auto CheckCloseFloat = std::bind(CheckFloat, _1, _2, 0.001);

// Bind a version of CheckString that takes only two arguments
static const auto CheckExactString = std::bind(CheckString, _1, _2, 0);

// Check that the first letters of two strings match
static CheckResult CheckFirstLetter(char expected, const string &actual)
{
	return CheckInt(expected, actual[0]);
}

template<typename T>
static ostream& Print(ostream &o, const T &value)
{
	return (o << " " << value);
}

static ostream& PrintStringOnNewLine(ostream &o, const string &s)
{
	return (o << "\n - \"" << s << "\"");
}


#if !defined(NO_MONEY)

// An uncopyable, user-defined type with no less-than operator
class Money
{
public:
	Money(Money&& orig)
		: value_(orig.value_)
	{
	}

	int value() const { return value_; }

	static bool lessThan(const Money &a, const Money &b)
	{
		return (a.value_ < b.value_);
	}

private:
	Money(int value)
		: value_(value)
	{
	}

	int value_;

	friend class Purse;
};

struct MoneyComparator
{
	bool operator() (const Money &a, const Money &b)
	{
		return Money::lessThan(a, b);
	}
};

static CheckResult CheckMoney(const Money &expected, const Money &actual)
{
	return CheckInt(expected.value(), actual.value());
}


// A object that holds value which can be disbursed as Money
class Purse
{
public:
	Purse(int value)
		: value_(value)
	{
	}

	Money withdraw(int amount)
	{
		if (amount > value_)
		{
			return Money(0);
		}

		value_ -= amount;
		return Money(amount);
	}

private:
	int value_;
};

#endif // !defined(NO_MONEY)


static const TestSuite tests =
{
	Test("pre-order traversal of integers",
		" - construct an empty BinarySearchTree<int>\n"
		" - insert elements 20, 10, 30, 5, 12, 25, 35, 7, 11\n"
		" - traversal should yield: 20, 10, 5, 7, 12, 11, 30, 25, 35\n"
		,
		[]()
		{
			BinarySearchTree<int> t;
			const auto Order = decltype(t)::Traversal::PreOrder;

			for (int n : { 20, 10, 30, 5, 12, 25, 35, 7, 11 })
			{
				t.insert(n);
			}

			CheckTraversal<int>(t.begin(Order), t.end(),
				{ 20, 10, 5, 7, 12, 11, 30, 25, 35 },
				CheckInt, Print<int>);
		}
	),

	Test("in-order traversal of integers",
		" - construct an empty BinarySearchTree<int>\n"
		" - insert elements 4, 2, 6, 1, 3, 5, 7\n"
		" - traverse in-order: should yield 1, 2, 3, 4, 5, 6, 7\n"
		,
		[]()
		{
			BinarySearchTree<int> t;
			const auto Order = decltype(t)::Traversal::InOrder;

			for (int n : { 4, 2, 6, 1, 3, 5, 7 })
			{
				t.insert(n);
			}

			CheckTraversal<int>(t.begin(Order), t.end(),
				{ 1, 2, 3, 4, 5, 6, 7 }, CheckInt, Print<int>);
		}
	),

	Test("post-order traversal of integers",
		" - construct an empty BinarySearchTree<int>\n"
		" - insert elements 2, 1, 6, 3, 7, 5, 4\n"
		" - traverse post-order: should yield 1, 4, 5, 3, 7, 6, 2\n"
		,
		[]()
		{
			BinarySearchTree<int> t;
			const auto Order = decltype(t)::Traversal::PostOrder;

			for (int n : { 2, 1, 6, 3, 7, 5, 4 })
			{
				t.insert(n);
			}

			CheckTraversal<int>(t.begin(Order), t.end(),
				{ 1, 4, 5, 3, 7, 6, 2 }, CheckInt, Print<int>);
		}
	),

#if !defined(NO_STRINGS)
	Test("pre-order traversal of strings",
		" - construct an empty BinarySearchTree<std::string>\n"
		" - insert elements:\n"
		"    - Painting pink pajamas\n"
		"    - Icabod is itchy\n"
		"    - Four fluffy feathers\n"
		"    - Nine new neckties\n"
		"    - Silly Sammy Slick\n"
		"    - Rosy's going riding on her red rhinoceros\n"
		"    - Young Yolanda Yorgenson\n"
		" - traverse pre-order: should yield P[...], I, F, N, S, R, Y\n"
		,
		[]()
		{
			BinarySearchTree<std::string> t;
			const auto Order = decltype(t)::Traversal::PreOrder;

			for (const char *s : {
				"Painting pink pajamas",
				"Icabod is itchy",
				"Four fluffy feathers",
				"Nine new neckties",
				"Silly Sammy Slick",
				"Rosy's going riding on her red rhinoceros",
				"Young Yolanda Yorgenson",
			})
			{
				t.insert(s);
			}

			CheckTraversal<char>(t.begin(Order), t.end(),
				{ 'P', 'I', 'F', 'N', 'S', 'R', 'Y' },
				CheckFirstLetter, PrintStringOnNewLine);
		}
	),
#endif

	Test("in-order traversal of integers (reverse order)",
		" - construct an empty BinarySearchTree<int, std::greater<int>>\n"
		" - insert elements 4, 2, 6, 1, 3, 5, 7\n"
		" - traverse in-order: should yield 7, 6, 5, 4, 3, 2, 1\n"
		,
		[]()
		{
			BinarySearchTree<int, std::greater<int>> t;
			const auto Order = decltype(t)::Traversal::InOrder;

			for (int n : { 4, 2, 6, 1, 3, 5, 7 })
			{
				t.insert(n);
			}

			CheckTraversal<int>(t.begin(Order), t.end(),
				{ 7, 6, 5, 4, 3, 2, 1 }, CheckInt, Print<int>);
		}
	),

#if !defined(NO_MONEY)
	Test("post-order traversal of Money",
		"A Money object is not copyable (its copy constructor has been\n"
		"deleted) and it has no < operator. We must pass in an explicit\n"
		"comparison function in order to create a BST of Money.\n"
		"\n"
		" - construct an empty BinarySearchTree<Money, MoneyComparator>\n"
		" - insert elements: $42, $18, $7, $29\n"
		" - traverse in post-order: $7, $29, $18, $42\n"
		,
		[]()
		{
			BinarySearchTree<Money, MoneyComparator> t;
			const auto Order = decltype(t)::Traversal::PostOrder;

			Purse p(200);

			t.insert(p.withdraw(42));
			t.insert(p.withdraw(18));
			t.insert(p.withdraw(7));
			t.insert(p.withdraw(29));
		}
	),
#endif
};


int main(int argc, char *argv[])
{
	const TestSuite::Statistics stats = tests.Run(argc, argv);

	if (stats.total > 0)
	{
		cout << endl
			<< "Passed " << stats.passed
			<< "/" << stats.total << " tests\n";

		float grade = 2 + 3 * stats.score;
		cout << endl << "Grade: " << grade << "/5 " << endl;
	}

	return 0;
}
