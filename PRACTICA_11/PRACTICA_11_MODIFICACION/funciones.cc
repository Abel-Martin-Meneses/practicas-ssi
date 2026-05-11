#include <utility>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>

#include "funciones.h"

int SolicitarModo() {
  int modo;
  std::cout << "Seleccione el modo a utilizar:" << std::endl;
  std::cout << "1. Diffie-Hellman Elíptico" << std::endl;
  std::cout << "2. ElGamal Elíptico" << std::endl;
  std::cin >> modo;
  if (modo != 1 && modo != 2) {
    throw std::invalid_argument("Modo no válido. Por favor, seleccione 1 o 2.");
  }
  return modo;
}

void SolicitarParametros(int &a, int &b, int &p) {
  std::cout << "Introduzca el parámetro a: ";
  std::cin >> a;
  std::cout << "Introduzca el parámetro b: ";
  std::cin >> b;
  std::cout << "Introduzca el módulo p: ";
  std::cin >> p;
}

Punto SolicitarPuntoGenerador(int p) {
  int coord_x, coord_y;
  std::cout << "Introduzca la coordenada x del punto generador: ";
  std::cin >> coord_x;
  std::cout << "Introduzca la coordenada y del punto generador: ";
  std::cin >> coord_y;
  Punto punto_generador(coord_x, coord_y, p);
  return punto_generador;
}

void SolicitarClavePrivada(int &clave_privada_a, int &clave_privada_b) {
  std::cout << "Introduzca la clave privada de A (dA): ";
  std::cin >> clave_privada_a;
  std::cout << "Introduzca la clave privada de B (dB): ";
  std::cin >> clave_privada_b;
}

void CalcularClavePublica(const Punto &punto_generador, int clave_privada_a, int clave_privada_b, Punto &clave_publica_a, Punto &clave_publica_b, int a) {
  clave_publica_a = MultiplicacionPunto(punto_generador, clave_privada_a, a, punto_generador.getP());
  clave_publica_b = MultiplicacionPunto(punto_generador, clave_privada_b, a, punto_generador.getP());
  std::cout << "Clave pública de A: punto dA * G = " << clave_privada_a << " * " << punto_generador << " = " << clave_publica_a << std::endl;
  std::cout << "Clave pública de B: punto dB * G = " << clave_privada_b << " * " << punto_generador << " = " << clave_publica_b << std::endl;
}

void CalcularClaveCompartida(const Punto &clave_publica, int clave_privada, Punto &clave_secreta, int a, int p) {
  clave_secreta = MultiplicacionPunto(clave_publica, clave_privada, a, p);
}

void DifieHellmanEliptico(int& clave_privada_b, Punto& clave_publica_a, Punto& clave_secreta_a, Punto& clave_secreta_b, const std::vector<Punto>& puntos, int a, int p) {
  std::cout << "Puntos generados en la curva elíptica:" << std::endl;
  for (const Punto& punto : puntos) {
    std::cout << "(" << punto.getX() << ", " << punto.getY() << ")" << std::endl;
  }
  Punto punto_generador = SolicitarPuntoGenerador(p);
  if (std::find(puntos.begin(), puntos.end(), punto_generador) == puntos.end()) {
    throw std::invalid_argument("El punto generador no pertenece a la curva elíptica.");
    return;
  }

  int clave_privada_a;
  SolicitarClavePrivada(clave_privada_a, clave_privada_b);

  Punto clave_publica_b;
  CalcularClavePublica(punto_generador, clave_privada_a, clave_privada_b, clave_publica_a, clave_publica_b, a);

  CalcularClaveCompartida(clave_publica_b, clave_privada_a, clave_secreta_a, a, p);
  CalcularClaveCompartida(clave_publica_a, clave_privada_b, clave_secreta_b, a, p);
  std::cout << "Clave secreta compartida calculada por A: " << clave_privada_a << " * " << clave_publica_b << " = " << clave_secreta_a << std::endl;
  std::cout << "Clave secreta compartida calculada por B: " << clave_privada_b << " * " << clave_publica_a << " = " << clave_secreta_b << std::endl;  

  if (clave_secreta_a != clave_secreta_b) {
    throw std::runtime_error("Las claves secretas no coinciden.");
    return;
  }
}

