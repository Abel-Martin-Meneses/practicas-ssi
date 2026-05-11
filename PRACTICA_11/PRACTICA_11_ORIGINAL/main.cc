#include <iostream>
#include <algorithm>

#include "funciones.h"
#include "punto.h"

int main() {
  int modo = SolicitarModo();
  int a, b, p;
  SolicitarParametros(a, b, p);
  std::vector<Punto> puntos = GenerarPuntos(a, b, p);

  Punto clave_secreta_a, clave_secreta_b, clave_publica_a;

  DifieHellmanEliptico(clave_publica_a, clave_secreta_a, clave_secreta_b, puntos, a, p);

  if (modo == 2) {
    int mensaje;
    std::cout << "Introduzca el mensaje a codificar (entero): ";
    std::cin >> mensaje;
    Punto punto_codificado;
    try {
      punto_codificado = CodificarMensaje(mensaje, puntos, p);
      std::cout << "Mensaje codificado en el punto: " << punto_codificado << std::endl;
    } catch (const std::invalid_argument& e) {
      std::cerr << e.what() << std::endl;
      return 1;
    }

    Punto mensaje_cifrado = CifradoElGamal(punto_codificado, clave_secreta_a, a, p);
    std::cout << "Mensaje cifrado y clave pública enviados de A a B: {" << mensaje_cifrado << ", " << clave_publica_a << "}" << std::endl;
  }

  return 0;
}