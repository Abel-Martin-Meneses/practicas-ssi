#include <vector>
#include <string>

#ifndef FUNCIONES_H
#define FUNCIONES_H

#define GREEN "\033[32m"
#define RESET "\033[0m"

long long ExpoRapida(long long, long long, long long);

bool ComprobarPrimos(long long);
bool ComprobarPrimosPequeños(long long);
std::vector<long long> GenerarNumerosAleatorios(long long);

std::pair<bool, long long> PrimosEuclidesExtendido(long long, long long);

std::vector<long long> CifradoRSA(std::vector<long long>, long long, long long);
/*std::vector<long long> DescifradoRSA(std::vector<long long>, long long, long long);*/

bool ConfigurarClaves(long long&, long long&, long long&);
std::vector<long long> ProcesarTextoADecimal(std::string, long long);
std::string DecimalATexto(long long, long long);

long long VerificarFirma(long long, long long, long long);

#endif