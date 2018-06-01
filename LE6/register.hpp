// LE6_OA
// ALUNOS:
//	Otto K. von Sperling	12/0131510
//	Gustavo Sousa		xx/xxxxxxx
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
		string id;
		string name;
		string entry_time;
//
	public:
		void set(string field, string args); 
};
#endif
