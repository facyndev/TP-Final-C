#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Variables Globales
int capacidadDestinos[4] = {60, 60, 60, 60};
int importePasajeroDestino[4] = {25000, 14000, 19000, 23000};
char codigosDestinosValidos[4][4] = {"BRA", "MDQ", "MZA", "BRC"};

/*Funcion que imprime las opciones del menu y devuelve la opcion seleccionada en un tipo entero.
MENU()-> NUMBER
*/

int menu()
{
    int opcion;
    printf("1. Mostar lista de pasajeros ordenada por Apellido y Nombre\n2. Mostrar lista de pasajeros ordenada por Codigo Destino y Apellido-Nombre\n3. Mostrar lista de Destinos\n4. Buscar por Pasajero\n5. Mostrar estadisticas\n6. Salir\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

/* Funcion que recibe un array de tipo number y valida una serie de condiciones, si no estan correcto, va a generar un bucle hasta que los datos sean correctos.
validar_dni(->array[NUMBER])-> VOID
*/
int validar_dni(char dni[9])
{
    int longitudDNI = strlen(dni);
    int estadoError = 0;
    if (longitudDNI == 8)
    {
        /*
            Se verifica que los dos primeros caracteres del DNI ingresado sean iguales al menos a uno de los numeros
            que se encuentre entre 10 y 60. Realizamos un contador de 10 hasta 60 el cual se va comparando uno a uno
            con los 2 primeros digitos que ingreso el usuario. El contador es convertido a un caracter ya que si bien el DNI
            es un numero, en este caso estamos manejando todo con el tipo char.
        */
        char primerosDigitos[] = {dni[0], dni[1], '\0'};
        int contador = 10;
        char stringConvertido[3];
        sprintf(stringConvertido, "%d", contador);
        while (contador < 60 && strcmp(primerosDigitos, stringConvertido) != 0)
        {
            sprintf(stringConvertido, "%d", contador);
            estadoError = 1;
            contador++;
        }

        // Verificar cuando corta el while si realmente salio porque la cadena son iguales.
        if (strcmp(primerosDigitos, stringConvertido) == 0)
        {
            estadoError = 0;
        }
        else
        {
            estadoError = 1;
        }
    }
    else if (longitudDNI == 7)
    {
        if (dni[0] != '5' && dni[0] != '6')
        {
            estadoError = 1;
        }
    }
    else
    {
        estadoError = 1;
    }

    return estadoError;
}

/*
    Funcion para validar que el dato ingresado sea unicamente un numero, es decir que no contenga caracteres.
    Devuelve 1 en caso de error y 0 en caso de exito.

    - validar_numero(->array[STRING])->number
*/
int validar_numero(char numero[])
{
    int longitudNumero = strlen(numero);
    int estadoError = 0;
    for (int i = 0; i < longitudNumero; i++)
    {
        if (isdigit(numero[i]) == 0)
        {
            estadoError = 1;
        }
    }
    return estadoError;
}

/*
    Funcion para validar que el dato ingresado sean unicamente caracteres, es decir que no contenga numeros.
    Devuelve 1 en caso de error y 0 en caso de exito.

    - validar_caracteres(->array[STRING])->number

*/
int validar_caracteres(char caracteres[])
{
    int longitudCaracteres = strlen(caracteres);
    int estadoError = 0;
    for (int i = 0; i < longitudCaracteres; i++)
    {
        if (isalpha(caracteres[i]) == 0)
        {
            estadoError = 1;
        }
    }

    return estadoError;
}

/*
    Funcion para validar que el codigo ingresado se encuentre en la agencia.
    Devuelve 1 en caso de error y 0 en caso de exito.

    validar_codigos(->array[string])-> number
*/
int validar_codigos(char codigo[])
{
    int estadoError = 1;
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(codigo, codigosDestinosValidos[i]) == 0)
        {
            estadoError = 0;
        }
    }

    return estadoError;
}
/*
    Funcion para vincular el destino con su respectivo importe.

    definir_importe(->array[string])-> number
*/
int definir_importe(char codigo[], int metodoPago, char edad[])
{
    int precio;
    int seguroMenores = 2000;
    // La funcion atoi permite convertir una cadena a entero.
    int edadConvertida = atoi(edad);

    if (strcmp(codigo, "BRA") == 0)
    {
        precio = importePasajeroDestino[0];
        capacidadDestinos[0] = capacidadDestinos[0] - 1;
    }
    else if (strcmp(codigo, "MDQ") == 0)
    {
        precio = importePasajeroDestino[1];
        capacidadDestinos[1] = capacidadDestinos[1] - 1;
    }
    else if (strcmp(codigo, "MZA") == 0)
    {
        precio = importePasajeroDestino[2];
        capacidadDestinos[2] = capacidadDestinos[2] - 1;
    }
    else if (strcmp(codigo, "BRC") == 0)
    {
        precio = importePasajeroDestino[3];
        capacidadDestinos[3] = capacidadDestinos[3] - 1;
    }

    // En caso de que el pasajero abona con tarjeta de credito
    if(metodoPago == 1) { 
        precio += precio * 0.05;
    }

    // Para los niños menores a 5 años deberan abonar un seguro.
    if(edadConvertida < 5) {
        precio += seguroMenores;
    }
    
    return precio;
}

