// Archivo: tarea.c
// Programación I - UTN INSPT 
// Tarea: sistema de stock en archivo binario (productos.dat)
//
// El programa está completo y compila. Completar ÚNICAMENTE el cuerpo de las
// 5 funciones marcadas con TODO:
//   modificarPrecio, reactivarProducto, exportarStockBajo,
//   buscarPorDescripcion y generarCodigoUnico
// No modificar el resto del archivo.
//
// Apellido y nombre:
//

#include "../../../utiles.h"

#define MAX_DESC        30
#define NO_ENCONTRADO   -1
#define ERROR_ARCHIVO   -1
#define NOMBRE_ARCHIVO  "productos.dat"
#define NOMBRE_TEMP     "productos.tmp"
#define NOMBRE_EXPORT   "stock.txt"
#define STOCK_MINIMO    10          // por debajo de este valor el producto se exporta
#define STOCK_MAX    99999
#define COD_MIN          1
#define COD_MAX       9999
#define ANCHO_LINEA     60
#define ACTIVO           1
#define DADO_DE_BAJA     0

enum { OPCION_SALIR = 0, OPCION_ALTA, OPCION_LISTAR, OPCION_CONSULTAR, OPCION_POSICION,
       OPCION_STOCK, OPCION_BAJA, OPCION_COMPACTAR, OPCION_PRECIO, OPCION_REACTIVAR,
       OPCION_EXPORTAR, OPCION_BUSCAR_DESC, OPCION_ALTA_AUTO };

typedef struct
{
    int   codigo;
    char  descripcion[MAX_DESC];
    float precio;
    int   stock;
    int   activo;          // 1 vigente, 0 dado de baja
} Producto;

// Prototipos de archivos
FILE *abrirArchivo(const char *nombreArchivo);
int leerRegistro(FILE *arch, long posicion, Producto *prod);
int escribirRegistro(FILE *arch, long posicion, Producto prod);
long contarRegistros(FILE *arch);
long buscarCodigo(FILE *arch, int codigo, int activoBuscado);
long buscarPorCodigo(FILE *arch, int codigo);
int guardarAlFinal(FILE *arch, Producto prod);
int actualizarStock(FILE *arch, long posicion, int cantidad);
int darDeBaja(FILE *arch, long posicion);
long compactarArchivo(const char *nombreArchivo, const char *nombreTemp);
int modificarPrecio(FILE *arch, long posicion, float nuevoPrecio);              // TODO 1
int reactivarProducto(FILE *arch, long posicion);                               // TODO 2
long exportarStockBajo(FILE *arch, const char *nombreTxt, int stockMinimo);     // TODO 3
long buscarPorDescripcion(FILE *arch, const char *descripcionBuscada);          // TODO 4
int generarCodigoUnico(FILE *arch, int minimo, int maximo);                     // TODO 5

// Prototipos de pantalla
int menu(void);
Producto ingresarProducto(int codigo);
void encabezadoListado(void);
void mostrarProducto(Producto prod, long posicion);
void listarProductos(FILE *arch);
void opcionAlta(FILE *arch);
void opcionConsultar(FILE *arch);
void opcionPosicion(FILE *arch);
void opcionStock(FILE *arch);
void opcionBaja(FILE *arch);
void opcionPrecio(FILE *arch);
void opcionReactivar(FILE *arch);
void opcionExportar(FILE *arch);
void opcionBuscarDescripcion(FILE *arch);
void opcionAltaAutomatica(FILE *arch);

