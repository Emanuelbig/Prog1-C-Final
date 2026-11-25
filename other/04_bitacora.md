# Bitácora y estado

## ▶ Retomar acá (cierre 25/11/2026)
1. Siguiente: **TODO 4 `buscarPorDescripcion`** (molde B, modelo `buscarCodigo`). Él lo escribe, yo reviso. Después TODO 5.
2. Limpiar comentarios del TODO 3 (ver Pendientes).
3. Ensayo oral: todavía no explicó ningún TODO en voz alta, por eso ninguno tiene 🎤.

## Estado de los TODO
| # | Función | Estado | Notas |
|---|---|---|---|
| 1 | modificarPrecio | ✔ hecha y probada | Caso de la consigna OK ($1200.00 -> $1300.00) |
| 2 | reactivarProducto | ✔ hecha y probada | Caso de la consigna OK, también el mensaje al repetir |
| 3 | exportarStockBajo | ✔ hecha y probada | Probado: consigna, exportar dos veces, 103 de baja, error al crear el txt. Falta limpiar comentarios. Se le mostró la función completa después de tres intentos: **reforzarla en el oral** |
| 4 | buscarPorDescripcion | ⬜ sin empezar | Warning esperable por `const` al llamar a `sonIguales` (comprobado: avisa, pero compila) |
| 5 | generarCodigoUnico | ⬜ sin empezar | Pista dada: `do { } while`, buscar vigente y dado de baja |

Leyenda: ⬜ sin empezar · 🟡 en curso · ✔ hecha y probada · 🎤 sabe explicarla

## Pendientes
- TODO 3, antes de entregar, borrar comentarios: `// por que llamo a esta variable?...`, `// 9`, `// ¿vigente?` (quedó al lado de una `}`) y, si no lo quiere entregar, el bloque "Los pasos".
- Include: resuelto el 23/11 con `#include "utiles.h"` (tarea.c y utiles.h en la misma carpeta). Compila sin warnings. **Antes de entregar: preguntarle al profe si deja así o vuelve a `../../../utiles.h`.**
- `productos.dat` actual (5 registros, stock mínimo 20): con la opción 10 exporta 0 productos y **está bien**. Para ver resultados, cargar los datos de `01_consigna.md`.
- No leyó los pptx. Plan: aprender con el código, pptx solo la diapositiva puntual. Orden que queda: TODO 4 → 5 → ensayo oral.

## Cómo le sirve aprender
- El 25/11 dijo que C se le hace muy cuesta arriba. Le funciona: partir de una función que ya existe, un cambio por vez, tablas y ejemplos con los datos de la consigna.
- Los blancos sueltos (`____`) lo trabaron. Mejor: molde + tabla de qué cambiar.
- Los errores que tuvo: `=!` por `!=`, `Product` por `Producto`, llamar a `abrirArchivo` sin guardar lo que devuelve, no saber armar la segunda condición del `if`, dudas con tipo y nombre (`size_t leidos`).
- Manual hecho a pedido suyo: `Manual de C - TP archivos binarios.docx` (esta carpeta, Word editable, 5 páginas). Los **cuatro moldes** (A recorrer, B buscar, C modificar, D exportar) están en las págs. 2 y 3: usar esos nombres al explicar.

## Preguntas probables del oral (ir sumando; respuestas cortas en el manual, sección 9)
- ¿Por qué baja lógica y no física?
- ¿Por qué hay que hacer fseek antes de escribir, si ya leí ese registro?
- ¿Qué es la lectura adelantada y por qué no usar feof?
- ¿Por qué `int activo` y no `bool`? (lo preguntó él 19/11: ambos sirven; con bool el struct sigue en 48 bytes por el relleno; en el ABM el profe usa bool. En tarea.c no se cambia)
- ¿Por qué `&prod` al leer y `prod` al escribir?
- ¿Por qué `rewind` en exportar y no en compactar?
- ¿Qué diferencia hay entre devolver 0 y -1 al exportar?
- ¿Por qué no usar `abrirArchivo` para el txt? (lo intentó él: `rb+` no vacía el archivo y abre en binario)

Se le dejaron tres sin responder (TODO 3), para arrancar el ensayo: ¿qué pasa si sacás `exportados = 0` y exportás 2?, ¿si movés el segundo `fread` adentro del `if`?, ¿si cambiás `"w"` por `"a"` y exportás dos veces?

## Sesiones
- 19/11/2026: se leyó todo el material y se armó este cerebro. Siguiente: Emanuel lee pptx Binarios y arrancamos TODO 1.
- 23/11/2026: notas movidas de `Programacion 1\_cerebro_final_prog1\` a `FINAL PROG 1 2026 DICIEMBRE\other\`.
- 23/11/2026 (tarde): include resuelto. Clase 0: archivo como vector de structs + leerRegistro/escribirRegistro + darDeBaja. Siguiente: él escribe TODO 1.
- 25/11/2026: TODO 1 y 2 ya escritos (v2 y v3 del repo). TODO 3 escrito y probado. Manual de C en Word. Siguiente: TODO 4, en la compu de su casa.
