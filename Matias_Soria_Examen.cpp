#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max_titulo 100
#define max_autor 50
#define ARCHIVO_LIBROS "libros.dat"

// Declaración de la estructura "libro"
typedef struct {
    char titulo[max_titulo];
    char autor[max_autor];
    int publicacion;
} Libro;

// Estructura para nodo
typedef struct nodo {
    Libro libro;
    struct nodo* siguiente;
} Nodo;

// Estructura para lista enlazada simple
typedef struct {
    Nodo* cabeza;
    int tamaño;
} ListaLibros;



/// FUNCIONES DE LISTA ///

// Inicialización de la lista
void inicializarLista(ListaLibros* lista) {
    lista->cabeza = NULL;
    lista->tamaño = 0;
}

// Liberar lista de libros
void liberarLista(ListaLibros* lista) {
    Nodo* actual = lista->cabeza;
    Nodo* siguiente;
    
    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    
    lista->cabeza = NULL;
    lista->tamaño = 0;
}

// Función ingreso de libros
void ingreso(ListaLibros* lista) {
    Libro nuevoLibro;
    
    printf("=== INGRESO DE NUEVO LIBRO ===\n");
    printf("Ingrese el titulo del libro: ");
    getchar(); // Consume el \n anterior
    fgets(nuevoLibro.titulo, max_titulo, stdin);
    
    // Remueve el \n del final de la cadena
    size_t len = strlen(nuevoLibro.titulo);
    if (len > 0 && nuevoLibro.titulo[len-1] == '\n') {
        nuevoLibro.titulo[len-1] = '\0';
    }
    if (strlen(nuevoLibro.titulo) == 0) {
        printf("Error: El título no puede estar vacío.\n");
        return;
    }
    
    printf("Ingrese el autor del libro: ");
    fgets(nuevoLibro.autor, max_autor, stdin);
    
    // Remueve el \n del final de la cadena
    len = strlen(nuevoLibro.autor);
    if (len > 0 && nuevoLibro.autor[len-1] == '\n') {
        nuevoLibro.autor[len-1] = '\0';
    }
    if (strlen(nuevoLibro.autor) == 0) {
        printf("Error: El autor no puede estar vacío.\n");
        return;
    }
    
    printf("Ingrese el año de publicación del libro: ");
    if (scanf("%d", &nuevoLibro.publicacion) != 1 || nuevoLibro.publicacion < 0) {
        printf("Error: Debe ingresar un año válido.\n");
        while (getchar() != '\n'); // Limpiar buffer
        return;
    }
    
    // Crear nuevo nodo
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return;
    }
    
    // Copiar el libro al nodo
    nuevoNodo->libro = nuevoLibro;
    nuevoNodo->siguiente = lista->cabeza;
    lista->cabeza = nuevoNodo;
    lista->tamaño++;
    
    printf("Libro agregado exitosamente.\n");
    printf("Título: %s | Autor: %s | Año: %d\n", 
           nuevoLibro.titulo, nuevoLibro.autor, nuevoLibro.publicacion);
}

// Función para mostrar los libros cargados
void mostrar(ListaLibros* lista) {
    if (lista->tamaño == 0) {
        printf("No hay libros en la lista.\n");
        return;
    }
    
    printf("=== LISTA DE LIBROS ===\n");
    Nodo* actual = lista->cabeza;
    int indice = 1;
    
    while (actual != NULL) {
        printf("Libro %d:\n", indice);
        printf("Título: %s\n", actual->libro.titulo);
        printf("Autor: %s\n", actual->libro.autor);
        printf("Año de publicación: %d\n", actual->libro.publicacion);
        printf("-----------------------\n");
        actual = actual->siguiente;
        indice++;
    }
    printf("Total de libros: %d\n", lista->tamaño);
}

/// FUNCIONES DE BÚSQUEDA ///

