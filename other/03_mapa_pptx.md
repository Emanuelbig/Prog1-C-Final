# Mapa de pptx → qué diapositiva mirar

Pptx en la carpeta de arriba (`..\`). Orden de estudio sugerido: Binarios → ABM → Texto (solo lo puntual).

(Emanuel los renombró con número de orden: "… 1/2/3.pptx")

## Archivos Binarios 2026  1.pptx (20 diap., el principal)
2 texto vs binario · 3 archivo como vector · 4 struct · 5 modos rb/wb/rb+ · 6 fwrite · 7 fread + lectura adelantada · 8 fseek/ftell/rewind · 9 alta · 10 listado · 11 acceso directo · 12 búsqueda con bandera · **13–14 modificar in place (TODO 1, 2)** · 15 baja lógica/física · 16 compactar · 18 errores frecuentes · 19 machete

## ABM_Archivos_Binarios_Baja_Logica 2.pptx (18 diap., teoría para el oral)
3 struct Cliente con `bool estado` (29 bytes datos, 32 con relleno) · 6–9 baja física vs lógica y por qué lógica · 10 baja en 5 pasos · 11 todas las operaciones miran la bandera · 12 alta: 3 casos · 13 patrón leer-modificar-volver-escribir · 15–17 purga física · 18 lo que tiene que quedar

## Archivos de Texto 2026_1 3.pptx (24 diap., repaso)
5 ciclo de vida (declarar/abrir/verificar/usar/cerrar) · 6–7 fopen y modos · 9 primero se lee, después se pregunta · **19 fprintf (TODO 3)** · 22 errores frecuentes · 23 machete

## TODO → teoría
1, 2 → Bin 13–14, ABM 13 · 3 → Texto 5–7, 19 + Bin 7, 10 · 4 → Bin 12 · 5 → Bin 12 + ABM 12 (código duplicado)
