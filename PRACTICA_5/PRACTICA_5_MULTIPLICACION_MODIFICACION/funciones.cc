#include "funciones.h"

int ContadorUnos(std::bitset<8> byte_binario) {
  return byte_binario.count();
}

std::vector<std::bitset<8>> Distributiva(std::bitset<8> byte_menor_peso) {
  std::vector<std::bitset<8>> byte_separado;
  for (int i{0}; i < 8; i++) {
    if (byte_menor_peso[i] == 1) {
      std::bitset<8> aux;
      aux.set(i);
      byte_separado.emplace_back(aux);
    }
  }

  return byte_separado;
}

std::pair<std::bitset<8>, int> Multiplicacion(std::bitset<8> byte, std::vector<std::bitset<8>> byte_menor_peso_separado, std::bitset<8> byte_algoritmo) {
  std::vector<std::bitset<8>> multiplicaciones;
  int contador_reducciones{0};
  for (size_t i{0}; i < byte_menor_peso_separado.size(); i++) {
    std::bitset<8> byte_aux = byte;
    std::bitset<8> byte_actual{byte_menor_peso_separado[i]};
    int indice_uno{0};
    for (int j{0}; j < 8; j++) {
      if (byte_actual[j] == 1) {
        indice_uno = j;
      }
    }
    for (int j{0}; j < indice_uno; j++) {
      if (byte_aux[7] == 1) {
        byte_aux <<= 1;
        byte_aux ^= byte_algoritmo;
        contador_reducciones++;
      } else {
        byte_aux <<= 1;
      }
    }
    multiplicaciones.emplace_back(byte_aux);
  }
  std::bitset<8> resultado;
  for (std::bitset<8> b : multiplicaciones) {
    resultado ^= b;
  }
  return {resultado, contador_reducciones};
}