// Función para buscar por título
void btitulo(ListaLibros* lista, char *tit) {
    Nodo* actual = lista->cabeza;
    int indice = 1;
    int encontrados = 0;
    
    if (lista->tamaño == 0) {
        printf("No hay libros en la lista.\n");
        return;
    }
    
    printf("=== BÚSQUEDA POR TÍTULO: %s ===\n", tit);
    
    while (actual != NULL) {
        if (strcmp(actual->libro.titulo, tit) == 0) {
            printf("Libro %d:\n", indice);
            printf("Título: %s\n", actual->libro.titulo);
            printf("Autor: %s\n", actual->libro.autor);
            printf("Año de publicación: %d\n", actual->libro.publicacion);
            printf("-----------------------\n");
            encontrados++;
        }
        actual = actual->siguiente;
        indice++;
    }
    
    if (encontrados == 0) {
        printf("No se encontraron libros con el título: %s\n", tit);
    } else {
        printf("Se encontraron %d libro(s) con ese título.\n", encontrados);
    }
}

// Función para buscar por autor
void bautor(ListaLibros* lista, char *aut) {
    Nodo* actual = lista->cabeza;
    int indice = 1;
    int encontrados = 0;
    
    if (lista->tamaño == 0) {
        printf("No hay libros en la lista.\n");
        return;
    }
    
    printf("=== BÚSQUEDA POR AUTOR: %s ===\n", aut);
    
    while (actual != NULL) {
        if (strcmp(actual->libro.autor, aut) == 0) {
            printf("Libro %d:\n", indice);
            printf("Título: %s\n", actual->libro.titulo);
            printf("Autor: %s\n", actual->libro.autor);
            printf("Año de publicación: %d\n", actual->libro.publicacion);
            printf("-----------------------\n");
            encontrados++;
        }
        actual = actual->siguiente;
        indice++;
    }
    
    if (encontrados == 0) {
        printf("No se encontraron libros del autor: %s\n", aut);
    } else {
        printf("Se encontraron %d libro(s) de ese autor.\n", encontrados);
    }
}

// Función para buscar por año
void bano(ListaLibros* lista, int a) {
    Nodo* actual = lista->cabeza;
    int encontrados = 0;
    
    if (lista->tamaño == 0) {
        printf("No hay libros en la lista.\n");
        return;
    }
    
    printf("=== BÚSQUEDA POR AÑO: %d ===\n", a);
    
    while (actual != NULL) {
        if (actual->libro.publicacion == a) {
            printf("Título: %s\n", actual->libro.titulo);
            printf("Autor: %s\n", actual->libro.autor);
            printf("Año de publicación: %d\n", actual->libro.publicacion);
            printf("-----------------------\n");
            encontrados++;
        }
        actual = actual->siguiente;
    }
    
    if (encontrados == 0) {
        printf("No hay libros publicados en el año %d.\n", a);
    } else {
        printf("Se encontraron %d libro(s) publicados en ese año.\n", encontrados);
    }
}

// Función para buscar un libro
void buscar(ListaLibros* lista) {
    int opc, a;
    char tit[max_titulo], aut[max_autor];
    
    printf("¿Cómo desea buscar el libro?\n");
    printf("1- Por título\n");
    printf("2- Por autor\n");
    printf("3- Por año de publicación\n");
    printf("Ingrese su opción: ");
    
    if (scanf("%d", &opc) != 1) {
        printf("Error: Opción inválida.\n");
        while (getchar() != '\n');
        return;
    }
    
    switch(opc) {
        case 1:
            printf("Ingrese el titulo del libro:\n");
            getchar(); // Limpiar buffer
            fgets(tit, max_titulo, stdin);
            // Validación de datos de titulo ingresado
            size_t len = strlen(tit);
            if (len > 0 && tit[len-1] == '\n') {
                tit[len-1] = '\0';
            }
            if (strlen(tit) == 0) {
                printf("Error: El título no puede estar vacío.\n");
                return;
            }
            btitulo(lista, tit);
            break;
        case 2:
            printf("Ingrese el autor del libro:\n");
            getchar(); // Limpiar buffer
            fgets(aut, max_autor, stdin);
            // Validación de datos de autor ingresado
            len = strlen(aut);
            if (len > 0 && aut[len-1] == '\n') {
                aut[len-1] = '\0';
            }
            if (strlen(aut) == 0) {
                printf("Error: El autor no puede estar vacío.\n");
                return;
            }
            bautor(lista, aut);
            break;
        case 3:
            printf("Ingrese el año de publicación del libro: ");
            if (scanf("%d", &a) != 1) {
                printf("Error: Debe ingresar un número válido.\n");
                while (getchar() != '\n');
                return;
            }
            if (a < 0) {
                printf("Error: El año no puede ser negativo.\n");
                while (getchar() != '\n');
                return;
            }
            bano(lista, a);
            break;
        default:
            printf("Opción no válida.\n");
            break;
    }
}

