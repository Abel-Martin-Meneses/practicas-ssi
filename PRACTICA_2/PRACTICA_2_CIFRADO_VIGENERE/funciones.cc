#include "funciones.h"

/*
const std::string ALFABETO = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string CifradoVigenere(std::string mensaje, std::string clave) {
  std::string resultado = "";
  int N = ALFABETO.length();
  for (size_t i = 0; i < mensaje.size(); i++) {
    size_t pos_m = ALFABETO.find(mensaje[i]);
    size_t pos_k = ALFABETO.find(clave[i % clave.size()]);
    if (pos_m == std::string::npos) {
      resultado += mensaje[i];
    } else {
      // AQUÍ IRÍA LA LÓGICA SI NOS PIDEN SUMAR EN POSICIONES IMPARES Y RESTAR EN PARES Y VICEVERSA
      int nueva_pos = (pos_m + pos_k) % N;
      resultado += ALFABETO[nueva_pos];
    }
  }
  return resultado;
}
*/


std::string CifradoVigenere(std::string mensaje_usuario, std::string clave) {
  std::string resultado{""};
  for (size_t i{0}; i < mensaje_usuario.size(); i++) {
    size_t posicion_clave{i % clave.size()};
    int num_caracter_cifrado{(mensaje_usuario[i] + clave[posicion_clave]) % 26};
    resultado += static_cast<char>(num_caracter_cifrado + 65);
  }
  return resultado;
}


/*
std::string DescifradoVigenere(std::string mensaje, std::string clave) {
  std::string resultado = "";
  int N = ALFABETO.length();
  for (size_t i = 0; i < mensaje.size(); i++) {
    size_t pos_m = ALFABETO.find(mensaje[i]);
    size_t pos_k = ALFABETO.find(clave[i % clave.size()]);
    if (pos_m == std::string::npos) {
      resultado += mensaje[i];
    } else {
      // AQUÍ IRÍA LA LÓGICA DE SUMAR EN IMPARES Y RESTAR EN PARES Y VICEVERSA
      int nueva_pos = (static_cast<int>(pos_m) - static_cast<int>(pos_k));
      if (nueva_pos < 0) nueva_pos += N; 
      resultado += ALFABETO[nueva_pos % N];
    }
  }
  return resultado;
}
*/

std::string DescifradoVigenere(std::string mensaje_usuario, std::string clave) {
  std::string resultado{""};
  for (size_t i{0}; i < mensaje_usuario.size(); i++) {
    size_t posicion_clave{i % clave.size()};
    int num_caracter_cifrado{(mensaje_usuario[i] - clave[posicion_clave]) % 26};
    if (num_caracter_cifrado < 0) num_caracter_cifrado += 26;
    resultado += static_cast<char>(num_caracter_cifrado + 65);
  }
  return resultado;
}

// SI PERMITIMOS LA Ñ HAY QUE BORRARLA DE AQUÍ
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