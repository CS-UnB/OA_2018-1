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

void burn_separator(fstream &file)
{
	string buffer;
	list<string> data_fields = {"Sobrenome", "Nome", "Endereco", "CEP", "Telefone"};
	list<string> data_input = {"Sperling", "Otto", "SQNSQN", "77777777", "999999999"};
	list<string>::iterator jt = data_input.begin();	// for the sake of debuggin


	for(list<string>::iterator it = data_fields.begin(); it != data_fields.end(); ++it)
	{
		//cout << (*it) << " = ";
		// cin >> buffer;	// in the actual program
		buffer = (*jt);	// for the sake of debugging

		buffer.append("|");
		file << buffer;
		buffer.clear();
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

void read_separator(fstream &file)
{
	string buffer;
	list<string> data_fields = {"Sobrenome", "Nome", "Endereco", "CEP", "Telefone"};
	list<string>::iterator it = data_fields.begin();
	streambuf *pbuf = file.rdbuf();
	char trash;

	while(pbuf->sgetc() != EOF)
	{
		while(pbuf->sgetc() != '|')
			buffer += pbuf->sbumpc();
		trash = pbuf->sbumpc();
		cout << (*it) << ": " << buffer << endl;
		buffer.clear();
		it++;
	}
}

int main(int argc, char** argv)
{
	fstream f_one("dataFront.txt", fstream::in | fstream::out | fstream::trunc);
	if(! f_one.is_open())
		throw "FILE_ONE NOT OPEN";
	burn_sizeInFront(f_one);
	f_one.clear();
	f_one.seekg(0, ios::beg);
	read_sizeInFront(f_one);
	f_one.close();
	
	fstream f_two("dataSep.txt", fstream::in | fstream::out | fstream::trunc);
	if(!f_two.is_open())
		throw "FILE_TWO NOT OPEN";
	burn_separator(f_two);
	f_two.clear();
	f_two.seekg(0, ios::beg);
	read_separator(f_two);
	f_two.close();

	return 0;
}