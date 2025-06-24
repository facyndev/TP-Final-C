#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Variables Globales
int capacidadDestinos[4] = {60, 60, 60, 60};
int importePasajeroDestino[4] = {25000, 14000, 19000, 23000};
char codigosDestinosValidos[][4] = {"BRA", "MDQ", "MZA", "BRC"};
float porcentajesMenoresDestinos[] = {0, 0, 0, 0};

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

/*
    Funcion que recibe un array de tipo char (string) y valida una serie de condiciones, si no estan correcto, va a generar un bucle hasta que los datos sean correctos.
    Devuelve 1 en caso de error y 0 en caso de exito.
    validar_dni(->array[string]) -> number
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
        // Funcion para convertir un dato numerico a un dato tipo char (string)
        sprintf(stringConvertido, "%d", contador);
        while (contador < 60 && strcmp(primerosDigitos, stringConvertido) != 0)
        {
            contador++;
            estadoError = 1;
            sprintf(stringConvertido, "%d", contador);
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

    - validar_numero(->array[string]) -> number
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
    // Codigo ASCII de la letra ñ
    int ascii = 164;
    for (int i = 0; i < longitudCaracteres; i++)
    {
        if (isalpha(caracteres[i]) == 0 && caracteres[i] == ascii)
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
    Funcion que determina el importe final por pasajero y ademas descuenta la capacidad de cada destino.

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
    }
    else if (strcmp(codigo, "MDQ") == 0)
    {
        precio = importePasajeroDestino[1];
    }
    else if (strcmp(codigo, "MZA") == 0)
    {
        precio = importePasajeroDestino[2];
    }
    else if (strcmp(codigo, "BRC") == 0)
    {
        precio = importePasajeroDestino[3];
    }

    // En caso de que el pasajero abone con tarjeta de credito
    if (metodoPago == 1)
    {
        precio += precio * 0.05;
    }

    // Para los niños menores a 5 años deberan abonar un seguro.
    if (edadConvertida < 5)
    {
        precio += seguroMenores;
    }

    return precio;
}

/*
    Funcion que descuenta los pasajeros del destino seleccionado.
    Devuelve 1 en caso de error y 0 en caso de exito y ademas descuenta el pasajero de su capacidad.
*/
int descontar_pasajeros(char codigo[])
{
    int estadoError = 0;
    if (strcmp(codigo, "BRA") == 0 && capacidadDestinos[0] > 0)
    {
        capacidadDestinos[0] = capacidadDestinos[0] - 1;
    }
    else if (strcmp(codigo, "MDQ") == 0 && capacidadDestinos[1] > 0)
    {
        capacidadDestinos[1] = capacidadDestinos[1] - 1;
    }
    else if (strcmp(codigo, "MZA") == 0 && capacidadDestinos[2] > 0)
    {
        capacidadDestinos[2] = capacidadDestinos[2] - 1;
    }
    else if (strcmp(codigo, "BRC") == 0 && capacidadDestinos[3] > 0)
    {
        capacidadDestinos[3] = capacidadDestinos[3] - 1;
    }
    else
    {
        estadoError = 1;
    }

    return estadoError;
}

