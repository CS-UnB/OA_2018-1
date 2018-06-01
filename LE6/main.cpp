#include "register.hpp"
#include <fstream>
//
using namespace std;
#define NUM_REG 20
#define NUM_FIELDS 3
//
void generate(vector<string> &data)	{
	data.reserve (NUM_REG*NUM_FIELDS);
//	
	for (int it = 65; it < NUM_REG+65; it++)	{
		string buf (5, char(it+1));
		data.push_back (buf);
	}
}
//
//
void populate(vector<REGISTER> &source)	{
	time_t curr_time;
	REGISTER registers;
	//	mock up data:
	vector<string> mock_data;
	generate (mock_data);
	//	end_mock up data;
//
	string buf;
	for (int i = 0; i < NUM_REG; ++i)	{
		//cin >> buf;
		buf = mock_data[i];
		registers.set("name", buf);
		//
		//cin >> buf;
		registers.set("id", buf);
		buf.clear();
		//
		time (&curr_time);
		registers.set("time", ctime(&curr_time));
		//
		source.push_back (registers);
	}

}
//
//
void save_to_file(vector<REGISTER> &registers)	{
	fstream file ("register.txt", fstream::out);
//
	if (file.is_open())	{
		for (int i = 0; i < NUM_REG; ++i)	{
			file << registers[i].id;
			file << registers[i].name;
			file << registers[i].entry_time;
		}
	} else	{
		cout << "File could not be opened" << endl;
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
