#include <stdio.h>//para poder usar el lenguaje C
#include <stdlib.h>
#include <string.h>//Para usar funciones tipo stringcomo strcmp
#include <conio.h>
#include <windows.h>//Para declarar estructuras de datos
#include <time.h>//Para usar funciones de tiempo
#include <basicthings.h>// Para usar navergaropciones, bloquear el teclado y generar el codigo aleatorio

#define MAX_PRODUCTOS 10 // Define el max de productos
#define MAX_CLIENTES 10 //Define el max de clientes
#define COLOR_DEFAULT 7  // Definir color blanco
#define COLOR_SELECTED 10 // Definir color verde
#define PRODUCTOS_POR_PAGINA 1
#define COSTO_MES 100
#define MAX_MESES 12
#define COSTO_MES 100
#define CLIENTES_POR_PAGINA 1

typedef struct { // Se crea la estructura de datos Inventario
    char nombre[50];
    char descripcion[50];
    int codigo;
    char precio[5];
    char cantidad[3];
} Inventario;

Inventario productosTotal[MAX_PRODUCTOS]; //Declara un arreglo productosTotal de tipo Inventario, que se usa para almacenar los detalles de los productos que se registran en el sistema.
int totalProductos = 0;

typedef struct {
    char nombre[50];
    char telefono[9];
    int codigo;
    int mesesMembresia;
    int costoTotal;
    int mesPagados[MAX_MESES];  // Arreglo para los meses pagados
    int mesesAdicionales[MAX_MESES]; // Arreglo para los meses adicionales
    int numMesesAdicionales; // Número de meses adicionales
    int costoTotalAdicional; // Costo total adicional
    char compania[20];
    int vuelto;
} Cliente;


//Struct para almacenar el user y contrasena de la persona.
typedef struct {
    char nombre[30];
    char contrasena[30];
} Usuario;

Usuario persona; //Declara una variable persona de tipo Usuario, que se usa para almacenar los detalles del usuario que se registra en el sistema.
Cliente listaClientes[MAX_CLIENTES];
int totalClientes = 0; 

//Funcion para generar un codigo aleatorio, entre 1000 y 9000, osea para un codigo de 4 digitos.
int generarCodigoAleatorio() {
    return rand() % 9000 + 1000;  
}

//Funcion para poder agregar productos
void agregarProductos() {
    
    //Validando que no ingrese mas productos del limite permitido
    if (totalProductos >= MAX_PRODUCTOS) {
        system("cls");
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3        Ya se alcanzo el maximo de productos,     \xB3");
        gotoxy(40, 9);
        printf("\xB3              no hay espacio para mas.            \xB3");
        gotoxy(40, 10);
        parteInferior();
        gotoxy(40, 12);
        system("pause");
        return;
    }

    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD  AGREGAR PRODUCTO  \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
    
    //Validando que ingrese algun nombre en el arreglo, sino no contnuara
    do {
        gotoxy(40, 9);
        parteMedia();
        gotoxy(40, 10);
        printf("\xB3          Ingrese el nombre del producto:         \xB3");
        gotoxy(40, 11);
        parteVacia();
        gotoxy(50, 11);
        ingresarProducto(productosTotal[totalProductos].nombre);
        fflush(stdin); 
        if (strlen(productosTotal[totalProductos].nombre) == 0) {
            gotoxy(40, 12);
            parteMedia();
            gotoxy(40, 13);
            printf("\xB3   El nombre del producto no puede estar vacio.   \xB3");
            gotoxy(40, 14);
            parteInferior();
            gotoxy(40, 16);
            system("pause");
            return;
        }
    } while (strlen(productosTotal[totalProductos].nombre) == 0);

    //Validando que ingrese algun precio en el arreglo, sino no continuara
    do {
        gotoxy(40, 12);
        parteMedia();
        gotoxy(40, 13);
        printf("\xB3         Ingrese el precio del producto:          \xB3");
        gotoxy(40, 14);
        parteVacia();
        gotoxy(65, 14);
        ingresarNumeros(productosTotal[totalProductos].precio, 4);  
        fflush(stdin);
        gotoxy(40, 15);
        parteMedia();
        
        //Convertimos en entero una cadena de caracteres
        int precioNum = atoi(productosTotal[totalProductos].precio);
        if (precioNum <= 0) {
            gotoxy(40, 16);
            printf("\xB3          El precio debe ser mayor que 0          \xB3");
            gotoxy(40, 17);
            printf("\xB3              y no puede estar vacio.             \xB3");
            gotoxy(40, 18);
            parteInferior();
            gotoxy(40, 20);
            system("pause");
            return;
        } else if (precioNum > 5000) {
            gotoxy(40, 16);
            printf("\xB3      El precio no puede ser mayor a 5000 C$.     \xB3");
            gotoxy(40, 17);
            parteInferior();
            gotoxy(40, 19);
            system("pause");
            return;
        } else {
            gotoxy(40, 16);
            printf("\xB3              El precio es aceptable.             \xB3");
            gotoxy(40, 17);
            parteMedia();
            break;
        }
    } while (1);

    //Validando que ingrese alguna cantidad en el arreglo, sino no continuara 
    do {
        gotoxy(40, 18);
        printf("\xB3        Ingrese la cantidad del producto:         \xB3");
        gotoxy(40, 19);
        parteVacia();
        gotoxy(65, 19);
        ingresarNumeros(productosTotal[totalProductos].cantidad, 2);  
        fflush(stdin);
        gotoxy(40, 20);
        parteMedia();
        
        //Convertimos en entero una cadena de caracteres
        int cantidadNum = atoi(productosTotal[totalProductos].cantidad);
        if (cantidadNum <= 0) {
            gotoxy(40, 21);
            printf("\xB3         La cantidad debe ser mayor que 0         \xB3");
            gotoxy(40, 22);
            printf("\xB3             y no puede estar vacia.              \xB3");
            gotoxy(40, 23);
            parteInferior();
            gotoxy(40, 25);
            system("pause");
            return;
        } else if (cantidadNum > 30) {
            gotoxy(40, 21);
            printf("\xB3       La cantidad no puede ser mayor a 30.       \xB3");
            gotoxy(40, 22);
            parteInferior();
            gotoxy(40, 24);
            system("pause");
            return;
        } else {
            gotoxy(40, 21);
            printf("\xB3             La cantidad es aceptable.            \xB3");
            gotoxy(40, 22);
            parteMedia();
            break;
        }
    } while (1);

    //Validando que ingrese alguna descripcion en el arreglo, sino no continuara
    do {
        gotoxy(40, 23);
        printf("\xB3      Agregue una descripcion al producto:        \xB3");
        gotoxy(40, 24);
        parteVacia();
        gotoxy(41, 24);
        ingresarDescripcion(productosTotal[totalProductos].descripcion);
        fflush(stdin);
        gotoxy(40, 25);
        parteInferior();
        if (strlen(productosTotal[totalProductos].descripcion) == 0) {
            gotoxy(40, 27);
            parteSuperior();
            gotoxy(40, 28);
            printf("\xB3 La descripcion del producto no puede estar vacia.\xB3");
            gotoxy(40, 29);
            parteInferior();
            gotoxy(40, 31);
            system("pause");
            return;
        }
        gotoxy(40, 27);
        system("pause");
    } while (strlen(productosTotal[totalProductos].descripcion) == 0);
    
    //Generamos el codigo del producto
    productosTotal[totalProductos].codigo = generarCodigoAleatorio();

    system("cls");
    
    //Imprimimos los detalles del producto
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD  DETALLES DEL PRODUCTO  \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3             Nombre del producto:                 \xB3");
    gotoxy(40, 11);
    parteVacia();
    gotoxy(50, 11);
    printf("%s", productosTotal[totalProductos].nombre);
    gotoxy(40, 12);
    parteMedia();
    gotoxy(40, 13);
    printf("\xB3             Codigo del producto:                 \xB3");
    gotoxy(40, 14);
    parteVacia();
    gotoxy(65, 14);
    printf("%d", productosTotal[totalProductos].codigo);
    gotoxy(40, 15);
    parteMedia();
    gotoxy(40, 16);
    printf("\xB3             Precio del producto:                 \xB3");
    gotoxy(40, 17);
    parteVacia(); 
    gotoxy(65, 17);
    printf("%d C$", atoi(productosTotal[totalProductos].precio)); 
    gotoxy(40, 18);
    parteMedia(); 
    gotoxy(40, 19);
    printf("\xB3            Cantidad del producto:                \xB3");
    gotoxy(40, 20);
    parteVacia();
    gotoxy(65, 20);
    printf("%d", atoi(productosTotal[totalProductos].cantidad));
    gotoxy(40, 21);
    parteMedia();  
    gotoxy(40, 22);
    printf("\xB3           Descripcion del producto:              \xB3");
    gotoxy(40, 23);
    parteVacia();
    gotoxy(41, 23);
    printf("%s", productosTotal[totalProductos].descripcion);
    gotoxy(40, 24);
    parteMedia();
    gotoxy(40, 25);
    printf("\xB3          Producto agregado con exito.            \xB3");
    gotoxy(40, 26);
    parteInferior();
    gotoxy(40, 28);
    system("pause");

    totalProductos++;
}

//Funcion para buscar el prudcto
void buscarProducto() {
    char nombre[50];
    char codigo[5];
    int tecla;
    
    //Imprimiendo las opciones que tiene el usuario
    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD   BUSCAR PRODUCTO  \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3      Si no recuerda el nombre ni el codigo,      \xB3 ");
    gotoxy(40, 11);
    printf("\xB3        presiona 'n' o 'N' para regresar.         \xB3 ");
    gotoxy(40, 12);
    printf("\xB3        Para continuar, presione 's' o 'S'.       \xB3 ");
    gotoxy(40, 13);
    parteInferior();
    
    // No continuar si no hay ningún producto registrado
    if (totalProductos == 0) {
        gotoxy(40, 15);
        parteSuperior();
        gotoxy(40, 16);
        printf("\xB3           No hay productos registrados.          \xB3");
        gotoxy(40, 17);
        parteInferior();
        gotoxy(40, 19);
        system("pause");
        return;
    }
    
    // Validar las teclas para continuar o regresar
    while (1) {
        tecla = getch();
        if (tecla == 'n' || tecla == 'N') {
            return;  
        } else if (tecla == 's' || tecla == 'S') {
            break;  
        } else {
            gotoxy(40, 15);
            parteSuperior();
            gotoxy(40, 16);
            printf("\xB3                  Tecla invalida.                 \xB3");
            gotoxy(40, 17);
            printf("\xB3         Presione 's' o 'S' para continuar        \xB3");
            gotoxy(40, 18);
            printf("\xB3            o 'n' o 'N' para regresar.            \xB3");
            gotoxy(40, 19);
            parteInferior();
        }
    }
    
    //Le pedimos al usuario el nombre y codigo del producto que busca
    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD   BUSCAR PRODUCTO  \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3         Ingrese el nombre del producto:          \xB3");
    gotoxy(40, 11);
    parteVacia();
    gotoxy(50, 11);
    ingresarProducto(nombre);
    fflush(stdin);
    gotoxy(40, 12);
    parteMedia();
    gotoxy(40, 13);
    printf("\xB3    Ingrese el codigo del producto (4 digitos):   \xB3"); 
    gotoxy(40, 14);
    parteVacia();
    gotoxy(65, 14);
    ingresarNumeros(codigo, 4);  
    fflush(stdin);
    gotoxy(40, 15);
    parteInferior();
    gotoxy(40, 17);
    system("pause");
    
    system("cls");
    
    //Convertimos en entero una cadena de caracteres
    int codigoNum = atoi(codigo);
    
    //Validamos que el codigo sea exactamente de 4 digitos
    if (strlen(codigo) != 4) {
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3                  Codigo invalido.                \xB3");
        gotoxy(40, 9);
        printf("\xB3        Debe tener exactamente 4 digitos.         \xB3");
        gotoxy(40, 10);
        parteInferior();
        gotoxy(40, 12);
        system("pause");
        return;
    }
    
    int productoIndex = -1;
    
    //Ciclo for para buscar el producto que queremos actualizar
    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(productosTotal[i].nombre, nombre) == 0 && productosTotal[i].codigo == codigoNum) {
            productoIndex = i;
            break;
        }
    }
    
    //Validamos en caso de que no encuentre el producto
    if (productoIndex == -1) {
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3              Producto no encontrado.             \xB3");
        gotoxy(40, 9);
        parteInferior();
        gotoxy(40, 11);
        system("pause");
        return;
    }
    
    //Imprimimos la informacion del producto que estabamos buscando
    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD  INFORMACION DEL PRODUCTO  \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3             Nombre del producto:                 \xB3");
    gotoxy(40, 11);
    parteVacia();
    gotoxy(50, 11);
    printf("%s", productosTotal[productoIndex].nombre);
    gotoxy(40, 12);
    parteMedia();
    gotoxy(40, 13);
    printf("\xB3             Codigo del producto:                 \xB3");
    gotoxy(40, 14);
    parteVacia();
    gotoxy(65, 14);
    printf("%d", productosTotal[productoIndex].codigo);
    gotoxy(40, 15);
    parteMedia();
    gotoxy(40, 16);
    printf("\xB3             Precio del producto:                 \xB3");
    gotoxy(40, 17);
    parteVacia();
    gotoxy(65, 17);
    printf("%s C$", productosTotal[productoIndex].precio);
    gotoxy(40, 18);
    parteMedia();
    gotoxy(40, 19);
    printf("\xB3            Cantidad del producto:                \xB3 ");
    gotoxy(40, 20);
    parteVacia();
    gotoxy(65, 20);
    printf("%s", productosTotal[productoIndex].cantidad);
    gotoxy(40, 21);
    parteMedia();
    gotoxy(40, 22);
    printf("\xB3          Descripcion del producto:               \xB3");
    gotoxy(40, 23);
    parteVacia();
    gotoxy(41, 23);
    printf("%s", productosTotal[productoIndex].descripcion);
    gotoxy(40, 24);
    parteInferior();
    gotoxy(40, 26);
    system("pause");
}

