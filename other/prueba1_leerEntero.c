#include <stdio.h> // Necesaria para usar printf, fgets, sscanf y stdin

// Prototipo de la funcion: le avisa al compilador que esta funcion existe
// mas abajo, antes de que main() intente usarla.
int leerEntero(const char *mensaje);

int main()
{
    int num1;
    int num2;
    int suma;

    printf("=== Mini calculadora de suma ===\n\n");

    // Llamamos a la funcion y le pasamos el texto que queremos mostrar.
    // El programa se pausa dentro de leerEntero hasta que el usuario
    // ingrese un entero valido. Cuando lo logra, el valor se guarda en num1.
    num1 = leerEntero("Ingrese el primer numero entero: ");

    // Reutilizamos la misma funcion, pero con otro mensaje distinto.
    num2 = leerEntero("Ingrese el segundo numero entero: ");

    // Ya con ambos datos seguros, hacemos la cuenta
    suma = num1 + num2;

    // Mostramos el resultado final en pantalla
    printf("\nEl resultado de %d + %d es: %d\n", num1, num2, suma);

    return 0; // Indica al sistema operativo que el programa termino bien
}

// Implementacion de tu funcion tal cual la pasaste
int leerEntero(const char *mensaje)
{
    char buffer[100]; // Guarda temporalmente toda la linea escrita como texto
    int numero;       // Guarda el entero una vez convertido
    int flag = 1;     // Bandera de control: 1 = seguir pidiendo, 0 = terminar
    char extra;

    while (flag) // Mientras flag valga 1 (verdadero), el bucle se repite
    {
        printf("%s", mensaje); // Imprime el mensaje recibido desde main

        // Lee una linea completa del teclado (stdin) y la guarda en buffer
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            // Busca un numero entero (%d) dentro del texto en buffer.
            // Si logra convertir 1 numero, sscanf devuelve 1.
            if (sscanf(buffer, "%d %c", &numero, &extra) == 1)
                flag = 0; // Como el dato es valido, ponemos flag en 0 para salir
            else
                printf("Entrada invalida. Intente nuevamente.\n");
        }
    }

    return numero; // Devuelve el numero validado al lugar donde se la llamo
}