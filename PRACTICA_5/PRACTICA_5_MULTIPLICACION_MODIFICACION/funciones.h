#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <bitset>
#include <vector>
#include <iostream>

int ContadorUnos(std::bitset<8>);
std::vector<std::bitset<8>> Distributiva(std::bitset<8>);
std::pair<std::bitset<8>, int> Multiplicacion(std::bitset<8> ,std::vector<std::bitset<8>>, std::bitset<8>);

#endif