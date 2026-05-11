#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <string>
#include <random>
#include <bitset>
#include <sstream>

// Definición de colores ANSI
#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BOLD    "\033[1m"

void Intro();
std::string GenerarClaveAleatoria(int);
std::string ConvertirStringBinario(const std::string&);
std::string ConvertirBinarioString(const std::string&);

#endif