// Función para borrar libro
void borrar(ListaLibros* lista) {
    if (lista->cabeza == NULL) {
        printf("Error: No hay libros cargados en el programa.\n");
        return;
    }
    
    char tituloborra[max_titulo];
    
    printf("=== BORRAR LIBRO ===\n");
    printf("Ingrese el titulo del libro a borrar: ");
    getchar(); // Limpiar buffer
    fgets(tituloborra, max_titulo, stdin);
    
    // Validación de datos del titulo ingresado
    size_t len = strlen(tituloborra);
    if (len > 0 && tituloborra[len-1] == '\n') {
        tituloborra[len-1] = '\0';
    }
    if (strlen(tituloborra) == 0) {
        printf("Error: El titulo no puede estar vacío.\n");
        return;
    }
    
    Nodo* actual = lista->cabeza;
    Nodo* anterior = NULL;
    
    // Buscar el libro a borrar
    while (actual != NULL && strcmp(actual->libro.titulo, tituloborra) != 0) {
        anterior = actual;
        actual = actual->siguiente;
    }
    
    // Si no se encontró el libro
    if (actual == NULL) {
        printf("Error: No se encontró ningún libro con el título: %s\n", tituloborra);
        return;
    }
    
    // Actualizar los enlaces
    if (anterior == NULL) {
        // Es el primer nodo
        lista->cabeza = actual->siguiente;
    } else {
        // No es el primer nodo
        anterior->siguiente = actual->siguiente;
    }
    
    printf("Libro borrado exitosamente:\n");
    printf("Título: %s\n", actual->libro.titulo);
    printf("Autor: %s\n", actual->libro.autor);
    printf("Año: %d\n", actual->libro.publicacion);
    
    free(actual);
    lista->tamaño--;
}

/// FUNCIONES DE ARCHIVO ///

// Función para guardar lista en archivo binario
void guardarArchivo(ListaLibros* lista) {
    FILE* archivo = fopen(ARCHIVO_LIBROS, "wb");
    
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo para escritura.\n");
        return;
    }
    
    // Escribir el tamaño de la lista primero
    if (fwrite(&lista->tamaño, sizeof(int), 1, archivo) != 1) {
        printf("Error: No se pudo escribir el tamaño de la lista.\n");
        fclose(archivo);
        return;
    }
    
    // Escribir cada libro
    Nodo* actual = lista->cabeza;
    int escritos = 0;
    
    while (actual != NULL) {
        if (fwrite(&actual->libro, sizeof(Libro), 1, archivo) != 1) {
            printf("Error: No se pudo escribir el libro %d.\n", escritos + 1);
            fclose(archivo);
            return;
        }
        escritos++;
        actual = actual->siguiente;
    }
    
    fclose(archivo);
    printf("Lista guardada exitosamente en %s (%d libros).\n", ARCHIVO_LIBROS, escritos);
}

