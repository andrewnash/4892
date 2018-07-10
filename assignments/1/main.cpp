#include "List.h"

int main(){

	List<int> firstList;
	cout << "firstList created:" << endl;

	firstList.push_front(5);
	firstList.push_back(6);
	firstList.push_back(7);
	firstList.push_back(8);
	firstList.push_front(4);

	// print all
	cout << endl << "Printing firstList values: size = " << firstList.size() << endl;
	for(auto i = firstList.begin(); i != firstList.end(); i++)
		cout << *i << " ";
	cout << endl << endl;

	List<int> secondList = firstList;
	cout << "This is a copy of the first list as scondList:\n";
	for(auto i = secondList.begin(); i != secondList.end(); i++)
		cout << i.get_node() << " = " << *i << "\n";
	cout << endl;

	List<int> thirdList(move(firstList));
	cout << "thirdList created, firstList has now been moved to thridList:\nthirdlist = ";
	for(auto i = thirdList.begin(); i != thirdList.end(); i++)
		cout << *i << " ";
	cout << endl;

	cout << "the size of firstList is now: " << firstList.size() << endl << endl;

	cout << "Attempting to erase item 2 from secondList:" << endl;
	secondList.erase(++secondList.begin());

	cout << "Attempting to delete secondList" << endl;
	delete  &secondList;
	cout << "Second list now deleted" << endl;

	return 0;
}