int main(void)
{
    FILE *arch;
    int opcion;
    long conservados;

    limpiaPantalla();
    utf8();
    srand(time(NULL));   // semilla aleatoria, necesaria para generarCodigoUnico (TODO 5)

    arch = abrirArchivo(NOMBRE_ARCHIVO);
    if (arch == NULL)
    {
        printf("\nNo se pudo abrir ni crear %s\n", NOMBRE_ARCHIVO);
        return 1;
    }

    do
    {
        limpiaPantalla();
        opcion = menu();
        limpiaPantalla();

        switch (opcion)
        {
        case OPCION_ALTA:
            opcionAlta(arch);
            break;
        case OPCION_LISTAR:
            listarProductos(arch);
            break;
        case OPCION_CONSULTAR:
            opcionConsultar(arch);
            break;
        case OPCION_POSICION:
            opcionPosicion(arch);
            break;
        case OPCION_STOCK:
            opcionStock(arch);
            break;
        case OPCION_BAJA:
            opcionBaja(arch);
            break;
        case OPCION_COMPACTAR:
            // compactarArchivo reemplaza el archivo: tiene que estar cerrado
            fclose(arch);
            conservados = compactarArchivo(NOMBRE_ARCHIVO, NOMBRE_TEMP);
            if (conservados == ERROR_ARCHIVO)
                printf("No se pudo compactar el archivo.\n");
            else
                printf("Archivo compactado: quedaron %ld productos.\n", conservados);

            arch = abrirArchivo(NOMBRE_ARCHIVO);
            if (arch == NULL)
            {
                printf("No se pudo reabrir %s. Fin del programa.\n", NOMBRE_ARCHIVO);
                opcion = OPCION_SALIR;
            }
            break;
        case OPCION_PRECIO:
            opcionPrecio(arch);
            break;
        case OPCION_REACTIVAR:
            opcionReactivar(arch);
            break;
        case OPCION_EXPORTAR:
            opcionExportar(arch);
            break;
        case OPCION_BUSCAR_DESC:
            opcionBuscarDescripcion(arch);
            break;
        case OPCION_ALTA_AUTO:
            opcionAltaAutomatica(arch);
            break;
        case OPCION_SALIR:
            printf("\nFin del programa.\n");
            break;
        }

        if (opcion != OPCION_SALIR)
            pausa();

    } while (opcion != OPCION_SALIR);

    if (arch != NULL)
        fclose(arch);

    return 0;
}

// *********************************************************************************
//                               FUNCIONES DE ARCHIVO
//            (no imprimen nada: devuelven el resultado y el main decide)
// *********************************************************************************

// Abre para leer y modificar; si no existe, lo crea
FILE *abrirArchivo(const char *nombreArchivo)
{
    FILE *arch;

    arch = fopen(nombreArchivo, "rb+");
    if (arch == NULL)
        arch = fopen(nombreArchivo, "wb+");
    return arch;
}

// Acceso directo: salta 'posicion' registros desde el inicio
int leerRegistro(FILE *arch, long posicion, Producto *prod)
{
    fseek(arch, posicion * (long)sizeof(Producto), SEEK_SET);
    return fread(prod, sizeof(Producto), 1, arch) == 1;
}

// Gemela de leerRegistro: misma posición, pero escribe
int escribirRegistro(FILE *arch, long posicion, Producto prod)
{
    fseek(arch, posicion * (long)sizeof(Producto), SEEK_SET);
    return fwrite(&prod, sizeof(Producto), 1, arch) == 1;
}

long contarRegistros(FILE *arch)
{
    fseek(arch, 0L, SEEK_END);
    return ftell(arch) / (long)sizeof(Producto);
}

// Búsqueda secuencial por código y estado: devuelve la posición o NO_ENCONTRADO.
// Se generalizó con activoBuscado para no duplicar la búsqueda (regla 12):
// la reactivación necesita encontrar justamente a los dados de baja.
long buscarCodigo(FILE *arch, int codigo, int activoBuscado)
{
    Producto prod;
    long posicion = 0;
    long encontrado = NO_ENCONTRADO;
    size_t leidos;

    rewind(arch);
    leidos = fread(&prod, sizeof(Producto), 1, arch);
    while (leidos == 1 && encontrado == NO_ENCONTRADO)
    {
        if (prod.codigo == codigo && prod.activo == activoBuscado)
            encontrado = posicion;
        else
        {
            posicion++;
            leidos = fread(&prod, sizeof(Producto), 1, arch);
        }
    }
    return encontrado;
}