//Funcion para poder actualizar el producto
void actualizarProducto() {
    char nombre[50];
    char codigoStr[5];
    int codigo;
    char precioStr[5];
    char cantidadStr[3];
    char descripcion[50];
    int productoEncontrado = 0;
    
    //Imprimiendo las opciones que tiene el usuario
    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD ACTUALIZAR PRODUCTO \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3      Si no recuerda el nombre ni el codigo,      \xB3 ");
    gotoxy(40, 11);
    printf("\xB3        presiona 'n' o 'N' para regresar.         \xB3 ");
    gotoxy(40, 12);
    printf("\xB3        Para continuar, presione 's' o 'S'.       \xB3 ");
    gotoxy(40, 13);
    parteInferior();
    
    // No continuar si no hay ningún producto registrado
    if (totalProductos == 0) {
        gotoxy(40, 15);
        parteSuperior();
        gotoxy(40, 16);
        printf("\xB3           No hay productos registrados.          \xB3");
        gotoxy(40, 17);
        parteInferior();
        gotoxy(40, 19);
        system("pause");
        return;
    }
    
    //Validad las teclas para continuar o regresar
    while (1) {
        char tecla = getch();
        if (tecla == 'n' || tecla == 'N') {
            return;  
        } else if (tecla == 's' || tecla == 'S') {
            break;  
        } else {
            gotoxy(40, 15);
            parteSuperior();
            gotoxy(40, 16);
            printf("\xB3                  Tecla invalida.                 \xB3");
            gotoxy(40, 17);
            printf("\xB3         Presione 's' o 'S' para continuar        \xB3");
            gotoxy(40, 18);
            printf("\xB3            o 'n' o 'N' para regresar.            \xB3");
            gotoxy(40, 19);
            parteInferior();
        }
    }
    
    //Le pedimos al usuario el nombre y codigo del producto que quiere actualizar
    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD ACTUALIZAR PRODUCTO \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3         Ingrese el nombre del producto:          \xB3");
    gotoxy(40, 11);
    parteVacia();
    gotoxy(50, 11);
    ingresarProducto(nombre);
    fflush(stdin);
    gotoxy(40, 12);
    parteMedia();
    gotoxy(40, 13);
    printf("\xB3    Ingrese el codigo del producto (4 digitos):   \xB3"); 
    gotoxy(40, 14);
    parteVacia();
    gotoxy(65, 14);
    ingresarNumeros(codigoStr, 4);
    fflush(stdin); 
    gotoxy(40, 15);
    parteInferior();
    gotoxy(40, 17);
    system("pause");

    system("cls");
    
    //Convertimos en entero una cadena de caracteres
    codigo = atoi(codigoStr);
    
    //Validamos que el codigo sea exactamente de 4 digitos
    if (strlen(codigoStr) != 4) {
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3                  Codigo invalido.                \xB3");
        gotoxy(40, 9);
        printf("\xB3        Debe tener exactamente 4 digitos.         \xB3");
        gotoxy(40, 10);
        parteInferior();
        gotoxy(40, 12);
        system("pause");
        return;
    }
    
    //Ciclo for para buscar el producto que queremos actualizar
    int productoIndex = -1;
    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(productosTotal[i].nombre, nombre) == 0 && productosTotal[i].codigo == codigo) {
            productoIndex = i;
            break;
        }
    }
    
    //Validamos en caso de que no encuentre el producto
    if (productoIndex == -1) {
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3              Producto no encontrado.             \xB3");
        gotoxy(40, 9);
        parteInferior();
        gotoxy(40, 11);
        system("pause");
        return;
    }
    
    //Imprimimos la informacion del producto que queremos actualizar
    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD  INFORMACION DEL PRODUCTO  \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3             Nombre del producto:                 \xB3");
    gotoxy(40, 11);
    parteVacia();
    gotoxy(50, 11);
    printf("%s", productosTotal[productoIndex].nombre);
    gotoxy(40, 12);
    parteMedia();
    gotoxy(40, 13);
    printf("\xB3             Codigo del producto:                 \xB3");
    gotoxy(40, 14);
    parteVacia();
    gotoxy(65, 14);
    printf("%d", productosTotal[productoIndex].codigo);
    gotoxy(40, 15);
    parteMedia();
    gotoxy(40, 16);
    printf("\xB3             Precio del producto:                 \xB3");
    gotoxy(40, 17);
    parteVacia();
    gotoxy(65, 17);
    printf("%s C$", productosTotal[productoIndex].precio);
    gotoxy(40, 18);
    parteMedia();
    gotoxy(40, 19);
    printf("\xB3            Cantidad del producto:                \xB3 ");
    gotoxy(40, 20);
    parteVacia();
    gotoxy(65, 20);
    printf("%s", productosTotal[productoIndex].cantidad);
    gotoxy(40, 21);
    parteMedia();
    gotoxy(40, 22);
    printf("\xB3          Descripcion del producto:               \xB3");
    gotoxy(40, 23);
    parteVacia();
    gotoxy(41, 23);
    printf("%s", productosTotal[productoIndex].descripcion);
    gotoxy(40, 24);
    parteInferior();
    gotoxy(40, 26);
    system("pause");

    system("cls");
    
    //Pedimos actualizar nombre o no
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3         Desea actualizar el nombre? (s/n):       \xB3");
    gotoxy(40, 9);
    parteInferior();
    
    //Validamos las respuestas que nos de el usuario
    char respuesta = getch();
    if (respuesta == 's' || respuesta == 'S') {
        gotoxy(40, 11);
        parteSuperior();
        gotoxy(40, 12);
        printf("\xB3             Ingrese el nuevo nombre:             \xB3");
        gotoxy(40, 13);
        parteVacia();
        gotoxy(50, 13);
        ingresarProducto(productosTotal[productoIndex].nombre);
        fflush(stdin);
        gotoxy(40, 14);
        parteInferior();

        gotoxy(40, 16);
        parteSuperior();
        gotoxy(40, 17);
        printf("\xB3         Nombre actualizado exitosamente.         \xB3");
        gotoxy(40, 18);
        parteInferior();
        gotoxy(40, 20);
        system("pause");
    } else if (respuesta == 'n' || respuesta == 'N') {
        gotoxy(40, 11);
        parteSuperior();
        gotoxy(40, 12);
        printf("\xB3         Nombre salteado, sin actualizar.         \xB3");
        gotoxy(40, 13);
        parteInferior();
        gotoxy(40, 14);
        system("pause");
    } else {
        gotoxy(40, 11);
        parteSuperior();
        gotoxy(40, 12);
        printf("\xB3        Tecla equivocada. Intente de nuevo.       \xB3");
        gotoxy(40, 13);
        parteInferior();
        gotoxy(40, 14);
        system("pause");
        return;
    }
    
    //Pedimos actualizar precio o no
    gotoxy(40, 22);
    parteSuperior();
    gotoxy(40, 23);
    printf("\xB3        Desea actualizar el precio? (s/n):        \xB3");
    gotoxy(40, 24);
    parteInferior();
    
    //Validamos las respuestas que nos de el usuario
    respuesta = getch();
    if (respuesta == 's' || respuesta == 'S') {
        gotoxy(40, 26);
        parteSuperior();
        gotoxy(40, 27);
        printf("\xB3             Ingrese el nuevo precio:             \xB3");
        gotoxy(40, 28);
        parteVacia();
        gotoxy(65, 28);
        ingresarNumeros(precioStr, 5);
        fflush(stdin);
        gotoxy(40, 29);
        parteInferior();

        int precioNum = atoi(precioStr);
        if (precioNum <= 0 || precioNum > 5000) {
            gotoxy(40, 31);
            parteSuperior();
            gotoxy(40, 32);
            printf("\xB3                 Precio invalido.                 \xB3");
            gotoxy(40, 33);
            parteInferior();
            gotoxy(40, 35);
            system("pause");
            return;
        }

        sprintf(productosTotal[productoIndex].precio, "%d", precioNum);
        
        gotoxy(40, 31);
        parteSuperior();
        gotoxy(40, 32);
        printf("\xB3         Precio actualizado exitosamente.         \xB3");
        gotoxy(40, 33);
        parteInferior();
        gotoxy(40, 35);
        system("pause");
    } else if (respuesta == 'n' || respuesta == 'N') {
        gotoxy(40, 26);
        parteSuperior();
        gotoxy(40, 27);
        printf("\xB3         Precio salteado, sin actualizar.         \xB3");
        gotoxy(40, 28);
        parteInferior();
        gotoxy(40, 30);
        system("pause");
    } else {
        gotoxy(40, 26);
        parteSuperior();
        gotoxy(40, 27);
        printf("\xB3        Tecla equivocada. Intente de nuevo.       \xB3");
        gotoxy(40, 28);
        parteInferior();
        gotoxy(40, 30);
        system("pause");
        return;
    }

    system("cls");
    
    //Pedimos actualizar cantidad o no
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3        Desea actualizar la cantidad? (s/n):      \xB3");
    gotoxy(40, 9);
    parteInferior();
    
    //Validamos las respuestas que nos de el usuario
    respuesta = getch();
    if (respuesta == 's' || respuesta == 'S') {
        gotoxy(40, 11);
        parteSuperior();
        gotoxy(40, 12);
        printf("\xB3            Ingrese la nueva cantidad:            \xB3");
        gotoxy(40, 13);
        parteVacia();
        gotoxy(65, 13);
        ingresarNumeros(cantidadStr, 3);
        fflush(stdin);
        gotoxy(40, 14);
        parteInferior();
        gotoxy(40, 15);
        system("pause");

        int cantidadNum = atoi(cantidadStr);
        if (cantidadNum <= 0 || cantidadNum > 30) {
            system("cls");
            gotoxy(40, 7);
            parteSuperior();
            gotoxy(40, 8);
            printf("\xB3                Cantidad invalida.                \xB3");
            gotoxy(40, 9);
            parteInferior();
            gotoxy(40, 11);
            system("pause");
            return;
        }

        sprintf(productosTotal[productoIndex].cantidad, "%d", cantidadNum);
        
        system("cls");
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3       Cantidad actualizada exitosamente.         \xB3");
        gotoxy(40, 9);
        parteInferior();
        gotoxy(40, 11);
        system("pause");
    } else if (respuesta == 'n' || respuesta == 'N') {
        gotoxy(40, 11);
        parteSuperior();
        gotoxy(40, 12);
        printf("\xB3        Cantidad salteada, sin actualizar.        \xB3");
        gotoxy(40, 13);
        parteInferior();
        gotoxy(40, 15);
        system("pause");
    } else {
        gotoxy(40, 11);
        parteSuperior();
        gotoxy(40, 12);
        printf("\xB3        Tecla equivocada. Intente de nuevo.       \xB3");
        gotoxy(40, 13);
        parteInferior();
        gotoxy(40, 15);
        system("pause");
        return;
    }
    
    system("cls");

    //Pedimos actualizar descripcion o no
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3      Desea actualizar la descripcion? (s/n):     \xB3");
    gotoxy(40, 9);
    parteInferior();
    
    //Validamos las respuestas que nos de el usuario
    respuesta = getch();
    if (respuesta == 's' || respuesta == 'S') {
        gotoxy(40, 11);
        parteSuperior();
        gotoxy(40, 12);
        printf("\xB3          Ingrese la nueva descripcion:           \xB3");
        gotoxy(40, 13);
        parteVacia();
        gotoxy(41, 13);
        ingresarDescripcion(productosTotal[productoIndex].descripcion);
        fflush(stdin);
        gotoxy(40, 14);
        parteInferior();
        gotoxy(40, 16);
        parteSuperior();
        gotoxy(40, 17);
        printf("\xB3       Descripcion actualizada exitosamente.      \xB3");
        gotoxy(40, 18);
        parteInferior();
        gotoxy(40, 20);
        system("pause");
    } else if (respuesta == 'n' || respuesta == 'N') {
        gotoxy(40, 11);
        parteSuperior();
        gotoxy(40, 12);
        printf("\xB3      Descripcion salteada, sin actualizar.       \xB3");
        gotoxy(40, 13);
        parteInferior();
        gotoxy(40, 15);
        system("pause");
    } else {
        gotoxy(40, 11);
        parteSuperior();
        gotoxy(40, 12);
        printf("\xB3        Tecla equivocada. Intente de nuevo.       \xB3");
        gotoxy(40, 13);
        parteInferior();
        gotoxy(40, 15);
        system("pause");
        return;
    }
    
    //Imprimimos la informacion que actualizamos y no actualizamos del producto
    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD  RESUMEN DEL PRODUCTO ACTUALIZADO  \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3             Nombre del producto:                 \xB3");
    gotoxy(40, 11);
    parteVacia();
    gotoxy(50, 11);
    printf("%s", productosTotal[productoIndex].nombre);
    gotoxy(40, 12);
    parteMedia();
    gotoxy(40, 13);
    printf("\xB3             Codigo del producto:                 \xB3");
    gotoxy(40, 14);
    parteVacia();
    gotoxy(65, 14);
    printf("%d", productosTotal[productoIndex].codigo);
    gotoxy(40, 15);
    parteMedia();
    gotoxy(40, 16);
    printf("\xB3             Precio del producto:                 \xB3");
    gotoxy(40, 17);
    parteVacia();
    gotoxy(65, 17);
    printf("%s C$", productosTotal[productoIndex].precio);
    gotoxy(40, 18);
    parteMedia();
    gotoxy(40, 19);
    printf("\xB3            Cantidad del producto:                \xB3 ");
    gotoxy(40, 20);
    parteVacia();
    gotoxy(65, 20);
    printf("%s", productosTotal[productoIndex].cantidad);
    gotoxy(40, 21);
    parteMedia();
    gotoxy(40, 22);
    printf("\xB3          Descripcion del producto:               \xB3");
    gotoxy(40, 23);
    parteVacia();
    gotoxy(41, 23);
    printf("%s", productosTotal[productoIndex].descripcion);
    gotoxy(40, 24);
    parteMedia();
    gotoxy(40, 25);
    printf("\xB3        Producto actualizado exitosamente.        \xB3");
    gotoxy(40, 26);
    parteInferior();
    gotoxy(40, 28);
    system("pause");
}

