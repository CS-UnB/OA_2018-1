// LE6_OA
// ALUNOS:
//	Otto K. von Sperling	12/0131510
//	Gustavo C. Sousa	14/0142568	
//
#ifndef REGISTER_HPP
#define REGISTER_HPP
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
//
using namespace std;
//
class REGISTER {
	public:	
		string first_name;
		string last_name;
		string birth_date;
		string birth_place;
	       	string marital_status;
		string CPF;
		string education;	
		string ethnicity;
		string children;
		string entry_time;	
//
	public:
		void set(string field, string args); 
};
#endif
