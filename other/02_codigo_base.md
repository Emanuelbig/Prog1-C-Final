# Código base disponible (tarea.c + utiles.h)

## Constantes
NO_ENCONTRADO -1 · ERROR_ARCHIVO -1 · STOCK_MINIMO 10 · COD_MIN 1 · COD_MAX 9999 · ACTIVO 1 · DADO_DE_BAJA 0 · MAX_DESC 30
Struct `Producto { int codigo; char descripcion[30]; float precio; int stock; int activo; }` (48 bytes)

## Funciones de archivo ya hechas (tarea.c líneas 173–310; TODO 1–5 en 318–425; opciones del menú desde 499)
- `abrirArchivo(nombre)`: "rb+" y si no existe "wb+".
- `leerRegistro(arch, pos, &prod)`: fseek a pos*sizeof + fread. Devuelve 1/0.
- `escribirRegistro(arch, pos, prod)`: gemela, con fwrite. Devuelve 1/0.
- `contarRegistros(arch)`: fseek END + ftell / sizeof.
- `buscarCodigo(arch, codigo, activoBuscado)`: rewind + lectura adelantada + bandera. Devuelve pos o NO_ENCONTRADO. **Modelo para TODO 3 y 4.**
- `buscarPorCodigo(arch, cod)` = buscarCodigo(..., ACTIVO).
- `actualizarStock` y `darDeBaja`: patrón leer → cambiar → escribir. **Modelo para TODO 1 y 2.**
- `compactarArchivo`: copia activos a temporal, remove + rename. Muestra cómo abrir/cerrar un 2º archivo (útil para TODO 3).

## utiles.h (lo que piden usar)
- `sonIguales(char*, char*)` → strcmp == 0. ⚠️ recibe `char*` y el TODO 4 tiene `const char*` (da warning, pero compila).
- `generarNumAleatorio(min, max)` → min + rand() % (max-min+1). `srand` ya está en main.
- También: leerCadena, leerFlotante, pedirEnteroRango, limpiaPantalla, linea.

## Compilar
tarea.c hace `#include "utiles.h"` (misma carpeta). Con gcc, parado en `tp final programacion 1\`: `gcc -Wall -Wextra tarea.c -o tarea.exe`. Para probar sin tocar `productos.dat`, ejecutarlo desde otra carpeta: los archivos se crean donde se lo ejecuta.

Prueba automática (la usa Claude, desde una carpeta de prueba): pasarle las opciones por stdin con `printf '1\n101\nCoca Cola 500\n1200\n40\n\n...0\n\n' | ./t.exe`. Después de cada opción va una línea vacía extra por el `system("pause")`. Orden del alta: código, descripción, precio, stock.
