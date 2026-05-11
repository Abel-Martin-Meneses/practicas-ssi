#include <vector>

#include "punto.h"

#ifndef FUNCIONES_H
#define FUNCIONES_H

int SolicitarModo();

void SolicitarParametros(int &a, int &b, int &p);
Punto SolicitarPuntoGenerador(int p);
void SolicitarClavePrivada(int &clave_privada_a, int &clave_privada_b);
void CalcularClavePublica(const Punto &punto_generador, int clave_privada_a, int clave_privada_b, Punto &clave_publica_a, Punto &clave_publica_b, int a);
void CalcularClaveCompartida(const Punto &clave_publica, int clave_privada, Punto &clave_secreta, int a, int p);

void DifieHellmanEliptico(int& clave_privada_b, Punto& clave_publica_a, Punto& clave_secreta_a, Punto& clave_secreta_b, const std::vector<Punto>& puntos, int a, int p);

long long ExpoRapida(long long, long long, long long);

void EuclidesExtendido(int, int, int&, int&);
int InversoModular(int a, int p);

std::vector<Punto> GenerarPuntos(int a, int b, int p);
Punto CodificarMensaje(int mensaje, const std::vector<Punto>& puntos, int p, int& h);

Punto SumaPuntos(const Punto&, const Punto&, int, int);
Punto MultiplicacionPunto(const Punto&, int, int, int);

Punto CifradoElGamal(const Punto& mensaje, const Punto& clave_publica, int a, int p);
int DescifradoElGamal(const Punto& mensaje_cifrado, const Punto& clave_publica, const int clave_privada, int a, int p, int h);

#endif