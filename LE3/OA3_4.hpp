#ifndef OA3_4_HPP
#define OA3_4_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>  
#include <cstdlib>
#include <vector>
#include <unistd.h>

void guarda(std::string str);
void atributo();
int	mostrarAtributo(std::string str, int pos);
void encontrarTodasStr(std::vector<size_t> & vec, std::string str, std::string search);
void procurar();
void menu_4();

#endif