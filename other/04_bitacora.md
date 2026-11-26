# Bitácora y estado

## ▶ Retomar acá (revisado 25/11/2026 a la noche)
1. Siguiente: **TODO 5 `generarCodigoUnico`**. Que lo intente él solo antes de pedir la solución. Después seguir el "Plan hasta la mesa".
2. Limpiar comentarios: TODO 1, 2 y 3, y los que agregó **fuera** de los TODO (ver Pendientes).
3. Ensayo oral: todavía no explicó ningún TODO en voz alta, por eso ninguno tiene 🎤. Quedó sin responder con sus palabras: ¿por qué `&prod` al leer y `prod` al escribir? (ya se le explicó con la analogía de la fotocopia).

## Estado de los TODO
| # | Función | Estado | Notas |
|---|---|---|---|
| 1 | modificarPrecio | ✔ hecha y probada | Caso de la consigna OK ($1200.00 -> $1300.00) |
| 2 | reactivarProducto | ✔ hecha y probada | Caso de la consigna OK, también el mensaje al repetir |
| 3 | exportarStockBajo | ✔ hecha y probada | Probado: consigna, exportar dos veces, 103 de baja, error al crear el txt. Falta limpiar comentarios. Se le mostró la función completa después de tres intentos: **reforzarla en el oral** |
| 4 | buscarPorDescripcion | ✔ hecha y probada (25/11) | Probado: "Pomelo" → pos 3; "pomelo", "Fanta" y Pomelo de baja → no encontrado. Solo el warning esperado del `const`. | Copió bien el recorrido de `buscarCodigo` (dejó nombres del molde y `return encontrado`: válido). Trabó en el `if` (quedó `prod.codigo == && codigo`, `=` por `==`). Pidió la solución al 1er intento y se le mostró: **reforzar en el oral** (sonIguales vs `==`, para qué la bandera en el while). Falta que la pegue, compile y pruebe ("Pomelo" → pos 3). Warning esperable por `const` al llamar a `sonIguales` (avisa, pero compila) |
| 5 | generarCodigoUnico | ⬜ sin empezar | Pista dada: `do { } while`, buscar vigente y dado de baja |

Leyenda: ⬜ sin empezar · 🟡 en curso · ✔ hecha y probada · 🎤 sabe explicarla

## Pendientes
- **Regla "no modificar el resto"**: agregó comentarios en `leerRegistro` y `darDeBaja` (código base, no TODO). El código no cambió, solo hay comentarios, pero antes de entregar hay que sacarlos (o dejar los apuntes en el manual).
- TODO 1 y 2, comentarios a corregir antes de entregar: `/*le paso la direccion del struct por que voy a tener que modificar una de sus varibles...*/` está **mal** (el `&` es porque leerRegistro llena la variable, no por el precio); `//leer registro era un fread` → es fseek + fread; `//el struct` → es una variable de tipo Producto; typo "ada".
- Git: `build/` y `productos.dat` están commiteados. Conviene un `.gitignore` (no se entregan).
- TODO 3, antes de entregar, borrar comentarios: `// por que llamo a esta variable?...`, `// 9`, `// ¿vigente?` (quedó al lado de una `}`) y, si no lo quiere entregar, el bloque "Los pasos".
- Include: resuelto el 23/11 con `#include "utiles.h"` (tarea.c y utiles.h en la misma carpeta). Compila sin warnings. **Antes de entregar: preguntarle al profe si deja así o vuelve a `../../../utiles.h`.**
- `productos.dat` actual (5 registros, stock mínimo 20): con la opción 10 exporta 0 productos y **está bien**. Para ver resultados, cargar los datos de `01_consigna.md`.
- No leyó los pptx. Plan: aprender con el código, pptx solo la diapositiva puntual. Orden que queda: TODO 4 → 5 → ensayo oral.