/* Funcion que recibe varios tres cadenas de caracter, dos arrays de numeros y un numero, se le pide al usuario que ingrese una serie de datos
carga_datos(->array[STRING],->array[STRING], array[STRING], array[NUMBER], NUMBER, array[NUMBER])->VOID
*/
void carga_datos(char apellidos[][10], char nombres[][10], char codigosDestinos[][4], char documentos[][9], int cantPasajeros, char edades[][3], float preciosPasajes[])
{
    int metodoPago;
    for (int i = 0; i < cantPasajeros; i++)
    {
        printf("Pasajero N%i\n\n", i + 1);

        do
        {
            printf("Ingrese su DNI (sin puntos): ");
            scanf("%s", documentos[i]);
            if (validar_numero(documentos[i]) == 1)
            {
                printf("Error: El D.N.I debe debe contener solo numeros.\n");
            }
            else if (validar_dni(documentos[i]) == 1)
            {
                printf("Error: El D.N.I debe comenzar con 5 o 6 en caso de tener 7 digitos.\nEn caso de tener 8 digitos, debe comenzar con numero que se encuentre entre 10 y 60.\n");
            }
        } while (validar_numero(documentos[i]) == 1 || validar_dni(documentos[i]) == 1);

        do
        {
            printf("Ingrese su nombre: ");
            scanf("%s", nombres[i]);
            if (validar_caracteres(nombres[i]) == 1)
            {
                printf("Error: El nombre debe contener solo caracteres.");
            }
        } while (validar_caracteres(nombres[i]) == 1);

        do
        {
            printf("Ingrese su apellido: ");
            scanf("%s", apellidos[i]);
            if (validar_caracteres(apellidos[i]) == 1)
            {
                printf("Error: El apellido debe contener solo caracteres.");
            }
        } while (validar_caracteres(apellidos[i]) == 1);

        do
        {
            printf("Ingrese su edad: ");
            scanf(" %s", edades[i]);
            if (validar_numero(edades[i]) == 1)
            {
                printf("Error: La edad solo debe contener solo numeros.\n");
            }
        } while (validar_numero(edades[i]) == 1);

        printf("Destino: Brasil - Codigo: BRA\nDestino: Mar del Plata - Codigo: MDQ\nDestino: Mendoza - Codigo: MZA\nDestino: Bariloche - Codigo: BRC\n\n");
        do
        {
            printf("Ingrese el codigo del destino: ");
            scanf("%s", codigosDestinos[i]);
            if (validar_caracteres(codigosDestinos[i]) == 1)
            {
                printf("Error: El codigo de destino debe contener solo caracteres.\n");
            }
            else if (validar_codigos(codigosDestinos[i]) == 1)
            {
                printf("Error: El codigo de destino no se encuentra en la agencia.\n");
            }
        } while (validar_caracteres(codigosDestinos[i]) == 1 || validar_codigos(codigosDestinos[i]) == 1);
        
        printf("¿Como desea abonar?\n");
        do
        {
            printf("1. Tarjeta de credito.\n2. Tarjeta de debito.\n3. Efectivo\n4. Transferencia\n");
            printf("Ingrese una opcion: ");
            scanf("%i", &metodoPago);
            if(metodoPago < 1 || metodoPago > 4) {
                printf("Error: La opcion ingresada no es valida.\n");
            }
        } while (metodoPago < 1 || metodoPago > 4);
        
        preciosPasajes[i] = definir_importe(codigosDestinos[i], metodoPago, edades[i]);
    }
}

