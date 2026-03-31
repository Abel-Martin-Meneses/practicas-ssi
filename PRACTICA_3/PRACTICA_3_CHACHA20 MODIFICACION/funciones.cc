#include "funciones.h"

std::vector<uint32_t> LittleEndian(const std::string& cadena) {
  std::vector<uint32_t> palabras;
  
  if (cadena.find(':') != std::string::npos) {
    std::stringstream ss(cadena);
    uint32_t b[4];
    char sep;
    while (ss >> std::hex >> b[0]) {
      for (int i = 1; i < 4; ++i) {
        ss >> sep >> std::hex >> b[i];
      }
      if (ss.peek() == ':' || ss.peek() == ' ') ss >> sep;
      uint32_t valor = (b[3] << 24) | (b[2] << 16) | (b[1] << 8) | b[0];
      palabras.push_back(valor);
    }
  } else {
    std::stringstream ss(cadena);
    uint32_t valor;
    while (ss >> std::hex >> valor) palabras.push_back(valor);
  }
  return palabras;
}

void ImprimirEstado(const uint32_t* estado) {
  std::cout << "\n--- MATRIZ DE ESTADO ---" << std::endl;
  for (int i = 0; i < 16; ++i) {
    std::cout << std::setw(8) << std::setfill('0') << std::hex << estado[i] << ( (i+1)%4 == 0 ? "\n" : "  " );
  }
  std::cout << "------------------------" << std::endl;
}

void QR(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d) {
  a += b; d ^= a; d = ROTL(d, 16);
  c += d; b ^= c; b = ROTL(b, 12);
  a += b; d ^= a; d = ROTL(d, 8);
  c += d; b ^= c; b = ROTL(b, 7);
}

uint32_t ROTL(uint32_t& estado, const uint32_t& despl) {
  return (((estado) << (despl)) | ((estado) >> (32 - (despl))));
}

void ChaCha20(uint32_t aux[16], const uint32_t estado_inicial[16], uint32_t salida[16]) {
  for (int i{0}; i < 16; i++) {
    aux[i] = estado_inicial[i];
  }

  for (int i{0}; i < ITERACIONES; i+=2) {
    QR(aux[0], aux[4], aux[8], aux[12]);
    QR(aux[1], aux[5], aux[9], aux[13]);
    QR(aux[2], aux[6], aux[10], aux[14]);
    QR(aux[3], aux[7], aux[11], aux[15]);
    
    QR(aux[0], aux[5], aux[10], aux[15]);
    QR(aux[1], aux[6], aux[11], aux[12]);
    QR(aux[2], aux[7], aux[8], aux[13]);
    QR(aux[3], aux[4], aux[9], aux[14]);
  }

  for (int i{0}; i < 16; i++) {
    salida[i] = estado_inicial[i] + aux[i];
  }
}