// Función para cargar lista desde archivo binario
void cargarArchivo(ListaLibros* lista) {
    FILE* archivo = fopen(ARCHIVO_LIBROS, "rb");
    
    if (archivo == NULL) {
        printf("Archivo %s no encontrado. Se iniciará con lista vacía.\n", ARCHIVO_LIBROS);
        return;
    }
    
    int tamaño;
    if (fread(&tamaño, sizeof(int), 1, archivo) != 1) {
        printf("Error: No se pudo leer el tamaño de la lista del archivo.\n");
        fclose(archivo);
        return;
    }
    
    if (tamaño <= 0) {
        printf("El archivo está vacío o es inválido.\n");
        fclose(archivo);
        return;
    }
    
    // Liberar lista actual si tiene datos
    liberarLista(lista);
    
    // Cargar libros
    for (int i = 0; i < tamaño; i++) {
        Libro libroTemp;
        
        if (fread(&libroTemp, sizeof(Libro), 1, archivo) != 1) {
            printf("Error: No se pudo leer el libro %d del archivo.\n", i + 1);
            break;
        }
        
        // Crear nuevo nodo
        Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
        if (nuevoNodo == NULL) {
            printf("Error: No se pudo asignar memoria para el libro %d.\n", i + 1);
            break;
        }
        
        nuevoNodo->libro = libroTemp;
        nuevoNodo->siguiente = lista->cabeza;
        lista->cabeza = nuevoNodo;
        lista->tamaño++;
    }
    
    fclose(archivo);
    printf("Lista cargada exitosamente desde %s (%d libros).\n", ARCHIVO_LIBROS, lista->tamaño);
}

// Función para buscar directamente en archivo
void buscarEnArchivo() {
    FILE* archivo = fopen(ARCHIVO_LIBROS, "rb");
    
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo %s.\n", ARCHIVO_LIBROS);
        return;
    }
    
    int tamaño;
    if (fread(&tamaño, sizeof(int), 1, archivo) != 1) {
        printf("Error: No se pudo leer el archivo.\n");
        fclose(archivo);
        return;
    }
    
    if (tamaño <= 0) {
        printf("El archivo está vacío.\n");
        fclose(archivo);
        return;
    }
    
    int opc;
    printf("¿Cómo desea buscar en el archivo?\n");
    printf("1- Por título\n");
    printf("2- Por autor\n");
    printf("3- Por año de publicación\n");
    printf("Ingrese su opción: ");
    
    if (scanf("%d", &opc) != 1) {
        printf("Error: Opción inválida.\n");
        while (getchar() != '\n');
        fclose(archivo);
        return;
    }
    
    char busqueda[max_titulo];
    int anoBusqueda;
    int encontrados = 0;
    
    switch(opc) {
        case 1: // Búsqueda por título
            printf("Ingrese el título a buscar: ");
            getchar(); // Limpiar buffer
            fgets(busqueda, max_titulo, stdin);
            // Validación
            size_t len = strlen(busqueda);
            if (len > 0 && busqueda[len-1] == '\n') {
                busqueda[len-1] = '\0';
            }
            if (strlen(busqueda) == 0) {
                printf("Error: El título no puede estar vacío.\n");
                fclose(archivo);
                return;
            }
            
            printf("=== BÚSQUEDA EN ARCHIVO POR TÍTULO: %s ===\n", busqueda);
            
            for (int i = 0; i < tamaño; i++) {
                Libro libro;
                if (fread(&libro, sizeof(Libro), 1, archivo) == 1) {
                    if (strcmp(libro.titulo, busqueda) == 0) {
                        printf("Título: %s\n", libro.titulo);
                        printf("Autor: %s\n", libro.autor);
                        printf("Año: %d\n", libro.publicacion);
                        printf("-----------------------\n");
                        encontrados++;
                    }
                }
            }
            break;
            
        case 2: // Búsqueda por autor
            printf("Ingrese el autor a buscar: ");
            getchar(); // Limpiar buffer
            fgets(busqueda, max_autor, stdin);
            // Validación
            len = strlen(busqueda);
            if (len > 0 && busqueda[len-1] == '\n') {
                busqueda[len-1] = '\0';
            }
            if (strlen(busqueda) == 0) {
                printf("Error: El autor no puede estar vacío.\n");
                fclose(archivo);
                return;
            }
            
            printf("=== BÚSQUEDA EN ARCHIVO POR AUTOR: %s ===\n", busqueda);
            
            for (int i = 0; i < tamaño; i++) {
                Libro libro;
                if (fread(&libro, sizeof(Libro), 1, archivo) == 1) {
                    if (strcmp(libro.autor, busqueda) == 0) {
                        printf("Título: %s\n", libro.titulo);
                        printf("Autor: %s\n", libro.autor);
                        printf("Año: %d\n", libro.publicacion);
                        printf("-----------------------\n");
                        encontrados++;
                    }
                }
            }
            break;
            
        case 3: // Búsqueda por año
            printf("Ingrese el año a buscar: ");
            if (scanf("%d", &anoBusqueda) != 1) {
                printf("Error: Debe ingresar un número válido.\n");
                while (getchar() != '\n');
                fclose(archivo);
                return;
            }
            if (anoBusqueda < 0) {
                printf("Error: El año no puede ser negativo.\n");
                while (getchar() != '\n');
                fclose(archivo);
                return;
            }
            
            printf("=== BÚSQUEDA EN ARCHIVO POR AÑO: %d ===\n", anoBusqueda);
            
            for (int i = 0; i < tamaño; i++) {
                Libro libro;
                if (fread(&libro, sizeof(Libro), 1, archivo) == 1) {
                    if (libro.publicacion == anoBusqueda) {
                        printf("Título: %s\n", libro.titulo);
                        printf("Autor: %s\n", libro.autor);
                        printf("Año: %d\n", libro.publicacion);
                        printf("-----------------------\n");
                        encontrados++;
                    }
                }
            }
            break;
            
        default:
            printf("Opción no válida.\n");
            fclose(archivo);
            return;
    }
    
    fclose(archivo);
    
    if (encontrados == 0) {
        printf("No se encontraron coincidencias en el archivo.\n");
    } else {
        printf("Se encontraron %d coincidencia(s) en el archivo.\n", encontrados);
    }
}