// La búsqueda de siempre: solo productos vigentes
long buscarPorCodigo(FILE *arch, int codigo)
{
    return buscarCodigo(arch, codigo, ACTIVO);
}

// Devuelve 1 si pudo escribir el registro completo
int guardarAlFinal(FILE *arch, Producto prod)
{
    fseek(arch, 0L, SEEK_END);
    return fwrite(&prod, sizeof(Producto), 1, arch) == 1;
}

// Modificación in place: leer, cambiar y reescribir
int actualizarStock(FILE *arch, long posicion, int cantidad)
{
    Producto prod;
    int actualizado = 0;

    // cantidad positiva ingresa, negativa egresa: el stock resultante no puede ser negativo
    if (leerRegistro(arch, posicion, &prod) &&
        prod.stock + cantidad >= 0)
    {
        prod.stock += cantidad;
        actualizado = escribirRegistro(arch, posicion, prod);
    }
    return actualizado;
}

// Baja lógica: el registro queda en el archivo con activo = 0
int darDeBaja(FILE *arch, long posicion)
{
    Producto prod;
    int ok = 0;

    if (leerRegistro(arch, posicion, &prod))
    {
        prod.activo = DADO_DE_BAJA;
        ok = escribirRegistro(arch, posicion, prod);
    }
    return ok;
}

// Baja física: copia los activos a un temporal, borra el original y renombra.
// Devuelve cuántos productos quedaron, o ERROR_ARCHIVO.
// El archivo tiene que estar CERRADO antes de llamarla.
long compactarArchivo(const char *nombreArchivo, const char *nombreTemp)
{
    FILE *origen, *destino;
    Producto prod;
    long conservados = ERROR_ARCHIVO;
    size_t leidos;

    origen  = fopen(nombreArchivo, "rb");
    destino = fopen(nombreTemp, "wb");
    if (origen != NULL && destino != NULL)
    {
        conservados = 0;
        leidos = fread(&prod, sizeof(Producto), 1, origen);
        while (leidos == 1)
        {
            if (prod.activo)
            {
                fwrite(&prod, sizeof(Producto), 1, destino);
                conservados++;
            }
            leidos = fread(&prod, sizeof(Producto), 1, origen);
        }
        fclose(origen);
        fclose(destino);
        // se borra recién cuando el temporal está completo
        remove(nombreArchivo);
        rename(nombreTemp, nombreArchivo);
    }
    else
    {
        if (origen != NULL)
            fclose(origen);
        if (destino != NULL)
            fclose(destino);
    }
    return conservados;
}

// TODO 1 - MODIFICAR PRECIO
// Cambia el precio del producto que está en 'posicion' por 'nuevoPrecio'.
// Devuelve 1 si pudo reescribir el registro, 0 si no.
int modificarPrecio(FILE *arch, long posicion, float nuevoPrecio)
{
    int modificado = 0;

    // eliminar estas tres líneas al implementar la función
    (void)arch;
    (void)posicion;
    (void)nuevoPrecio;

    return modificado;
}

// TODO 2 - REACTIVAR PRODUCTO
// Deshace la baja lógica del producto que está en 'posicion'.
// Devuelve 1 si pudo reescribir el registro, 0 si no.
int reactivarProducto(FILE *arch, long posicion)
{
    int reactivado = 0;

    // eliminar estas dos líneas al implementar la función
    (void)arch;
    (void)posicion;

    return reactivado;
}