//Funcion para poder eliminar un producto
void eliminarProducto() {
    char nombre[50];
    char codigo[5];
    int productoEncontrado = 0;

    system("cls");
    //Imprimiendo las opciones que tiene el usuario
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD ELIMINAR PRODUCTO \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3      Si no recuerda el nombre ni el codigo,      \xB3 ");
    gotoxy(40, 11);
    printf("\xB3        presiona 'n' o 'N' para regresar.         \xB3 ");
    gotoxy(40, 12);
    printf("\xB3        Para continuar, presione 's' o 'S'.       \xB3 ");
    gotoxy(40, 13);
    parteInferior();
    
    //No continuar si no hay ningun producto registrado
    if (totalProductos == 0) {
        gotoxy(40, 15);
        parteSuperior();
        gotoxy(40, 16);
        printf("\xB3           No hay productos registrados.          \xB3");
        gotoxy(40, 17);
        parteInferior();
        gotoxy(40, 19);
        system("pause");
        return;
    }
    
    //Validando el teclado para continuar y regresar
    while (1) {
        char tecla = getch();
        if (tecla == 'n' || tecla == 'N') {
            return;  
        } else if (tecla == 's' || tecla == 'S') {
            break;  
        } else {
            gotoxy(40, 15);
            parteSuperior();
            gotoxy(40, 16);
            printf("\xB3                  Tecla invalida.                 \xB3");
            gotoxy(40, 17);
            printf("\xB3         Presione 's' o 'S' para continuar        \xB3");
            gotoxy(40, 18);
            printf("\xB3            o 'n' o 'N' para regresar.            \xB3");
            gotoxy(40, 19);
            parteInferior();
        }
    }
    
    //Le pedimos al usuario el nombre y el codigo del producto que quiere eliminar
    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD ELIMINAR PRODUCTO \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3         Ingrese el nombre del producto:          \xB3");
    gotoxy(40, 11);
    parteVacia();
    gotoxy(50, 11);
    ingresarProducto(nombre);
    fflush(stdin);
    gotoxy(40, 12);
    parteMedia();
    gotoxy(40, 13);
    printf("\xB3    Ingrese el codigo del producto (4 digitos):   \xB3"); 
    gotoxy(40, 14);
    parteVacia();
    gotoxy(65, 14);
    ingresarNumeros(codigo, 4);  
    fflush(stdin);
    gotoxy(40, 15);
    parteInferior();
    gotoxy(40, 17);
    system("pause");
    
    system("cls");
    
    //Convertimos en entero una cadena de caracteres
    int codigoNum = atoi(codigo);
    
    //Validando que el codigo tenga si o si 4 digitos
    if (strlen(codigo) != 4) {
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3                  Codigo invalido.                \xB3");
        gotoxy(40, 9);
        printf("\xB3        Debe tener exactamente 4 digitos.         \xB3");
        gotoxy(40, 10);
        parteInferior();
        gotoxy(40, 12);
        system("pause");
        return;
    }
    
    //Ciclo for para poder buscar el producto
    for (int i = 0; i < totalProductos; i++) {
        //Validamos que lo que ingreso el usuario sea correcto usando strcmp
        if (strcmp(productosTotal[i].nombre, nombre) == 0 && productosTotal[i].codigo == codigoNum) {
            productoEncontrado = 1;
            
            //Validando que el precio y la cantidad esten correctos
            if (atoi(productosTotal[i].precio) < 0 || atoi(productosTotal[i].cantidad) < 0) {
                gotoxy(40, 7);
                parteSuperior();
                gotoxy(40, 8);
                printf("\xB3    Error: El producto tiene valores invalidos.   \xB3");
                gotoxy(40, 9);
                parteInferior();
                gotoxy(40, 11);
                system("pause");
                return;
            }
            
            //Imprimiendo la informacion del producto encontrado
            system("cls");
            gotoxy(40, 7);
            parteSuperior();
            gotoxy(40, 8);
            printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD  INFORMACION DEL PRODUCTO  \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
            gotoxy(40, 9);
            parteMedia();
            gotoxy(40, 10);
            printf("\xB3             Nombre del producto:                 \xB3");
            gotoxy(40, 11);
            parteVacia();
            gotoxy(50, 11);
            printf("%s", productosTotal[i].nombre);
            gotoxy(40, 12);
            parteMedia();
            gotoxy(40, 13);
            printf("\xB3             Codigo del producto:                 \xB3");
            gotoxy(40, 14);
            parteVacia();
            gotoxy(65, 14);
            printf("%d", productosTotal[i].codigo);
            gotoxy(40, 15);
            parteMedia();
            gotoxy(40, 16);
            printf("\xB3             Precio del producto:                 \xB3");
            gotoxy(40, 17);
            parteVacia();
            gotoxy(65, 17);
            printf("%d C$", atoi(productosTotal[i].precio));
            gotoxy(40, 18);
            parteMedia();
            gotoxy(40, 19);
            printf("\xB3            Cantidad del producto:                \xB3 ");
            gotoxy(40, 20);
            parteVacia();
            gotoxy(65, 20);
            printf("%d", atoi(productosTotal[i].cantidad));
            gotoxy(40, 21);
            parteMedia();
            gotoxy(40, 22);
            printf("\xB3          Descripcion del producto:               \xB3");
            gotoxy(40, 23);
            parteVacia();
            gotoxy(41, 23);
            printf("%s", productosTotal[i].descripcion);
            gotoxy(40, 24);
            parteMedia();
            
            //Preguntandole al usuario si quiere eliminar el producto
            gotoxy(40, 25);
            printf("\xB3 Esta seguro que desea borrar este producto?(s/n):\xB3");
            gotoxy(40, 26);
            parteInferior();
            int confirmacion = getch();

            //Validando el getch para que muestre la eliminacion del producto
            if (confirmacion == 's' || confirmacion == 'S') {
                for (int j = i; j < totalProductos - 1; j++) {
                    productosTotal[j] = productosTotal[j + 1];
                }
                totalProductos--;
                gotoxy(40, 28);
                parteSuperior();
                gotoxy(40, 29);
                printf("\xB3               Producto con codigo:               \xB3");
                gotoxy(40, 30);
                parteVacia();
                gotoxy(65, 30);
                printf("%d", codigoNum);
                gotoxy(40, 31);
                printf("\xB3               Eliminado con exito.               \xB3");
                gotoxy(40, 32);
                parteInferior();
                gotoxy(40, 34);
                system("pause");
            } else if (confirmacion == 'n' || confirmacion == 'N') {
                gotoxy(40, 28);
                parteSuperior();
                gotoxy(40, 29);
                printf("\xB3              Eliminacion cancelada.              \xB3");
                gotoxy(40, 30);
                parteInferior();
                gotoxy(40, 32);
                system("pause");
                return;
            } else {
                gotoxy(40, 28);
                parteSuperior();
                gotoxy(40, 29);
                printf("\xB3        Tecla equivocada. Intente de nuevo.       \xB3");
                gotoxy(40, 30);
                parteInferior();
                gotoxy(40, 32);
                system("pause");
                return;
            }
        }
    }
    
    //Validacion en caso de que no se encuentre el producto
    if (!productoEncontrado) {
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3             Producto no encontrado.              \xB3");
        gotoxy(40, 9);
        parteInferior();
        gotoxy(40, 11);
        system("pause");
        return;
    }
}

//FUncion para poder ver todos los productos que ya tenemos registrados
void verProductos() {
    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD LISTA DE PRODUCTOS \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
    gotoxy(40, 9);
    parteInferior();
    gotoxy(40, 11);
    system("pause");
    
    //Validando que no se pueda continuar, sino hay productos ingresados
    if (totalProductos == 0) {
        gotoxy(40, 13);
        parteSuperior();
        gotoxy(40, 14);
        printf("\xB3           No hay productos registrados.          \xB3");
        gotoxy(40, 15);
        parteInferior();
        gotoxy(40, 17);
        system("pause");
        return;
    } 

    int totalPaginas = (totalProductos + PRODUCTOS_POR_PAGINA - 1) / PRODUCTOS_POR_PAGINA; 
    int paginaActual = 0;
    int tecla;

    do {
        system("cls");
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD LISTA DE PRODUCTOS \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
        gotoxy(40, 9);
        parteMedia();
        
        //Ciclor for para imprimir todos los productos que se encuentren registrados
        int y = 10;
        for (int i = 0; i < PRODUCTOS_POR_PAGINA; i++) {
            int indiceProducto = paginaActual * PRODUCTOS_POR_PAGINA + i;
            if (indiceProducto >= totalProductos) {
                break; // Si no hay más productos, salir del bucle
            }

            gotoxy(40, y);
            printf("\xB3             Nombre del producto:                 \xB3");
            y++;
            
            gotoxy(40, y);
            parteVacia();
            gotoxy(50, y);
            printf("%s", productosTotal[indiceProducto].nombre); 
            y++;

            gotoxy(40, y);
            parteMedia();
            y++;

            gotoxy(40, y);
            printf("\xB3             Codigo del producto:                 \xB3"); 
            y++;
            
            gotoxy(40, y);
            parteVacia();
            gotoxy(65, y);
            printf("%d", productosTotal[indiceProducto].codigo); 
            y++;

            gotoxy(40, y);
            parteMedia();
            y++;

            gotoxy(40, y);
            printf("\xB3             Precio del producto:                 \xB3"); 
            y++;
            
            gotoxy(40, y);
            parteVacia();
            gotoxy(65, y);
            printf("%s C$", productosTotal[indiceProducto].precio); 
            y++;

            gotoxy(40, y);
            parteMedia();
            y++;

            gotoxy(40, y);
            printf("\xB3            Cantidad del producto:                \xB3"); 
            y++;
            
            gotoxy(40, y);
            parteVacia();
            gotoxy(65, y);
            printf("%s", productosTotal[indiceProducto].cantidad);
            y++;

            gotoxy(40, y);
            parteMedia();
            y++;

            gotoxy(40, y);
            printf("\xB3         Descripcion del producto:                \xB3");
            y++;
            
            gotoxy(40, y);
            parteVacia();
            gotoxy(41, y);
            printf("%s", productosTotal[indiceProducto].descripcion); 
            y++;

            gotoxy(40, y);
            parteInferior();

            y += 3; 
        }
        
        //Nos muestra el numero de pagina en que estamos y las intrucciones para cruzarlas
        gotoxy(40, y);
        printf("Pagina %d de %d", paginaActual + 1, totalPaginas);
        gotoxy(40, y + 1);
        printf("Usa las flechas izquierda y derecha para navegar.");
        
        //Funcion para movernos entre paginas
        tecla = _getch(); 
        if (tecla == 0 || tecla == 224) { 
            tecla = _getch(); 
            if (tecla == 75) { // Flecha izquierda
                if (paginaActual > 0) {
                    paginaActual--;
                }
            } else if (tecla == 77) { // Flecha derecha
                if (paginaActual < totalPaginas - 1) {
                    paginaActual++;
                }
            }
        }

    } while (tecla == 75 || tecla == 77); 
    
    gotoxy(40, 35);
    system("pause");
}

