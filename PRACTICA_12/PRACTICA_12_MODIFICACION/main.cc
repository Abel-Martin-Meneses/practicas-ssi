#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "funciones.h"

int main() {
  int opcion_principal{0};

  std::cout << "\n========================================\n";
  std::cout << "                 FIRMA RSA\n";
  std::cout << "========================================\n";
  std::cout << "1. Cifrar\n";
  std::cout << "2. Verificar firma\n";
  std::cout << "3. Salir\n";
  std::cout << "Elige una opción: ";
  std::cin >> opcion_principal;

  if (opcion_principal == 3) {
    std::cout << "Saliendo...\n";
    return 1;
  }

  if (opcion_principal != 1 && opcion_principal != 2) {
    std::cerr << "Introduzca una opción válida: " << opcion_principal << " no es una opción disponible.\n";
    return 1;
  }

  if (opcion_principal == 1) {
    long long num_n{0}, num_e{0}, num_d{0};
    if (!ConfigurarClaves(num_n, num_e, num_d)) {
      return 1;
    }

    std::cout << "Introduce el texto a cifrar (MAYÚSCULAS): ";
    std::string texto;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, texto);

    std::vector<long long> bloques_originales{ProcesarTextoADecimal(texto, num_n)};
    std::vector<long long> bloques_cifrados{CifradoRSA(bloques_originales, num_e, num_n)};

    std::cout << "\nBloques cifrados: \n";
    for (long long c : bloques_cifrados) {
      std::cout << c << " ";
    }
    std::cout << "\n";
  } else if (opcion_principal == 2) {
    long long num_n{0}, num_e{0}, bloque_firma{0};
    std::cout << "Introduce el bloque de la firma a verificar: "; std::cin >> bloque_firma;
    std::cout << "Introduce el número n: "; std::cin >> num_n;
    std::cout << "Introduce el número e: "; std::cin >> num_e;
    long long firma_verificada{VerificarFirma(bloque_firma, num_e, num_n)};
    std::cout << GREEN << "Se calcula la potencia " << bloque_firma << "^" << num_e << " mod " << num_n << " obteniendo " << firma_verificada << RESET << std::endl;

    std::string texto_original{DecimalATexto(firma_verificada, num_n)};
    std::cout << GREEN << "Se decodifica obteniendo el texto original: " << texto_original << RESET << std::endl;
  }
  return 0;
}