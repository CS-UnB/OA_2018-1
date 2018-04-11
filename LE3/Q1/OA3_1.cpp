#include <iostream>
#include <sstream>
#include <string>
#include <fstream>  
#include <locale>
#include <cstdlib>
#include <vector>
#include <unistd.h>

#define TAM 60

using namespace std;

ofstream registro;

string getIt()
{
	char buffer[TAM];
	string s0;
	unsigned aux;
	unsigned sz = s0.size();
	cin.width(TAM);
	cin.getline(buffer, sizeof(buffer));
	s0 = buffer;
	aux = TAM - sz;
	s0.resize(sz+aux, '#');

	return s0;
}

void tamanhoFixo()
{
	string nome, sobrenome, endereco, cep, telefone;

	registro.open("registro.txt", ofstream::out | ofstream::app);

	cout << "Digite seu nome:\n";
	nome = getIt();
	registro << nome;

	cout << "Digite seu sobrenome:\n";
	sobrenome = getIt();
	registro << sobrenome;

	cout << "Digite seu endereço:\n";
	endereco = getIt();
	registro << endereco;

	cout << "Digite seu cep:\n";
	cep = getIt();
	registro << cep;

	cout << "Digite seu telefone:\n";
	telefone = getIt();
	registro <<	telefone;
	registro.close();
	cout << "Registrado\n";
	sleep(1);

}

void mostrarAteHash(std::string str,int pos)
{
	while (str[pos] != '#')
	{
		cout << str[pos];
		pos+=1;
	}
	cout << endl;
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
		mostrarAteHash(str,pos);
		cout << "Sobrenome: ";
		mostrarAteHash(str, pos+TAM);
		cout << "Endereco: ";
		mostrarAteHash(str, pos+2*TAM);
		cout << "CEP: ";
		mostrarAteHash(str, pos+3*TAM);
		cout << "Telefone: ";
		mostrarAteHash(str, pos+4*TAM);
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
			tamanhoFixo();
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