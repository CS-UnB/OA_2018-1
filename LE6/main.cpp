#include "register.hpp"
#include <fstream>
#include <utility>
//
using namespace std;
#define NUM_REG 20
//
void generate(vector<string> &data)	{
	data.reserve (NUM_REG);
//	
	for (int it = 65; it < NUM_REG+65; it++)	{
		string buf (5, char(it));
		data.push_back (buf);
	}
}
//
//
void populate(vector<REGISTER> &source)	{
	time_t curr_time;
	REGISTER registers;
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
			tag.second	= registers[i].last_name;
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
int find_register(string args)	{
	ifstream t_file ("tag.txt", ifstream::in);
//	
	if (t_file.is_open())	{
		string buf;
		int count = 0;
		size_t pos;
		while (t_file.good())	{
			getline (t_file, buf);
			pos = buf.find (args);
			if (pos != string::npos)
				return count;
			else
				count++;
		}
		t_file.close();
		return -1;	// if register is not found
	} else	{
		cout << "Could not open tag file" << endl;
		return -1;
	}
}
//
//
int main (int argc, char** argv)	{
	vector<REGISTER> registers;
	string search;
	int id;
	//
	populate (registers);
	save_to_file (registers);
	//
	cout << "\t\tOtto K. von Sperling - 12/0131510\n\t\tGustavo C. Sousa - 14/0142568" << endl;
	cout << "Register to be found - CPF or last name: ";
	cin >> search;
	id = find_register(search);
	if (id == -1)
		cout << "Register not found." << endl;
	else	{
		cout << "\tNAME:\t\t" << registers[id].first_name << " " << registers[id].last_name << endl;
		cout << "\tRACE:\t\t" << registers[id].ethnicity << endl;
		cout << "\tCPF:\t\t" << registers[id].CPF << endl;
		cout << "\tBIRTH:\t\t" << registers[id].birth_date << " in " << registers[id].birth_place << endl;
		cout << "\tMARITAL:\t" << registers[id].marital_status << " with " << registers[id].children << " children" << endl;
		cout << "\tEDU:\t\t" << registers[id].education << endl;
	}
	//
	return 0;
}
