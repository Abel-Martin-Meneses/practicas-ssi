#include <iostream>

#include "funciones.h"

int main(int argc, char* argv[]) {
  bool ejemplo_guion{false};
  if (argc != 1 && argc != 2) {
    std::cerr << "El programa se tiene que ejecutar con uno o ningún argumento.\n";
    return 1;
  } else if (argc == 2 && std::string(argv[1]) == "eg") {
    ejemplo_guion = true;
  }

  if (ejemplo_guion) {
    EjecutarEjemplosGuion();
    return 0;
  }
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