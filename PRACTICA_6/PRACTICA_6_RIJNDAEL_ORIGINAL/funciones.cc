#include "funciones.h"

void AddRoundKey(unsigned char* estado, const unsigned char* clave_round) {
  for (int i = 0; i < 16; i++) {
    estado[i] = estado[i] ^ clave_round[i];
  }
}

void ImprimirBloque(const unsigned char* bloque) {
  for (int i{0}; i < 16; i++) {
    printf("%02x", bloque[i]); 
  }
}

void SubBytes(unsigned char* estado) {
  for (int i{0}; i < 16; i++) {
    estado[i] = sbox[estado[i]];
  }
}

void ShiftRows(unsigned char* estado) {
  unsigned char temporal;

  temporal = estado[1];
  estado[1] = estado[5];
  estado[5] = estado[9];
  estado[9] = estado[13];
  estado[13] = temporal;
  
  temporal = estado[2];
  estado[2] = estado[10];
  estado[10] = temporal;
  temporal = estado[6];
  estado[6] = estado[14];
  estado[14] = temporal;
  
  temporal = estado[15];
  estado[15] = estado[11];
  estado[11] = estado[7];
  estado[7] = estado[3];
  estado[3] = temporal;
}

void GMixColumn(unsigned char *r) {
  unsigned char a[4];
  unsigned char b[4];
  unsigned char c;
  unsigned char h;
  
  for(c = 0; c < 4; c++) {
    a[c] = r[c];
    h = r[c] & 0x80;
    b[c] = r[c] << 1;
    if(h == 0x80) {
      b[c] ^= 0x1b;
    }
  }

  r[0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
  r[1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
  r[2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
  r[3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
}

void MixColumns(unsigned char* estado) {
  unsigned char columna_temporal[4];
  for (int i = 0; i < 4; i++) {
    columna_temporal[0] = estado[i * 4];
    columna_temporal[1] = estado[i * 4 + 1];
    columna_temporal[2] = estado[i * 4 + 2];
    columna_temporal[3] = estado[i * 4 + 3];
    
    GMixColumn(columna_temporal);
    
    estado[i * 4] = columna_temporal[0];
    estado[i * 4 + 1] = columna_temporal[1];
    estado[i * 4 + 2] = columna_temporal[2];
    estado[i * 4 + 3] = columna_temporal[3];
  }
}

void RotarPalabra(unsigned char* palabra_temporal) {
  unsigned char byte_intercambio = palabra_temporal[0];
  palabra_temporal[0] = palabra_temporal[1];
  palabra_temporal[1] = palabra_temporal[2];
  palabra_temporal[2] = palabra_temporal[3];
  palabra_temporal[3] = byte_intercambio;
}

void SustituirPalabra(unsigned char* palabra_temporal) {
  for (int i = 0; i < 4; i++) {
    palabra_temporal[i] = sbox[palabra_temporal[i]];
  }
}

void ExpandirClave(const unsigned char* clave_original, unsigned char* clave_expandida) {
  for (int i = 0; i < 16; i++) {
    clave_expandida[i] = clave_original[i];
  }
  int bytes_generados = 16;   
  int rcon_indice = 0;        
  unsigned char temporal[4];  
  while (bytes_generados < 176) {
    for (int i = 0; i < 4; i++) {
      temporal[i] = clave_expandida[bytes_generados - 4 + i];
    }

    if (bytes_generados % 16 == 0) {
      RotarPalabra(temporal);     
      SustituirPalabra(temporal); 
      temporal[0] = temporal[0] ^ rcon[rcon_indice];
      rcon_indice++;
    }
  
    for (int i = 0; i < 4; i++) {
      clave_expandida[bytes_generados] = clave_expandida[bytes_generados - 16] ^ temporal[i];
      bytes_generados++;
    }
  }
}

void CifradoRijndael(unsigned char* estado, const unsigned char* clave_expandida) {
  AddRoundKey(estado, clave_expandida);

  std::cout << "R0 (Subclave = ";
  ImprimirBloque(clave_expandida);
  std::cout << ") = ";
  ImprimirBloque(estado);
  std::cout << std::endl;

  for (int iteracion = 1; iteracion <= 9; iteracion++) {
    SubBytes(estado);
    ShiftRows(estado);
    MixColumns(estado);
    AddRoundKey(estado, &clave_expandida[iteracion * 16]);
    
    std::cout << "R" << iteracion << " (Subclave = ";
    ImprimirBloque(&clave_expandida[iteracion * 16]);
    std::cout << ") = ";
    ImprimirBloque(estado);
    std::cout << std::endl;
  }

  SubBytes(estado);
  ShiftRows(estado);
  AddRoundKey(estado, &clave_expandida[10 * 16]); 

  std::cout << "R10 (Subclave = ";
  ImprimirBloque(&clave_expandida[10 * 16]);
  std::cout << ") = ";
  ImprimirBloque(estado);
  std::cout << std::endl;
}

// DESCIFRADO

void InvertirSubBytes(unsigned char* estado) {
  for (int i = 0; i < 16; i++) {
    estado[i] = sbox_inversa[estado[i]];
  }
}

void InvertirShiftRows(unsigned char* estado) {
  unsigned char temporal;

  temporal = estado[13];
  estado[13] = estado[9];
  estado[9] = estado[5];
  estado[5] = estado[1];
  estado[1] = temporal;

  temporal = estado[2]; 
  estado[2] = estado[10]; 
  estado[10] = temporal;
  temporal = estado[6]; 
  estado[6] = estado[14]; 
  estado[14] = temporal;

  temporal = estado[3];
  estado[3] = estado[7];
  estado[7] = estado[11];
  estado[11] = estado[15];
  estado[15] = temporal;
}

unsigned char MultiplicarGalois(unsigned char a, unsigned char b) {
  unsigned char resultado = 0;
  for (int contador = 0; contador < 8; contador++) {
    if ((b & 1) != 0) resultado ^= a;
    bool bit_alto = (a & 0x80) != 0;
    a <<= 1;
    if (bit_alto) a ^= 0x1b;
    b >>= 1;
  }
  return resultado;
}

void InvertirMixColumns(unsigned char* estado) {
  unsigned char temporal[4];
  for (int i = 0; i < 4; i++) {
    temporal[0] = estado[i * 4];
    temporal[1] = estado[i * 4 + 1];
    temporal[2] = estado[i * 4 + 2];
    temporal[3] = estado[i * 4 + 3];
    
    estado[i * 4]     = MultiplicarGalois(temporal[0], 0x0e) ^ MultiplicarGalois(temporal[1], 0x0b) ^ MultiplicarGalois(temporal[2], 0x0d) ^ MultiplicarGalois(temporal[3], 0x09);
    estado[i * 4 + 1] = MultiplicarGalois(temporal[0], 0x09) ^ MultiplicarGalois(temporal[1], 0x0e) ^ MultiplicarGalois(temporal[2], 0x0b) ^ MultiplicarGalois(temporal[3], 0x0d);
    estado[i * 4 + 2] = MultiplicarGalois(temporal[0], 0x0d) ^ MultiplicarGalois(temporal[1], 0x09) ^ MultiplicarGalois(temporal[2], 0x0e) ^ MultiplicarGalois(temporal[3], 0x0b);
    estado[i * 4 + 3] = MultiplicarGalois(temporal[0], 0x0b) ^ MultiplicarGalois(temporal[1], 0x0d) ^ MultiplicarGalois(temporal[2], 0x09) ^ MultiplicarGalois(temporal[3], 0x0e);
  }
}

void DescifradoRijndael(unsigned char* estado, const unsigned char* clave_expandida) {
  AddRoundKey(estado, &clave_expandida[10 * 16]);

  /*std::cout << "R0 (Subclave = ";
  ImprimirBloque(&clave_expandida[10 * 16]);
  std::cout << ") = ";
  ImprimirBloque(estado);
  std::cout << std::endl;*/

  for (int iteracion = 9; iteracion >= 1; iteracion--) {
    InvertirShiftRows(estado);
    InvertirSubBytes(estado);
    AddRoundKey(estado, &clave_expandida[iteracion * 16]);
    InvertirMixColumns(estado);

    /*std::cout << "R" << iteracion << " (Subclave = ";
    ImprimirBloque(&clave_expandida[iteracion * 16]);
    std::cout << ") = ";
    ImprimirBloque(estado);
    std::cout << std::endl;*/
  }

  InvertirShiftRows(estado);
  InvertirSubBytes(estado);  
  AddRoundKey(estado, clave_expandida); 

  /*std::cout << "R10 (Subclave = ";
  ImprimirBloque(clave_expandida);
  std::cout << ") = ";
  ImprimirBloque(estado);
  std::cout << std::endl;*/
}