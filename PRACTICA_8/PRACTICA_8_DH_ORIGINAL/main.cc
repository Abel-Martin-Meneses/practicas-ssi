#include <iostream>

#include "funciones.h"

int main() {
  int primo{0};
  int alpha{0};
  int secreto_A{0};
  int secreto_B{0};
  ProcesarDatos(primo, alpha, secreto_A, secreto_B);
  int num_yA{ExpoRapida(alpha, secreto_A, primo)};
  int num_yB{ExpoRapida(alpha, secreto_B, primo)};
  int clave_compartida{ExpoRapida(num_yA, secreto_B, primo)};
  ImprimirSolucion(primo, alpha, secreto_A, secreto_B, num_yA, num_yB, clave_compartida);
  
  return 0;
}