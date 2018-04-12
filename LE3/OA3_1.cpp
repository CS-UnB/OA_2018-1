#include "OA3_1.hpp"

#define TAM 60

using namespace std;

ofstream registro_1;

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

	registro_1.open("registro.txt", ofstream::out | ofstream::app);

	cout << "Digite seu nome:\n";
	nome = getIt();
	registro_1 << nome;

	cout << "Digite seu sobrenome:\n";
	sobrenome = getIt();
	registro_1 << sobrenome;

	cout << "Digite seu endereço:\n";
	endereco = getIt();
	registro_1 << endereco;

	cout << "Digite seu cep:\n";
	cep = getIt();
	registro_1 << cep;

	cout << "Digite seu telefone:\n";
	telefone = getIt();
	registro_1 <<	telefone;
	registro_1.close();
	cout << "Registrado\n";

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

void encontrarTodasStr_1(std::vector<size_t> & vec, std::string str, std::string search)
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

void procurar_1()
{
	vector<size_t> vec;
	string filename = "registro_1.txt";
	string search;
	registro_1.open(filename.c_str(), ofstream::out | ofstream::app);

	ifstream file(filename.c_str());
    stringstream buffer;

    buffer << file.rdbuf();
    string str = buffer.str();

    cout << "Digite o nome da pessoa que deseja procurar_1: \n";
    cin >> search;
    //cin.clear();
	//cin.ignore(256, '\n');

	encontrarTodasStr_1(vec, str , search);

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
	registro_1.close();
}


void menu_1()
{
	int choice;
	bool menu = true;
	while (menu != false){
		cout << "*******************************\n";
		cout << " 1 - Registrar uma pessoa\n";
		cout << " 2 - Procurar registro\n";
		cout << " 3 - Exit.\n";
		cout << " Digite uma opção: ";

		cin >> choice;
		//cin.clear();
		//cin.ignore(256, '\n');

		switch (choice)
		{
			case 1:
			tamanhoFixo();
			break;

			case 2:
			procurar_1();		
			break;
			
			case 3:
			menu = false;
			break;

			default:
			cout << "Escolha não válida \n";
			cout << "Escolha novamente\n";
			cin >> choice;
			//cin.clear();
			//cin.ignore(256, '\n');
			break;
		}
	}
}