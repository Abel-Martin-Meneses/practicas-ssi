#include <iostream>

#include "funciones.h"

unsigned char HexCharToByte(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  return 0;
}

int main() {
  unsigned char clave[16];
  std::string input_clave;
  std::cout << "Clave de 128 bits en hexadecimal: ";
  std::cin >> input_clave;
  if (input_clave.length() != 32) {
    std::cerr << "Error: la clave debe tener exactamente 32 caracteres hexadecimales.\n";
    return 1;
  }

  for (int i{0}; i < 16; i++) {
    unsigned char mitad_izq = HexCharToByte(input_clave[i * 2]);
    unsigned char mitad_dcha = HexCharToByte(input_clave[(i * 2) + 1]);

    clave[i] = (mitad_izq << 4) | mitad_dcha;
  }

  std::string input_texto_original;
  unsigned char texto_original[16];
  std::cout << "Bloque de texto original de 128 bits en hexadecimal: ";
  std::cin >> input_texto_original;
  if (input_texto_original.length() != 32) {
    std::cerr << "Error: el bloque de texto original debe tener exactamente 32 caracteres hexadecimales.\n";
    return 1;
  }

  for (int i{0}; i < 16; i++) {
    unsigned char mitad_izq = HexCharToByte(input_texto_original[i * 2]);
    unsigned char mitad_dcha = HexCharToByte(input_texto_original[(i * 2) + 1]);

    texto_original[i] = (mitad_izq << 4) | mitad_dcha;
  }

  unsigned char estado[16];
  for (int i{0}; i < 16; i++) {
    estado[i] = texto_original[i];
  }

  unsigned char clave_expandida[176]; // 11 claves de 16 bytes (1 original + 10 subclaves)

  ExpandirClave(clave, clave_expandida);

  std::cout << "\n==========================================" << std::endl;
  std::cout << "        INICIANDO CIFRADO AES         " << std::endl;
  std::cout << "==========================================" << std::endl;

CifradoRijndael(estado, clave_expandida);

  std::cout << "\nBloque de Texto Cifrado: ";
  ImprimirBloque(estado);
  std::cout << std::endl;

  std::cout << "\n==========================================" << std::endl;
  std::cout << "       INICIANDO DESCIFRADO AES       " << std::endl;
  std::cout << "==========================================" << std::endl;

  DescifradoRijndael(estado, clave_expandida);

  std::cout << "\nBloque de Texto Descifrado (Debe coincidir con el original): ";
  ImprimirBloque(estado);
  std::cout << std::endl;

  return 0;
}