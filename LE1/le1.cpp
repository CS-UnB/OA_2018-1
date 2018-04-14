//LE1 OA - Otto von Sperling

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

// FUNÇÃO PARA CONCATENAR N ARQUIVOS TEXTO
void concN_Txt(const std::vector<std::string> &inputTxt, const char *outputTxts)
{
	try
	{
		std::ofstream output(outputTxts, std::ios::binary);
		unsigned int i = 0;

		while(i < inputTxt.size())
		{
			std::ifstream in(inputTxt[i].c_str(), std::ios::binary);
			output << in.rdbuf();
			++i;
		}
	}
	catch(std::exception& e)
	{
		std::cout << "Standard exception thrown - " << e.what() << std::endl;
	}
}

// FUNCAO PARA LER O ARQUIVO EM BLOCOS
void readChucnks(std::fstream &fin)
{
	int buffersize = 512;

	std::cout << "SELECIONE O TAMANHO DO BLOCO EM BYTES..\n\tPADRAO = 512 BYTES\n";
	std::cin >> buffersize;

	std::vector<char> buffer(buffersize, 0);
	std::cout << "\tBUFFER = " << buffersize << std::endl; 
	while(true)
	{
		fin.read(&buffer[0], buffer.size());
		std::string bufferString(buffer.begin(), buffer.end());
		std::cout << bufferString << "\n";
		if(fin.eof())
		{
			break;
		}
	}
}

// FUNCAO PARA LER O ARQUIVO CARACTER A CARACTER
void readChars(std::fstream &fin)
{
	char buffer;
	std::cout << "LENDO CARACTER A CARACTER\n";

	while(true)
	{
		fin >> buffer;
		std::cout << buffer;
		if(fin.eof())
		{
			break;
		}
	}
}

// ################# MAIN ####################################
int main(int argc, char **argv)
{
	std::string file_Name;
	std::vector<std::string> input_Files;
	std::string input_Names;
	int numTxts = 0;
	int switchOption = 0;

	std::cout << "LE1 - OA - 2018/1\n\tOtto K. von Sperling\n\tMAT: 12/0131510\n\n";
	while(switchOption != 5)
	{
		std::cout << "1- CONCATENAR N ARQUIVOS\t2- VISUALIZAR ARQUIVO | BLOCOS\n3- VISUALIZAR ARQUIVO | CARACTER A CARACTER\t4- COMPARAR TXT E BINARIO\t5- ENCERRAR\n\n";
		std::cin >> switchOption;
		switch(switchOption)
		{
			case 1:	//CONCATENA ARQUIVOS
				
				std::cout << "Numero de arquivos a serem concatenados - ";
				std::cin >> numTxts;
				input_Files.reserve(numTxts);
			
				std::cout << "Digite o nome do arquivo.\ni.e. Arquivo.txt\n\n";
				for(int i = 0; i < numTxts; )
				{
					std::cout << "Arquivo " << (i+1) << std::endl;
					std::cin >> input_Names;
					if((input_Names.find(".txt") != std::string::npos))	//VERIFICA FORMATACAO DO NOME DO ARQUIVO
					{
						std::fstream fs;
						fs.open(input_Names, std::fstream::in);
						if(fs.is_open())	//VERIFICA A EXISTENCIA DO ARQUIVO
						{
							input_Files.push_back(input_Names);	//ADICIONA AO VETOR COM O NOME DOS ARQUIVOS A SEREM CONCATENADOS
							++i;
							std::cout << "\n";
							fs.close();
						}
						else
						{
							std::cout << "Arquivo .txt nao encontrado. Tente novamente ou digite -1 para encerrar.\n\n";
						}
					}
					else if(input_Names == "-1")
					{
						std::cout << "MENU PRINCIPAL: \n";
						break;	//saida pelo usuario
					}
					else
					{
						std::cout << "Formatacao do nome do arquivo incorreta. Tente novamente ou digite -1 para encerrar.\n\n";
					}
				}
				 concN_Txt(input_Files, "txtConc.txt");
				 std::cout << "CONCATENACAO COMPLETA - Arquivo 'txtConc.txt' criado.\n\n" << std::endl;
				break;
	
			case 2:		//VISUALIZA EM BLOCOS
				while(true)
				{
					std::cout << "Digite o nome do arquivo.\ni.e. Arquivo.txt\n\n";
					std::cin >> file_Name;
					if((file_Name.find(".txt") != std::string::npos))	//VERIFICA FORMATACAO DO NOME DO ARQUIVO
					{
						std::fstream fs1;
						fs1.open(file_Name, std::fstream::in);
						if(fs1.is_open())	//VERIFICA A EXISTENCIA DO ARQUIVO
						{
							readChucnks(fs1);
							std::cout << "\n";
							fs1.close();
							break;
						}
						else
						{
							std::cout << "Arquivo .txt nao encontrado. Tente novamente ou digite -1 para encerrar.\n\n";
						}
					}
					else if(file_Name == "-1")
					{
						std::cout << "MENU PRINCIPAL: \n";
						break;	//saida pelo usuario
					}
					else
					{
						std::cout << "Formatacao do nome do arquivo incorreta. Tente novamente ou digite -1 para encerrar.\n\n";
					}
				}
				break;

			case 3:
				while(true)
				{
					std::cout << "Digite o nome do arquivo.\ni.e. Arquivo.txt\n\n";
					std::cin >> file_Name;
					if((file_Name.find(".txt") != std::string::npos))	//VERIFICA FORMATACAO DO NOME DO ARQUIVO
					{
						std::fstream fs1;
						fs1.open(file_Name, std::fstream::in);
						if(fs1.is_open())	//VERIFICA A EXISTENCIA DO ARQUIVO
						{
							readChars(fs1);
							std::cout << "\n\n";
							fs1.close();
							break;
						}
						else
						{
							std::cout << "Arquivo .txt nao encontrado. Tente novamente ou digite -1 para encerrar.\n\n";
						}
					}
					else if(file_Name == "-1")
					{
						std::cout << "MENU PRINCIPAL: \n";
						break;	//saida pelo usuario
					}
					else
					{
						std::cout << "Formatacao do nome do arquivo incorreta. Tente novamente ou digite -1 para encerrar.\n\n";
					}
				}
				break;

			case 4:
				break;

			case 5:
				exit(0);

			default:	
				break;
		}
	}
	return 0;
}