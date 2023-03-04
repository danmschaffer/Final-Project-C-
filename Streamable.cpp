/* Citation and Sources...
Final Project Milestone 3
Module: Streamable
Filename: Streamable.cpp
Version 1.0

-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#include <iostream>
#include "Streamable.h"

using namespace std;

namespace sdds
{
	ostream &operator<<(ostream &os, const Streamable &obj)
	{
		obj.write(os);
		return os;
	}

	istream &operator>>(istream &is, Streamable &obj)
	{
		obj.read(is);
		return is;
	}
}