//Funcion para poder vender un producto
void venderProducto() {
    char cantidadCliente[3];
    char nombre[50];
    int codigo;
    char bufferMonto[8];
    char nombreCliente[50];
    char codigoStr[5];

    system("cls");
    //Imprimiendo las opciones que tiene el usuario
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD VENDER PRODUCTO \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3      Si no recuerda el nombre ni el codigo,      \xB3 ");
    gotoxy(40, 11);
    printf("\xB3        presiona 'n' o 'N' para regresar.         \xB3 ");
    gotoxy(40, 12);
    printf("\xB3        Para continuar, presione 's' o 'S'.       \xB3 ");
    gotoxy(40, 13);
    parteInferior();
    
    //Validando que no continue, sino hay productos ingresados
    if (totalProductos == 0) {
        gotoxy(40, 15);
        parteSuperior();
        gotoxy(40, 16);
        printf("\xB3           No hay productos registrados.          \xB3");
        gotoxy(40, 17);
        parteInferior();
        gotoxy(40, 19);
        system("pause");
        return;
    }
    
    //Validando el teclado para que continue o regrese
    while (1) {
        char tecla = getch();
        if (tecla == 'n' || tecla == 'N') {
            return;  
        } else if (tecla == 's' || tecla == 'S') {
            break;  
        } else {
            gotoxy(40, 15);
            parteSuperior();
            gotoxy(40, 16);
            printf("\xB3                  Tecla invalida.                 \xB3");
            gotoxy(40, 17);
            printf("\xB3         Presione 's' o 'S' para continuar        \xB3");
            gotoxy(40, 18);
            printf("\xB3            o 'n' o 'N' para regresar.            \xB3");
            gotoxy(40, 19);
            parteInferior();
        }
    }
    
    //Validando que el usuario ingrese el nombre y codigo del producto que desa vender
    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD VENDER PRODUCTO \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3         Ingrese el nombre del producto:          \xB3");
    gotoxy(40, 11);
    parteVacia();
    gotoxy(50, 11);
    ingresarProducto(nombre);
    fflush(stdin);
    gotoxy(40, 12);
    parteMedia();
    gotoxy(40, 13);
    printf("\xB3    Ingrese el codigo del producto (4 digitos):   \xB3"); 
    gotoxy(40, 14);
    parteVacia();
    gotoxy(65, 14);
    ingresarNumeros(codigoStr, 4);
    fflush(stdin); 
    gotoxy(40, 15);
    parteInferior();
    gotoxy(40, 17);
    system("pause");
    
    system("cls");

    //COnvertimos en entero una cadena de caracteres
    int codigoNum = atoi(codigoStr);
    
    //Validando que el codigo si o si sea de 4 digitos
    if (strlen(codigoStr) != 4) {
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3                  Codigo invalido.                \xB3");
        gotoxy(40, 9);
        printf("\xB3        Debe tener exactamente 4 digitos.         \xB3");
        gotoxy(40, 10);
        parteInferior();
        gotoxy(40, 12);
        system("pause");
        return;
    }
    
    //Ciclo for para poder buscar el producto
    for (int i = 0; i < totalProductos; i++) {
        //Validando que lo que ingreso el usario haya sido lo correcto usando strcmp
        if (strcmp(productosTotal[i].nombre, nombre) == 0 && productosTotal[i].codigo == codigoNum) {
            int cantidadNum = atoi(productosTotal[i].cantidad); 
            int precioNum = atoi(productosTotal[i].precio); 
            
            //Verificando el minimo de la cantidad del producto
            if (cantidadNum <= 5) {
                gotoxy(40, 7);
                parteSuperior();
                gotoxy(40, 8);
                printf("\xB3  Aviso: La cantidad esta en su minimo, rellene.  \xB3");
                gotoxy(40, 9);
                parteInferior();
                gotoxy(40, 11);
                system("pause");
                return;
            } else {
                gotoxy(40, 7);
                parteSuperior();
                gotoxy(40, 8);
                printf("\xB3         La cantidad actual es aceptable,         \xB3");
                gotoxy(40, 9);
                printf("\xB3                se puede continuar.               \xB3");
                gotoxy(40, 10);
                parteInferior();
                gotoxy(40, 12);
                system("pause");
            }
            
            //Pidiendole al usuario su nombre
            gotoxy(40, 14);
            parteSuperior();
            gotoxy(40, 15);
            printf("\xB3               Producto encontrado.               \xB3");
            gotoxy(40, 16);
            parteMedia();
            gotoxy(40, 17);
            printf("\xB3                Ingrese su nombre:                \xB3");
            gotoxy(40, 18);
            parteVacia();
            gotoxy(45, 18);
            ingresarNombre(nombreCliente);
            fflush(stdin);
            gotoxy(40, 19);
            parteInferior();
            
            //Pidiendole al usuario si desea comprar el producto
            gotoxy(40, 21);
            parteSuperior();
            gotoxy(40, 22);
            printf("\xB3        Desea comprar este producto?: (s/n)       \xB3");
            gotoxy(40, 23);
            parteVacia();
            gotoxy(50, 23);
            printf("%s", nombre);
            gotoxy(40, 24);
            parteInferior();

            char respuesta = getch();
            
            //Validando las respuestas del getch que ´pueda ingresar el usuario
            if (respuesta == 's' || respuesta == 'S') {
                gotoxy(40, 26);
                parteSuperior();
                gotoxy(40, 27);
                printf("\xB3         Cuantas unidades desea comprar?:         \xB3");
                gotoxy(40, 28);
                parteVacia();
                gotoxy(65, 28);
                ingresarNumeros(cantidadCliente, 2);
                gotoxy(40, 29);
                parteInferior();
                
                //Convertir en entero una cadena de caracteres
                int cantidadClienteNum = atoi(cantidadCliente);
                
                //Validando que la cantidad sea la correcta
                if (cantidadClienteNum <= 0) {
                    gotoxy(40, 31);
                    parteSuperior();
                    gotoxy(40, 32);
                    printf("\xB3 La cantidad que desea no puede ser 0 o negativa. \xB3");
                    gotoxy(40, 33);
                    parteInferior();
                    gotoxy(40, 35);
                    system("pause");
                    return;
                } else if (cantidadClienteNum > cantidadNum) {
                    gotoxy(40, 31);
                    parteSuperior();
                    gotoxy(40, 32);
                    printf("\xB3          La cantidad que desea es mayor          \xB3");
                    gotoxy(40, 33);
                    printf("\xB3            a la cantidad disponible.             \xB3");
                    gotoxy(40, 34);
                    parteInferior();
                    gotoxy(40, 36);
                    system("pause");
                    return;
                } 
                
                //Calculando el costo total
                int costoTotal = cantidadClienteNum * precioNum;
                
                //Mostrandole al usuario el monto a pagar
                gotoxy(40, 31);
                parteSuperior();
                gotoxy(40, 32);
                printf("\xB3               Monto total a pagar:               \xB3");
                gotoxy(40, 33);
                parteVacia();
                gotoxy(65, 33);
                printf("%d C$", costoTotal);
                gotoxy(40, 34);
                parteInferior();
                
                //Pidiendole al usuario que ingrese su monto
                gotoxy(40, 36);
                parteSuperior();
                gotoxy(40, 37);
                printf("\xB3     Ingrese el monto con el que desea pagar:     \xB3");
                gotoxy(40, 38);
                parteVacia();
                gotoxy(65, 38);
                ingresarNumeros(bufferMonto, 9); 
                gotoxy(40, 39);
                parteInferior();
                int montoPagar = atoi(bufferMonto);
                int vuelto = montoPagar - costoTotal;
                
                // Validar el monto ingresado y mostrar el vuelto
                if (vuelto < 0) {
                    gotoxy(40, 41);
                    parteSuperior(); 
                    gotoxy(40, 42);
                    printf("\xB3       Monto insuficiente. El monto total es      \xB3");
                    gotoxy(40, 43);
                    parteVacia();
                    gotoxy(65, 43);
                    printf("%d C$", costoTotal);
                    gotoxy(40, 44);
                    parteInferior();
                    gotoxy(40, 46);
                    system("pause");
                    return;
                } else {
                    gotoxy(40, 41);
                    parteSuperior();
                    gotoxy(40, 42);
                    printf("\xB3                       Vuelto:                    \xB3");
                    gotoxy(40, 43);
                    parteVacia();
                    gotoxy(65, 43);
                    printf("%d C$", vuelto);
                    gotoxy(40, 44);
                    parteInferior();
                    
                    //Restamos la cantidad actual de la que pidio el usario
                    cantidadNum -= cantidadClienteNum; 

                    sprintf(productosTotal[i].cantidad, "%d", cantidadNum); 
                    gotoxy(40, 46);
                    system("pause");
                }
                
                //Imprimiendo la factura del usuario
                system("cls");
                gotoxy(40, 7);
                parteSuperior();
                gotoxy(40, 8);
                printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD  FACTURA  \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
                gotoxy(40, 9);
                parteMedia();
                gotoxy(40, 10);
                printf("\xB3                Nombre del cliente:               \xB3");
                gotoxy(40, 11);
                parteVacia();
                gotoxy(50, 11);
                printf("%s", nombreCliente);
                gotoxy(40, 12);
                parteMedia();
                gotoxy(40, 13);
                printf("\xB3               Nombre del producto:               \xB3");
                gotoxy(40, 14);
                parteVacia();
                gotoxy(50, 14);
                printf("%s", nombre);
                gotoxy(40, 15);
                parteMedia();  
                gotoxy(40, 16);
                printf("\xB3              Cantidad del producto:              \xB3");
                gotoxy(40, 17);
                parteVacia();
                gotoxy(65, 17);
                printf("%d", cantidadClienteNum);
                gotoxy(40, 18);
                parteMedia();
                gotoxy(40, 19);
                printf("\xB3               Codigo del producto:               \xB3");
                gotoxy(40, 20);
                parteVacia();
                gotoxy(65, 20);
                printf("%d", codigoNum);
                gotoxy(40, 21);
                parteMedia();
                gotoxy(40, 22);
                printf("\xB3               Costo total por todo:              \xB3");
                gotoxy(40, 23);
                parteVacia();
                gotoxy(65, 23);
                printf("%d C$", costoTotal);
                gotoxy(40, 24);
                parteMedia();
                gotoxy(40, 25);
                printf("\xB3                  Vuelto total:                   \xB3");
                gotoxy(40, 26);
                parteVacia();
                gotoxy(65, 26);
                printf("%d C$", vuelto);
                gotoxy(40, 27);
                parteMedia();
                gotoxy(40, 28);
                printf("\xB3\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD  UNI GYM  \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB3");
                gotoxy(40, 29);
                parteInferior();
                gotoxy(40, 31);
                system("pause");
            } else if (respuesta == 'n' || respuesta == 'N') {
                gotoxy(40, 26);
                parteSuperior();
                gotoxy(40, 27);
                printf("\xB3     Compra cancelada. Que tenga un buen dia.     \xB3");
                gotoxy(40, 28);
                parteInferior();
                gotoxy(40, 30);
                system("pause");
                return;
            } else {
                gotoxy(40, 26);
                parteSuperior();
                gotoxy(40, 27);
                printf("\xB3        Tecla equivocada. Intente de nuevo.       \xB3");
                gotoxy(40, 28);
                parteInferior();
                gotoxy(40, 30);
                system("pause");
                return;
            }
        } 
    }  
}

