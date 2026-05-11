#!/bin/bash

# Función para compilar y ejecutar las prácticas escritas en C++
ejecutar_cpp() {
    DIR=$1
    EXEC=$2
    if [ -d "$DIR" ]; then
        echo -e "\n--- Entrando a '$DIR' ---"
        cd "$DIR" || return
        
        # Compila usando el Makefile
        make
        
        # Ejecuta el programa
        echo -e "\n--- Ejecutando $EXEC ---\n"
        # Intentamos ejecutar el binario. Si el nombre en el Makefile es distinto de $EXEC,
        # puedes cambiarlo en la llamada de la función abajo.
        ./"$EXEC"
        
        # Vuelve al directorio principal
        cd - > /dev/null
    else
        echo -e "\n[ERROR] No se encontró el directorio:\n$DIR"
        echo "Asegúrate de que la carpeta existe y el nombre es correcto."
    fi
}

# Función para ejecutar las prácticas escritas en Python
ejecutar_py() {
    DIR=$1
    SCRIPT=$2
    if [ -d "$DIR" ]; then
        echo -e "\n--- Entrando a '$DIR' ---"
        cd "$DIR" || return
        
        # Ejecuta el script de Python
        echo -e "\n--- Ejecutando $SCRIPT ---\n"
        python3 "$SCRIPT"
        
        # Vuelve al directorio principal
        cd - > /dev/null
    else
        echo -e "\n[ERROR] No se encontró el directorio:\n$DIR"
    fi
}

# Función para mostrar el submenú de selección (Original vs Modificación) para C++
seleccionar_version_cpp() {
    local nombre_practica=$1
    local dir_original=$2
    local dir_modificacion=$3
    local exec_name=$4

    echo -e "\n>>> Has seleccionado: $nombre_practica"
    echo "  1. Versión Original"
    echo "  2. Versión Modificación"
    echo "  0. Volver atrás"
    read -p "Elige la versión a ejecutar: " sub_opcion

    case $sub_opcion in
        1) ejecutar_cpp "$dir_original" "$exec_name" ;;
        2) ejecutar_cpp "$dir_modificacion" "$exec_name" ;;
        0) echo "Volviendo al menú principal..." ;;
        *) echo -e "\n[!] Opción no válida." ;;
    esac
}

# Función para mostrar el submenú de selección para Python (Práctica 9)
seleccionar_version_py() {
    local nombre_practica=$1
    local dir_base=$2
    local script_original=$3
    local script_modificacion=$4

    echo -e "\n>>> Has seleccionado: $nombre_practica"
    echo "  1. Versión Original ($script_original)"
    echo "  2. Versión Modificación ($script_modificacion)"
    echo "  0. Volver atrás"
    read -p "Elige la versión a ejecutar: " sub_opcion

    case $sub_opcion in
        1) ejecutar_py "$dir_base" "$script_original" ;;
        2) ejecutar_py "$dir_base" "$script_modificacion" ;;
        0) echo "Volviendo al menú principal..." ;;
        *) echo -e "\n[!] Opción no válida." ;;
    esac
}

# Bucle principal del menú
while true; do
    echo ""
    echo "======================================================"
    echo "          MENÚ DE PRÁCTICAS DE SSI                    "
    echo "======================================================"
    echo "  1. Práctica 1: Cifrado de Vernam"
    echo "  2. Práctica 2: Cifrado Vigenère"
    echo "  3. Práctica 3: Generador ChaCha20"
    echo "  4. Práctica 4: Generador C/A GPS"
    echo "  5. Práctica 5: Multiplicación SNOW3G/AES"
    echo "  6. Práctica 6: Cifrado Rijndael"
    echo "  7. Práctica 7: Cifrado en modo CBC"
    echo "  8. Práctica 8: Diffie-Hellman"
    echo "  9. Práctica 9: Protocolo BB84 (Python)"
    echo " 10. Práctica 10: Criptosistema RSA"
    echo " 11. Práctica 11: Curvas Elípticas (DH y ElGamal)"
    echo " 12. Práctica 12: Firma RSA"
    echo "  0. Salir"
    echo "======================================================"
    read -p "Elige una práctica: " opcion

    case $opcion in
        1) seleccionar_version_cpp "Práctica 1 (Vernam)" "PRACTICA_1/PRACTICA_1_ORIGINAL" "PRACTICA_1/Modificación Práctica 1 - Cifrado de Vernam" "cifrado_vernam" ;;
        2) seleccionar_version_cpp "Práctica 2 (Vigenère)" "PRACTICA_2/PRACTICA_2_CIFRADO_VIGENERE" "PRACTICA_2/PRACTICA_2_CIFRADO_VIGENERE_MODIFICACION" "cifrado_vigenere" ;;
        3) seleccionar_version_cpp "Práctica 3 (ChaCha20)" "PRACTICA_3/PRACTICA_3_CHACHA20 ORIGINAL" "PRACTICA_3/PRACTICA_3_CHACHA20 MODIFICACION" "chacha20" ;;
        4) seleccionar_version_cpp "Práctica 4 (GPS)" "PRACTICA_4/PRACTICA_4_GPS_ORIGINAL" "PRACTICA_4/PRACTICA_4_GPS_MODIFICACION" "gps" ;;
        5) seleccionar_version_cpp "Práctica 5 (SNOW3G/AES)" "PRACTICA_5/PRACTICA_5_MULTIPLICACION_ORIGINAL" "PRACTICA_5/PRACTICA_5_MULTIPLICACION_MODIFICACION" "mult" ;;
        6) seleccionar_version_cpp "Práctica 6 (Rijndael)" "PRACTICA_6/PRACTICA_6_RIJNDAEL_ORIGINAL" "PRACTICA_6/PRACTICA_6_RIJNDAEL_MODIFICACION" "rijndael" ;;
        7) seleccionar_version_cpp "Práctica 7 (CBC)" "PRACTICA_7/PRACTICA_7_CBC_ORIGINAL" "PRACTICA_7/PRACTICA_7_CBC_MODIFICACION" "cbc" ;;
        8) seleccionar_version_cpp "Práctica 8 (Diffie-Hellman)" "PRACTICA_8/PRACTICA_8_DH_ORIGINAL" "PRACTICA_8/PRACTICA_8_DH_MODIFICACION" "dh" ;;
        9) seleccionar_version_py "Práctica 9 (BB84)" "PRACTICA_9/PRACTICA_9_BB84_ORIGINAL" "main.py" "modificacion.py" ;;
        10) seleccionar_version_cpp "Práctica 10 (RSA)" "PRACTICA_10/PRACTICA_10_RSA_ORIGINAL" "PRACTICA_10/PRACTICA_10_RSA_MODIFICACION" "rsa" ;;
        11) seleccionar_version_cpp "Práctica 11 (Curvas Elípticas)" "PRACTICA_11/PRACTICA_11_ORIGINAL" "PRACTICA_11/PRACTICA_11_MODIFICACION" "eliptica" ;;
        12) seleccionar_version_cpp "Práctica 12 (Firma RSA)" "PRACTICA_12/PRACTICA_12_ORIGINAL" "PRACTICA_12/PRACTICA_12_MODIFICACION" "firma-rsa" ;;
        0) echo -e "\nSaliendo del menú...\n"; exit 0 ;;
        *) echo -e "\n[!] Opción no válida." ;;
    esac
    
    echo ""
    read -p "Presiona Enter para continuar..."
done