/// FUNCIÓN PRINCIPAL ///
int main(int argc, char *argv[]) {
    ListaLibros lista;
    inicializarLista(&lista);
    
    // Cargar datos del archivo al iniciar
    cargarArchivo(&lista);
    
    int op;
    
    do {
        printf("\n=== SISTEMA DE GESTIÓN DE LIBROS ===\n");
        printf("1- Ingresar un nuevo libro\n");
        printf("2- Mostrar libros en memoria\n");
        printf("3- Buscar libro en memoria\n");
        printf("4- Borrar libro de memoria\n");
        printf("5- Guardar lista en archivo\n");
        printf("6- Cargar lista desde archivo\n");
        printf("7- Buscar libro en archivo\n");
        printf("8- Salir\n");
        printf("Ingrese una opción: ");
        
        if (scanf("%d", &op) != 1) {
            printf("Error: Ingrese un número válido.\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch(op) {
            case 1:
                ingreso(&lista);
                break;
            case 2:
                mostrar(&lista);
                break;
            case 3:
                buscar(&lista);
                break;
            case 4:
                borrar(&lista);
                break;
            case 5:
                guardarArchivo(&lista);
                break;
            case 6:
                cargarArchivo(&lista);
                break;
            case 7:
                buscarEnArchivo();
                break;
            case 8:
                printf("¿Desea guardar los cambios antes de salir? (s/n): ");
                char respuesta;
                scanf(" %c", &respuesta);
                if (respuesta == 's' || respuesta == 'S') {
                    guardarArchivo(&lista);
                }
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Ingrese un número válido (1-8).\n");
                break;
        }
    } while(op != 8);
    
    // Liberar memoria antes de salir
    liberarLista(&lista);
    
    return 0;
}