/*
    Funcion que recibe varios tres cadenas de caracter, dos arrays de numeros y un numero, se le pide al usuario que ingrese una serie de datos
    carga_datos(->array[STRING],->array[STRING], array[STRING], array[NUMBER], NUMBER, array[NUMBER])->VOID
*/
void carga_datos(char apellidos[][10], char nombres[][10], char codigosDestinos[][4], char documentos[][9], int cantPasajeros, char edades[][3], float preciosPasajes[])
{
    int metodoPago;
    int estadoNumero, estadoDNI, estadoCaracteres, estadoCapacidad, estadoCodigo;
    for (int i = 0; i < cantPasajeros; i++)
    {
        printf("Pasajero N%i\n\n", i + 1);

        do
        {
            printf("Ingrese su DNI (sin puntos): ");
            scanf("%s", documentos[i]);
            estadoNumero = validar_numero(documentos[i]);
            estadoDNI = validar_dni(documentos[i]);
            if (estadoNumero == 1)
            {
                printf("Error: El D.N.I debe debe contener solo numeros.\n");
            }
            else if (estadoDNI == 1)
            {
                printf("Error: El D.N.I debe comenzar con 5 o 6 en caso de tener 7 digitos.\nEn caso de tener 8 digitos, debe comenzar con numero que se encuentre entre 10 y 60.\n");
            }
        } while (estadoNumero == 1 || estadoDNI == 1);

        do
        {
            printf("Ingrese su nombre: ");
            scanf("%s", nombres[i]);
            estadoCaracteres = validar_caracteres(nombres[i]);
            if (estadoCaracteres == 1)
            {
                printf("Error: El nombre debe contener solo caracteres.");
            }
        } while (estadoCaracteres == 1);

        do
        {
            printf("Ingrese su apellido: ");
            scanf("%s", apellidos[i]);
            estadoCaracteres = validar_caracteres(apellidos[i]);
            if (estadoCaracteres == 1)
            {
                printf("Error: El apellido debe contener solo caracteres.\n");
            }
        } while (estadoCaracteres == 1);

        do
        {
            printf("Ingrese su edad: ");
            scanf(" %s", edades[i]);
            estadoNumero = validar_numero(edades[i]);
            if (estadoNumero == 1)
            {
                printf("Error: La edad solo debe contener solo numeros.\n");
            }
        } while (estadoNumero == 1);

        printf("Destino: Brasil - Codigo: BRA\nDestino: Mar del Plata - Codigo: MDQ\nDestino: Mendoza - Codigo: MZA\nDestino: Bariloche - Codigo: BRC\n\n");

        do
        {
            printf("Ingrese el codigo del destino: ");
            scanf("%s", codigosDestinos[i]);
            estadoCaracteres = validar_caracteres(codigosDestinos[i]);
            estadoCapacidad = descontar_pasajeros(codigosDestinos[i]);
            estadoCodigo = validar_codigos(codigosDestinos[i]);
            if (estadoCaracteres == 1)
            {
                printf("Error: El codigo de destino debe contener solo caracteres.\n");
            }
            else if (estadoCodigo == 1)
            {
                printf("Error: El codigo de destino no se encuentra en la agencia.\n");
            }
            else if (estadoCapacidad == 1)
            {
                printf("Error: La capacidad del destino esta llena. Debes seleccionar otro destino.\n");
            }
        } while (estadoCaracteres == 1 || estadoCodigo == 1 || estadoCapacidad == 1);

        printf("%cComo desea abonar?\n", 168);
        do
        {
            printf("1. Tarjeta de credito.\n2. Tarjeta de debito.\n3. Efectivo\n4. Transferencia\n");
            printf("Ingrese una opcion: ");
            scanf("%i", &metodoPago);
            if (metodoPago < 1 || metodoPago > 4)
            {
                printf("Error: La opcion ingresada no es valida.\n");
            }
        } while (metodoPago < 1 || metodoPago > 4);

        preciosPasajes[i] = definir_importe(codigosDestinos[i], metodoPago, edades[i]);
    }
}

/*
    Funcion para ordenamiento alfabetico por apellido. Ademas ordena sus datos aliados correspondientes,
    como los son el nombre, codigo destino, DNI.

    ordenamiento_por_apellidos(->array[STRING],->array[STRING], array[STRING], array[NUMBER], NUMBER, array[NUMBER], number)->VOID
*/
void ordenamiento_por_apellidos(char apellidos[][10], char nombres[][10], char codigosDestinos[][4], char documentos[][9], char edades[][3], float preciosPasajes[], int n)
{
    char tempApellido[10], tempNombre[10], tempCodigo[4], tempEdades[3], tempDocumentos[9];
    float tempPrecio;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(apellidos[j], apellidos[j + 1]) > 0)
            {
                // Documentos
                strcpy(tempDocumentos, documentos[j]);
                strcpy(documentos[j], documentos[j + 1]);
                strcpy(documentos[j + 1], tempDocumentos);

                // Apellido
                strcpy(tempApellido, apellidos[j]);
                strcpy(apellidos[j], apellidos[j + 1]);
                strcpy(apellidos[j + 1], tempApellido);

                // Nombre
                strcpy(tempNombre, nombres[j]);
                strcpy(nombres[j], nombres[j + 1]);
                strcpy(nombres[j + 1], tempNombre);

                // Codigo destino
                strcpy(tempCodigo, codigosDestinos[j]);
                strcpy(codigosDestinos[j], codigosDestinos[j + 1]);
                strcpy(codigosDestinos[j + 1], tempCodigo);

                // Edades
                strcpy(tempEdades, edades[j]);
                strcpy(edades[j], edades[j + 1]);
                strcpy(edades[j + 1], tempEdades);

                // Precio
                tempPrecio = preciosPasajes[j];
                preciosPasajes[j] = preciosPasajes[j + 1];
                preciosPasajes[j + 1] = tempPrecio;
            }
        }
    }
}


