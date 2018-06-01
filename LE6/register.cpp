// register.cpp
#include "register.hpp"
//
using namespace std;
//
void REGISTER::set(string field, string args)	{
	if (field == "first_name")
		this->first_name = args;
	else if (field == "second_name")
		this->second_name = args;
	else if (field == "birth_date")
		this->$$ = args;
	else if (field == "birth_place")
		this->$$ = args;
	else if (field == "marital_status")
		this->$$ = args;
	else if (field == "CPF")
		this->$$ = args;
	else if (field == "education")
		this->$$ = args;
	else if (field == "ethnicity")
		this->$$ = args;
	else if (field == "children")
		this->$$ = args;
	else if (field == "entry_time")
		this->entry_time = args;

	else
		cout << "Field could not be set!" << endl;
}
