# Consigna (resumen del .docx)

UTN INSPT, Com 1.605, Unidad 8 Archivos. Prof. Behringer, Ay. Avalos.

## Reglas
- Completar SOLO el cuerpo de los 5 TODO. No tocar el resto de tarea.c.
- Borrar las líneas `(void)x;` de cada TODO.
- Las 5 funciones NO imprimen: devuelven y el programa muestra el mensaje.
- Entrega: tarea.c con apellido y nombre en el encabezado.

## Los 5 TODO (menú 8–12)
| # | Firma | Qué hace | Devuelve |
|---|---|---|---|
| 1 | `int modificarPrecio(FILE*, long posicion, float nuevoPrecio)` | cambia precio. Reusar leerRegistro + escribirRegistro | 1 ok / 0 no |
| 2 | `int reactivarProducto(FILE*, long posicion)` | deshace baja lógica (activo=1). Reusar leer/escribirRegistro | 1 ok / 0 no |
| 3 | `long exportarStockBajo(FILE*, const char *nombreTxt, int stockMinimo)` | crea .txt, `fprintf` una línea `codigo;descripcion;stock` por cada VIGENTE con stock < mínimo. Recorrer desde el principio | cantidad exportada / ERROR_ARCHIVO |
| 4 | `long buscarPorDescripcion(FILE*, const char *desc)` | primer VIGENTE con descripción exacta. Usar `sonIguales` | posición / NO_ENCONTRADO |
| 5 | `int generarCodigoUnico(FILE*, int min, int max)` | código al azar en [min,max] que no exista (ni vigente ni de baja). Usar `generarNumAleatorio` + `buscarCodigo` | el código |

## Datos de prueba (cargar con opción 1)
101 Coca Cola 500 $1200 st40 · 102 Agua tonica $720 st15 · 103 Sprite $650 st8 · 104 Pomelo $580 st5

## Resultados esperados
- Op 8: 101 → precio 1300 → "Precio actualizado ($1200.00 -> $1300.00)"
- Op 9: baja 103 (op 6), reactivar → "Producto reactivado."; repetir → "No hay un producto dado de baja con ese código."
- Op 10: "Se exportaron 2 productos…" → stock.txt = `103;Sprite;8` y `104;Pomelo;5`
- Op 11: "Pomelo" → `[  3]   104  Pomelo   580.00   5`
- Op 12: código al azar (ej 4821), cargar Fanta $500 st20
