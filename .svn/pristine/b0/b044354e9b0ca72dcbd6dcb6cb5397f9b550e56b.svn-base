#include <iostream>
#include <vector>
#include <list>

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

template<typename T, typename container>
void removeTens(container v)
{
	for(auto i = v.begin(); i != v.end(); i++)
	{
		if(*i % 10 == 0)
		{
			v.erase(i);
			i--;
		}
	}
}

int main()
{
	vector<int> v = {1,4,7,10,20,30,56,70,67,23,40,22};
	cout << "starting v" << v << endl;
	removeTens(v);
	cout << "ending v" << v << endl;

	list<int> l = {1,4,7,10,20,30,56,70,67,23,40,22}
	cout << endl << "starting l" << l << endl;
	removeTens(l);
	cout << "ending l" << l << endl;

	return 0;
}

