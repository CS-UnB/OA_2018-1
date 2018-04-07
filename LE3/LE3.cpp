//LE3_OA_Otto_Gabriel

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cstdio>

using namespace std;

void burn_sizeInFront(fstream &file)
{
	string buffer;
	list<string> data_fields = {"Sobrenome", "Nome", "Endereco", "CEP", "Telefone"};
	list<string> data_input = {"Sperling", "Otto", "SQNSQN", "77777777", "999999999"};
	string data_size;
	list<string>::iterator jt = data_input.begin();	// for the sake of debugging

	if(!file.is_open())
		throw "FIle not open!!";


	for(list<string>::iterator it = data_fields.begin(); it != data_fields.end(); ++it)
	{
		//cout << (*it) << " = ";
		// cin >> buffer;	// in the actual program
		buffer = (*jt);	// for the sake of debugging

		if(buffer.size() < 10)						// START_ standardize size field to 2 bytes
		{											//
			data_size = "0";						//
			data_size.append(to_string(buffer.size()));	//	
		}											//
		else										//
		{											//
			data_size = to_string(buffer.size());		//
		}											// END_ standardize size field to 2 bytes
		
		buffer.insert(0, data_size);
		file << buffer;
		buffer.clear();
		data_size.clear();
		jt++;
	}

}

void read_sizeInFront(fstream &file)
{
	int data_length = 0;
	string buffer;
	list<string> data_fields = {"Sobrenome", "Nome", "Endereco", "CEP", "Telefone"};
	list<string>::iterator it = data_fields.begin();
	streambuf *pbuf = file.rdbuf();

	if(!file.is_open())
		throw "File is not open";
	while(pbuf->sgetc() != EOF)
	{
		if(buffer.size() < 2)
		{
			buffer.append(1, pbuf->sbumpc());
		}
		else
		{
			data_length = stoi(buffer);
			buffer.clear();
			for(int i = 0; i < data_length; ++i)
			{
				buffer.append(1, pbuf->sbumpc());
			}
			cout << (*it) << ": " << buffer << endl;
			buffer.clear();
			it++;
		}
	}
}

int main(int argc, char** argv)
{
	fstream file("data.txt", fstream::out | fstream::in);
	burn_sizeInFront(file);
	file.clear();
	file.seekg(0, ios::beg);
	read_sizeInFront(file);
	file.close();

	return 0;
}