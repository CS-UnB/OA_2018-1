#include <iostream>
#include <sstream>
#include <string>
#include <fstream>  
#include <locale>
#include <cstdlib>
#include <vector>
#include <unistd.h>

using namespace std;

ofstream registro;

void guarda(std::string str)
{
	string aux;
	getline(std::cin, aux);
	str += aux;
	str += '|';
	registro << str;
}

void atributo()
{
	registro.open("registro.txt", ofstream::out | ofstream::app);
	string str;

	cout << "Digite seu nome:\n";
	str = "Nome=";
	guarda(str);

	cout << "Digite seu sobrenome:\n";
	str = "Sobrenome=";
	guarda(str);

	cout << "Digite seu endereço:\n";
	str = "Endereço=";
	guarda(str);

	cout << "Digite seu cep:\n";
	str = "CEP=";
	guarda(str);

	cout << "Digite seu telefone:\n";
	str = "Telefone=";
	guarda(str);

	registro.close();

}

int	mostrarAtributo(std::string str,int pos)
{
	if(str[pos-1]!='=')
	{
		while (str[pos] != '=')
		{
			pos+=1;
		}
		pos+=1;	
	}
	
	while(str[pos] != '|')
	{
		cout << str[pos];
		pos+=1;
	}
	cout << endl;
	pos+=1;
	return pos;
}

void encontrarTodasStr(std::vector<size_t> & vec, std::string str, std::string search)
{
	// Get the first occurrence
	size_t pos = str.find(search);
 
	// Repeat till end is reached
	while( pos != string::npos)
	{
		// Add position to the vector
		vec.push_back(pos);
 
		// Get the next occurrence from the current position
		pos =str.find(search, pos + search.size());
	}
}

void procurar()
{
	vector<size_t> vec;
	string filename = "registro.txt";
	string search;
	registro.open(filename.c_str(), ofstream::out | ofstream::app);

	ifstream file(filename.c_str());
    stringstream buffer;

    buffer << file.rdbuf();
    string str = buffer.str();

    cout << "Digite o nome da pessoa que deseja procurar: \n";
    cin >> search;
    cin.clear();
	cin.ignore(256, '\n');

	encontrarTodasStr(vec, str , search);

	for (size_t pos : vec)
	{
		cout << "--------------------------------------------\n";
		cout << "Nome: ";
		pos = mostrarAtributo(str,pos);
		cout << "Sobrenome: ";
		pos = mostrarAtributo(str, pos);
		cout << "Endereco: ";
		pos = mostrarAtributo(str, pos);
		cout << "CEP: ";
		pos = mostrarAtributo(str, pos);
		cout << "Telefone: ";
		mostrarAtributo(str, pos);
		cout << "--------------------------------------------\n";
	}

	cout << "Pressione Enter pra voltar ao menu\n";
	getchar();
	registro.close();
}


void menu()
{
	int choice;
	bool menu = true;
	while (menu != false){
		system("clear");
		cout << "*******************************\n";
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
			atributo();
			break;

			case 2:
			procurar();		
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

int main(int argc, char const *argv[])
{
	locale::global(std::locale("en_US.utf8"));
	wcout.imbue(std::locale());
	menu();
	return 0;
}