//Funcion para poder agregar clientes
void agregarCliente() {
    //Verificando que no continue ingresando mas clientes mas alla del limite establecido
    if (totalClientes >= MAX_CLIENTES) {
        system("cls");
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3        No se pueden agregar mas clientes.        \xB3");
        gotoxy(40, 9);
        printf("\xB3                 Limite alcanzado.                \xB3");
        gotoxy(40, 10);
        parteInferior();
        gotoxy(40, 11);
        system("pause");
        return;
    }

    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3==================AGREGAR CLIENTE=================\xB3");
   
   //Validacion para ingresar el nombre del cliente y repetir en caso de que no haya nada ingresado en el
   do {
        gotoxy(40, 9);
        parteMedia();
        gotoxy(40, 10);
        printf("\xB3          Ingrese el nombre del cliente:          \xB3");
        gotoxy(40, 11);
        parteVacia();
        gotoxy(50, 11);
        ingresarNombre(listaClientes[totalClientes].nombre);
        fflush(stdin); 
        if (strlen(listaClientes[totalClientes].nombre) == 0) {
            gotoxy(40, 12);
            parteMedia();
            gotoxy(40, 13);
            printf("\xB3    El nombre del cliente no puede estar vacio.   \xB3");
            gotoxy(40, 14);
            parteInferior();
            gotoxy(40, 16);
            system("pause");
            return;
        }
    } while (strlen(listaClientes[totalClientes].nombre) == 0);
    
    //Ingresando el numero de telefono
    gotoxy(40, 12);
    parteMedia();
    gotoxy(40, 13);
    printf("\xB3    Ingrese el numero de telefono (8 digitos):    \xB3");
    gotoxy(40, 14);
    parteVacia();
    gotoxy(65, 14);
    ingresarNumeros(listaClientes[totalClientes].telefono, 9);
    fflush(stdin);

    if (strlen(listaClientes[totalClientes].telefono) != 8) {
        gotoxy(40, 15);
        parteMedia();
        gotoxy(40, 16);
        printf("\xB3           Numero de telefono invalido.           \xB3");
        gotoxy(40, 17);
        printf("\xB3         Debe tener exactamente 8 digitos.        \xB3");
        gotoxy(40, 19);
        system("pause");
        return;
    }

    // Verifica la compañía usando la función celu
    char compania[20];
    celu(listaClientes[totalClientes].telefono, compania);
    strcpy(listaClientes[totalClientes].compania, compania);

    if (strcmp(compania, "Desconocido") == 0) {
        gotoxy(40, 15);
        parteMedia();
        gotoxy(40, 16);
        printf("\xB3                Numero de telefono                \xB3");
        gotoxy(40, 17);
        parteVacia();
        gotoxy(65, 17);
        printf("%s",(listaClientes[totalClientes].telefono) );
        gotoxy(40, 18);
        printf("\xB3    no pertenece a ninguna compania reconocida.   \xB3");
        gotoxy(40, 19);
        parteInferior();
        gotoxy(40, 21);
        system("pause");
        return;
    }

    int mesesPagados = 0;
    int costoTotal = 0;
    char bufferMes[3];
    char bufferMonto[10];
    char respuesta;
    int vuelto = 0; // Variable para almacenar el vuelto
    
    gotoxy(40, 15);
    parteMedia();
    gotoxy(40, 16);
    printf("\xB3          Desea pagar todo el ano? (s/n):         \xB3 ");
    respuesta = getch();
    fflush(stdin);
    gotoxy(40, 17);
    parteMedia();

    if (respuesta == 's' || respuesta == 'S') {
        // Pago completo del año
        mesesPagados = (1 << 12) - 1; // Marca los 12 meses como pagados
        costoTotal = 12 * 100;

        gotoxy(40, 18);
        printf("\xB3                Monto total a pagar:              \xB3");
        gotoxy(40, 19);
        parteVacia();
        gotoxy(65, 19);
        printf("%d", costoTotal);
        
        gotoxy(40, 20);
        parteMedia();
        gotoxy(40, 21);
        printf("\xB3     Ingrese el monto con el que desea pagar:     \xB3");
        gotoxy(40, 22);
        parteVacia();
        gotoxy(65, 22);
        ingresarNumeros(bufferMonto, 9);
        int montoPagado = atoi(bufferMonto);
        fflush(stdin);

        vuelto = montoPagado - costoTotal; // Calcular el vuelto
        if (vuelto < 0) {
            gotoxy(40, 23);
            parteMedia();
            gotoxy(40, 24);
            printf("\xB3      Monto insuficiente. El monto total es:      \xB3");
            gotoxy(40, 25);
            parteVacia();
            gotoxy(65, 25);
            printf("%d", costoTotal);
            gotoxy(40, 27);
            system("pause");
            return;
        }
        
        gotoxy(40, 23);
        parteMedia();
        gotoxy(40, 24);
        printf("\xB3                      Vuelto:                     \xB3");
        gotoxy(40, 25);
        parteVacia();
        gotoxy(65, 25);
        printf("%d", vuelto);
        gotoxy(40, 26);
        parteInferior();
        gotoxy(40, 27);
        system("pause");

    } else {
        // Limpiar la pantalla antes de preguntar cuántos meses quiere pagar
        system("cls");
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3==================AGREGAR CLIENTE=================\xB3");
        gotoxy(40, 9);
        parteMedia();

        // El cliente selecciona cuántos meses quiere pagar
        int cantidadMeses;

        gotoxy(40, 10);
        printf("\xB3            Cuantos meses desea pagar?:           \xB3");
        char bufferCantidad[3];
        gotoxy(40, 11);
        parteVacia();
        gotoxy(65, 11);
        ingresarNumeros(bufferCantidad, 3);
        cantidadMeses = atoi(bufferCantidad);
        fflush(stdin);
        gotoxy(40, 12);
        parteInferior();
        gotoxy(40, 14);
        system("pause");

        if (cantidadMeses < 1 || cantidadMeses > 12) {
            gotoxy(40, 16);
            parteSuperior();
            gotoxy(40, 17);
            printf("\xB3     Cantidad invalida. Debe ser entre 1 y 12.    \xB3");
            gotoxy(40, 18);
            parteInferior();
            gotoxy(40, 20);
            system("pause");
            return;
        }

        // Limpiar pantalla para la selección de meses
        system("cls");
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3================SELECCION DE MESES================\xB3"); // Título para la selección de meses
        gotoxy(40, 9);
        parteInferior();
        gotoxy(40, 11);
        system("puase");

        // Procesa los meses seleccionados
        mesesPagados = 0;
        costoTotal = 0;
        int mesSeleccionado = 0;

        for (int i = 1; i <= cantidadMeses; i++) {
            // Limpiar pantalla antes de solicitar el siguiente mes
            system("cls");
            gotoxy(40, 7);
            parteSuperior();
            gotoxy(40, 8);
            printf("\xB3================SELECCION DE MESES================\xB3"); // Título para la selección de meses
            gotoxy(40, 9);
            parteMedia();
            gotoxy(40, 10);
            printf("\xB3                Seleccione el mes                 \xB3");
            gotoxy(40, 11);
            parteVacia();
            gotoxy(65, 11);
            printf("%d", i);
            gotoxy(40, 12);
            printf("\xB3                      a pagar                     \xB3");
            gotoxy(40, 13);
            parteMedia();
            gotoxy(40, 14);
            printf("\xB3  1. Enero    \xB3    2. Febrero    \xB3    3. Marzo    \xB3");
            gotoxy(40, 15);
            parteMedia();
            gotoxy(40, 16);
            printf("\xB3  4. Abril    \xB3    5. Mayo       \xB3    6. Junio    \xB3");
            gotoxy(40, 17);
            parteMedia();
            gotoxy(40, 18);
            printf("\xB3  7. Julio    \xB3    8. Agosto     \xB3   9. Septiembre\xB3");
            gotoxy(40, 19);
            parteMedia();
            gotoxy(40, 20);
            printf("\xB3  10. Octubre \xB3  11. Noviembre   \xB3  12. Diciembre \xB3");
            gotoxy(40, 21);
            parteMedia();

            gotoxy(40, 22);
            printf("\xB3     Ingrese el mes que desea pagar (1 a 12):     \xB3");
            gotoxy(40, 23);
            parteVacia();
            gotoxy(65, 23);
            ingresarNumeros(bufferMes, 3);
            mesSeleccionado = atoi(bufferMes);
            fflush(stdin);
            gotoxy(40, 24);
            parteInferior();
            gotoxy(40, 26);
            system("pause");

            // Verificar si el mes ingresado es válido
            if (mesSeleccionado < 1 || mesSeleccionado > 12) {
                gotoxy(40, 28);
                parteSuperior();
                gotoxy(40, 29);
                printf("\xB3                 Numero invalido.                 \xB3");
                gotoxy(40, 30);
                printf("\xB3       Debe ingresar un numero entre 1 y 12.      \xB3");
                gotoxy(40, 31);
                parteInferior();
                gotoxy(40, 33);
                system("pause");
                return;
            }

            // Verificar si el mes ya fue pagado
            if (mesesPagados & (1 << (mesSeleccionado - 1))) {
                gotoxy(40, 28);
                parteSuperior();
                gotoxy(40, 29);
                printf("\xB3                      El mes:                     \xB3");
                gotoxy(40, 30);
                parteVacia();
                gotoxy(65, 30);
                printf("%d", mesSeleccionado);
                gotoxy(40, 31);
                printf("\xB3Ya ha sido seleccionado. Ingrese un mes diferente.\xB3");
                i--;  // Restar uno para que se vuelva a pedir este mes
                gotoxy(40, 32);
                parteInferior();
                gotoxy(40, 34);
                system("pause");
                continue;
            }

            // Acumular el mes pagado utilizando bits
            mesesPagados |= (1 << (mesSeleccionado - 1));
            costoTotal += 100;  // Sumar el costo de un mes
        }

        system("cls");
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3           Monto total a pagar por los            \xB3");
        gotoxy(40, 9);
        parteVacia();
        gotoxy(65, 9);
        printf("%d", cantidadMeses);
        gotoxy(40, 10);
        printf("\xB3              meses seleccionados:                \xB3");
        gotoxy(40, 11);
        parteVacia();
        gotoxy(65, 11);
        printf("%d", costoTotal);
        gotoxy(40, 12);
        parteMedia();

        gotoxy(40, 13);
        printf("\xB3     Ingrese el monto con el que desea pagar:     \xB3");
        gotoxy(40, 14);
        parteVacia();
        gotoxy(65, 14);
        ingresarNumeros(bufferMonto, 9);
        int montoPagado = atoi(bufferMonto);
        fflush(stdin);

        vuelto = montoPagado - costoTotal; // Calcular el vuelto

        //Mostrar el vuelto o no
        if (vuelto < 0) {
            gotoxy(40, 15);
            parteMedia();
            gotoxy(40, 16);
            printf("\xB3      Monto insuficiente. El monto total es:      \xB3");
            gotoxy(40, 17);
            parteVacia();
            gotoxy(65, 17);
            printf("%d", costoTotal);
            gotoxy(40, 18);
            parteInferior();
            gotoxy(40, 20);
            system("pause");
            return;
        }
        
        gotoxy(40, 15);
        parteMedia();
        gotoxy(40, 16);
        printf("\xB3                      Vuelto:                     \xB3");
        gotoxy(40, 17);
        parteVacia();
        gotoxy(65, 17);
        printf("%d", vuelto);
        gotoxy(40, 18);
        parteInferior();
        gotoxy(40, 20);
        system("pause");
    }

    // Guardar la información del cliente
    listaClientes[totalClientes].mesesMembresia = mesesPagados;
    listaClientes[totalClientes].costoTotal = costoTotal;
    listaClientes[totalClientes].codigo = generarCodigoAleatorio();
    listaClientes[totalClientes].vuelto = vuelto; // Guardar el vuelto en el cliente

    const char *nombresMeses[] = {
        "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
        "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };

    system("cls");
    gotoxy(40, 1);
    parteSuperior();
    gotoxy(40, 2);
    printf("\xB3================RESUMEN DE CLIENTE================\xB3");
    gotoxy(40, 3);
    parteMedia();

    int y = 4; // Línea de inicio

    gotoxy(40, y);
    printf("\xB3                     Nombre:                      \xB3");
    y++;

    gotoxy(40, y);
    parteVacia();
    gotoxy(60, y);
    printf("%s", listaClientes[totalClientes].nombre);
    y++;

    // Muestra la compañía en el resumen
    gotoxy(40, y);
    parteMedia();
    y++;

    gotoxy(40, y);
    printf("\xB3               Compania telefonica:               \xB3");
    y++;

    gotoxy(40, y);
    parteVacia();
    gotoxy(63, y);
    printf("%s", listaClientes[totalClientes].compania);
    y++;

    gotoxy(40, y);
    parteMedia();
    y++;

    gotoxy(40, y);
    printf("\xB3                     Telefono:                    \xB3");
    y++;

    gotoxy(40, y);
    parteVacia();
    gotoxy(62, y);
    printf("%s", listaClientes[totalClientes].telefono);
    y++;

    gotoxy(40, y);
    parteMedia();
    y++;

    gotoxy(40, y);
    printf("\xB3                 Codigo de cliente:               \xB3");
    y++;

    gotoxy(40, y);
    parteVacia();
    gotoxy(63, y);
    printf("%d", listaClientes[totalClientes].codigo);
    y++;

    gotoxy(40, y);
    parteMedia();
    y++;

    gotoxy(40, y);
    printf("\xB3                   Costo total:                   \xB3");
    y++;

    gotoxy(40, y);
    parteVacia();
    gotoxy(63, y);
    printf("%d", listaClientes[totalClientes].costoTotal);
    y++;

    gotoxy(40, y);
    parteMedia();
    y++;

    gotoxy(40, y);
    printf("\xB3                      Vuelto:                     \xB3");
    y++;

    gotoxy(40, y);
    parteVacia();
    gotoxy(63, y);
    printf("%d", listaClientes[totalClientes].vuelto); // Mostrar el vuelto
    y++;

    gotoxy(40, y);
    parteMedia();
    y++;
    // Mostrar resumen de los meses pagados
    if (listaClientes[totalClientes].mesesMembresia == (1 << 12) - 1) {
        gotoxy(40, y);
        printf("\xB3             Meses pagados: Todo el ano           \xB3");
        y++;
    } else {
        gotoxy(40, y);
        printf("\xB3                  Meses pagados:                  \xB3");
        y++;
        for (int i = 0; i < 12; i++) {
            if (mesesPagados & (1 << i)) {
                gotoxy(40, y);
                parteVacia();
                gotoxy(60, y);
                printf("%s", nombresMeses[i]);
                y++;
            }
        }
    }
    gotoxy(40, y);
    parteMedia();
    y++;

    totalClientes++;
    
    gotoxy(40, y);
    printf("\xB3            Cliente agregado con exito.           \xB3");
    y++;

    gotoxy(40, y);
    parteInferior();
    y++;

    gotoxy(40, y + 4);
    system("pause");
}

//Funcion para poder buscar a un cliente
void buscarCliente() {
    char nombre[30];
    char codigo[5];
    int tecla;

    const char *nombresMeses[] = {
        "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
        "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };

    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3==================BUSCAR CLIENTE==================\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3      Si no recuerda el nombre ni el codigo,      \xB3 ");
    gotoxy(40, 11);
    printf("\xB3        presiona 'n' o 'N' para regresar.         \xB3 ");
    gotoxy(40, 12);
    printf("\xB3        Para continuar, presione 's' o 'S'.       \xB3 ");
    gotoxy(40, 13);
    parteInferior();

    // No continuar si no hay ningún producto registrado
    if (totalClientes == 0) {
        gotoxy(40, 15);
        parteSuperior();
        gotoxy(40, 16);
        printf("\xB3            No hay clientes registrados.          \xB3");
        gotoxy(40, 17);
        parteInferior();
        gotoxy(40, 19);
        system("pause");
        return;
    }
    
    //Validando el teclado para que continue o regrese
    while (1) {
        tecla = getch();
        if (tecla == 'n' || tecla == 'N') {
            return;  
        } else if (tecla == 's' || tecla == 'S') {
            break;  
        } else {
            gotoxy(40, 15);
            parteSuperior();
            gotoxy(40, 16);
            printf("\xB3                  Tecla invalida.                 \xB3");
            gotoxy(40, 17);
            printf("\xB3         Presione 's' o 'S' para continuar        \xB3");
            gotoxy(40, 18);
            printf("\xB3            o 'n' o 'N' para regresar.            \xB3");
            gotoxy(40, 19);
            parteInferior();
        }
    }
    
    //Le pedimos al usuario que ingrese nombre y codigo del cliente que busca
    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3==================BUSCAR CLIENTE==================\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3          Ingrese el nombre del cliente:          \xB3");
    gotoxy(40, 11);
    parteVacia();
    gotoxy(50, 11);
    ingresarNombre(nombre);  
    gotoxy(40, 12);
    parteMedia();
    gotoxy(40, 13);
    printf("\xB3    Ingrese el codigo del cliente (4 digitos):    \xB3");
    gotoxy(40, 14);
    parteVacia();
    gotoxy(65, 14);
    ingresarNumeros(codigo, 4);  
    gotoxy(40, 15);
    parteInferior();
    gotoxy(40, 17);
    system("pause");

    system("cls");
    
    //COnvertir en entero una cadena de caracteres
    int codigoNumerico = atoi(codigo);
    
    //Validando que el codigo si o si debe tener 4 digitos
    if (strlen(codigo) != 4) {
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3                  Codigo invalido.                \xB3");
        gotoxy(40, 9);
        printf("\xB3        Debe tener exactamente 4 digitos.         \xB3");
        gotoxy(40, 10);
        parteInferior();
        gotoxy(40, 12);
        system("pause");
        return;
    }
    
    //Ciclo for para buscar al cliente
    int clienteIndex = -1; 
    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(listaClientes[i].nombre, nombre) == 0 && listaClientes[i].codigo == codigoNumerico) {
            clienteIndex = i;
            break;
        }
    }
    
    //Validacion para cuando no encontremos al cliente
    if (clienteIndex == -1) {
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3              Cliente no encontrado.             \xB3");
        gotoxy(40, 9);
        parteInferior();
        gotoxy(40, 11);
        system("pause");
        return;
    }

    // Imprimir la información del cliente
    system("cls");
    gotoxy(40, 1);
    parteSuperior();
    gotoxy(40, 2);
    printf("\xB3==============INFORMACION DEL CLIENTE=============\xB3");
    gotoxy(40, 3);
    parteMedia();
    
    int y = 4; // Línea de inicio
    gotoxy(40, y);
    printf("\xB3                     Nombre:                      \xB3");
    y++;

    gotoxy(40, y);
    parteVacia();
    gotoxy(60, y);
    printf("%s", listaClientes[clienteIndex].nombre);
    y++;

    gotoxy(40, y);
    parteMedia();
    y++;

    gotoxy(40, y);
    printf("\xB3                    Telefono:                     \xB3");
    y++;

    gotoxy(40, y);
    parteVacia();
    gotoxy(62, y);
    printf("%s", listaClientes[clienteIndex].telefono);
    y++;

    gotoxy(40, y);
    parteMedia();
    y++;

    gotoxy(40, y);
    printf("\xB3                    Codigo:                       \xB3");
    y++;

    gotoxy(40, y);
    parteVacia();
    gotoxy(62, y);
    printf("%d", listaClientes[clienteIndex].codigo);
    y++;

    gotoxy(40, y);
    parteMedia();
    y++;

    gotoxy(40, y);
    printf("\xB3               Compania telefonica:               \xB3");
    y++;

    gotoxy(40, y);
    parteVacia();
    gotoxy(63, y);
    printf("%s", listaClientes[clienteIndex].compania);
    y++;

    gotoxy(40, y);
    parteMedia();
    y++;

    gotoxy(40, y);
    printf("\xB3               Costo total pagado:                \xB3");
    y++;

    gotoxy(40, y);
    parteVacia();
    gotoxy(63, y);
    printf("%d", listaClientes[clienteIndex].costoTotal);
    y++;

    gotoxy(40, y);
    parteMedia();
    y++;

    gotoxy(40, y);
    printf("\xB3                 Meses pagados:                   \xB3");
    y++;
    
    int meses = listaClientes[clienteIndex].mesesMembresia;
    if (meses == 12) {
        gotoxy(40, y);
        printf("\xB3                    Todo el ano                   \xB3");
        y++;
    } else {
        for (int j = 0; j < 12; j++) {
            if (meses & (1 << j)) { 
                gotoxy(40, y);
                parteVacia();
                gotoxy(60, y);
                printf("%s", nombresMeses[j]);
                y++;
            }
        }
    }
    gotoxy(40, y);
    parteInferior();
    
    gotoxy(40, y + 3);
    system("pause");
}

