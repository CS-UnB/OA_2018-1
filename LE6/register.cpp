// register.cpp
#include "register.hpp"
//
using namespace std;
//
void REGISTER::set(string field, string args)	{
	if (field == "first_name")
		this->first_name = args;
	else if (field == "last_name")
		this->last_name = args;
	else if (field == "birth_date")
		this->birth_date = args;
	else if (field == "birth_place")
		this->birth_place = args;
	else if (field == "marital_status")
		this->marital_status = args;
	else if (field == "CPF")
		this->CPF = args;
	else if (field == "education")
		this->education = args;
	else if (field == "ethnicity")
		this->ethnicity = args;
	else if (field == "children")
		this->children = args;
	else if (field == "entry_time")
		this->entry_time = args;
	else
		cout << "Field could not be set!" << endl;
}
