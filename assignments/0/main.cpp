#include <iostream>
#include "assign0.h"

int main()
{
	std::cout << "the colour of a pen should be " << engi4892::bestColour(engi4892::ColouredObject::Pen) << std::endl;
	std::cout << "the colour of a car should be " << engi4892::bestColour(engi4892::ColouredObject::Car) << std::endl;
	return 0;
}