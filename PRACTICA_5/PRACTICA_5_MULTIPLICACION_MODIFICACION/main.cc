#include <iostream>
#include <bitset>

#include "funciones.h"

std::bitset<8> BYTE_SNOW_3G = 0b10101001;
std::bitset<8> BYTE_AES = 0b00011011;

int main() {
  std::string primer_hex{""};
  std::cout << "Primer byte: ";
  std::cin >> primer_hex;
  if (primer_hex.length() != 2) {
    std::cerr << "Debe introducir un byte hexadecimal de la forma XX donde X es un valor entre 0-F\n"; 
    return 1;
  } 
  int aux{std::stoi(primer_hex, nullptr, 16)};
  std::bitset<8> primer_byte_binario{std::bitset<8>(aux)};
  
  std::string segundo_hex{""};
  std::cout << "Segundo byte: ";
  std::cin >> segundo_hex;
  if (segundo_hex.length() != 2) {
    std::cerr << "Debe introducir un byte hexadecimal de la forma XX donde X es un valor entre 0-F\n"; 
    return 1;
  }
  aux = std::stoi(segundo_hex, nullptr, 16);
  std::bitset<8> segundo_byte_binario{std::bitset<8>(aux)};

  std::string modo;
  std::cout << "Introduce modo (SNOW3G / AES): ";
  std::cin >> modo;
  if (modo != "SNOW3G" && modo != "AES" && modo != "snow3g" && modo != "aes") {
    std::cerr << "Ha introducido un modo erróneo. Debe ser SNOW3G o AES\n";
    return 1;
  }

  std::bitset<8> byte_menor_peso = (ContadorUnos(primer_byte_binario) < ContadorUnos(segundo_byte_binario)) ? primer_byte_binario : segundo_byte_binario;
  std::bitset<8> byte_mayor_peso = (byte_menor_peso == primer_byte_binario) ? segundo_byte_binario : primer_byte_binario;

  std::vector<std::bitset<8>> byte_menor_peso_separado{Distributiva(byte_menor_peso)};
  std::pair<std::bitset<8>, int> resultado;
  std::cout << "\nPrimer byte: " << primer_byte_binario << std::endl;
  std::cout << "Segundo byte: " << segundo_byte_binario << std::endl;
  if (modo == "SNOW3G") {
    resultado = Multiplicacion(byte_mayor_peso, byte_menor_peso_separado, BYTE_SNOW_3G);
    std::cout << "Byte algoritmo: " << BYTE_SNOW_3G << std::endl;
    std::cout << "Multiplicación: " << resultado.first << std::endl;
    std::cout << "Contador reducciones: " << resultado.second << std::endl;
  } else {
    resultado = Multiplicacion(byte_mayor_peso, byte_menor_peso_separado, BYTE_AES);
    std::cout << "Byte algoritmo: " << BYTE_AES << std::endl;
    std::cout << "Multiplicación: " << resultado.first << std::endl;
    std::cout << "Contador reducciones: " << resultado.second << std::endl;
  }

  return 0;
}