# Código base disponible (tarea.c + utiles.h)

## Constantes
NO_ENCONTRADO -1 · ERROR_ARCHIVO -1 · STOCK_MINIMO 10 · COD_MIN 1 · COD_MAX 9999 · ACTIVO 1 · DADO_DE_BAJA 0 · MAX_DESC 30
Struct `Producto { int codigo; char descripcion[30]; float precio; int stock; int activo; }` (48 bytes)

## Funciones de archivo ya hechas (tarea.c ~líneas 172–310)
- `abrirArchivo(nombre)`: "rb+" y si no existe "wb+".
- `leerRegistro(arch, pos, &prod)`: fseek a pos*sizeof + fread. Devuelve 1/0.
- `escribirRegistro(arch, pos, prod)`: gemela, con fwrite. Devuelve 1/0.
- `contarRegistros(arch)`: fseek END + ftell / sizeof.
- `buscarCodigo(arch, codigo, activoBuscado)`: rewind + lectura adelantada + bandera. Devuelve pos o NO_ENCONTRADO. **Modelo para TODO 3 y 4.**
- `buscarPorCodigo(arch, cod)` = buscarCodigo(..., ACTIVO).
- `actualizarStock` y `darDeBaja`: patrón leer → cambiar → escribir. **Modelo para TODO 1 y 2.**
- `compactarArchivo`: copia activos a temporal, remove + rename. Muestra cómo abrir/cerrar un 2º archivo (útil para TODO 3).

## utiles.h (lo que piden usar)
- `sonIguales(char*, char*)` → strcmp == 0. ⚠️ recibe `char*` y el TODO 4 tiene `const char*` (puede dar warning).
- `generarNumAleatorio(min, max)` → min + rand() % (max-min+1). `srand` ya está en main.
- También: leerCadena, leerFlotante, pedirEnteroRango, limpiaPantalla, linea.

## Compilar
tarea.c hace `#include "../../../utiles.h"` → busca `C:\Users\emanu\Documents\utiles.h` (NO existe). No modificar el include (regla). Opción: copiar utiles.h a esa ruta, o compilar desde una carpeta tres niveles más abajo. Pendiente decidir con Emanuel.
