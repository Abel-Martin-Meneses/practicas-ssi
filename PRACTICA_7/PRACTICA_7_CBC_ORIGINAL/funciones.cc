#include "funciones.h"
#include <iostream>
#include <string>

unsigned char HexCharToByte(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  return 0;
}

void ReadHexBlock(const std::string& label, unsigned char* block) {
  std::string input;
  bool is_valid = false;
  while (!is_valid) {
    std::cout << label << " (32 caracteres hex): ";
    std::cin >> input;
  
    if (input.length() == 32) {
      is_valid = true;
      for (int i = 0; i < 16; i++) {
        unsigned char high_nibble = HexCharToByte(input[i * 2]);
        unsigned char low_nibble = HexCharToByte(input[(i * 2) + 1]);
        block[i] = (high_nibble << 4) | low_nibble;
      }
    } else {
      std::cerr << "Error: longitud incorrecta (" << input.length() << "). Inténtelo de nuevo.\n";
    }
  }
}

void PrintBlock(const unsigned char* block) {
  for (int i{0}; i < 16; i++) {
    printf("%02x", block[i]); 
  }
}

void AddRoundKey(unsigned char* state, const unsigned char* round_key) {
  for (int i = 0; i < 16; i++) {
    state[i] = state[i] ^ round_key[i];
  }
}

void SubBytes(unsigned char* state) {
  for (int i{0}; i < 16; i++) {
    state[i] = kSBox[state[i]];
  }
}

