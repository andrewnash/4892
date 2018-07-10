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

#include "List.h"

using namespace grading;
using namespace std;
using namespace std::placeholders;


//! Check that a List<T> contains expected elements (in order)
template<typename T, typename Checker>
void CheckList(List<T> &l, string name, const vector<T> &expected,
               Checker check)
{
	CheckInt(expected.size(), l.size()) << "Incorrect list size";

	size_t count = 0;
	auto i = l.begin();

	while (i != l.end())
	{
		check(expected[count], *i)
			<< "(element @ position " << count << " in list '" << name << "')\n"
			;

		count++;
		i++;
	}

	CheckInt(expected.size(), count)
		<< "Incorrect number of iterations from list's begin() to end()";
}

// Bind a version of CheckFloat that takes only two arguments
static const auto CheckCloseFloat = std::bind(CheckFloat, _1, _2, 0.001);

// Bind a version of CheckString that takes only two arguments
static const auto CheckExactString = std::bind(CheckString, _1, _2, 0);


static const TestSuite tests =
{
	Test("empty List<int> instantiation",
		"Construct an empty List<int> using the default constructor"
		,
		[]()
		{
			List<int> l;
		}
	),

	Test("empty List<string> instantiation",
		"Construct an empty List<string> using the default constructor"
		,
		[]()
		{
			List<string> l;
		}
	),

	Test("push a few elements into a List<int>",
		" - construct an empty List<int>\n"
		" - push elements 5, 4, 3, 2 and 1 into it\n"
		,
		[]()
		{
			List<int> l;
			for (int i = 5; i > 0; i--)
			{
				l.push_back(i);
			}
		}
	),

	Test("push a few elements into a List<string>",
		" - construct an empty List<string>\n"
		" - push elements \"Hello\", \", \" and \"world!\\n\" into it\n"
		" - the size should be 3\n"
		,
		[]()
		{
			List<string> l;
			for (string s : { "Hello", ", ", "world!\n" })
			{
				l.push_back(s);
			}

			CheckInt(3, l.size())
				<< "There should now be three elements"
				   " in the list";
		}
	),

	Test("push_front() and iteration",
		" - construct an empty List<int>\n"
		" - push elements 4, 3, 2, 1, 0 to the front\n"
		" - iterating from begin-end should come out backwards\n"
		,
		[]()
		{
			List<int> numbers;
			for (int i : { 4, 3, 2, 1, 0 })
			{
				numbers.push_front(i);
			}

			CheckList(numbers, "l", { 0, 1, 2, 3, 4 }, CheckInt);
		}
	),

	Test("push_back() and iteration",
		" - construct an empty List<int>\n"
		" - push elements 1020, 3891, 4892, 5895, 8894 into the back\n"
		" - iterating from begin-end should yield the same order\n"
		,
		[]()
		{
			const vector<int> testValues = {
				1020, 3891, 4892, 5895, 8894
			};

			List<int> courses;
			for (int i : testValues)
			{
				courses.push_back(i);
			}

			CheckList(courses, "courses", testValues, CheckInt);
		}
	),

	Test("insert at beginning",
		" - construct a List<double>, push_back { 1.1, 2.2 }\n"
		" - insert 3.3 at list.begin()\n"
		" - result should be 3.3, 1.1, 2.2\n"
		,
		[]()
		{
			List<double> l;
			l.push_back(1.1);
			l.push_back(2.2);

			l.insert(l.begin(), 3.3);

			CheckList(l, "l", { 3.3, 1.1, 2.2 }, CheckCloseFloat);
		}
	),

	Test("insert in the middle",
		" - construct a List<double>, push_back { 1.1, 2.2 }\n"
		" - insert 3.3 at ++list.begin()\n"
		" - result should be 1.1, 3.3, 2.2\n"
		,
		[]()
		{
			List<double> l;
			l.push_back(1.1);
			l.push_back(2.2);

			l.insert(++l.begin(), 3.3);

			CheckList(l, "l", { 1.1, 3.3, 2.2 }, CheckCloseFloat);
		}
	),

	Test("insert at the end",
		" - construct a List<double>, push_back { 1.1, 2.2 }\n"
		" - insert 3.3 at list.end()\n"
		" - result should be 1.1, 2.2, 3.3\n"
		,
		[]()
		{
			List<double> l;
			l.push_back(1.1);
			l.push_back(2.2);

			l.insert(l.end(), 3.3);

			CheckList(l, "l", { 1.1, 2.2, 3.3 }, CheckCloseFloat);
		}
	),

	Test("explicit iterators",
		" - construct List<int> with elements { 0, 1, 2, 3 }\n"
		" - get an iterator from the begin() method\n"
		" - ensure that begin() != end()\n"
		" - check each element using pre- and post-increments\n"
		,
		[]()
		{
			List<int> l;
			l.push_back(0);
			l.push_back(1);
			l.push_back(2);
			l.push_back(3);

			List<int>::iterator i = l.begin();

			Check(i != l.end(), "begin() should not equal end()");

			CheckInt(0, *i++) << "first element should be 0";
			CheckInt(1, *i) << "second element should be 1";
			CheckInt(2, *(++i)) << "third element should be 2";
			CheckInt(2, *i) << "third element should (still) be 2";
			i++;
			CheckInt(3, *i) << "fourth element should be 3";

			i++;

			Check(i == l.end(), "i should == end after iteration");
		}
	),

	Test("copy construction",
		" - construct List<double> with element 3.14, 1.41, 0\n"
		" - copy-construct another List<double>\n"
		" - iterating over new list should yield correct elements\n"
		,
		[]()
		{
			const vector<double> testValues = {
				3.14, 1.41, 0
			};

			List<double> l;
			for (double v : testValues)
			{
				l.push_back(v);
			}

			List<double> copy(l);

			Check(l.begin() != copy.begin(),
			      "Iterators from l and copy should not be equal");

			CheckList(l, "l", { 3.14, 1.41, 0 }, CheckCloseFloat);
		}
	),

	Test("move construction",
		" - construct List<string> with elements 'a' and 'b'\n"
		" - construct another List<double> using move semantics\n"
		" - the old list should be empty\n"
		" - iterating over the new list should yield 'a' and 'b'\n"
		,
		[]()
		{
			const vector<string> testValues = { "a", "b" };

			List<string> orig;
			for (string v : testValues)
			{
				orig.push_back(v);
			}

			List<string> thief = std::move(orig);

			Check(orig.empty(), "the old list should now be empty")
				<< "After its contents have been std::move'd"
				<< " out, the old list should be empty";

			Check(orig.begin() != thief.begin(),
			      "Iterators from orig and thief should not be equal");

			CheckList(thief, "thief", { "a", "b" }, CheckExactString);
		}
	),

	Test("copy assignment",
		" - construct List<const char*> l1 with \"hi\", \"there\"\n"
		" - construct an empty List<const char*> l2\n"
		" - assign l1 into l2\n"
		" - iterating over both lists should yield \"hi\", \"there\"\n"
		,
		[]()
		{
			const char *strings[] = { "hi", "there" };
			constexpr size_t N = sizeof(strings) / sizeof(*strings);

			List<const char*> orig, copy;
			for (size_t i = 0; i < N; i++)
			{
				orig.push_back(strings[i]);
			}

			copy = orig;

			Check(orig.begin() != copy.begin(),
			      "Iterators from orig and copy should not be equal");

			CheckList(orig, "orig", vector<const char*>(strings, strings + N),
			          CheckExactString);
			CheckList(copy, "copy", vector<const char*>(strings, strings + N),
			          CheckExactString);
		}
	),

	Test("move assignment",
		" - construct List<int> with element 9\n"
		" - construct an empty List<int> l2\n"
		" - assign std::move(l1) into l2\n"
		" - the old list should be empty\n"
		" - iterating over the new list should yield 9\n"
		,
		[]()
		{
			List<int> l1, l2;
			l1.push_back(9);

			l2 = std::move(l1);

			CheckInt(1, l2.size())
				<< "There should be one number in l2,"
				   " not " << l2.size();

			Check(l1.empty(), "the old list should now be empty")
				<< "Post-move, l1 should be empty";

			auto i = l2.begin();
			CheckInt(9, *i)
				<< "The (only) element in l2 should be 9";
		}
	),

	Test("const iterators",
		" - construct List<double> with elements { 1.1, 2.2, 3.3 }\n"
		" - copy list into a const list\n"
		" - get a const_iterator from the begin() method\n"
		" - ensure that begin() != end()\n"
		" - check each element using pre- and post-increments\n"
		,
		[]()
		{
			List<double> l1;
			l1.push_back(1.1);
			l1.push_back(2.2);
			l1.push_back(3.3);

			const List<double> l2 = l1;

			List<double>::const_iterator i = l2.begin();

			Check(i != l2.end(), "begin() should not equal end()");

			CheckFloat(1.1, *i++)
				<< "The first element should be 1.1, not "
				<< *i;

			CheckFloat(2.2, *i)
				<< "The second element should be 2.2, not "
				<< *i;

			CheckFloat(3.3, *(++i))
				<< "The third element should be 3.3, not "
				<< *i;
		}
	),

	Test("explicit erase()",
		" - construct List<int> with elements { 2, 4, 6, 8, 10 }\n"
		" - get an iterator from begin(); advance with ++i\n"
		" - call erase(i++)\n"
		" - result should be { 2, 6, 8, 10 }\n"
		,
		[]()
		{
			List<int> l;
			l.push_back(2);
			l.push_back(4);
			l.push_back(6);
			l.push_back(8);
			l.push_back(10);

			auto i = l.begin();
			i++;

			l.erase(i++);

			CheckList(l, "l", { 2, 6, 8, 10 }, CheckInt);
		}
	),
};


int main(int argc, char *argv[])
{
	const TestSuite::Statistics stats = tests.Run(argc, argv);

	if (stats.total > 0)
	{
		cout << endl
			<< "Passed " << stats.passed
			<< "/" << stats.total << " tests\n";

		float grade = 1 + 4 * stats.score;
		cout << endl << "Grade: " << grade << "/5 " << endl;
	}

	return 0;
}