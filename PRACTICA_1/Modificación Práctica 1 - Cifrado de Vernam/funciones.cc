#include "funciones.h"

void Intro() {
  std::cout << CYAN << BOLD << "========================================" << RESET << std::endl;
  std::cout << CYAN << BOLD << "       CIFRADO DE VERNAM (OTP)          " << RESET << std::endl;
  std::cout << CYAN << BOLD << "========================================" << RESET << std::endl;
  
  std::cout << GREEN << "Este programa permite realizar el cifrado y" << std::endl;
  std::cout << "descifrado de mensajes utilizando la técnica" << std::endl;
  std::cout << "de Vernam (One-Time Pad)." << RESET << std::endl;
  
  std::cout << "\n" << YELLOW << BOLD << "PASOS DEL PROGRAMA:" << RESET << std::endl;
  std::cout << " 1. " << BOLD << "Modo:" << RESET << " Seleccione Cifrar [1] o Descifrar [2]." << std::endl;
  std::cout << " 2. " << BOLD << "Mensaje:" << RESET << " Introduzca el texto a procesar." << std::endl;
  std::cout << " 3. " << BOLD << "Clave:" << RESET << " Introduzca una cadena de bits (0s y 1s)." << std::endl;
  std::cout << "    " << CYAN << "* Si deja la clave vacia, se generara una *" << RESET << std::endl;
  std::cout << "    " << CYAN << "* aleatoria automaticamente.              *" << RESET << std::endl;
  std::cout << " 4. " << BOLD << "Resultado:" << RESET << " El programa mostrara el proceso" << std::endl;
  std::cout << "    binario y el mensaje resultante." << std::endl;
  std::cout << CYAN << "----------------------------------------\n" << RESET << std::endl;
}

std::string GenerarClaveAleatoria(int bytes_msj_original) {
  std::string clave;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(0,255);
  for (int i{0}; i < bytes_msj_original; i++) {
    clave += static_cast<unsigned char>(distrib(gen));
  }
  return clave;
}

std::string ConvertirStringBinario(const std::string& mensaje) {
  std::string binario{""};
  for (char c : mensaje) {
    binario += std::bitset<8>(c).to_string();
  }
  return binario;
}

std::string ConvertirBinarioString(const std::string& binario) {
  std::stringstream ss;
  for (size_t i{0}; i < binario.size(); i += 8) {
    ss << static_cast<unsigned char>(std::bitset<8>(binario.substr(i, 8)).to_ulong());
  }
  return ss.str();
}