//Funcion para poder ver los clientes agregados
void verClientes() {
    // Puntero que contiene a los meses
    const char *nombresMeses[] = {
        "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
        "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };

    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3=================LISTA DE CLIENTES================\xB3");
    gotoxy(40, 9);
    parteInferior();

    if (totalClientes == 0) {
        gotoxy(40, 13);
        parteSuperior();
        gotoxy(40, 14);
        printf("\xB3           No hay clientes registrados.           \xB3");
        gotoxy(40, 15);
        parteInferior();
        gotoxy(40, 17);
        system("pause");
    } else {
        int totalPaginas = (totalClientes + CLIENTES_POR_PAGINA - 1) / CLIENTES_POR_PAGINA;
        int paginaActual = 0;
        int tecla;

        do {
            // Limpiar pantalla y mostrar encabezado
            system("cls");
            gotoxy(40, 1);
            parteSuperior();
            gotoxy(40, 2);
            printf("\xB3=================LISTA DE CLIENTES================\xB3");
            gotoxy(40, 3);
            parteMedia();

            int y = 4; // Posición inicial de la información en cada página
            int clienteInicio = paginaActual * CLIENTES_POR_PAGINA;
            int clienteFin = clienteInicio + CLIENTES_POR_PAGINA;

            if (clienteFin > totalClientes) {
                clienteFin = totalClientes;
            }

            for (int i = clienteInicio; i < clienteFin; i++) {
                gotoxy(40, y);
                printf("\xB3                     Cliente:                     \xB3");
                y++;

                gotoxy(40, y);
                parteVacia();
                gotoxy(65, y);
                printf("%d", i + 1);
                y++;

                gotoxy(40, y);
                parteMedia();
                y++;

                gotoxy(40, y);
                printf("\xB3                     Nombre:                      \xB3");
                y++;

                gotoxy(40, y);
                parteVacia();
                gotoxy(60, y);
                printf("%s", listaClientes[i].nombre);
                y++;

                gotoxy(40, y);
                parteMedia();
                y++;

                gotoxy(40, y);
                printf("\xB3                    Telefono:                     \xB3");
                y++;

                gotoxy(40, y);
                parteVacia();
                gotoxy(63, y);
                printf("%s", listaClientes[i].telefono);
                y++;

                gotoxy(40, y);
                parteMedia();
                y++;

                gotoxy(40, y);
                printf("\xB3                     Codigo:                      \xB3");
                y++;

                gotoxy(40, y);
                parteVacia();
                gotoxy(63, y);
                printf("%d", listaClientes[i].codigo);
                y++;

                gotoxy(40, y);
                parteMedia();
                y++;

                gotoxy(40, y);
                printf("\xB3                    Compania:                     \xB3");
                y++;

                gotoxy(40, y);
                parteVacia();
                gotoxy(63, y);
                printf("%s", listaClientes[i].compania);
                y++;

                gotoxy(40, y);
                parteMedia();
                y++;

                gotoxy(40, y);
                printf("\xB3              Costo total pagado:                 \xB3");
                y++;

                gotoxy(40, y);
                parteVacia();
                gotoxy(63, y);
                printf("%d", listaClientes[i].costoTotal);
                y++;

                gotoxy(40, y);
                parteMedia();
                y++;

                gotoxy(40, y);
                printf("\xB3                   Meses pagados:                 \xB3");
                y++;

                int meses = listaClientes[i].mesesMembresia;
                if (meses == 12) {
                    gotoxy(40, y);
                    printf("\xB3                   Todo el ano                    \xB3");
                    y++;
                } else {
                    for (int j = 0; j < 12; j++) {
                        if (meses & (1 << j)) {
                            gotoxy(40, y);
                            parteVacia();
                            gotoxy(60, y);
                            printf("%s", nombresMeses[j]);
                            y++;
                        }
                    }
                }

                gotoxy(40, y);
                parteInferior();
            }

            // Mostrar información de paginación
            gotoxy(40, y + 2);
            printf("Pagina %d de %d", paginaActual + 1, totalPaginas);
            y++;

            gotoxy(40, y);
            printf("Usa las flechas izquierda y derecha para navegar.");

            // Detectar entrada del teclado para navegar entre páginas
            tecla = _getch();
            if (tecla == 0 || tecla == 224) { 
                tecla = _getch();
                if (tecla == 75) { // Flecha izquierda
                    if (paginaActual > 0) {
                        paginaActual--;
                    }
                } else if (tecla == 77) { // Flecha derecha
                    if (paginaActual < totalPaginas - 1) {
                        paginaActual++;
                    }
                }
            }

        } while (tecla == 75 || tecla == 77); // Continuar mientras se usan las flechas izquierda/derecha

    }

    gotoxy(40, 40);
    system("pause");
}

//Funcion para poder eliminar clientes
void eliminarCliente() {
    char nombre[30];
    char codigo[5];  
    int clienteEncontrado = 0;

    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3=================ELIMINAR CLIENTE=================\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3      Si no recuerda el nombre ni el codigo,      \xB3 ");
    gotoxy(40, 11);
    printf("\xB3        presiona 'n' o 'N' para regresar.         \xB3 ");
    gotoxy(40, 12);
    printf("\xB3        Para continuar, presione 's' o 'S'.       \xB3 ");
    gotoxy(40, 13);
    parteInferior();
    
    //Validamos que no continue, si no hay cleintes ingresados
    if (totalClientes == 0) {
        gotoxy(40, 15);
        parteSuperior();
        gotoxy(40, 16);
        printf("\xB3            No hay clientes registrados.          \xB3");
        gotoxy(40, 17);
        parteInferior();
        gotoxy(40, 19);
        system("pause");
        return;
    }
    
    //Validamos el teclado para que continue o regrese
    while (1) {
        int tecla = getch();
        if (tecla == 'n' || tecla == 'N') {
            return;  
        } else if (tecla == 's' || tecla == 'S') {
            break;  
        } else {
            gotoxy(40, 15);
            parteSuperior();
            gotoxy(40, 16);
            printf("\xB3                  Tecla invalida.                 \xB3");
            gotoxy(40, 17);
            printf("\xB3         Presione 's' o 'S' para continuar        \xB3");
            gotoxy(40, 18);
            printf("\xB3            o 'n' o 'N' para regresar.            \xB3");
            gotoxy(40, 19);
            parteInferior();
        }
    }
    
    //Le pedimos al usuario que ingrese el nombre y codigo del cliente que desea eliminar
    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3=================ELIMINAR CLIENTE=================\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3          Ingrese el nombre del cliente:          \xB3");
    gotoxy(40, 11);
    parteVacia();
    gotoxy(50, 11);
    ingresarNombre(nombre);  
    gotoxy(40, 12);
    parteMedia();
    gotoxy(40, 13);
    printf("\xB3    Ingrese el codigo del cliente (4 digitos):    \xB3");
    gotoxy(40, 14);
    parteVacia();
    gotoxy(65, 14);
    ingresarNumeros(codigo, 4);  
    gotoxy(40, 15);
    parteInferior();
    gotoxy(40, 17);
    system("pause");

    system("cls");

    if (strlen(codigo) != 4) {
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3                  Codigo invalido.                \xB3");
        gotoxy(40, 9);
        printf("\xB3        Debe tener exactamente 4 digitos.         \xB3");
        gotoxy(40, 10);
        parteInferior();
        gotoxy(40, 12);
        system("pause");
        return;
    }

    // Convertir código a número entero
    int codigoNumerico = atoi(codigo);

    // Buscar el cliente
    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(listaClientes[i].nombre, nombre) == 0 && listaClientes[i].codigo == codigoNumerico) {
            clienteEncontrado = 1;
            
            //Nos imprime la infromacion del cliente que queremos eliminar
            system("cls");
            gotoxy(40, 1);
            parteSuperior();
            gotoxy(40, 2);
            printf("\xB3================RESUMEN DE CLIENTE================\xB3");
            gotoxy(40, 3);
            parteMedia();

            int y = 4; // Línea de inicio

            gotoxy(40, y);
            printf("\xB3                     Nombre:                      \xB3");
            y++;

            gotoxy(40, y);
            parteVacia();
            gotoxy(60, y);
            printf("%s", listaClientes[i].nombre);
            y++;

            gotoxy(40, y);
            parteMedia();
            y++;

            gotoxy(40, y);
            printf("\xB3               Compania telefonica:               \xB3");
            y++;

            gotoxy(40, y);
            parteVacia();
            gotoxy(63, y);
            printf("%s", listaClientes[i].compania);
            y++;

            gotoxy(40, y);
            parteMedia();
            y++;

            gotoxy(40, y);
            printf("\xB3                    Telefono:                     \xB3");
            y++;

            gotoxy(40, y);
            parteVacia();
            gotoxy(62, y);
            printf("%s", listaClientes[i].telefono);
            y++;

            gotoxy(40, y);
            parteMedia();
            y++;

            gotoxy(40, y);
            printf("\xB3                Codigo de cliente:                \xB3 ");
            y++;

            gotoxy(40, y);
            parteVacia();
            gotoxy(63, y);
            printf("%d", listaClientes[i].codigo);
            y++;

            gotoxy(40, y);
            parteMedia();
            y++;

            gotoxy(40, y);
            printf("\xB3                  Costo total:                    \xB3 ");
            y++;

            gotoxy(40, y);
            parteVacia();
            gotoxy(63, y);
            printf("%d", listaClientes[i].costoTotal);
            y++;

            gotoxy(40, y);
            parteMedia();
            y++;

            gotoxy(40, y);
            printf("\xB3                  Meses pagados:                  \xB3");
            y++;
            if (listaClientes[i].mesesMembresia == 12) {
                gotoxy(40, y);
                printf("\xB3                    Todo el ano.                  \xB3");
                y++;
            } else {
                const char *nombresMeses[] = {
                    "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", 
                    "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
                };
                for (int j = 0; j < 12; j++) {
                    if ((listaClientes[i].mesesMembresia >> j) & 1) {
                        gotoxy(40, y);
                        parteVacia();
                        gotoxy(60, y);
                        printf("%s", nombresMeses[j]);
                        y++;
                    }
                }
            }
            gotoxy(40, y);
            parteMedia();
            y++;

            //Le preguntamos al usuario si dea borrar al cleitne o no
            gotoxy(40, y);
            printf("\xB3 Esta seguro que busca borrar este cliente?(s/n): \xB3");
            y++;

            gotoxy(40, y);
            parteMedia();
            y++;
            int confirmacion = getch();

            //Validamos el getch s o S del usuario
            if (confirmacion == 's' || confirmacion == 'S') {
                for (int j = i; j < totalClientes - 1; j++) {
                    listaClientes[j] = listaClientes[j + 1];
                }
                totalClientes--;
                
                gotoxy(40, y);
                printf("\xB3                Cliente con codigo:               \xB3");
                y++;

                gotoxy(40, y);
                parteVacia();
                gotoxy(65, y);
                printf("%d", codigoNumerico);
                y++;

                gotoxy(40, y);
                printf("\xB3                Eliminado con exito.              \xB3");
                y++;

                gotoxy(40, y);
                parteInferior();

                gotoxy(40, y + 3);
                system("pause");
            } else if (confirmacion == 'n' || confirmacion == 'N') {
                gotoxy(40, y);
                printf("\xB3              Eliminacion cancelada.              \xB3");
                y++;

                gotoxy(40, y);
                parteInferior();
                y++;

                gotoxy(40, y + 3);
                system("pause");
                return;
            } else {
                gotoxy(40, y);
                printf("\xB3        Tecla equivocada. Intente de nuevo.       \xB3");
                y++;

                gotoxy(40, y);
                parteInferior();
                y++;

                gotoxy(40, y + 3);
                system("pause");
                return;
            }
        }
    }
    
    //Funcion para en caso de que no se encuentre el cleinte
    if (!clienteEncontrado) {
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3                Cliente con nombre:               \xB3");
        gotoxy(40, 9);
        parteVacia();
        gotoxy(50, 9);
        printf("%s", nombre);
        gotoxy(40, 10);
        printf("\xB3                     Y codigo:                    \xB3");
        gotoxy(40, 11);
        parteVacia();
        gotoxy(65, 11);
        printf("%d", codigoNumerico);
        gotoxy(40, 12);
        printf("\xB3                  No encontrado.                  \xB3");
        gotoxy(40, 13);
        parteInferior();
        gotoxy(40, 15);
        system("pause");
    }
}