/* Funcion que toma un array de numeros, y solo ordena los numeros de menor a mayor
ORDEMANIENTO(->NUMBER)->VOID
*/
void ordenamiento(int arr[60])
{
    int min, aux;
    int length = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < length - 1; i++)
    {
        min = i;
        for (int j = 0; j < length; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }

        if (min != i)
        {
            aux = arr[i];
            arr[i] = arr[min];
            arr[min] = aux;
        }
    }
}

/*
    Funcion que toma una cadena de caracteres y su longitud, y solo ordena la cadena de forma Alfabetica
    ORDEMANIENTO_STRING(->array[STRING], ->NUMBER)->VOID
*/
void ordenamiento_string(char nombres[][10], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(nombres[j], nombres[j + 1]) > 0)
            {
                char temp[10];
                strcpy(temp, nombres[j]);
                strcpy(nombres[j], nombres[j + 1]);
                strcpy(nombres[j + 1], temp);
            }
        }
    }
}

int main()
{
    printf("----- Bienvenidos a Viaje Magico -----\n\n");
    int cantPasajeros;
    printf("Por favor, ingrese la cantidad de pasajeros: ");
    scanf("%d", &cantPasajeros);
    char edades[cantPasajeros][3];
    char documentos[cantPasajeros][9];
    char apellidos[cantPasajeros][10];
    char nombres[cantPasajeros][10];
    char codigosDestinos[cantPasajeros][4];
    float preciosPasajes[cantPasajeros];

    // Variable bandera para el control del menu
    int estadoPrograma = 1;

    carga_datos(apellidos, nombres, codigosDestinos, documentos, cantPasajeros, edades, preciosPasajes);

    while (estadoPrograma == 1)
    {
        int opcion = menu();
        switch (opcion)
        {
        case 1:
            printf("%d\n", cantPasajeros);
            printf("---Ordenado\n\n");
            // ordenamiento_string(nombres, cantPasajeros);
            for (int i = 0; i < cantPasajeros; i++)
            {
                printf("Nombre: %s\n", nombres[i]);
                printf("Apellido: %s\n", apellidos[i]);
                printf("Edad: %s\n", edades[i]);
                printf("DNI: %s\n", documentos[i]);
                printf("Destino: %s\n", codigosDestinos[i]);
                printf("Precio del destino: $%.2f\n\n", preciosPasajes[i]);
            }
            printf("-------------------\n\n");
            break;
        case 2:
            printf("2");
            break;
        case 3:
            printf("3");
            break;
        case 4:
            printf("4");
            break;
        case 5:
            printf("5");
            break;
        case 6:
            printf("Muchas gracias por utilizar nuestro programa. Nos vemos pronto");
            estadoPrograma = 0;
            break;
        default:
            printf("Error: La opcion ingresada no es valida.\n");
            break;
        }
    }
    return 0;
}