#include "funciones.h"

std::string DescifradoVigenere(std::string mensaje_usuario, std::string clave) {
  std::string resultado{""};
  for (size_t i{0}; i < mensaje_usuario.size(); i++) {
    size_t posicion_clave{i % clave.size()};
    int num_caracter_cifrado{(mensaje_usuario[i] + clave[posicion_clave]) % 26};
    resultado += static_cast<char>(num_caracter_cifrado + 65);
  }
  return resultado;
}

std::string CifradoVigenere(std::string mensaje_usuario, std::string clave) {
  std::string resultado{""};
  for (size_t i{0}; i < mensaje_usuario.size(); i++) {
    size_t posicion_clave{i % clave.size()};
    int num_caracter_cifrado{(mensaje_usuario[i] - clave[posicion_clave]) % 26};
    if (num_caracter_cifrado < 0) num_caracter_cifrado += 26;
    resultado += static_cast<char>(num_caracter_cifrado + 65);
  }
  return resultado;
}

void LimpiarString(std::string &s) {
  std::string buscar[] = {"á", "é", "í", "ó", "ú", "ñ", "Á", "É", "Í", "Ó", "Ú", "Ñ"};
  std::string poner[]  = {"A", "E", "I", "O", "U", "N", "A", "E", "I", "O", "U", "N"};
  for (int i = 0; i < 12; ++i) {
    size_t pos = 0;
    while ((pos = s.find(buscar[i], pos)) != std::string::npos) {
      s.replace(pos, buscar[i].length(), poner[i]);
      pos += poner[i].length();
    }
  }
  for (char &c : s) {
    c = std::toupper((unsigned char)c);
  }
}

void ImprimirMensajeTrozos(std::string mensaje, std::string clave, std::string resultado, int modo) {
  modo == 1 ? std::cout << "\nTexto original: " : std::cout << "\nTexto cifrado:  ";
  for (size_t i{0}; i < mensaje.size(); i += clave.size()) {
    std::cout << mensaje.substr(i, clave.size()) << ' ';
  }
  std::cout << "\nClave:          ";
  for (size_t i{0}; i < std::ceil(static_cast<float>(mensaje.size()) / clave.size()); i++) {
    if (i == std::ceil(static_cast<float>(mensaje.size()) / clave.size()) - 1) {
      std::cout << clave;
    } else {
      std::cout << clave << ' ';
    }
  }
  modo == 1 ? std::cout << "\nTexto cifrado:  " : std::cout << "\nTexto original: ";
  for (size_t i{0}; i < resultado.size(); i += clave.size()) {
    std::cout << resultado.substr(i, clave.size()) << ' ';
  }
  std::cout << std::endl;
}