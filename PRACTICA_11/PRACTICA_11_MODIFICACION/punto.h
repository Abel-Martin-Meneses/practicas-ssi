#include <limits>
#include <stdexcept>
#include <iostream>

#ifndef PUNTO_H
#define PUNTO_H

#define INF std::numeric_limits<int>::max()

class Punto {
 public:
  // El constructor por defecto debe crear el punto en el infinito, es decir, con coordenadas (inf, inf).
  Punto() : x(INF), y(INF), p(0) {};
  Punto(int x, int y, int p) : x(x), y(y), p(p) {}

  int getX() const { return x; }
  int getY() const { return y; }
  int getP() const { return p; }

  bool esInfinito() const { return x == INF && y == INF; }

  bool operator==(const Punto& other) const {
    return this->getX() == other.getX() && this->getY() == other.getY();
  }

  bool operator!=(const Punto& other) const {
    return !(*this == other);
  }

  friend std::ostream& operator<<(std::ostream& os, const Punto& punto) {
    if (punto.esInfinito()) {
      os << "Punto en el infinito";
    } else {
      os << "(" << punto.getX() << ", " << punto.getY() << ")";
    }
    return os;
  }

  void NegacionPunto() {
    if (esInfinito()) return;
    y = - y % p;
  }

 private:
  int x, y, p;
};

#endif