//Funcion para poder actualizar los clientes
void actualizarCliente() {

    int i;
    char nombre[30];
    int codigo;
    char codigoStr[5];
    
    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8); 
    printf("\xB3================ACTUALIZAR CLIENTE================\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3      Si no recuerda el nombre ni el codigo,      \xB3 ");
    gotoxy(40, 11);
    printf("\xB3        presiona 'n' o 'N' para regresar.         \xB3 ");
    gotoxy(40, 12);
    printf("\xB3        Para continuar, presione 's' o 'S'.       \xB3 ");
    gotoxy(40, 13);
    parteInferior();
    
    //Para que no continue, si no hay cliente ingresados
    if (totalClientes == 0) {
        gotoxy(40, 15);
        parteSuperior();
        gotoxy(40, 16);
        printf("\xB3            No hay clientes registrados.          \xB3");
        gotoxy(40, 17);
        parteInferior();
        gotoxy(40, 19);
        system("pause");
        return;
    }
    
    //Validando para que el teclado continue o regrese
    char tecla;
    while (1) {
        tecla = getch();
        if (tecla == 'n' || tecla == 'N') {
            return; // Regresar a la opción de ver
        } else if (tecla == 's' || tecla == 'S') {
            break; // Continuar con la actualización
        } else {
            gotoxy(40, 15);
            parteSuperior();
            gotoxy(40, 16);
            printf("\xB3                  Tecla invalida.                 \xB3");
            gotoxy(40, 17);
            printf("\xB3         Presione 's' o 'S' para continuar        \xB3");
            gotoxy(40, 18);
            printf("\xB3            o 'n' o 'N' para regresar.            \xB3");
            gotoxy(40, 19);
            parteInferior();
        }
    }
    
    //Le pedimos al usario que ingrese el nombre y codigo del cliente que busca actualizar
    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3================ACTUALIZAR CLIENTE================\xB3");
    gotoxy(40, 9);
    parteMedia();
    gotoxy(40, 10);
    printf("\xB3          Ingrese el nombre del cliente:          \xB3");
    gotoxy(40, 11);
    parteVacia();
    gotoxy(50, 11);
    ingresarNombre(nombre);  
    gotoxy(40, 12);
    parteMedia();
    gotoxy(40, 13);
    printf("\xB3    Ingrese el codigo del cliente (4 digitos):    \xB3");
    gotoxy(40, 14);
    parteVacia();
    gotoxy(65, 14);
    ingresarNumeros(codigoStr, 4);  
    gotoxy(40, 15);
    parteInferior();
    gotoxy(40, 17);
    system("pause");

    system("cls");
    
    //No continuara si el codigo no es del 4 digitos
    if (strlen(codigoStr) != 4) {
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3                  Codigo invalido.                \xB3");
        gotoxy(40, 9);
        printf("\xB3        Debe tener exactamente 4 digitos.         \xB3");
        gotoxy(40, 10);
        parteInferior();
        gotoxy(40, 12);
        system("pause");
        return;
    }

    // Convertir código a número entero
    codigo = atoi(codigoStr); 
    
    //Ciclo for para buscar al cliente
    int clienteIndex = -1; 
    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(listaClientes[i].nombre, nombre) == 0 && listaClientes[i].codigo == codigo) {
            clienteIndex = i;
            break;
        }
    }
    
    //Validacion en caso de que no se encuentre al clinente
    if (clienteIndex == -1) {
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3              Cliente no encontrado.              \xB3");
        gotoxy(40, 9);
        parteInferior();
        gotoxy(40, 11);
        system("pause");
        return;
    }
    
    //Imprime la infromacion del cliente que deseas actualizar
    system("cls");
    gotoxy(40, 1);
    parteSuperior();
    gotoxy(40, 2);
    printf("\xB3==============INFORMACION DE CLIENTE==============\xB3");
    gotoxy(40, 3);
    parteMedia();

    int y = 4; // Línea de inicio

    gotoxy(40, y);
    printf("\xB3                     Nombre:                      \xB3");
    y++;

    gotoxy(40, y);
    parteVacia();
    gotoxy(60, y);
    printf("%s", listaClientes[clienteIndex].nombre);
    y++;

    gotoxy(40, y);
    parteMedia();
    y++;

    gotoxy(40, y);
    printf("\xB3               Compania telefonica:               \xB3");
    y++;

    gotoxy(40, y);
    parteVacia();
    gotoxy(63, y);
    printf("%s", listaClientes[clienteIndex].compania);
    y++;

    gotoxy(40, y);
    parteMedia();
    y++;
    
    gotoxy(40, y);
    printf("\xB3                    Telefono:                     \xB3");
    y++;

    gotoxy(40, y);
    parteVacia();
    gotoxy(60, y);
    printf("%s", listaClientes[clienteIndex].telefono);
    y++;

    gotoxy(40, y);
    parteMedia();
    y++;

    gotoxy(40, y);
    printf("\xB3                Codigo de cliente:                \xB3 ");
    y++;

    gotoxy(40, y);
    parteVacia();
    gotoxy(63, y);
    printf("%d", listaClientes[clienteIndex].codigo);
    y++;

    gotoxy(40, y);
    parteMedia();
    y++;

    gotoxy(40, y);
    printf("\xB3                  Costo total:                    \xB3 ");
    y++;

    gotoxy(40, y);
    parteVacia();
    gotoxy(63, y);
    printf("%d", listaClientes[clienteIndex].costoTotal);
    y++;

    gotoxy(40, y);
    parteMedia();
    y++;

    gotoxy(40, y);
    printf("\xB3                  Meses pagados:                  \xB3");
    y++;
    if (listaClientes[clienteIndex].mesesMembresia == 12) {
        gotoxy(40, y);
        printf("\xB3                    Todo el ano.                  \xB3");
        y++;
    } else {
        const char *nombresMeses[] = {
            "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", 
            "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
        };
        for (int j = 0; j < 12; j++) {
            if ((listaClientes[clienteIndex].mesesMembresia >> j) & 1) {
                gotoxy(40, y);
                parteVacia();
                gotoxy(63, y);
                printf("%s", nombresMeses[j]);
                y++;
            }
        }
    }
    gotoxy(40, y);
    parteInferior();
    gotoxy(40, y + 3);
    system("pause");

    system("cls");

    // Pregunta si desea actualizar el nombre
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3        Desea actualizar el nombre? (s/n):        \xB3");
    gotoxy(40, 9);
    parteInferior();
    char respuesta = getch();
    if (respuesta == 's' || respuesta == 'S') {
        gotoxy(40, 11);
        parteSuperior();
        gotoxy(40, 12);
        printf("\xB3             Ingrese el nuevo nombre:             \xB3");
        gotoxy(40, 13);
        parteVacia();
        gotoxy(50, 13);
        ingresarNombre(listaClientes[clienteIndex].nombre);
        fflush(stdin);
        gotoxy(40, 14);
        parteInferior();

        gotoxy(40, 16);
        parteSuperior();
        gotoxy(40, 17);
        printf("\xB3         Nombre actualizado exitosamente.         \xB3");
        gotoxy(40, 18);
        parteInferior();
        gotoxy(40, 20);
        system("pause");
    } else if (respuesta == 'n' || respuesta == 'N') {
        gotoxy(40, 11);
        parteSuperior();
        gotoxy(40, 12);
        printf("\xB3         Nombre salteado, sin actualizar.         \xB3");
        gotoxy(40, 13);
        parteInferior();
        gotoxy(40, 15);
        system("pause");
    } else {
        gotoxy(40, 11);
        parteSuperior();
        gotoxy(40, 12);
        printf("\xB3        Tecla equivocada. Intente de nuevo.       \xB3");
        gotoxy(40, 13);
        parteInferior();
        gotoxy(40, 15);
        system("pause");
        return;
    }

    // Pregunta si desea actualizar el telefono
    gotoxy(40, 22);
    parteSuperior();
    gotoxy(40, 23);
    printf("\xB3       Desea actualizar el telefono? (s/n):       \xB3");
    gotoxy(40, 24);
    parteInferior();
    respuesta = getch();
    if (respuesta == 's' || respuesta == 'S') {
        char telefono[9];
        gotoxy(40, 26);
        parteSuperior();
        gotoxy(40, 27);
        printf("\xB3      Ingrese el nuevo telefono (8 digitos):      \xB3");
        gotoxy(40, 28);
        parteVacia();
        gotoxy(65, 28);
        ingresarNumeros(telefono, 8);  
        fflush(stdin);
        gotoxy(40, 29);
        parteInferior();
        gotoxy(40, 31);
        system("pause");

        if (strlen(telefono) != 8) {
            gotoxy(40, 33);
            parteSuperior();
            gotoxy(40, 34);
            printf("\xB3           Numero de telefono invalido.           \xB3");
            gotoxy(40, 35);
            parteInferior();
            gotoxy(40, 37);
            system("pause");
            return;
        }

        int countCeros = 0;
        for (int j = 0; j < 8; j++) {
            if (telefono[j] == '0') {
            countCeros++;
            }
        }
        if (countCeros > 3) {
            gotoxy(40, 33);
            parteSuperior();
            gotoxy(40, 34);
            printf("\xB3           Numero de telefono invalido.           \xB3");
            gotoxy(40, 35);
            parteInferior();
            gotoxy(40, 37);
            system("pause");
            return;
        }


        strcpy(listaClientes[clienteIndex].telefono, telefono);
    } else if (respuesta == 'n' || respuesta == 'N') {
        gotoxy(40, 26);
        parteSuperior();
        gotoxy(40, 27);
        printf("\xB3        Telefono salteado, sin actualizar.        \xB3");
        gotoxy(40, 28);
        parteInferior();
        gotoxy(40, 30);
        system("pause");
    } else {
        gotoxy(40, 26);
        parteSuperior();
        gotoxy(40, 27);
        printf("\xB3        Tecla equivocada. Intente de nuevo.       \xB3");
        gotoxy(40, 28);
        parteInferior();
        gotoxy(40, 30);
        system("pause");
        return;
    }
    
    // Proceso para actualizar los meses pagados
    int mesesPagados = listaClientes[clienteIndex].mesesMembresia; // Obtener meses actuales
    int costoTotal = 0;
    char bufferMes[3];
    
    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8);
    printf("\xB3         Desea actualizar los meses? (s/n):       \xB3");
    gotoxy(40, 9);
    parteInferior();
     
    respuesta = getch();
    if (respuesta == 's' || respuesta == 'S') {
        gotoxy(40, 11);
        parteSuperior();
        gotoxy(40, 12);
        printf("\xB3            Procedera a actualizarlos.            \xB3");
        gotoxy(40, 13);
        parteInferior();
        gotoxy(40, 15);
        system("pause");

        system("cls");

        if (listaClientes[clienteIndex].mesesMembresia == (1 << 12) - 1){
            gotoxy(40, 7);
            parteSuperior();
            gotoxy(40, 8);
            printf("\xB3         El cliente ya ha pagado todo el ano.     \xB3");
            gotoxy(40, 9);
            printf("\xB3                No se pueden actualizar.          \xB3");
            gotoxy(40, 10);
            parteInferior();
            gotoxy(40, 12);
            system("pause");
            return;
        }

        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8);
        printf("\xB3           Cuantos meses desea agregar?:          \xB3");
        gotoxy(40, 9);
        parteVacia();
        gotoxy(65, 9);
        ingresarNumeros(bufferMes, 3);
        int cantidadMeses = atoi(bufferMes);
        fflush(stdin);
        gotoxy(40, 10);
        parteInferior();
        gotoxy(40, 11);
        system("pause");

        if (cantidadMeses < 1 || cantidadMeses > 12) {
            gotoxy(40, 13);
            parteSuperior();
            gotoxy(40, 14);
            printf("\xB3     Cantidad invalida. Debe ser entre 1 y 12.    \xB3");
            gotoxy(40, 15);
            parteInferior();
            gotoxy(40, 17);
            system("pause");
            return;
        }

        for (int i = 1; i <= cantidadMeses; i++) {
            // Limpiar pantalla antes de solicitar el siguiente mes
            system("cls");
            gotoxy(40, 7);
            parteSuperior();
            gotoxy(40, 8);
            printf("\xB3================SELECCION DE MESES================\xB3"); // Título para la selección de meses
            gotoxy(40, 9);
            parteMedia();
            gotoxy(40, 10);
            printf("\xB3                Seleccione el mes                 \xB3");
            gotoxy(40, 11);
            parteVacia();
            gotoxy(65, 11);
            printf("%d", i);
            gotoxy(40, 12);
            printf("\xB3                      a pagar                     \xB3");
            gotoxy(40, 13);
            parteMedia();
            gotoxy(40, 14);
            printf("\xB3  1. Enero    \xB3    2. Febrero    \xB3    3. Marzo    \xB3");
            gotoxy(40, 15);
            parteMedia();
            gotoxy(40, 16);
            printf("\xB3  4. Abril    \xB3    5. Mayo       \xB3    6. Junio    \xB3");
            gotoxy(40, 17);
            parteMedia();
            gotoxy(40, 18);
            printf("\xB3  7. Julio    \xB3    8. Agosto     \xB3   9. Septiembre\xB3");
            gotoxy(40, 19);
            parteMedia();
            gotoxy(40, 20);
            printf("\xB3  10. Octubre \xB3  11. Noviembre   \xB3  12. Diciembre \xB3");
            gotoxy(40, 21);
            parteMedia();

            gotoxy(40, 22);
            printf("\xB3     Ingrese el mes que desea pagar (1 a 12):     \xB3");
            gotoxy(40, 23);
            parteVacia();
            gotoxy(65, 23);
            ingresarNumeros(bufferMes, 3);
            int mesSeleccionado = atoi(bufferMes);
            fflush(stdin);
            gotoxy(40, 24);
            parteInferior();
            gotoxy(40, 26);
            system("pause");

            // Verificar si el mes ingresado es válido
            if (mesSeleccionado < 1 || mesSeleccionado > 12) {
                gotoxy(40, 28);
                parteSuperior();
                gotoxy(40, 29);
                printf("\xB3                 Numero invalido.                 \xB3");
                gotoxy(40, 30);
                printf("\xB3       Debe ingresar un numero entre 1 y 12.      \xB3");
                gotoxy(40, 31);
                parteInferior();
                gotoxy(40, 33);
                system("pause");
                return;
            }

            // Verificar si el mes ya fue pagado
            if (mesesPagados & (1 << (mesSeleccionado - 1))) {
                gotoxy(40, 28);
                parteSuperior();
                gotoxy(40, 29);
                printf("\xB3                      El mes:                     \xB3");
                gotoxy(40, 30);
                parteVacia();
                gotoxy(65, 30);
                printf("%d", mesSeleccionado);
                gotoxy(40, 31);
                printf("\xB3Ya ha sido seleccionado. Ingrese un mes diferente.\xB3");
                i--;  // Restar uno para que se vuelva a pedir este mes
                gotoxy(40, 32);
                parteInferior();
                gotoxy(40, 34);
                system("pause");
                continue;
            }

            // Acumular el mes pagado utilizando bits
            mesesPagados |= (1 << (mesSeleccionado - 1));
            costoTotal += 100;  // Sumar el costo de un mes
        }

        // Actualiza la información del cliente
        listaClientes[clienteIndex].mesesMembresia = mesesPagados;
        listaClientes[clienteIndex].costoTotal += costoTotal;
    } else if (respuesta == 'n' || respuesta == 'N') {
        gotoxy(40, 11);
        parteSuperior();
        gotoxy(40, 12);
        printf("\xB3                  Meses salteados                 \xB3");
        gotoxy(40, 13);
        parteInferior();
        gotoxy(40, 15);
        system("pause");
    } else {
        gotoxy(40, 11);
        parteSuperior();
        gotoxy(40, 12);
        printf("\xB3        Tecla equivocada. Intente de nuevo.       \xB3");
        gotoxy(40, 13);
        parteInferior();
        gotoxy(40, 15);
        system("pause");
        return;
    }
    
    // Mostrar resumen actualizado
    system("cls");
    gotoxy(40, 1);
    parteSuperior();
    gotoxy(40, 2);
    printf("\xB3================RESUMEN ACTUALIZADO===============\xB3");
    gotoxy(40, 3);
    parteMedia();

    int z = 4; // Línea de inicio

    gotoxy(40, z);
    printf("\xB3                     Nombre:                      \xB3");
    z++;

    gotoxy(40, z);
    parteVacia();
    gotoxy(60, z);
    printf("%s", listaClientes[clienteIndex].nombre);
    z++;

    gotoxy(40, z);
    parteMedia();
    z++;

    gotoxy(40, z);
    printf("\xB3                    Telefono:                     \xB3");
    z++;

    gotoxy(40, z);
    parteVacia();
    gotoxy(63, z);
    printf("%s", listaClientes[clienteIndex].telefono);
    z++;

    gotoxy(40, z);
    parteMedia();
    z++;

    gotoxy(40, z);
    printf("\xB3              Costo total acumulado:              \xB3");
    z++;

    gotoxy(40, z);
    parteVacia();
    gotoxy(60, z);
    printf("%d", listaClientes[clienteIndex].costoTotal);
    z++;

    gotoxy(40, z);
    parteMedia();
    z++;
    const char *nombresMeses[] = {
        "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
        "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };

    gotoxy(40, z);
    printf("\xB3                 Meses pagados:                   \xB3");
    z++;
    for (int j = 0; j < 12; j++) {
        if (mesesPagados & (1 << j)) {
            gotoxy(40, z);
            parteVacia();
            gotoxy(63, z);
            printf("%s", nombresMeses[j]);
            z++;
        }
    }
    gotoxy(40, z);
    parteMedia();
    z++;

    gotoxy(40, z);
    printf("\xB3          Cliente actualizado con exito.          \xB3");
    z++;

    gotoxy(40, z);
    parteInferior();
    gotoxy(40, z + 3);
    system("pause");
}

