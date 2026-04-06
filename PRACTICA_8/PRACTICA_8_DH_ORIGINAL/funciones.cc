#include "funciones.h"

std::vector<std::vector<int>> EJEMPLOS_GUION{{13, 4, 5, 2}, {43, 23, 25, 33}, {113, 43, 54, 71}};

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

void EjecutarEjemplosGuion() {
  for (int i{0}; i < 3; i++) {
    std::cout << "====== EJEMPLO " << i + 1 << " ======\n";
    int primo{EJEMPLOS_GUION[i][0]};
    int alpha{EJEMPLOS_GUION[i][1]};
    int secreto_A{EJEMPLOS_GUION[i][2]};
    int secreto_B{EJEMPLOS_GUION[i][3]};
    int num_yA{ExpoRapida(alpha, secreto_A, primo)};
    int num_yB{ExpoRapida(alpha, secreto_B, primo)};
    int clave_compartida{ExpoRapida(num_yB, secreto_A, primo)};
    ImprimirSolucion(primo, alpha, secreto_A, secreto_B, num_yA, num_yB, clave_compartida);
  }
}