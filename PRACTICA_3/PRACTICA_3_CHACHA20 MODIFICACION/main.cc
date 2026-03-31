#include <iostream>
#include <random>

#include "funciones.h"

int main() {
  std::string clave, contador, nonce;
  std::cout << "Introduzca la clave de 256 bits en formato hexadecimal: ";
  std::getline(std::cin, clave);
  std::cout << "Introduzca el contador de 32 bits en formato hexadecimal: ";
  std::getline(std::cin, contador);
  std::cout << "Introduzca el nonce de 96 bits en formato hexadecimal: ";
  std::getline(std::cin, nonce);
  uint32_t estado_inicial[16];
  uint32_t salida[16];
  uint32_t aux[16];
  estado_inicial[0] = 0x61707865;
  estado_inicial[1] = 0x3320646e;
  estado_inicial[2] = 0x79622d32;
  estado_inicial[3] = 0x6b206574;
  std::vector<uint32_t> v_clave = LittleEndian(clave);
  for (size_t i = 0; i < 8 && i < v_clave.size(); ++i) {
    estado_inicial[4 + i] = v_clave[i];
  }
  std::vector<uint32_t> v_cont = LittleEndian(contador);
  if (!v_cont.empty()) {
    estado_inicial[12] = v_cont[0];
  }
  std::vector<uint32_t> v_nonce = LittleEndian(nonce);
  for (size_t i = 0; i < 3 && i < v_nonce.size(); ++i) {
    estado_inicial[13 + i] = v_nonce[i];
  }
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint32_t> dist(0, 0xFFFFFFFF);
  uint32_t num_aleatorio = dist(gen);
  estado_inicial[12] = num_aleatorio;
  std::cout << "\nCONTADOR ALEATORIO: " << std::hex << num_aleatorio << std::endl;
  std::cout << "Estado inicial:\n";
  ImprimirEstado(estado_inicial);
  ChaCha20(aux, estado_inicial, salida);
  std::cout << "Estado tras las 20 iteraciones:\n";
  ImprimirEstado(aux);
  std::cout << "Estado de salida del generador:\n";
  ImprimirEstado(salida);
  return 0;
}