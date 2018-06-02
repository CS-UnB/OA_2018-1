#include "register.hpp"
#include <fstream>
//
using namespace std;
#define NUM_REG 20
<<<<<<< HEAD
//
void generate(vector<string> &data)	{
	data.reserve (NUM_REG);
//	
	for (int it = 65; it < NUM_REG+65; it++)	{
		string buf (5, char(i));
		data.push_back (buf);
	}
}
//
//
void populate(vector<REGISTER> &source)	{
	time_t curr_time;
	REGISTER registers;
<<<<<<< HEAD
	vector<string> mock_data;
	generate (mock_data);
//
	string buf;
	for (int i = 0; i < NUM_REG; ++i)	{
		//cin >> buf;
		buf = mock_data[i];
		registers.set("first_name", buf);
		//
		//cin >> buf;
		registers.set("last_name", buf);
		//
		//cin >> buf;
		registers.set("birth_date", buf);
		//
		//cin >> buf;
		registers.set("birth_place", buf);
		//
		//cin >> buf;
		registers.set("marital_status", buf);
		//
		//cin >> buf;
		registers.set("CPF", buf);
		//
		//cin >> buf;
		registers.set("education", buf);
		//
		//cin >> buf;
		registers.set("ethnicity", buf);
		//
		//cin >> buf;
		registers.set("children", buf);
		//
		buf.clear();
		//
		time (&curr_time);
		registers.set("entry_time", ctime(&curr_time));
		//
		source.push_back (registers);
	}
}
//
//
void save_to_file(vector<REGISTER> &registers)	{
	fstream reg_file ("register.txt", fstream::out);
	fstream tag_file ("tag.txt", fstream::out);
//
	if (reg_file.is_open() && tag_file.is_open())	{
		pair<string, string> tag;
		for (int i = 0; i < NUM_REG; ++i)	{
			reg_file << registers[i].first_name << " | ";
			reg_file << registers[i].last_name << " | ";
			reg_file << registers[i].birth_date << " | ";
			reg_file << registers[i].birth_place << " | ";
			reg_file << registers[i].marital_status << " | ";
			reg_file << registers[i].CPF << " | ";
			reg_file << registers[i].education << " | ";
			reg_file << registers[i].ethnicity << " | ";
			reg_file << registers[i].children << " | ";
			reg_file << registers[i].entry_time << endl;
//			
			tag.first 	= registers[i].CPF;
			tag.secind	= registers[i].last_name;
			tag_file 	<< tag.first << " | ";
			tag_file	<< tag.second << endl;
		}
		reg_file.close();
		tag_file.close();
	} else	{
		cout << "Files could not be opened" << endl;
	}
}
//
//
int main (int argc, char** argv)	{
	vector<REGISTER> registers;
	//
	populate (registers);
	save_to_file (registers);
	return 0;
}
