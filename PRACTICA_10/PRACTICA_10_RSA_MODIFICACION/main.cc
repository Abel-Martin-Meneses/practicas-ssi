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
  std::cout << "        CRIPTO-SISTEMA RSA\n";
  std::cout << "========================================\n";
  std::cout << "1. Cifrar\n";
  std::cout << "2. Descifrar\n";
  std::cout << "3. Salir\n";
  std::cout << "Elige una opción: ";
  std::cin >> opcion_principal;

  if (opcion_principal == 3) {
    std::cout << "Saliendo...\n";
    return 1;
  }

  if (opcion_principal != 1 && opcion_principal != 2) {
    std::cerr << "Introduzca una opción válida: " << opcion_principal
              << " no es una opción disponible.\n";
    return 1;
  }

  long long num_n{0}, num_e{0}, num_d{0};
  if (!ConfigurarClaves(num_n, num_e, num_d)) {
    return 1;
  }

  int opcion_tipo{0};
  std::cout << "\n¿Qué formato de datos deseas "
            << (opcion_principal == 1 ? "cifrar" : "descifrar") << "?\n";

  if (opcion_principal == 1) {
    std::cout << "1. Texto original (A-Z)\n";
    std::cout << "2. Número directamente\n";
  } else {
    std::cout << "1. Lista de números cifrados (Ej: 111 4 88)\n";
    std::cout << "2. Número suelto\n";
    std::cout << "3. Texto cifrado en letras (Ej: XLPFDS)\n";
  }

  std::cout << "Opción: ";
  std::cin >> opcion_tipo;

  // --- LÓGICA DE CIFRADO ---
  if (opcion_principal == 1) {
    if (opcion_tipo == 1) {
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
    } else if (opcion_tipo == 2) {
      std::cout << "Introduce el número a cifrar: ";
      long long numero;
      std::cin >> numero;

      std::vector<long long> cifrado{CifradoRSA({numero}, num_e, num_n)};
      std::cout << "\nNúmero cifrado: " << cifrado[0] << "\n";
    }
  }
  // --- LÓGICA DE DESCIFRADO ---
  else if (opcion_principal == 2) {
    if (opcion_tipo == 1) {
      std::cout << "¿Cuántos bloques numéricos vas a descifrar?: ";
      int cantidad;
      std::cin >> cantidad;

      std::vector<long long> bloques_cifrados;
      for (int i{0}; i < cantidad; i++) {
        long long bloque;
        std::cout << "Bloque " << i + 1 << ": ";
        std::cin >> bloque;
        bloques_cifrados.push_back(bloque);
      }
      std::vector<long long> bloques_descifrados{DescifradoRSA(bloques_cifrados, num_d, num_n)};
      std::string texto_recuperado{ProcesarDecimalATexto(bloques_descifrados, num_n)};
      std::cout << "\nTexto original: " << texto_recuperado << "\n";

    } else if (opcion_tipo == 2) {
      std::cout << "Introduce el número cifrado: ";
      long long numero_cifrado;
      std::cin >> numero_cifrado;

      std::vector<long long> descifrado{DescifradoRSA({numero_cifrado}, num_d, num_n)};
      std::cout << "\nNúmero original: " << descifrado[0] << "\n";

    } else if (opcion_tipo == 3) {
      std::cout << "Introduce el texto cifrado (MAYÚSCULAS): ";
      std::string texto_cifrado;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::getline(std::cin, texto_cifrado);

      std::vector<long long> bloques_cifrados_num{ProcesarTextoCifradoADecimal(texto_cifrado, num_n)};
      std::vector<long long> bloques_descifrados{DescifradoRSA(bloques_cifrados_num, num_d, num_n)};
      std::string texto_original{ProcesarDecimalATexto(bloques_descifrados, num_n)};

      std::cout << "\nMensaje descifrado original: " << texto_original << "\n";
    }
  }
  return 0;
}