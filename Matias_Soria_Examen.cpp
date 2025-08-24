#include <stdio.h>
#include <iostream>
#include <string.h>
#define max_titulo 100
#define max_autor 50	
using namespace std;
//Declaracion de la estructura "libro"
typedef struct{
	char titulo[max_titulo];
	char autor[max_autor];
	int publicacion;
}Libro;
//Estructura para nodo
typedef struct nodo {
    Libro libro;
    struct nodo* siguiente;
} Nodo;
//estructura para lista enlazada simple
typedef struct {
	Nodo* cabeza;
	int tamaño;
} ListaLibros;

///FUNCIONES///
//Inilicializacion de la lista
void inicializarLista(ListaLibros* lista) {
	lista->cabeza = NULL;
	lista->tamaño = 0;
}
//liberar lista de libros
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
//Funcion ingreso de libros
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
			nuevoLibro.titulo, 
			nuevoLibro.autor, 
			nuevoLibro.publicacion);
}
//funcion para mostrar los libros cargados
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
}
// funcion para buscar por titulo
void btitulo(ListaLibros* lista,char *tit){
	Nodo* actual = lista->cabeza;
	int indice = 1;
	int encontrados = 0;
	if (lista->tamaño == 0) {
		printf("No hay libros en la lista.\n");
		return;
	}
	while (actual != NULL ){
		if (actual->libro.titulo == tit) 
		{
		printf("Libro %d:\n", indice);
		printf("Título: %s\n", actual->libro.titulo);
		printf("Autor: %s\n", actual->libro.autor);
		printf("Año de publicación: %d\n", actual->libro.publicacion);
		printf("-----------------------\n\n");

		}
		actual = actual->siguiente;
		indice++;
	}
	if(encontrados == 0 ){
		printf("El Titulo del libro ingresado no corresponde a un libro registrado.\n\n\n");
	}
}
//funcion para buscar por autor
void bautor(ListaLibros* lista,char *aut){
	Nodo* actual = lista->cabeza;
	int indice = 1;
	int encontrados = 0;
	if (lista->tamaño == 0) {
		printf("No hay libros en la lista.\n");
		return;
	}
	while (actual != NULL ){
		if (actual->libro.autor == aut){
			printf("Libro %d:\n", indice);
			printf("Título: %s\n", actual->libro.titulo);
			printf("Autor: %s\n", actual->libro.autor);
			printf("Año de publicación: %d\n", actual->libro.publicacion);
			printf("-----------------------\n\n");
		}
		actual = actual->siguiente;
		indice++;
	}
	if(encontrados == 0 ){
		printf("El Autor ingresado no contiene ningun libro cargado.\n\n\n");
	}
}
//funcion para buscar por ano
void bano(ListaLibros* lista,int a){
	Nodo* actual = lista->cabeza;
	if(lista->tamaño == 0) {
		printf("No hay libros en la lista.\n");
		return;
	}
	int encontrados = 0;
	while (actual != NULL ){
		if (actual->libro.publicacion == a){
			printf("Título: %s\n", actual->libro.titulo);
			printf("Autor: %s\n", actual->libro.autor);
			printf("Año de publicación: %d\n", actual->libro.publicacion);
			printf("-----------------------\n\n");
			encontrados++;
		}
		actual = actual->siguiente;
	}
	if (encontrados == 0) {
		printf("No hay libros publicados en ese año en la lista.\n\n");
	}
}
//funcion para buscar un libro 
void buscar(ListaLibros* lista){
	int opc,a;
	char tit[max_titulo],aut[max_autor]; 
	printf("Como desea buscar el archivo.\n");
	printf("1- Por titulo.");
	printf("2- Por autor.");
	printf("3- Por año de publicación.");
	switch(opc){
	case 1:
		printf("Ingrese el titulo del libro:\n");
		fgets(tit,max_titulo, stdin);
    	//Validación de datos de titulo ingresado
		size_t len = strlen(tit);
    	if (len > 0 && tit[len-1] == '\n') {
        	tit[len-1] = '\0';
    	}
    	if (strlen(tit) == 0) {
        	printf("Error: La etiqueta no puede estar vacía.\n");
        return;
    	}
		btitulo(lista , tit);
		break;
	case 2:
		printf("Ingrese el autor del libro:\n");
		fgets(aut,max_autor, stdin);
    	//Validación de datos de autor ingresado
		size_t len = strlen(aut);
    	if (len > 0 && aut[len-1] == '\n') {
        	aut[len-1] = '\0';
    	}
    	if (strlen(aut) == 0) {
        	printf("Error: La etiqueta no puede estar vacía.\n");
        return;
    	}
		bautor(lista,aut);
		break;
	case 3:
		printf("Ingrese el a�o de publicaci�n del libro:\n");
		printf("Ingrese el año de publicacion del libro: ");
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
		bano(lista,a);
	}
}
//funcion para guardar archivo
/*void guardara (int cl){
	FILE* lib;
	lib=fopen("libros.txt","w");
	if (lib == NULL){
		printf("Error al abrir el archivo.");
	}
	fprintf("\n\n");
	fprintf("Libro N°: %d\n", i);
	fprintf("Titulo: %s\n",libro[i].titulo);
	fprintf("Autor: %s\n",libro[i].autor);
	fprintf("Año de publicacion: %d\n",libro[i].publicacion);
}
*/
//FUNCION PRINCIPAL
int main(int argc, char *argv[]) {
	ListaLibros lista;
	inicializarLista(&lista);
	int op;
	int ban=0;
	int cl=0;
	do{
		printf("\n\nIngrese una opcion:\n");
		printf("1-Ingresar un nuevo libro.\n");
		printf("2-Mostrar libros.\n");
		printf("3-Buscar libro.\n");
		printf("4-Salir.\n");
		scanf("%d",&op);
		switch(op){
		case 1:
			ingreso(&lista);//Por cada libro que se ingresa cl (Cantida libros) aumenta 
			break;
		case 2:
			mostrar(&lista);//Muestra los libros almacenados
			break;
		case 3:
			buscar(&lista);//Busca un libro por titulo, autor o año de publicación
			break;
		case 4:
			//guardara(cl);
			break;
		case 5:
			printf("Saliendo....\n");
			break;
		default:
			printf("Ingrese un numero valido....\n");
			break;
		};
	} while(op!=5);
	return 0;
}