/*
    Funcion para ordenamiento alfabetico por codigos y luego ordenamiento alfabetico de apellidos de cada codigo. Ademas ordena sus datos aliados correspondientes,
    como los son el nombre, codigo destino, DNI.

    ordenamiento_por_codigo_apellido(->array[STRING],->array[STRING], array[STRING], array[NUMBER], NUMBER, array[NUMBER], number)->VOID
*/
void ordenamiento_por_codigo_apellido(char apellidos[][10], char nombres[][10], char codigosDestinos[][4], char documentos[][9], char edades[][3], float preciosPasajes[], int n)
{
    char tempApellido[10], tempNombre[10], tempCodigo[4], tempEdades[3], tempDocumentos[9];
    float tempPrecio;

    // Ordenamiento por codigo de destino
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(codigosDestinos[j], codigosDestinos[j + 1]) > 0)
            {
                // Codigo destino
                strcpy(tempCodigo, codigosDestinos[j]);
                strcpy(codigosDestinos[j], codigosDestinos[j + 1]);
                strcpy(codigosDestinos[j + 1], tempCodigo);

                // Apellido
                strcpy(tempApellido, apellidos[j]);
                strcpy(apellidos[j], apellidos[j + 1]);
                strcpy(apellidos[j + 1], tempApellido);

                // Nombre
                strcpy(tempNombre, nombres[j]);
                strcpy(nombres[j], nombres[j + 1]);
                strcpy(nombres[j + 1], tempNombre);

                // Edades
                strcpy(tempEdades, edades[j]);
                strcpy(edades[j], edades[j + 1]);
                strcpy(edades[j + 1], tempEdades);

                // Precio
                tempPrecio = preciosPasajes[j];
                preciosPasajes[j] = preciosPasajes[j + 1];
                preciosPasajes[j + 1] = tempPrecio;
            }
        }
    }

    // Ordenamiento por apellido, teniendo en cuenta los codigos de destinos
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(apellidos[j], apellidos[j + 1]) > 0 && strcmp(codigosDestinos[j], codigosDestinos[j + 1]) == 0)
            {
                // Codigo destino
                strcpy(tempCodigo, codigosDestinos[j]);
                strcpy(codigosDestinos[j], codigosDestinos[j + 1]);
                strcpy(codigosDestinos[j + 1], tempCodigo);

                // Apellido
                strcpy(tempApellido, apellidos[j]);
                strcpy(apellidos[j], apellidos[j + 1]);
                strcpy(apellidos[j + 1], tempApellido);

                // Nombre
                strcpy(tempNombre, nombres[j]);
                strcpy(nombres[j], nombres[j + 1]);
                strcpy(nombres[j + 1], tempNombre);

                // Edades
                strcpy(tempEdades, edades[j]);
                strcpy(edades[j], edades[j + 1]);
                strcpy(edades[j + 1], tempEdades);

                // Precio
                tempPrecio = preciosPasajes[j];
                preciosPasajes[j] = preciosPasajes[j + 1];
                preciosPasajes[j + 1] = tempPrecio;
            }
        }
    }
}

void mostrar_pasajeros_por_apellidos(char apellidos[][10], char nombres[][10], char codigosDestinos[][4], char documentos[][9], char edades[][3], float preciosPasajes[], int n)
{
    printf("-- Lista de pasajeros (ordenada por apellidos) --\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("Apellido y Nombre: %s %s\n", apellidos[i], nombres[i]);
        printf("DNI: %s\n", documentos[i]);
        printf("Edad: %s\n", edades[i]);
        if (strcmp(codigosDestinos[i], "BRA") == 0)
        {
            printf("Destino seleccionado: Brasil");
        }
        else if (strcmp(codigosDestinos[i], "MDQ") == 0)
        {
            printf("Destino seleccionado: Mar del Plata");
        }
        else if (strcmp(codigosDestinos[i], "MZA") == 0)
        {
            printf("Destino seleccionado: Mendoza");
        }
        else if (strcmp(codigosDestinos[i], "BRC") == 0)
        {
            printf("Destino seleccionado: Bariloche");
        }
        printf("\n-------------------\n");
    }
}

void mostrar_pasajeros_por_codigosyapellidos(char apellidos[][10], char nombres[][10], char codigosDestinos[][4], char documentos[][9], char edades[][3], float preciosPasajes[], int n)
{
    printf("-- Lista de pasajeros (ordenada por codigo y apellido-nombre) --\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("Codigo destino: %s\n", codigosDestinos[i]);
        printf("Apellido y nombre: %s %s\n", apellidos[i], nombres[i]);
        printf("DNI: %s\n", documentos[i]);
        printf("Edad: %s\n", edades[i]);
        printf("\n-------------------\n");
    }
}

