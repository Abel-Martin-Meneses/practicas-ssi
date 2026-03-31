#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <bitset>

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

const std::vector<std::vector<int>> SATELITES = {
  {2, 6}, {3, 7}, {4, 8}, {5, 9}, 
  {1, 9}, {2, 10}, {1, 8}, {2, 9}, 
  {3, 10}, {2, 3}, {3, 4}, {5, 6},
  {6, 7}, {7, 8}, {8, 9}, {9, 10},
  {1, 4}, {2, 5}, {3, 6}, {4, 7}, 
  {5, 8}, {6, 9}, {1, 3}, {4, 6},
  {5, 7}, {6, 8}, {7, 9}, {8, 10}, 
  {1, 6}, {2, 7}, {3, 8}, {4, 9}
};

const std::bitset<10> LFSR_INI = 0b1111111111;

std::string ResaltarTaps(std::bitset<10>, std::vector<int>);
void GenerarSecuencia(std::bitset<10>, std::bitset<10>, int, int, int, std::vector<int>&);
void ImprimirConFormato(std::bitset<10>, std::bitset<10>, bool, bool, bool);

#endif