#include <iostream>
#include <iomanip>

#include "funciones.h"

int main() {
  std::cout << "ID del satélite: ";
  int id_sat{0};
  std::cin >> id_sat;
  if (id_sat < 1 || id_sat > 32) {
    std::cerr << "Error: ha introducido un número de satélite erróneo, debe ser entre 1 y 32.\n"; 
    return 1;
  }
  std::cout << "Longitud de la secuencia de salida: ";
  int longitud_salida{0};
  std::cin >> longitud_salida;

  std::bitset<10> lfsr_1 = LFSR_INI;
  std::bitset<10> lfsr_2 = LFSR_INI;

  const int tap_1 = SATELITES[id_sat - 1][0];
  const int tap_2 = SATELITES[id_sat - 1][1];

  std::vector<int> secuencia_salida{};

  std::cout << std::endl << std::left
          << BOLD << std::setw(14)  << "LFSR1"
          << std::setw(20) << "Realimentación"
          << std::setw(14) << "LFSR2"
          << std::setw(20) << "Realimentación"
          << std::setw(10) << "Secuencia C/A"
          << std::endl << RESET;
  
  std::cout << std::string(82, '-') << std::endl;

  GenerarSecuencia(lfsr_1, lfsr_2, longitud_salida, tap_1, tap_2, secuencia_salida);

  std::cout << "\nSecuencia completa: ";
  for (int n : secuencia_salida) {
    std::cout << CYAN << n;
  }
  std::cout << RESET << std::endl;
  
  return 0;
}