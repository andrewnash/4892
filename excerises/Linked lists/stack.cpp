#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

template<typename Iter>
void RPN(const Iter& begin, const Iter& end)
{
	double ans;
	if(*(begin + 2) == "+")
	{
		ans = stod(*begin) + stod(*(begin + 1));
	}
	if(*(begin + 2) == "-")
	{
		ans = stod(*begin) - stod(*(begin + 1));
	}
	if(*(begin + 2) == "/")
	{
		ans = stod(*begin) / stod(*(begin + 1));
	}
	if(*(begin + 2) == "*")
	{
		ans = stod(*begin) * stod(*(begin + 1));
	}
	if(*(begin + 2) == "%")
	{
		ans = stoi(*begin) % stoi(*(begin + 1));
	}
	cout << ans;
}

template<typename T>
class Queue
{
public:
	Queue(int size_)
	{
		Qsize = size_;
		T Q[Qsize];
		count = 0;
	}

	void enqueue(T data)
	{
		Q[count] = data;
		count++;
	}

	void shift()
	{
		for(int i = 0; i < Qsize - 1; i++)
		{
			Q[i] = Q[i + 1];
		}
	}

	T dequeue()
	{
		count--;
		T tmp = Q[0];
		shift();
		return tmp;
	}

	int size()
	{
		return Qsize;
	}

private:
	int Qsize;
	T Q;
	int count;
};


int main()
{
	int a = 0;
	cout << "Address of a is " << &a << endl;
	int b = 0;
	cout << "Address of a is: " << &a << " Address of b is: " << &b << endl;
	cout << "Sense a - b = " << &a-&b << " the stack must grow downward!" << endl;

	vector<string> v = {"1", "1", "+"};
	RPN(v.begin(), v.end());

	//Queue <int> newQ = Queue(5);
	return 0;
}