## Plan hasta la mesa (lunes 30/11)
Él dijo (25/11) que se asiste mucho con IA y no retiene las funciones. Plan: no estudiar "C entero", solo lo que está en su tarea.c.
- Jue 26: TODO 5 (él solo, con molde) + limpiar comentarios.
- Vie 27: entender las 7 funciones base, una por una, con "explicámelo vos".
- Sáb 28: ensayo oral 1 (yo de profe, preguntas de la lista).
- Dom 29: ensayo oral 2 + cambios en vivo ("¿y si buscara por stock?") + repaso de lo que falló.
- Lun 30: repaso corto de la lista de preguntas, nada nuevo.
Concepto aclarado 25/11: `&` = paso la dirección para que la función cambie MI variable; no se "devuelve" (el cambio queda hecho); la declaración es `int f(int *p)`, la llamada `f(&x)`.

## Fichas en papel (pedido suyo 25/11: "explicame todas las funciones así, paso por paso, y yo anoto")
Formato que le gustó: ejemplo chico (`duplicar` + main), qué va en la declaración vs. en la llamada, dibujo de memoria. Una ficha por vez, corta, para copiar a mano.
26/11: pidió frenar el TODO 5 (ya se le dio la explicación: do-while, `||`, buscarCodigo con ACTIVO y DADO_DE_BAJA) y ver **la arquitectura del programa en bloques chicos** primero. Bloques: A arquitectura (2 capas: pantalla/opciones vs. archivo; main = menú en do-while + switch) ✔ · B include/define/enum ✔ · C prototipos · D main · E una opción completa (opcionPrecio → TODO 1) · después volver al TODO 5.
Orden fichas: 0 punteros/& ✔ · Ficha 2 leer/escribirRegistro ✔ (entendió `fread(prod)` sin & porque ya es dirección) (corregido: `char *m` no `*char m`; `&` solo si la función tiene que cambiar mi variable; arrays/textos van SIN `&`) · 1 struct + archivo como vector + abrirArchivo ✔ · 2 leer/escribirRegistro (fseek, fread, fwrite) · 3 buscarCodigo (lectura adelantada + bandera) · 4 darDeBaja/actualizarStock · 5 compactar · 6–10 sus TODO 1–5 · 11 TODO 5 cuando esté.

## Cómo le sirve aprender
- El 25/11 dijo que C se le hace muy cuesta arriba. Le funciona: partir de una función que ya existe, un cambio por vez, tablas y ejemplos con los datos de la consigna.
- Los blancos sueltos (`____`) lo trabaron. Mejor: molde + tabla de qué cambiar.
- Los errores que tuvo: `=!` por `!=`, `Product` por `Producto`, llamar a `abrirArchivo` sin guardar lo que devuelve, no saber armar la segunda condición del `if`, dudas con tipo y nombre (`size_t leidos`).
- Manual hecho a pedido suyo: `Manual de C - TP archivos binarios.docx` (esta carpeta, Word editable, 5 páginas). Los **cuatro moldes** (A recorrer, B buscar, C modificar, D exportar) están en las págs. 2 y 3: usar esos nombres al explicar.

## Preguntas probables del oral (ir sumando; respuestas cortas en el manual, sección 9)
- ¿Por qué baja lógica y no física?
- ¿Por qué hay que hacer fseek antes de escribir, si ya leí ese registro? (dos razones: el fread dejó el cursor en el registro siguiente, y en modo `rb+`/`wb+` C exige reposicionarse entre leer y escribir)
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
- 25/11/2026 (noche, otra compu): se releyó el proyecto (repo en v4). Compila sin warnings. Prueba automática con los datos de la consigna: op 8, 9 (y repetir), 10 y `stock.txt` dan exactamente lo esperado. Se encontraron comentarios fuera de los TODO (ver Pendientes). Aclaraciones dadas: el `&` con analogía de la fotocopia; con fseek sí se podría escribir solo un campo (se reescribe entero por simple y porque la consigna pide reusar leer/escribirRegistro).
