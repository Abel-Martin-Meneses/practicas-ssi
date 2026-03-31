#include <iostream>

#include "funciones.h"

std::string ResaltarTaps(std::bitset<10> registro, std::vector<int> indices) {
  std::string reg_str = registro.to_string();
  std::string resultado = "";
  
  for (int i{0}; i < 10; i++) {
    bool resaltar = false;
    int bitset_idx = 9 - i;     
    for (int idx : indices) {
      if (idx == bitset_idx) resaltar = true;
    }
    
    if (resaltar) {
      resultado += std::string(GREEN) + BOLD + reg_str[i] + RESET;
    } else {
      resultado += reg_str[i];
    }
  }
  return resultado;
}

void GenerarSecuencia(std::bitset<10> lfsr_1, std::bitset<10> lfsr_2, int longitud_salida, int tap_1, int tap_2, std::vector<int>& secuencia_salida) {
  for (int i{0}; i < longitud_salida; i++) {
    bool salida_lfsr_1 = lfsr_1[0];
    bool realimentacion_lfsr_1 = lfsr_1[7] ^ lfsr_1[0];
    bool salida_lfsr_2 = lfsr_2[10 - tap_1] ^ lfsr_2[10 - tap_2];
    bool realimentacion_lfsr_2 = lfsr_2[8] ^ lfsr_2[7] ^ lfsr_2[4] ^ lfsr_2[2] ^ lfsr_2[1] ^ lfsr_2[0];
    bool salida = salida_lfsr_1 ^ salida_lfsr_2;
    secuencia_salida.emplace_back(salida);

    ImprimirConFormato(lfsr_1, lfsr_2, realimentacion_lfsr_1, realimentacion_lfsr_2, salida);

    lfsr_1 >>= 1;
    lfsr_1[9] = realimentacion_lfsr_1;
    lfsr_2 >>= 1;
    lfsr_2[9] = realimentacion_lfsr_2;
  }
}

void ImprimirConFormato(std::bitset<10> lfsr_1, std::bitset<10> lfsr_2, bool realimentacion_lfsr_1, bool realimentacion_lfsr_2, bool salida) {
  std::cout << ResaltarTaps(lfsr_1, {7, 0}) << "    ";
  std::cout << std::string(7, ' ') << YELLOW << realimentacion_lfsr_1 << RESET << std::string(11, ' ');
  std::cout << ResaltarTaps(lfsr_2, {8, 7, 4, 2, 1, 0}) << "    ";
  std::cout << std::string(7, ' ') << YELLOW << realimentacion_lfsr_2 << RESET << std::string(11, ' ');
  std::cout << BOLD << CYAN << "       " << salida << RESET << std::endl;
} 