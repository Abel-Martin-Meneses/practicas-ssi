#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <cstdint>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <random>

const int ITERACIONES = 20;
const double INFINITO = std::numeric_limits<double>::infinity();

std::vector<uint32_t> LittleEndian(const std::string&);
void ImprimirEstado(const uint32_t*);
void QR(uint32_t&, uint32_t&, uint32_t&, uint32_t&);
uint32_t ROTL(uint32_t&, const uint32_t&);
void ChaCha20(uint32_t [16], const uint32_t [16], uint32_t [16]);

#endif