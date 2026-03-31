#include <iostream>
#include <string>
#include "funciones.h"

int main() {
  unsigned char key[16];
  unsigned char iv[16];
  unsigned char original_text_1[16];
  unsigned char original_text_2[16];
  unsigned char expanded_key[176];
  bool input_1_incomplete = false;
  bool input_2_incomplete = false;
  size_t length_input_1 = 0;
  size_t length_input_2 = 0;

  ReadHexBlock("Clave de 128 bits", key, input_1_incomplete, length_input_1);
  ReadHexBlock("Vector de Inicialización (IV)", iv, input_1_incomplete, length_input_1);
  ReadHexBlock("Bloque 1 de texto original", original_text_1, input_1_incomplete, length_input_1);
  ReadHexBlock("Bloque 2 de texto original", original_text_2, input_2_incomplete, length_input_2);

  unsigned char state_1[16];
  unsigned char state_2[16];
  for (int i = 0; i < 16; i++) {
    state_1[i] = original_text_1[i];
    state_2[i] = original_text_2[i];
  }

  PrintBlock(state_1);
  std::cout << std::endl;

  ExpandKey(key, expanded_key);

  std::cout << "\n==========================================\n";
  std::cout << "        INICIANDO CIFRADO CBC         \n";
  std::cout << "==========================================" << std::endl;

  EncryptCBC(state_1, state_2, iv, expanded_key, input_1_incomplete, input_2_incomplete, length_input_1, length_input_2);

  /*std::cout << "\n==========================================\n";
  std::cout << "       INICIANDO DESCIFRADO CBC       \n";
  std::cout << "==========================================" << std::endl;

  DecryptCBC(state_1, state_2, iv, expanded_key);*/

  return 0;
}