void mostrar_lista_destinos(char codigosDestinos[][4], int capacidadDestinos[], float preciosPasajes[], int cantidadPasajeros)
{
    float importeTotal = 0;
    float importesAcumuladosDestino[] = {0, 0, 0, 0};
    for (int i = 0; i < cantidadPasajeros; i++)
    {
        if (strcmp(codigosDestinos[i], "BRA") == 0)
        {
            importesAcumuladosDestino[0] += preciosPasajes[i];
        }
        else if (strcmp(codigosDestinos[i], "MDQ") == 0)
        {
            importesAcumuladosDestino[1] += preciosPasajes[i];
        }
        else if (strcmp(codigosDestinos[i], "MZA") == 0)
        {
            importesAcumuladosDestino[2] += preciosPasajes[i];
        }
        else if (strcmp(codigosDestinos[i], "BRC") == 0)
        {
            importesAcumuladosDestino[3] += preciosPasajes[i];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        printf("Codigo de Destino: %s\n", codigosDestinosValidos[i]);
        printf("Cantidad Pasajeros del destino: %d\n", 60 - capacidadDestinos[i]);
        printf("Importe Total del destino: $%.2f", importesAcumuladosDestino[i]);
        importeTotal += importesAcumuladosDestino[i];
        printf("\n-------------------\n");
    }
    printf("\nImporte Total de los destinos: $%.2f\n\n", importeTotal);
}

int buscar_pasajero_dni(char documentos[][9], int cantidadPasajeros)
{
    int estadoNumero, estadoDNI;
    char doc[9];
    do
    {
        printf("Ingrese su DNI (sin puntos): ");
        scanf("%s", doc);
        estadoNumero = validar_numero(doc);
        estadoDNI = validar_dni(doc);
        if (estadoNumero == 1)
        {
            printf("Error: El D.N.I debe debe contener solo numeros.\n");
        }
        else if (estadoDNI == 1)
        {
            printf("Error: El D.N.I debe comenzar con 5 o 6 en caso de tener 7 digitos.\nEn caso de tener 8 digitos, debe comenzar con numero que se encuentre entre 10 y 60.\n");
        }
    } while (estadoNumero == 1 || estadoDNI == 1);

    int posicionDocumento = 0;

    while (posicionDocumento < cantidadPasajeros && strcmp(doc, documentos[posicionDocumento]) != 0)
    {
        posicionDocumento++;
    }

    /*
        En caso de que el while termino y no encontro el documento, indicamos que la posicion es negativa.
        De tal manera, indicamos que no existe el pasajero
    */
    if (strcmp(doc, documentos[posicionDocumento]) != 0)
    {
        posicionDocumento = -1;
    }

    return posicionDocumento;
}

void mostrar_datos_pasajeros(int posicion, char edades[][3], char apellidos[][10], char nombres[][10], char codigosDestinos[][4], float precioPasajes[])
{
    printf("Apellido y Nombre: %s %s\n", apellidos[posicion], nombres[posicion]);
    printf("Edad: %s\n", edades[posicion]);
    printf("Codigo Destino: %s\n", codigosDestinos[posicion]);
    printf("Precio del destino: $%.2f\n", precioPasajes[posicion]);
}

void mostrar_estadisticas(char edades[][3], char codigosDestinos[][4], int cantidadPasajeros)
{
    // Cuando menor capacidad tenga el destino, mas pasajeros lo estan ocupando
    int capacidadDestinoMenor = capacidadDestinos[0];
    int posicionDestinoMasSolicitado = 0;

    for (int i = 0; i < 4; i++)
    {
        float porcentajeMenores = 0;
        int contadorMenores = 0;
        int contadorPasajerosDestino = 0;
        int edadConvertida = 0;
        float porcentajePasajeros = ((60 - capacidadDestinos[i]) * 100) / 60;
        if (i == 0)
        {
            printf("Brasil\n\n");
            printf("Porcentaje de pasajeros: %%%.2f\n", porcentajePasajeros);
            for (int j = 0; j < cantidadPasajeros; j++)
            {
                if (strcmp(codigosDestinos[j], "BRA") == 0)
                {
                    contadorPasajerosDestino++;
                }
                edadConvertida = atoi(edades[j]);
                if (edadConvertida < 5)
                {
                    contadorMenores++;
                }
            }

            // Evitar la division por 0, para evitar errores 0
            if (contadorPasajerosDestino != 0)
            {
                porcentajeMenores = (contadorMenores * 100) / contadorPasajerosDestino;
            }
            else
            {
                porcentajeMenores = 0;
            }
            printf("Porcentaje de menores: %%%.2f\n", porcentajeMenores);
        }
        else if (i == 1)
        {
            printf("Mar del Plata\n\n");
            printf("Porcentaje de pasajeros: %%%.2f\n", porcentajePasajeros);
            for (int j = 0; j < cantidadPasajeros; j++)
            {
                if (strcmp(codigosDestinos[j], "MDQ") == 0)
                {
                    contadorPasajerosDestino++;
                }
                edadConvertida = atoi(edades[j]);
                if (edadConvertida < 5)
                {
                    contadorMenores++;
                }
            }
            // Evitar la division por 0, para evitar errores 0
            if (contadorPasajerosDestino != 0)
            {
                porcentajeMenores = (contadorMenores * 100) / contadorPasajerosDestino;
            }
            else
            {
                porcentajeMenores = 0;
            }
            printf("Porcentaje de menores: %%%.2f\n", porcentajeMenores);
        }
        else if (i == 2)
        {
            printf("Mendoza\n\n");
            printf("Porcentaje de pasajeros: %%%.2f \n", porcentajePasajeros);
            for (int j = 0; j < cantidadPasajeros; j++)
            {
                if (strcmp(codigosDestinos[j], "MZA") == 0)
                {
                    contadorPasajerosDestino++;
                }
                edadConvertida = atoi(edades[j]);
                if (edadConvertida < 5)
                {
                    contadorMenores++;
                }
            }
            // Evitar la division por 0, para evitar errores 0
            if (contadorPasajerosDestino != 0)
            {
                porcentajeMenores = (contadorMenores * 100) / contadorPasajerosDestino;
            }
            else
            {
                porcentajeMenores = 0;
            }
            printf("Porcentaje de menores: %%%.2f\n", porcentajeMenores);
        }
        else if (i == 3)
        {
            printf("Bariloche\n\n");
            printf("Porcentaje de pasajeros: %%%.2f\n", porcentajePasajeros);
            for (int j = 0; j < cantidadPasajeros; j++)
            {
                if (strcmp(codigosDestinos[j], "BRC") == 0)
                {
                    contadorPasajerosDestino++;
                }
                edadConvertida = atoi(edades[j]);
                if (edadConvertida < 5)
                {
                    contadorMenores++;
                }
            }
            // Evitar la division por 0, para evitar errores 0
            if (contadorPasajerosDestino != 0)
            {
                porcentajeMenores = (contadorMenores * 100) / contadorPasajerosDestino;
            }
            else
            {
                porcentajeMenores = 0;
            }
            printf("Porcentaje de menores: %%%.2f\n", porcentajeMenores);
        }

        if (capacidadDestinos[i] < capacidadDestinoMenor)
        {
            capacidadDestinoMenor = capacidadDestinos[i];
            posicionDestinoMasSolicitado = i;
        }
    }

    if (posicionDestinoMasSolicitado == 0)
    {
        printf("Destino mas solicitado: Brasil\n");
    }
    else if (posicionDestinoMasSolicitado == 1)
    {
        printf("Destino mas solicitado: Mar de Plata\n");
    }
    else if (posicionDestinoMasSolicitado == 2)
    {
        printf("Destino mas solicitado: Mendoza\n");
    }
    else if (posicionDestinoMasSolicitado == 3)
    {
        printf("Destino mas solicitado: Bariloche\n");
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
        int posicionPasajeroEncontrado;

        switch (opcion)
        {
        case 1:
            ordenamiento_por_apellidos(apellidos, nombres, codigosDestinos, documentos, edades, preciosPasajes, cantPasajeros);
            mostrar_pasajeros_por_apellidos(apellidos, nombres, codigosDestinos, documentos, edades, preciosPasajes, cantPasajeros);
            break;
        case 2:
            ordenamiento_por_codigo_apellido(apellidos, nombres, codigosDestinos, documentos, edades, preciosPasajes, cantPasajeros);
            mostrar_pasajeros_por_codigosyapellidos(apellidos, nombres, codigosDestinos, documentos, edades, preciosPasajes, cantPasajeros);
            break;
        case 3:
            mostrar_lista_destinos(codigosDestinos, capacidadDestinos, preciosPasajes, cantPasajeros);
            break;
        case 4:
            posicionPasajeroEncontrado = buscar_pasajero_dni(documentos, cantPasajeros);
            if (posicionPasajeroEncontrado < 0)
            {
                printf("Error: No existe pasajero con ese D.N.I.\n");
            }
            else
            {
                mostrar_datos_pasajeros(posicionPasajeroEncontrado, edades, apellidos, nombres, codigosDestinos, preciosPasajes);
            }
            break;
        case 5:
            mostrar_estadisticas(edades, codigosDestinos, cantPasajeros);
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