// TODO 3 - EXPORTAR STOCK BAJO
// Escribe en el archivo de texto 'nombreTxt' los productos vigentes con stock
// menor a 'stockMinimo', una línea por producto: codigo;descripcion;stock
// Devuelve cuántos productos exportó, o ERROR_ARCHIVO si no pudo crear el archivo.
long exportarStockBajo(FILE *arch, const char *nombreTxt, int stockMinimo)
{
    long exportados = ERROR_ARCHIVO;

    // eliminar estas tres líneas al implementar la función
    (void)arch;
    (void)nombreTxt;
    (void)stockMinimo;

    return exportados;
}

// TODO 4 - BUSCAR POR DESCRIPCIÓN
// Busca secuencialmente, desde el principio del archivo, el primer producto
// VIGENTE cuya descripción coincida exactamente con 'descripcionBuscada'.
// Usar sonIguales() de utiles.h para comparar las cadenas.
// Devuelve la posición del registro encontrado, o NO_ENCONTRADO si no existe.
long buscarPorDescripcion(FILE *arch, const char *descripcionBuscada)
{
    long posicion = NO_ENCONTRADO;

    // eliminar estas dos líneas al implementar la función
    (void)arch;
    (void)descripcionBuscada;

    return posicion;
}

// TODO 5 - GENERAR CÓDIGO ÚNICO
// Genera un código de producto al azar en el rango [minimo, maximo] que no
// pertenezca a ningún producto ya existente en el archivo (ni vigente ni dado
// de baja). Usar generarNumAleatorio() de utiles.h y reutilizar buscarCodigo()
// para comprobar que el código generado todavía no existe.
// Devuelve el código único generado.
int generarCodigoUnico(FILE *arch, int minimo, int maximo)
{
    int codigo = 0;

    // eliminar estas tres líneas al implementar la función
    (void)arch;
    (void)minimo;
    (void)maximo;

    return codigo;
}

// *********************************************************************************
//                         FUNCIONES DE PANTALLA Y OPCIONES
// *********************************************************************************

int menu(void)
{
    printf("\n\tSTOCK DEL DEPÓSITO - %s\n", NOMBRE_ARCHIVO);
    linea(ANCHO_LINEA, '=');
    printf("  %2d. Alta de producto\n", OPCION_ALTA);
    printf("  %2d. Listar productos\n", OPCION_LISTAR);
    printf("  %2d. Consultar por código\n", OPCION_CONSULTAR);
    printf("  %2d. Ver registro por posición\n", OPCION_POSICION);
    printf("  %2d. Ingreso / egreso de stock\n", OPCION_STOCK);
    printf("  %2d. Baja lógica\n", OPCION_BAJA);
    printf("  %2d. Compactar archivo (baja física)\n", OPCION_COMPACTAR);
    printf("  %2d. Modificar precio\n", OPCION_PRECIO);
    printf("  %2d. Reactivar producto\n", OPCION_REACTIVAR);
    printf("  %2d. Exportar stock bajo a %s\n", OPCION_EXPORTAR, NOMBRE_EXPORT);
    printf("  %2d. Buscar por descripción\n", OPCION_BUSCAR_DESC);
    printf("  %2d. Alta automática (código al azar)\n", OPCION_ALTA_AUTO);
    printf("  %2d. Salir\n", OPCION_SALIR);
    linea(ANCHO_LINEA, '=');

    return pedirEnteroRango("Opción: ", OPCION_SALIR, OPCION_ALTA_AUTO);
}

// Arma el struct con datos del teclado (no toca el archivo)
Producto ingresarProducto(int codigo)
{
    Producto prod;

    prod.codigo = codigo;
    leerCadena(prod.descripcion, MAX_DESC, "Descripción: ");
    leerFlotante("Precio: ", &prod.precio);
    prod.stock = pedirEnteroRango("Stock inicial: ", 0, STOCK_MAX);
    prod.activo = ACTIVO;
    return prod;
}

void encabezadoListado(void)
{
    printf("\n[Pos]  Cód.  %-30s %10s %7s\n", "Descripción", "Precio", "Stock");
    linea(ANCHO_LINEA, '-');
}