//Funcion para ya tener 4 productos desde el inicio
void cargarProductosIniciales() {
    //Cargar el primer producto
    strcpy(productosTotal[0].nombre, "Gatorade Zero Naranja");
    strcpy(productosTotal[0].precio, "38");
    strcpy(productosTotal[0].cantidad, "11");
    productosTotal[0].codigo = generarCodigoAleatorio();
    strcpy(productosTotal[0].descripcion, "Bebida isotonica de 600 ml, sin azucar.");
    
    //Cargar el segundo producto
    strcpy(productosTotal[1].nombre, "Botella Agua Fuente Pura");
    strcpy(productosTotal[1].precio, "23");
    strcpy(productosTotal[1].cantidad, "12");
    productosTotal[1].codigo = generarCodigoAleatorio();
    strcpy(productosTotal[1].descripcion, "Botella de alta calidad de 600 ml.");
    
    //Cargar el tercer producto
    strcpy(productosTotal[2].nombre, "Platinum Multi Vitamin");
    strcpy(productosTotal[2].precio, "432");
    strcpy(productosTotal[2].cantidad, "13");
    productosTotal[2].codigo = generarCodigoAleatorio();
    strcpy(productosTotal[2].descripcion, "Suplemento nutricional de la mejor calidad.");
    
    //Cargar el cuarto producto
    strcpy(productosTotal[3].nombre, "Mancuerna redonda Golds Gym");
    strcpy(productosTotal[3].precio, "23");
    strcpy(productosTotal[3].cantidad, "15");
    productosTotal[3].codigo = generarCodigoAleatorio();
    strcpy(productosTotal[3].descripcion, "Ideal para aumentar la intensidad de tus rutinas.");

    totalProductos = 4;
}

//Funcion para ya tener 3 clientes desde el inicio
void cargarClientesIniciales() {
    // Cargar el primer cliente
    strcpy(listaClientes[0].nombre, "Juan Perez");
    strcpy(listaClientes[0].telefono, "83291034");
    listaClientes[0].codigo = generarCodigoAleatorio();
    listaClientes[0].mesesMembresia = (1 << 12) - 1; 
    listaClientes[0].costoTotal = 12 * COSTO_MES; 
    memset(listaClientes[0].mesPagados, 1, sizeof(listaClientes[0].mesPagados));
    memset(listaClientes[0].mesesAdicionales, 0, sizeof(listaClientes[0].mesesAdicionales));
    listaClientes[0].numMesesAdicionales = 0;
    listaClientes[0].costoTotalAdicional = 0;
    celu(listaClientes[0].telefono, listaClientes[0].compania);

    // Cargar el segundo cliente
    strcpy(listaClientes[1].nombre, "Maria Gomez");
    strcpy(listaClientes[1].telefono, "85494321");
    listaClientes[1].codigo = generarCodigoAleatorio();
    listaClientes[1].mesesMembresia = (1 << 0) | (1 << 1) | (1 << 2); 
    listaClientes[1].costoTotal = 3 * COSTO_MES; 
    memset(listaClientes[1].mesPagados, 0, sizeof(listaClientes[1].mesPagados));
    listaClientes[1].mesPagados[0] = 1; 
    listaClientes[1].mesPagados[1] = 1; 
    listaClientes[1].mesPagados[2] = 1; 
    memset(listaClientes[1].mesesAdicionales, 0, sizeof(listaClientes[1].mesesAdicionales));
    listaClientes[1].numMesesAdicionales = 0;
    listaClientes[1].costoTotalAdicional = 0;
    celu(listaClientes[1].telefono, listaClientes[1].compania);

    // Cargar el tercer cliente
    strcpy(listaClientes[2].nombre, "Carlos Ruiz");
    strcpy(listaClientes[2].telefono, "83506789");
    listaClientes[2].codigo = generarCodigoAleatorio();
    listaClientes[2].mesesMembresia = (1 << 4) | (1 << 5); 
    listaClientes[2].costoTotal = 2 * COSTO_MES; 
    memset(listaClientes[2].mesPagados, 0, sizeof(listaClientes[2].mesPagados));
    listaClientes[2].mesPagados[4] = 1; 
    listaClientes[2].mesPagados[5] = 1; 
    memset(listaClientes[2].mesesAdicionales, 0, sizeof(listaClientes[2].mesesAdicionales));
    listaClientes[2].numMesesAdicionales = 0;
    listaClientes[2].costoTotalAdicional = 0;
    celu(listaClientes[2].telefono, listaClientes[2].compania);

    totalClientes = 3;
}

//Funcion para mostrar el menu principal del inventario
void menuInventario() {
    char opciones[11][60] = {
    "\t\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF",
    "\t\xB3   INVENTARIO  \xB3",
    "\t\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4",
    "\t\xB3 1. Agregar    \xB3",
    "\t\xB3 2. Buscar     \xB3",
    "\t\xB3 3. Actualizar \xB3",
    "\t\xB3 4. Eliminar   \xB3",
    "\t\xB3 5. Ver        \xB3",
    "\t\xB3 6. Vender     \xB3",
    "\t\xB3 7. Volver     \xB3",
    "\t\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9"
    };
    int opcionSeleccionada;
    
    //Ordernar todas las opciones
    do {

        opcionSeleccionada = navegarOpciones(opciones, 11);

        switch (opcionSeleccionada) {
            case 3:
                agregarProductos();
                break;
            case 4:
                buscarProducto();
                break;
            case 5:
                actualizarProducto();
                break;
            case 6:
                eliminarProducto();
                break;
            case 7:
                verProductos();
                break;
            case 8:
                venderProducto();
                break;
            case 9:
                return;
            default:
                system("cls");
                printf("\n\033[0;0m");
                gotoxy(40, 7);
                parteSuperior();
                gotoxy(40, 8); 
                printf("\xB3         Opcion erronea, intenta de nuevo         \xB3");
                gotoxy(40, 9);
                parteInferior();
                gotoxy(40, 11); 
                system("pause");
        }
    } while (opcionSeleccionada != 9);
}

//Funcion para mostrar el menu principal de los clientes
void menuCliente() {
    //Este arreglo es utilizado para mostrar las opciones del menú en la pantalla. 
    //El ciclo for dentro de la función navegarOpciones recorre este arreglo y presenta cada opción al usuario en la pantalla.
    char opciones[10][60] = {
    "\t\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF",
    "\t\xB3    CLIENTES    \xB3",
    "\t\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4",
    "\t\xB3 1. Agregar     \xB3",
    "\t\xB3 2. Actualizar  \xB3",
    "\t\xB3 3. Buscar      \xB3",
    "\t\xB3 4. Eliminar    \xB3",
    "\t\xB3 5. Ver         \xB3",
    "\t\xB3 6. Volver      \xB3",
    "\t\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9"};
    int opcionSeleccionada;

    do {
        opcionSeleccionada = navegarOpciones(opciones, 10);

        switch (opcionSeleccionada) {
            case 3:
                agregarCliente();
                break;
            case 4:
                actualizarCliente();
                break;
            case 5:
                buscarCliente();
                break;
            case 6:
                eliminarCliente();
                break;
            case 7:
                verClientes();
                break;
            case 8:
                return;
            default:
                system("cls");
                printf("\n\033[0;0m");
                gotoxy(40, 7);
                parteSuperior();
                gotoxy(40, 8); 
                printf("\xB3         Opcion erronea, intenta de nuevo         \xB3");
                gotoxy(40, 9);
                parteInferior();
                gotoxy(40, 11); 
                system("pause");
        }
    } while (opcionSeleccionada != 8);
}

//Funcion para mostrar el menu principal 
void mostrarMenu() {
    //Este arreglo es utilizado para mostrar las opciones del menú en la pantalla. 
    //El ciclo for dentro de la función navegarOpciones recorre este arreglo y presenta cada opción al usuario en la pantalla.
    char opciones[8][60] = {
    "\t\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF",
    "\t\xB3 MENU PRINCIPAL \xB3",
    "\t\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4",
    "\t\xB3 1. Inventario  \xB3",
    "\t\xB3 2. Cliente     \xB3",
    "\t\xB3 3. Creditos    \xB3",
    "\t\xB3 4. Salir       \xB3",
    "\t\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9"};
    int opcionSeleccionada;

    do {
        opcionSeleccionada = navegarOpciones(opciones, 8);

        switch (opcionSeleccionada) {
            case 3:
                menuInventario();
                break;
            case 4:
                menuCliente();
                break;
            case 5:
                presentacion();
                break;
            case 6:
                printf("\n\033[0;0m");
                gotoxy(40, 20);
                printf("Saliendo...");
                gotoxy(40, 21);
                system("pause");
                break;
            default:
                system("cls");
                printf("\n\033[0;0m");
                gotoxy(40, 7);
                parteSuperior();
                gotoxy(40, 8); 
                printf("\xB3         Opcion erronea, intenta de nuevo         \xB3");
                gotoxy(40, 9);
                parteInferior();
                gotoxy(40, 11); 
                system("pause");
        }
    } while (opcionSeleccionada != 6);
}

//Funcion para poder iniciar sesion
int iniciarSesion() {
    char nombre[30], contrasena[30];
    int intentos = 0;
    
    while (intentos < 3) {
        system("cls");
        //Le pide al usuario que ingrese su usuario y contraseña
        gotoxy(40, 7);
        parteSuperior();
        gotoxy(40, 8); 
        printf("\xB3=================INICIO DE SESION=================\xB3");
        gotoxy(40, 9);
        parteMedia();
        gotoxy(40, 10); 
        printf("\xB3          Ingrese el nombre de usuario:           \xB3");
        gotoxy(40, 11);
        parteVacia();
        gotoxy(50, 11); 
        scanf("%s", nombre);
        gotoxy(40, 12);
        parteMedia();
        gotoxy(40, 13); 
        printf("\xB3              Ingrese la contrasena:              \xB3");
        char c;
        int i = 0;
        gotoxy(40, 14);
        parteVacia();
        //Contraseña invisble validada
        gotoxy(55, 14); 
        while (1) {
            c = getch(); 
            if (c == 13) {  
                contrasena[i] = '\0'; 
                break;
            } else if (c == 8) {  
                if (i > 0) {
                    i--;
                    printf("\b \b"); 
                }
            } else if (c >= 32 && c <= 126 && i < 29) {
                contrasena[i] = c;
                printf("*");
                i++;
            }
        }
        gotoxy(40, 15);
        parteMedia();

        // Compara la contra y el user del registro con el de inicio de sesion, devuelve cero si ambas son iguales, indicando que son las correctas.
        if (strcmp(nombre, persona.nombre) == 0 && strcmp(contrasena, persona.contrasena) == 0) {
            gotoxy(40, 16); 
            printf("\xB3             Inicio de sesion exitoso.            \xB3");
            gotoxy(40, 17);
            parteInferior();
            gotoxy(40, 19); 
            system("pause");
            return 1; 
        } else {
            gotoxy(40, 16); 
            printf("\xB3         Usuario o contrasena incorrectos.        \xB3");
            gotoxy(40, 17);
            printf("\xB3               Intentos restantes: %d              \xB3", 2 - intentos);
            gotoxy(40, 18);
            parteInferior();
            intentos++;
            gotoxy(40, 20); 
            system("pause");
        }
    }
    
    gotoxy(40, 23); 
    printf("Se han agotado los intentos. Saliendo...");
    gotoxy(40, 24);
    system("pause");
    return 0;  
}

//Funcion para poder registrar usuario
void registrarUsuario() {
    system("cls");
    gotoxy(40, 7);
    parteSuperior();
    gotoxy(40, 8); 
    printf("\xB3===============REGISTRO DE USUARIO================\xB3");
    gotoxy(40, 9);
    parteMedia();

    // Validación del nombre de usuario
    do {
        gotoxy(40, 10); 
        printf("\xB3           Ingrese un nombre de usuario:          \xB3");
        gotoxy(40, 11);
        parteVacia();
        gotoxy(50, 11);
        fflush(stdin); // Limpiar el buffer
        scanf("%29s", persona.nombre); // Limitar el tamaño del nombre a 29 caracteres (+1 para el terminador nulo)
        if (strlen(persona.nombre) == 0) { // Validar si el nombre está vacío
            gotoxy(40, 12);
            printf("\xB3      El nombre de usuario no puede estar vacío.   \xB3");
        }
    } while (strlen(persona.nombre) == 0); // Repetir mientras el nombre esté vacío

    gotoxy(40, 12);
    parteMedia();

    // Validación de la contraseña
    gotoxy(40, 13); 
    printf("\xB3             Ingrese una contrasena:              \xB3");
    char c;
    int i = 0;
    do {
        i = 0; // Reiniciar el índice en cada intento
        gotoxy(40, 14);
        parteVacia();
        gotoxy(55, 14); 
        while (1) {
            c = getch(); // Captura un carácter de la entrada del usuario sin mostrarlo en pantalla
            if (c == 13) {  // Si el caracter es Enter, se rompe el bucle finalizando la entrada de la contraseña
                break;
            } else if (c == 8) {  // Si el caracter es backspace, se elimina el caracter de la contraseña
                if (i > 0) {
                    i--; 
                    printf("\b \b"); 
                }
            } else if (c >= 32 && c <= 126 && i < 29) { // Si el caracter es imprimible y hay espacio en el arreglo, se añade el caracter a la contraseña y se muestra un '*'
                persona.contrasena[i] = c;
                printf("*");
                i++;
            }
        }
        persona.contrasena[i] = '\0'; // Termina la cadena de la contraseña con un terminador nulo
        if (strlen(persona.contrasena) == 0) { // Validar si la contraseña está vacía
            gotoxy(40, 15);
            printf("\xB3       La contraseña no puede estar vacía.        \xB3");
        }
    } while (strlen(persona.contrasena) == 0); // Repetir mientras la contraseña esté vacía

    gotoxy(40, 15);
    parteMedia();

    gotoxy(40, 16);  
    printf("\xB3         Usuario registrado correctamente.        \xB3");
    gotoxy(40, 17);
    parteInferior();
    gotoxy(40, 19);
    system("pause");
}

int main() {
    srand(time(NULL)); // Esta funcion establece el valor inicial (semilla) para la generacion de numeros aleatorios.

    int duration = 1;
    loadingBarWithLogo(duration); //Muestra la barra de carga.

    cargarProductosIniciales();
    cargarClientesIniciales();

    registrarUsuario();

    if (iniciarSesion()) {
        mostrarMenu();
    }

    return 0; 
}