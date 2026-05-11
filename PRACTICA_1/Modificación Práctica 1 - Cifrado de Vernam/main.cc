#include <iostream>
#include <string>

#include "funciones.h"

int main() {

  Intro();

  std::cout << "Modos:\n";
  std::cout << "  [1] Cifrar\n";
  std::cout << "  [2] Descifrar\n";
  std::cout << "\nIntroduzca el modo que desea utilizar: ";

  int modo{0};
  std::cin >> modo;  
  std::cin.ignore(1000,'\n');

  if (modo != 1 && modo != 2) {
    std::cerr << "Error: ha introducido un modo inválido.\n";
    return 1;
  }

  std::string mensaje_usuario{""};

  if (modo == 1) {
    std::cout << "Mensaje original: ";
    std::getline(std::cin, mensaje_usuario);
  } else {
    std::cout << "Mensaje cifrado: ";
    std::getline(std::cin, mensaje_usuario);
  }

  std::string mensaje_binario{ConvertirStringBinario(mensaje_usuario)};

  if (modo == 1) {
    std::cout << "\nMensaje original en binario: " << mensaje_binario << std::endl;
  } else {
    std::cout << "\nMensaje cifrado en binario: " << mensaje_binario << std::endl;
  }

  std::cout << "Longitud del mensaje binario: " << mensaje_binario.size() << std::endl;
  std::cout << "\nClave aleatoria (dejar en blanco para generar una aleatoria): ";
  std::string clave{""};
  std::getline(std::cin, clave);
  int bytes_msj_usuario{static_cast<int>(mensaje_usuario.size())};
  if (clave.empty()) {
    clave = GenerarClaveAleatoria(bytes_msj_usuario);
    std::cout << "Clave aleatoria: " << ConvertirStringBinario(clave) << std::endl << std::endl;
  } else if (clave.size() != mensaje_usuario.size() * 8) {
    std::cerr << "Error: el tamaño de la clave debe ser igual al tamaño del mensaje original\n";
    return 1;
  } else {
    clave = ConvertirBinarioString(clave);
  }
  std::string resultado{""};
  for (int i{0}; i < bytes_msj_usuario; i++) {
    resultado += mensaje_usuario[i] ^ clave[i];
  }

  // Modificación
  for (char c : resultado) {
    if (c < 32 || c > 126) {
      std::cout << "No Imprimible: " << c << std::endl;
    }
  }

  std::cout << std::endl;

  if (modo == 1) {
    std::cout << "Mensaje cifrado en binario: " << ConvertirStringBinario(resultado) << std::endl;
    std::cout << "Mensaje cifrado: " << resultado << std::endl;
  } else {
    std::cout << "Mensaje original en binario: " << ConvertirStringBinario(resultado) << std::endl;
    std::cout << "Mensaje original: " << resultado << std::endl;
  }

  return 0;
}