#include "OA3_4.hpp"

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
	registro.open("registro4.txt", ofstream::out | ofstream::app);
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
	size_t pos = str.find(search);

	while( pos != string::npos)
	{
		vec.push_back(pos);
 
		pos =str.find(search, pos + search.size());
	}
}

void procurar()
{
	vector<size_t> vec;
	string filename = "registro4.txt";
	string search;
	registro.open(filename.c_str(), ofstream::out | ofstream::app);

	ifstream file(filename.c_str());
    stringstream buffer;

    buffer << file.rdbuf();
    string str = buffer.str();

    cout << "Digite o nome da pessoa que deseja procurar: \n";
    cin >> search;
    //cin.clear();
	//cin.ignore(256, '\n');

	encontrarTodasStr(vec, str , search);

	for (size_t pos : vec)
	{
		cout << "--------------------------------------------\n";
		cout << "Nome: ";
		pos = mostrarAtributo(str,pos);
		cout << "Sobrenome: ";
		pos = mostrarAtributo(str, pos);
		cout << "Endereço: ";
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


void menu_4()
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
