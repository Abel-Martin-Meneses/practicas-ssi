#!/bin/bash

echo "========================================="
echo "  LIMPIEZA DE DIRECTORIOS DE PRÁCTICAS   "
echo "========================================="
echo ""

# Busca todos los archivos llamados 'Makefile' dentro de las carpetas y subcarpetas
find . -name "Makefile" -type f | while read -r makefile_path; do
    
    # Extrae solo la ruta de la carpeta donde está el Makefile
    directorio=$(dirname "$makefile_path")
    
    echo "[*] Limpiando: $directorio"
    
    # Entra al directorio, ejecuta make clean y los mensajes de error se ocultan (por si acaso no hay nada que limpiar)
    (cd "$directorio" && make clean > /dev/null 2>&1)
    
done

echo ""
echo "========================================="
echo "       ¡Limpieza completada!             "
echo "========================================="