long long ExpoRapida(long long base, long long exponente, long long modulo) {
  long long x{1};
  long long y{base % modulo};

  while (exponente > 0) {
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

void EuclidesExtendido(int a, int b, int &mcd, int &inverso) {
  int x_prev = a; // x_{i-1}
  int x_curr = b; // x_i

  int z_prev2 = 0; // z_{i-2}
  int z_prev1 = 1; // z_{i-1}

  while (x_curr != 0) {
    int q = x_prev / x_curr;

    int resto = x_prev % x_curr;

    int z_curr = (-q * z_prev1 + z_prev2) % a;

    if (z_curr < 0) {
      z_curr += a;
    }

    x_prev = x_curr;
    x_curr = resto;

    z_prev2 = z_prev1;
    z_prev1 = z_curr;
  }

  mcd = x_prev;

  if (mcd == 1) {
    inverso = z_prev2;
  } else {
    inverso = -1;
  }
}

int InversoModular(int a, int p) {
  int mcd{0};
  int inverso{0};

  EuclidesExtendido(p, a, mcd, inverso);

  return inverso;
}

std::vector<Punto> GenerarPuntos(int a, int b, int p) {
  std::vector<Punto> puntos;
  for (int x{0}; x < p; x++) {
    int x_value = (x * x * x + a * x + b) % p;
    for (int y{0}; y < p; y++) {
      if ((y * y) % p == x_value) {
        puntos.emplace_back(x, y, p);
      }
    }
  }
  return puntos;
}

Punto CodificarMensaje(int mensaje, const std::vector<Punto> &puntos, int p, int& h) {
  int m_potencia_2{1};
  while (m_potencia_2 <= mensaje) {
    m_potencia_2 *= 2;
  }
  h = p / m_potencia_2;
  for (int j{0}; j < h; j++) {
    for (const Punto &punto : puntos) {
      if (punto.getX() == (mensaje * h) + j) {
        return punto;
      }
    }
  }
  throw std::invalid_argument("Mensaje no puede ser codificado");
}

Punto SumaPuntos(const Punto &p1, const Punto &p2, int a, int p) {
  if (p1.esInfinito()) return p2;
  if (p2.esInfinito()) return p1;

  if (p1.getX() == p2.getX() && (p1.getY() + p2.getY()) % p == 0) {
    return Punto(); // Punto en el infinito
  }

  int lambda{0};
  if (p1 == p2) {
    int numerador = (3 * p1.getX() * p1.getX() + a + p) % p;
    int denominador = (2 * p1.getY()) % p;
    
    lambda = (numerador * InversoModular(denominador, p)) % p;
  } else {
    int numerador = (p2.getY() - p1.getY() + p) % p;
    int denominador = (p2.getX() - p1.getX() + p) % p;
    
    lambda = (numerador * InversoModular(denominador, p)) % p;
  }

  int x3 = (lambda * lambda - p1.getX() - p2.getX() + 2 * p) % p;
  int y3 = (lambda * (p1.getX() - x3 + p) - p1.getY() + p) % p;

  return Punto(x3, y3, p);
}

Punto MultiplicacionPunto(const Punto &punto, int escalar, int a, int p) {
  if (escalar == 0 || punto.esInfinito()) {
    return Punto();
  }
  Punto resultado{punto};
  for (int i{0}; i < escalar - 1; ++i) {
    resultado = SumaPuntos(resultado, punto, a, p);
  }
  return resultado;
}

Punto CifradoElGamal(const Punto &mensaje, const Punto &clave_publica, int a, int p) {
  return SumaPuntos(mensaje, clave_publica, a, p);
}

int DescifradoElGamal(const Punto &mensaje_cifrado, const Punto &clave_publica, const int clave_privada, int a, int p, int h) {
  Punto clave_secreta_compartida{MultiplicacionPunto(clave_publica, clave_privada, a, p)};
  clave_secreta_compartida.NegacionPunto();
  Punto resta{SumaPuntos(mensaje_cifrado, clave_secreta_compartida, a , p)};
  int m_recuperado{resta.getX() / h};
  return m_recuperado;
}