void mostrarProducto(Producto prod, long posicion)
{
    printf("[%3ld] %5d  %-30s %10.2f %7d\n", posicion, prod.codigo,
           prod.descripcion, prod.precio, prod.stock);
}

void listarProductos(FILE *arch)
{
    Producto prod;
    long posicion = 0;
    size_t leidos;

    encabezadoListado();
    rewind(arch);
    leidos = fread(&prod, sizeof(Producto), 1, arch);
    while (leidos == 1)
    {
        if (prod.activo)
            mostrarProducto(prod, posicion);
        posicion++;
        leidos = fread(&prod, sizeof(Producto), 1, arch);
    }
}

// ALTA: si el código pertenece a un producto dado de baja, no se duplica:
// se indica que corresponde reactivarlo
void opcionAlta(FILE *arch)
{
    Producto prod;
    int codigo;

    printf("\n\tALTA DE PRODUCTO\n");
    linea(ANCHO_LINEA, '-');
    codigo = pedirEnteroRango("Código: ", COD_MIN, COD_MAX);

    if (buscarPorCodigo(arch, codigo) != NO_ENCONTRADO)
    {
        printf("Ya existe un producto vigente con ese código.\n");
    }
    else if (buscarCodigo(arch, codigo, DADO_DE_BAJA) != NO_ENCONTRADO)
    {
        printf("Ese código pertenece a un producto dado de baja.\n");
        printf("Use la opción %d para reactivarlo.\n", OPCION_REACTIVAR);
    }
    else
    {
        prod = ingresarProducto(codigo);
        if (guardarAlFinal(arch, prod))
            printf("Producto guardado.\n");
        else
            printf("No se pudo guardar el producto.\n");
    }
}

void opcionConsultar(FILE *arch)
{
    Producto prod;
    long posicion;

    printf("\n\tCONSULTA POR CÓDIGO\n");
    linea(ANCHO_LINEA, '-');
    posicion = buscarPorCodigo(arch, leerEntero("Código: "));

    if (posicion == NO_ENCONTRADO)
        printf("No existe un producto vigente con ese código.\n");
    else if (leerRegistro(arch, posicion, &prod))
    {
        encabezadoListado();
        mostrarProducto(prod, posicion);
    }
}

// Muestra el registro tal como está en el disco, aunque esté dado de baja
void opcionPosicion(FILE *arch)
{
    Producto prod;
    long cantidad, posicion;

    printf("\n\tVER REGISTRO POR POSICIÓN\n");
    linea(ANCHO_LINEA, '-');
    cantidad = contarRegistros(arch);

    if (cantidad == 0)
        printf("El archivo está vacío.\n");
    else
    {
        printf("El archivo tiene %ld registros (posiciones 0 a %ld).\n", cantidad, cantidad - 1);
        posicion = pedirEnteroRango("Posición: ", 0, (int)(cantidad - 1));
        if (leerRegistro(arch, posicion, &prod))
        {
            encabezadoListado();
            mostrarProducto(prod, posicion);
            if (!prod.activo)
                printf("(registro dado de baja: sigue en el archivo)\n");
        }
    }
}

void opcionStock(FILE *arch)
{
    Producto prod;
    long posicion;
    int cantidad;

    printf("\n\tINGRESO / EGRESO DE STOCK\n");
    linea(ANCHO_LINEA, '-');
    posicion = buscarPorCodigo(arch, leerEntero("Código: "));

    if (posicion == NO_ENCONTRADO)
        printf("No existe un producto vigente con ese código.\n");
    else if (leerRegistro(arch, posicion, &prod))
    {
        cantidad = leerEntero("Cantidad (+ ingresa / - egresa): ");
        if (actualizarStock(arch, posicion, cantidad))
            printf("Stock actualizado   (%d -> %d)\n", prod.stock, prod.stock + cantidad);
        else
            printf("Stock insuficiente\n");
    }
}

