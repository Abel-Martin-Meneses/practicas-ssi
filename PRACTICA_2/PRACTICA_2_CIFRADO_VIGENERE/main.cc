#include <iostream>
#include <string>
#include <algorithm>

#include "funciones.h"

int main() {
  std::cout << "Seleccione el modo que desea utilizar\n";
  std::cout << "  [1] Cifrado\n";
  std::cout << "  [2] Descifrado\n";
  std::cout << "Modo: ";
  int modo{0};
  std::cin >> modo;
  std::cin.ignore(1000, '\n');

  if (modo != 1 && modo != 2) {
    std::cerr << "Ha introducido un modo erróneo.\n";
    return 1;
  }

  std::string mensaje_usuario{""};
  std::string clave{""};

  modo == 1 ? std::cout << "\nMensaje original: " : 
              std::cout << "\nMensaje cifrado:  ";

  std::getline(std::cin, mensaje_usuario);
  mensaje_usuario.erase(std::remove(mensaje_usuario.begin(), mensaje_usuario.end(), ' '), mensaje_usuario.end());
  std::cout << "Clave:            ";
  std::getline(std::cin, clave);
  LimpiarString(mensaje_usuario);
  LimpiarString(clave);
  
  std::string resultado{modo == 1 ? CifradoVigenere(mensaje_usuario, clave) : DescifradoVigenere(mensaje_usuario, clave)};

  modo == 1 ? std::cout << "Mensaje cifrado:  " << resultado << std::endl :
              std::cout << "Mensaje original: " << resultado << std::endl;

  ImprimirMensajeTrozos(mensaje_usuario, clave, resultado, modo);

  return 0;
}