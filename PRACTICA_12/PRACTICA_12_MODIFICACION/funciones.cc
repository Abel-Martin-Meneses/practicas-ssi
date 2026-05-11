#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <random>

#include "funciones.h"

const std::string ALFABETO = "ABCDEFGHIJKLMNOPQRSTUVWXYZ .,!";
const int BASE = 30;

long long ExpoRapida(long long base, long long exponente, long long modulo) {
  long long x{1};
  long long y{base % modulo};
  
  while(exponente > 0) {
    if (exponente % 2 != 0) {
      x = (long long)(((__int128)x * y) % modulo);
      exponente -= 1;
    } else {
      y = (long long)(((__int128)y * y) % modulo);
      exponente /= 2;
    }
  }
  return x;
}

bool ComprobarPrimosPequeños(long long num) {
  std::vector<long long> primos_pequeños{2, 3, 5, 7, 11};
  for (size_t i{0}; i < primos_pequeños.size(); i++) {
    if (num == primos_pequeños[i]) {
      return true;
    }
  }
  return false;
}

std::vector<long long> GenerarNumerosAleatorios(long long num) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<long long> distribucion(2, num - 1);

  std::vector<long long> numeros_aleatorios;
  int num_enteros_aleatorios{std::min(50, int(num / 2))};

  for (int i{0}; i < num_enteros_aleatorios; i++) {
    numeros_aleatorios.emplace_back(distribucion(gen));
  }

  return numeros_aleatorios;
}

// Test Lehman-Peralta
bool ComprobarPrimos(long long num_p) {
  if (ComprobarPrimosPequeños(num_p)) return true;
  std::vector<long long> numeros_aleatorios{GenerarNumerosAleatorios(num_p)};
  std::vector<long long> resultados;
  for (long long n : numeros_aleatorios) {
    resultados.emplace_back(ExpoRapida(n, (num_p - 1) / 2, num_p));
  }

  bool todos_iguales{true};
  for (long long r : resultados) {
    if (r != 1) {
      todos_iguales = false;
    }
  }

  if (todos_iguales) {
    return false;
  } else {
    for (long long r : resultados) {
      if (r != num_p - 1 && r != 1) {
        return false;
      }
    }
  }

  return true;
}

std::pair<bool, long long> PrimosEuclidesExtendido(long long a, long long b) {
  long long x_prev = b;
  long long x_curr = a;

  long long z_prev = 0;
  long long z_curr = 1;

  while (x_curr != 0) {
    long long q = x_prev / x_curr;

    long long x_next = x_prev % x_curr;
    long long z_next = z_prev - (q * z_curr);

    x_prev = x_curr;
    x_curr = x_next;

    z_prev = z_curr;
    z_curr = z_next;
  }

  if (x_prev != 1) {
    return {false, 0};
  }

  if (z_prev < 0) {
    z_prev += b;
  }

  return {true, z_prev};
}

std::vector<long long> CifradoRSA(std::vector<long long> bloques_mensaje_original, long long num_e, long long num_n) {
  std::vector<long long> bloques_cifrados;
  std::cout << GREEN << "Se calcula en decimal el texto cifrado: ";
  for (size_t i{0}; i < bloques_mensaje_original.size(); i++) {
    long long bloque_cifrado{ExpoRapida(bloques_mensaje_original[i], num_e, num_n)};
    if (i == bloques_mensaje_original.size() - 1) {
      std::cout << bloque_cifrado << RESET << std::endl;
    } else {
      std::cout << bloque_cifrado << ", ";
    }
    bloques_cifrados.emplace_back(bloque_cifrado);
  }
  return bloques_cifrados;
}

/*
std::vector<long long> DescifradoRSA(std::vector<long long> bloques_cifrados, long long num_d, long long num_n) {
  std::vector<long long> bloques_mensaje_original;
  for (size_t i{0}; i < bloques_cifrados.size(); i++) {
    bloques_mensaje_original.emplace_back(ExpoRapida(bloques_cifrados[i], num_d, num_n));
  }
  return bloques_mensaje_original;
}
*/

bool ConfigurarClaves(long long& num_n, long long& num_e, long long& num_d) {
  long long p{0}, q{0};
  std::cout << "Introduce el primo p: "; std::cin >> p;
  std::cout << "Introduce el primo q: "; std::cin >> q;
  std::cout << "Introduce la clave privada d: "; std::cin >> num_d;

  if (!ComprobarPrimos(p) || !ComprobarPrimos(q)) {
    std::cerr << "Error: Los números p y q tienen que ser primos.\n";
    return false;
  }

  std::cout << GREEN << "\nSe comprueba que " << p << " y " << q << " son números primos.\n" << RESET;

  long long fi_n{(p - 1) * (q - 1)};
  std::pair<bool, long long> primos_e{PrimosEuclidesExtendido(num_d, fi_n)};
  
  if (!primos_e.first) {
    std::cerr << "Error: Los números d y (p - 1)(q - 1) deben ser primos entre sí.\n";
    return false;
  }

  std::cout << GREEN << "Se comprueba que " << num_d << " es primo con φ = " << fi_n << ".\n" << RESET; 

  num_e = primos_e.second;
  std::cout << GREEN << "Se calcula e = " << num_e << ".\n" << RESET;
  num_n = p * q;
  return true;
}

// Convierte Texto ORIGINAL a bloques decimales (Tamaño j-1)
std::vector<long long> ProcesarTextoADecimal(std::string mensaje, long long num_n) {
  int tamaño_bloque{int(log(num_n) / log(BASE))}; 
  std::cout << GREEN << "\nComo n = " << num_n << ", se divide el texto en bloques de " << tamaño_bloque << " caracteres.\n" << RESET;
  
  while (int(mensaje.size()) % tamaño_bloque != 0) {
    mensaje.append(".");
  }

  std::vector<long long> decimal_bloques;
  std::cout << GREEN << "Se pasa cada bloque a decimal para poder cifrar, obteniendo ";
  for (size_t i{0}; i < mensaje.size(); i += tamaño_bloque) {
    std::string bloque_actual{mensaje.substr(i, tamaño_bloque)};
    long long valor_bloque{0};
    for (size_t k{0}; k < bloque_actual.size(); k++) {
      long long valor_letra = ALFABETO.find(bloque_actual[k]);
      valor_bloque += valor_letra * pow(BASE, bloque_actual.size() - 1 - k);
    }
    decimal_bloques.emplace_back(valor_bloque);
    if (i == mensaje.size() - tamaño_bloque) {
      std::cout << valor_bloque << RESET << std::endl;
    } else {
      std::cout << valor_bloque << ", ";
    }
  }
  return decimal_bloques;
}

std::string DecimalATexto(long long valor_bloque, long long num_n) {
  int tamaño_bloque{int(log(num_n) / log(BASE))}; 
  std::string texto_bloque{""};
  
  for (int i{0}; i < tamaño_bloque; i++) {
    long long valor_letra{valor_bloque % BASE};
    
    texto_bloque += ALFABETO[valor_letra];
    
    valor_bloque /= BASE;
  }
  
  std::reverse(texto_bloque.begin(), texto_bloque.end());
  
  return texto_bloque;
}

long long VerificarFirma(long long bloque_firmado, long long num_e, long long num_n) {
  return ExpoRapida(bloque_firmado, num_e, num_n);
}