void opcionBaja(FILE *arch)
{
    long posicion;

    printf("\n\tBAJA LÓGICA\n");
    linea(ANCHO_LINEA, '-');
    posicion = buscarPorCodigo(arch, leerEntero("Código: "));

    if (posicion == NO_ENCONTRADO)
        printf("No existe un producto vigente con ese código.\n");
    else if (darDeBaja(arch, posicion))
        printf("Producto dado de baja.\n");
    else
        printf("No se pudo dar de baja.\n");
}

void opcionPrecio(FILE *arch)
{
    Producto prod;
    long posicion;
    float nuevoPrecio;

    printf("\n\tMODIFICAR PRECIO\n");
    linea(ANCHO_LINEA, '-');
    posicion = buscarPorCodigo(arch, leerEntero("Código: "));

    if (posicion == NO_ENCONTRADO)
        printf("No existe un producto vigente con ese código.\n");
    else if (leerRegistro(arch, posicion, &prod))
    {
        printf("%s - precio actual: $%.2f\n", prod.descripcion, prod.precio);
        leerFlotante("Nuevo precio: ", &nuevoPrecio);
        while (nuevoPrecio <= 0)
        {
            printf("El precio tiene que ser mayor que cero.\n");
            leerFlotante("Nuevo precio: ", &nuevoPrecio);
        }

        if (modificarPrecio(arch, posicion, nuevoPrecio))
            printf("Precio actualizado   ($%.2f -> $%.2f)\n", prod.precio, nuevoPrecio);
        else
            printf("No se pudo modificar el precio.\n");
    }
}

void opcionReactivar(FILE *arch)
{
    long posicion;
    int codigo;

    printf("\n\tREACTIVAR PRODUCTO\n");
    linea(ANCHO_LINEA, '-');
    codigo = leerEntero("Código: ");
    posicion = buscarCodigo(arch, codigo, DADO_DE_BAJA);

    if (posicion == NO_ENCONTRADO)
        printf("No hay un producto dado de baja con ese código.\n");
    else if (reactivarProducto(arch, posicion))
        printf("Producto reactivado.\n");
    else
        printf("No se pudo reactivar.\n");
}

void opcionExportar(FILE *arch)
{
    long exportados;

    printf("\n\tEXPORTAR STOCK BAJO\n");
    linea(ANCHO_LINEA, '-');
    exportados = exportarStockBajo(arch, NOMBRE_EXPORT, STOCK_MINIMO);

    if (exportados == ERROR_ARCHIVO)
        printf("No se pudo crear %s\n", NOMBRE_EXPORT);
    else
        printf("Se exportaron %ld productos con stock menor a %d a %s\n",
               exportados, STOCK_MINIMO, NOMBRE_EXPORT);
}

void opcionBuscarDescripcion(FILE *arch)
{
    char texto[MAX_DESC];
    Producto prod;
    long posicion;

    printf("\n\tBUSCAR POR DESCRIPCIÓN\n");
    linea(ANCHO_LINEA, '-');
    leerCadena(texto, MAX_DESC, "Descripción exacta a buscar: ");
    posicion = buscarPorDescripcion(arch, texto);

    if (posicion == NO_ENCONTRADO)
        printf("No existe un producto vigente con esa descripción.\n");
    else if (leerRegistro(arch, posicion, &prod))
    {
        encabezadoListado();
        mostrarProducto(prod, posicion);
    }
}

void opcionAltaAutomatica(FILE *arch)
{
    Producto prod;
    int codigo;

    printf("\n\tALTA AUTOMÁTICA (código al azar)\n");
    linea(ANCHO_LINEA, '-');
    codigo = generarCodigoUnico(arch, COD_MIN, COD_MAX);
    printf("Código asignado: %d\n", codigo);

    prod = ingresarProducto(codigo);
    if (guardarAlFinal(arch, prod))
        printf("Producto guardado.\n");
    else
        printf("No se pudo guardar el producto.\n");
}