void ShiftRows(unsigned char* state) {
  unsigned char temp;

  temp = state[1];
  state[1] = state[5];
  state[5] = state[9];
  state[9] = state[13];
  state[13] = temp;
  
  temp = state[2];
  state[2] = state[10];
  state[10] = temp;
  temp = state[6];
  state[6] = state[14];
  state[14] = temp;
  
  temp = state[15];
  state[15] = state[11];
  state[11] = state[7];
  state[7] = state[3];
  state[3] = temp;
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

void MixColumns(unsigned char* state) {
  unsigned char temp_column[4];
  for (int i = 0; i < 4; i++) {
    temp_column[0] = state[i * 4];
    temp_column[1] = state[i * 4 + 1];
    temp_column[2] = state[i * 4 + 2];
    temp_column[3] = state[i * 4 + 3];
    
    GMixColumn(temp_column);
    
    state[i * 4] = temp_column[0];
    state[i * 4 + 1] = temp_column[1];
    state[i * 4 + 2] = temp_column[2];
    state[i * 4 + 3] = temp_column[3];
  }
}

void RotateWord(unsigned char* temp_word) {
  unsigned char swap_byte = temp_word[0];
  temp_word[0] = temp_word[1];
  temp_word[1] = temp_word[2];
  temp_word[2] = temp_word[3];
  temp_word[3] = swap_byte;
}

void SubstituteWord(unsigned char* temp_word) {
  for (int i = 0; i < 4; i++) {
    temp_word[i] = kSBox[temp_word[i]];
  }
}

void ExpandKey(const unsigned char* original_key, unsigned char* expanded_key) {
  for (int i = 0; i < 16; i++) {
    expanded_key[i] = original_key[i];
  }
  int generated_bytes = 16;   
  int rcon_index = 0;        
  unsigned char temp[4];  
  while (generated_bytes < 176) {
    for (int i = 0; i < 4; i++) {
      temp[i] = expanded_key[generated_bytes - 4 + i];
    }

    if (generated_bytes % 16 == 0) {
      RotateWord(temp);     
      SubstituteWord(temp); 
      temp[0] = temp[0] ^ kRcon[rcon_index];
      rcon_index++;
    }
  
    for (int i = 0; i < 4; i++) {
      expanded_key[generated_bytes] = expanded_key[generated_bytes - 16] ^ temp[i];
      generated_bytes++;
    }
  }
}

void EncryptRijndael(unsigned char* state, const unsigned char* expanded_key) {
  AddRoundKey(state, expanded_key);

  /*std::cout << "R0 (Subclave = ";
  PrintBlock(expanded_key);
  std::cout << ") = ";
  PrintBlock(state);
  std::cout << std::endl;*/

  for (int iteration = 1; iteration <= 9; iteration++) {
    SubBytes(state);
    ShiftRows(state);
    MixColumns(state);
    AddRoundKey(state, &expanded_key[iteration * 16]);
    
    /*std::cout << "R" << iteration << " (Subclave = ";
    PrintBlock(&expanded_key[iteration * 16]);
    std::cout << ") = ";
    PrintBlock(state);
    std::cout << std::endl;*/
  }

  SubBytes(state);
  ShiftRows(state);
  AddRoundKey(state, &expanded_key[10 * 16]); 

  /*std::cout << "R10 (Subclave = ";
  PrintBlock(&expanded_key[10 * 16]);
  std::cout << ") = ";
  PrintBlock(state);
  std::cout << std::endl;*/
}

void EncryptCBC(unsigned char* state_1, unsigned char* state_2, const unsigned char* iv, const unsigned char* expanded_key) {
  for (int i{0}; i < 16; i++) {
    state_1[i] = state_1[i] ^ iv[i];
  }
  EncryptRijndael(state_1, expanded_key);
  std::cout << "Bloque 1 de texto cifrado: ";
  PrintBlock(state_1);
  std::cout << std::endl;
  for (int i{0}; i < 16; i++) {
    state_2[i] = state_2[i] ^ state_1[i];
  }
  EncryptRijndael(state_2, expanded_key);
  std::cout << "Bloque 2 de texto cifrado: ";
  PrintBlock(state_2);
  std::cout << std::endl;
}

// DESCIFRADO

void InvSubBytes(unsigned char* state) {
  for (int i = 0; i < 16; i++) {
    state[i] = kInvSBox[state[i]];
  }
}

void InvShiftRows(unsigned char* state) {
  unsigned char temp;

  temp = state[13];
  state[13] = state[9];
  state[9] = state[5];
  state[5] = state[1];
  state[1] = temp;

  temp = state[2]; 
  state[2] = state[10]; 
  state[10] = temp;
  temp = state[6]; 
  state[6] = state[14]; 
  state[14] = temp;

  temp = state[3];
  state[3] = state[7];
  state[7] = state[11];
  state[11] = state[15];
  state[15] = temp;
}

unsigned char GaloisMultiply(unsigned char a, unsigned char b) {
  unsigned char result = 0;
  for (int counter = 0; counter < 8; counter++) {
    if ((b & 1) != 0) result ^= a;
    bool high_bit = (a & 0x80) != 0;
    a <<= 1;
    if (high_bit) a ^= 0x1b;
    b >>= 1;
  }
  return result;
}

void InvMixColumns(unsigned char* state) {
  unsigned char temp[4];
  for (int i = 0; i < 4; i++) {
    temp[0] = state[i * 4];
    temp[1] = state[i * 4 + 1];
    temp[2] = state[i * 4 + 2];
    temp[3] = state[i * 4 + 3];
    
    state[i * 4]     = GaloisMultiply(temp[0], 0x0e) ^ GaloisMultiply(temp[1], 0x0b) ^ GaloisMultiply(temp[2], 0x0d) ^ GaloisMultiply(temp[3], 0x09);
    state[i * 4 + 1] = GaloisMultiply(temp[0], 0x09) ^ GaloisMultiply(temp[1], 0x0e) ^ GaloisMultiply(temp[2], 0x0b) ^ GaloisMultiply(temp[3], 0x0d);
    state[i * 4 + 2] = GaloisMultiply(temp[0], 0x0d) ^ GaloisMultiply(temp[1], 0x09) ^ GaloisMultiply(temp[2], 0x0e) ^ GaloisMultiply(temp[3], 0x0b);
    state[i * 4 + 3] = GaloisMultiply(temp[0], 0x0b) ^ GaloisMultiply(temp[1], 0x0d) ^ GaloisMultiply(temp[2], 0x09) ^ GaloisMultiply(temp[3], 0x0e);
  }
}

void DecryptRijndael(unsigned char* state, const unsigned char* expanded_key) {
  AddRoundKey(state, &expanded_key[10 * 16]);

  /*std::cout << "R0 (Subclave = ";
  PrintBlock(&expanded_key[10 * 16]);
  std::cout << ") = ";
  PrintBlock(state);
  std::cout << std::endl;*/

  for (int iteration = 9; iteration >= 1; iteration--) {
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, &expanded_key[iteration * 16]);
    InvMixColumns(state);

    /*std::cout << "R" << iteration << " (Subclave = ";
    PrintBlock(&expanded_key[iteration * 16]);
    std::cout << ") = ";
    PrintBlock(state);
    std::cout << std::endl;*/
  }

  InvShiftRows(state);
  InvSubBytes(state);  
  AddRoundKey(state, expanded_key); 

  /*std::cout << "R10 (Subclave = ";
  PrintBlock(expanded_key);
  std::cout << ") = ";
  PrintBlock(state);
  std::cout << std::endl;*/
}

void DecryptCBC(unsigned char* state_1, unsigned char* state_2, const unsigned char* iv, const unsigned char* expanded_key) {
  DecryptRijndael(state_2, expanded_key);
  for (int i{0}; i < 16; i++) {
    state_2[i] = state_2[i] ^ state_1[i];
  }
  std::cout << "Bloque 2 de texto descifrado: ";
  PrintBlock(state_2);
  std::cout << std::endl;
  DecryptRijndael(state_1, expanded_key);
  for (int i{0}; i < 16; i++) {
    state_1[i] = state_1[i] ^ iv[i];
  }
  std::cout << "Bloque 1 de texto descifrado: ";
  PrintBlock(state_1);
  std::cout << std::endl;
}