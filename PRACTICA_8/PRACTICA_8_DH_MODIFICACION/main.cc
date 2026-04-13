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
  int secreto_C{0};
  ProcesarDatos(primo, alpha, secreto_A, secreto_B, secreto_C);
  int num_yA{ExpoRapida(alpha, secreto_A, primo)};
  int num_yB{ExpoRapida(alpha, secreto_B, primo)};
  int num_yC{ExpoRapida(alpha, secreto_C, primo)};
  std::cout << "Alice envía a Bob: " << num_yA << std::endl;
  int aux_num_yB = ExpoRapida(alpha, secreto_A * secreto_B, primo);
  std::cout << "Bob envía a Carol: " << aux_num_yB << std::endl;
  int aux_num_yC = ExpoRapida(alpha, secreto_A * secreto_B * secreto_C, primo);
  std::cout << "Carol obtiene: " << aux_num_yC << std::endl;
  int clave_C = aux_num_yC;
  //ImprimirSolucion(primo, alpha, secreto_A, secreto_B, num_yA, num_yB, clave_A);
  
  std::cout << "Bob envía a Carol: " << num_yB << std::endl;
  aux_num_yC = ExpoRapida(alpha, secreto_B * secreto_C, primo);
  std::cout << "Carol envía a Alice: " << aux_num_yC << std::endl;
  int aux_num_yA = ExpoRapida(alpha, secreto_B * secreto_C * secreto_A, primo);
  std::cout << "Alice obtiene: " << aux_num_yA << std::endl;
  int clave_A = aux_num_yA;

  std::cout << "Carol envía a Alice: " << num_yC << std::endl;
  aux_num_yA = ExpoRapida(alpha, secreto_C * secreto_A, primo);
  std::cout << "Alice envía a Bob: " << aux_num_yA << std::endl;
  aux_num_yB = ExpoRapida(alpha, secreto_C * secreto_A * secreto_B, primo);
  std::cout << "Bob obtiene: " << aux_num_yB << std::endl;
  int clave_B = aux_num_yB;

  if (clave_A != clave_B || clave_A != clave_C || clave_B != clave_C) {
    std::cerr << "Error con las claves\n";
    return 1;
  }

  std::cout << "Clave compartida final: " << clave_A << std::endl;
  return 0;
}