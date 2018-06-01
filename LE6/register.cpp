// register.cpp
#include "register.hpp"
//
using namespace std;
//
void REGISTER::set(string field, string args)	{
	if (field == "name")
		this->name = args;
	else if (field == "id")
		this->id = args;
	else if (field == "time")
		this->entry_time = args;
	else
		cout << "Field could not be set!" << endl;
}
