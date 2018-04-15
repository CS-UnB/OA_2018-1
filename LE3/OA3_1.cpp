#include "OA3_1.hpp"

#define TAM 60

using namespace std;

ofstream registro_1;

void tamanhoFixo()
{
	string nome, sobrenome, endereco, cep, telefone;

	registro_1.open("registro.txt", ofstream::out | ofstream::app);

	cout << "Digite seu nome:"  << endl;
	getline(std::cin,nome);
	getline(std::cin,nome);
	for(int i = nome.size(); i < TAM; ++i)
		nome.append("#");
	registro_1 << nome;

	cout << "Digite seu sobrenome:" << endl;
	cin.clear();
	getline(std::cin,sobrenome);
	for(int i = sobrenome.size(); i < TAM; ++i)
		sobrenome.append("#");
	registro_1 << sobrenome;

	cout << "Digite seu endereço:"  << endl;
	cin.clear();
	getline(std::cin,endereco);
	for(int i = endereco.size(); i < TAM; ++i)
		endereco.append("#");
	registro_1 << endereco;

	cout << "Digite seu cep:" << endl;
	cin.clear();
	getline(std::cin,cep);
	for(int i = cep.size(); i < TAM; ++i)
		cep.append("#");
	registro_1 << cep;

	cout << "Digite seu telefone:" << endl;
	cin.clear();
	getline(std::cin,telefone);
	for(int i = telefone.size(); i < TAM; ++i)
		telefone.append("#");
	registro_1 <<	telefone;
	registro_1.close();
	cout << "Registrado\n";

}

void mostrarAteHash(std::string str)
{
	for(int i = 0; i < str.size(); ++i)
	{
		if(str[i] != '#')
			cout << str[i];
	}
	cout << endl;
}

string encontrarTodasStr_1(std::string str, std::string search)
{
	// Get the first occurrence
	size_t pos = str.find(search);
	
	if(pos == string::npos)
		return "-1";

	string buffer(str, pos, (5 * TAM));
	return buffer;
}

void procurar_1()
{
	string search, str, found, buf;
	string filename = "registro.txt";

	ifstream file(filename.c_str());
    stringstream buffer;

    buffer << file.rdbuf();
    str = buffer.str();

    cout << "Digite o nome da pessoa que deseja procurar_1:" << endl;
    cin.clear();
    getline(std::cin, search);
    getline(std::cin, search);

	found = encontrarTodasStr_1(str , search);
	if(found == "-1")
	{
		cout << "Pessoa nao localizada." << endl;
		file.close();
	}
	else
	{
		{
			cout << "--------------------------------------------\n";
			cout << "Nome: ";
			buf = found.substr(0, TAM);
			mostrarAteHash(buf);

			cout << "Sobrenome: ";
			buf = found.substr(TAM, TAM);
			mostrarAteHash(buf);

			cout << "Endereco: ";
			buf = found.substr((2 * TAM), TAM);
			mostrarAteHash(buf);

			cout << "CEP: ";
			buf = found.substr((3 * TAM), TAM);
			mostrarAteHash(buf);

			cout << "Telefone: ";
			buf = found.substr((4 * TAM), TAM);
			mostrarAteHash(buf);
			cout << "--------------------------------------------\n";
		}
	}


	cout << "Pressione Enter pra voltar ao menu\n";
	getchar();
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