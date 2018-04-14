#ifndef OA3_1_HPP
#define OA3_1_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>  
#include <cstdlib>
#include <vector>
#include <unistd.h>

std::string getIt();
void tamanhoFixo();
void mostrarAteHash(std::string str,int pos);
void encontrarTodasStr_1(std::vector<size_t> & vec, std::string str, std::string search);
void procurar_1();
void menu_1();

#endif