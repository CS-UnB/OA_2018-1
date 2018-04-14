	//LE2_OA
#include <iostream>  /* defines FILENAME_MAX */
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <cstdint>
#include <unistd.h>
#define GetCurrentDir getcwd

using namespace std;

string get_pathInfo(struct stat &buffer);
int save_inChunks(string in_fileName, string out_fileName, int custom_blockSize, int word_size);
int generateCustomFiles(string in_fileName, int word_size, int cluster);

int main(int argc, char** argv)
{
	int wordsize = 32; //default
	int clusterSize;
	string appPath;
	struct stat pathInfo;
	string in_file = "randomTxt.txt";

	cout << "ALUNOS\n\tOtto K. von Sperling - 12/0131510\n\tGabriel G. de Castro - 15/0126425\n";

	if(argc == 3) // if arguments passed in the commandline, use them
	{
		wordsize = atoi(argv[1]);
		clusterSize = atoi(argv[2]);
	}
	else if(argc == 1) // if no arguments passed in the commandline, get current directory info
	{
		appPath = get_pathInfo(pathInfo);	// gets directory info
		if(appPath == "ERROR")	
			return (-1);
		clusterSize = pathInfo.st_blksize;	// atributes cluster size from current directory
	}
	else	// parameter input controll
	{
		cout << "Wrong number of parameters. Either none or two -> <register_size> <cluster_size>" << endl;
		cout << "\tNo parameters implies default 32bits for register and cluster size from PATH:" << endl;
		cout << "\t\t" << appPath << endl;
		return (-1);
	}

	if(generateCustomFiles(in_file, wordsize, clusterSize) != 0) // makes .txt files and checks for error
		return (-1);
	
	cout << "\tArquivos criados com sucesso. Por favor, verique o seu diretorio." << endl; 
	return 0;
}

string get_pathInfo(struct stat &buffer)
{
	//char* cCurrentPath = param;
	char cCurrentPath[FILENAME_MAX];

	if(!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
		return "ERROR\n";	// if fail

	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; // mark the end of the "string"
	stat((const char*)cCurrentPath, &buffer);

	return cCurrentPath;	//if success
}

int save_inChunks(string in_fileName, string out_fileName, int custom_blockSize, int word_size)
{
	ifstream fin;
	ofstream fout;
	char word[word_size];	//register size
	vector<string> buffer(custom_blockSize); //cluster size
	vector<string>::iterator it = buffer.begin();

	fin.open(in_fileName, ifstream::in | ifstream::binary);	//opens and checks files
	if(!fin.is_open())
		return (-1);
	fout.open(out_fileName, ofstream::out | ofstream::binary);
	if(!fout.is_open())
		return (-1);

	filebuf *inbuf = fin.rdbuf();	//pointer to the file buffer
	int i = 0;
	while(true)
	{
		word[i] = inbuf->sbumpc();	// reads first element from file
		while((word[i] != EOF) && (i < word_size))
		{
			i++;
			word[i] = inbuf->sbumpc();	// reads next until EOF or the register is full
		}

		if(word[i] == EOF)
		{
			(*it) = word;
			for(it = buffer.begin(); it != buffer.end(); ++it)	// loads the register to the buffer (== cluster size)
				fout << (*it);
			fin.close();
			fout.close();
			return 0;		
		}

		(*it) = word;
		i = 0;
		it++;
		if(it == buffer.end())
		{
			for(it = buffer.begin(); it != buffer.end(); ++it)	// loads the buffer to the end file
				fout << (*it);		
			fout << "\n";
			it = buffer.begin();
		}
	}
} 

int generateCustomFiles(string in_fileName,int word_size, int cluster)
{
	vector<string> output_names(5, "out_randomTxt");
	vector<int> custom_sizes(5);

	output_names[0].append("512bytes.txt");
	output_names[1].append("_25percent.txt");
	output_names[2].append("_50percent.txt");
	output_names[3].append("_75percent.txt");
	output_names[4].append("_Cluster.txt");

	custom_sizes[0] = (512 / word_size);
	custom_sizes[1] = ((cluster / 4) / word_size);
	custom_sizes[2] = ((cluster) / word_size);
	custom_sizes[3] = (((3 * cluster) / 4) / word_size);
	custom_sizes[4] = ((cluster) / word_size);

	for(int i = 0; i < output_names.size(); ++i)
	{
		if(save_inChunks(in_fileName, output_names[i], custom_sizes[i], word_size) != 0)
			return (-1);
	}

	return 0;
}