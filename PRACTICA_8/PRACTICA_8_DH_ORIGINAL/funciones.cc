#include "funciones.h"

int ExpoRapida(int base, int exponente, int modulo) {
  int x{1};
  int y{base % modulo};
  while((exponente > 0) && (y > 1)) {
    if (exponente % 2 != 0) {
      x = (x * y) % modulo;
      exponente -= 1;
    } else {
      y = (y * y) % modulo;
      exponente /= 2;
    }
  }
  return x;
}

void ImprimirSolucion(int primo, int alpha, int secreto_A, int secreto_B, int num_yA, int num_yB, int clave_compartida) {
  std::cout << "p = " << primo;
  std::cout << "\nα = " << alpha;
  std::cout << "\nxA = " << secreto_A;
  std::cout << "\nxB = " << secreto_B;
  std::cout << "\nyA = " << num_yA;
  std::cout << "\nyB = " << num_yB;
  std::cout << "\nk = " << clave_compartida << std::endl;
}

void ProcesarDatos(int &primo, int &alpha, int &secreto_A, int &secreto_B) {
  std::cout << "Introduce el número primo (p): ";
  std::cin >> primo;
  std::cout << "Introduce el número α (α < p): ";
  std::cin >> alpha; 
  if (alpha >= primo) {
    std::cerr << "El número α debe ser menor que el número primo (α < p)\n";
    return;
  }
  std::cout << "Introduce el secreto de A (xA): ";
  std::cin >> secreto_A;
  std::cout << "Introduce el secreto de B (xB): ";
  std::cin >> secreto_B;
}