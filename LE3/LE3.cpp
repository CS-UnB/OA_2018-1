//LE3_OA_Otto_Gabriel

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cstdio>
#include "OA3_1.hpp"
#include "OA3_4.hpp"

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

void menu_2(fstream &file)
{
	int choice;
	bool menu = true;
	while (menu != false){
		system("clear");
		cout << "******* ITEM 2 **************\n";
		cout << " 1 - Registrar uma pessoa\n";
		cout << " 2 - Procurar registro\n";
		cout << " 3 - Exit.\n";
		cout << " Digite uma opção: ";

		cin >> choice;
		cin.clear();
		cin.ignore(256, '\n');

		switch (choice)
		{
			case 1:
			burn_sizeInFront(file);
			break;

			case 2:
			read_sizeInFront(file);		
			break;
			
			case 3:
			menu = false;
			break;

			default:
			cout << "Escolha não válida \n";
			cout << "Escolha novamente\n";
			cin >> choice;
			cin.clear();
			cin.ignore(256, '\n');
			break;
		}
	}
}

void menu_3(fstream &file)
{
	int choice;
	bool menu = true;
	while (menu != false){
		system("clear");
		cout << "******** ITEM 3 ***************\n";
		cout << " 1 - Registrar uma pessoa\n";
		cout << " 2 - Procurar registro\n";
		cout << " 3 - Exit.\n";
		cout << " Digite uma opção: ";

		cin >> choice;
		cin.clear();
		cin.ignore(256, '\n');

		switch (choice)
		{
			case 1:
			burn_separator(file);
			break;

			case 2:
			read_separator(file);		
			break;
			
			case 3:
			menu = false;
			break;

			default:
			cout << "Escolha não válida \n";
			cout << "Escolha novamente\n";
			cin >> choice;
			cin.clear();
			cin.ignore(256, '\n');
			break;
		}
	}
}

void main_menu()
{
	int choice;
	bool menu = true;
	fstream f_one("dataFront.txt", fstream::in | fstream::out | fstream::trunc);
	if(! f_one.is_open())
		throw "FILE_ONE NOT OPEN";
	fstream f_two("dataSep.txt", fstream::in | fstream::out | fstream::trunc);
	if(!f_two.is_open())
		throw "FILE_TWO NOT OPEN";
	
	cout << "\t\tLE3OA - Otto & Gabriel" << endl;
	cout << "\tOtto K. von Sperling\n\tMAT: 12/0131510" << endl;
	cout << "\tGabriel\n\tMAT: XXXXXXXX" << endl;
	
	while (menu != false){
		cout << "*******************************\n";
		cout << " Item 1 - STATIC SIZE OF DATA STREAM\n";
		cout << " Item 2 - SIZE TOKEN OF DATA STREAM\n";
		cout << " Item 3 - SEPARATOR FOR DATA STREAM\n";
		cout << " Item 4 - ATTRIBUTE FIELD FOR DATA STREAM\n";
		cout << " 5 - Exit.\n";
		cout << " Digite uma opção: ";

		cin >> choice;
		cin.clear();
		cin.ignore(256, '\n');

		switch (choice)
		{
			case 1:
			menu_1();
			system("clear");
			break;

			case 2:
			f_one.clear();
			f_one.seekg(0, ios::beg);
			menu_2(f_one);
			f_one.close();
			break;
			
			case 3:
			f_two.clear();
			f_two.seekg(0, ios::beg);
			menu_3(f_two);
			f_two.close();
			break;

			case 4:
			menu_4();
			break;

			case 5:
			menu = false;
			break;

			default:
			cout << "Escolha não válida \n";
			cout << "Escolha novamente\n";
			cin >> choice;
			cin.clear();
			cin.ignore(256, '\n');
			system("clear");
			break;
		}
	}
}

int main(int argc, char** argv)
{
	main_menu();
	return 0;
}