#include <stdio.h>
#include <iostream>
#include <string.h>
#define max_titulo 100
#define max_autor 50	
using namespace std;
//Declaracion de la estructura "libro"
struct libros{
	char titulo[max_titulo];
	char autor[max_autor];
	int publicacion;
}libro[100];

///FUNCIONES///
//Funcion ingreso de libros
void ingreso(int* cl) {
	printf("\nIngreso de nuevo libro:\n");
	printf("Ingrese el titulo del libro:");
	fgets(libro[*cl].titulo,max_titulo, stdin);
    //Validación de datos de titulo ingresado
	size_t len = strlen(libro[*cl].titulo);
    if (len > 0 && libro[*cl].titulo[len-1] == '\n') {
        libro[*cl].titulo[len-1] = '\0';
    }
    if (strlen(libro[*cl].titulo) == 0) {
        printf("Error: La etiqueta no puede estar vacía.\n");
        return;
    }

	printf("Ingrese el autor del libro:");
	fgets(libro[*cl].autor,max_autor, stdin);
    //Validación de datos de autor ingresado
	size_t len = strlen(libro[*cl].autor);
    if (len > 0 && libro[*cl].autor[len-1] == '\n') {
        libro[*cl].autor[len-1] = '\0';
    }
    if (strlen(libro[*cl].autor) == 0) {
        printf("Error: La etiqueta no puede estar vacía.\n");
        return;
    }

	printf("Ingrese el año de publicacion del libro: ");
 	if (scanf("%d", &libro[*cl].publicacion) != 1) {
        printf("Error: Debe ingresar un número válido.\n");
        while (getchar() != '\n');
        return;
    }
	if (libro[*cl].publicacion < 0) {
        printf("Error: El año no puede ser negativo.\n");
        while (getchar() != '\n');
        return;
    }
	*cl++;
}
//funcion para mostrar los libros cargados
void mostrar(int cl){
	int i;
	printf("\n\n");
	for(i=0;i<cl;i++){
		printf("Libro N�: %d\n", i);
		printf("Titulo: %s\n",libro[i].titulo);
		printf("Autor: %s\n",libro[i].autor);
		printf("A�o de publicacion: %d\n",libro[i].publicacion);
	}
}
// funcion para buscar por titulo
void btitulo(char *tit, int cl){
	int i,ba=0,cmp;
	for(i=0;i<cl;i++){
		cmp=strcmp(tit,libro[i].titulo);
		if(cmp==0){
			ba=1;
			printf("Libro N�: %d\n", i);
			printf("Titulo: %s\n",libro[i].titulo);
			printf("Autor: %s\n",libro[i].autor);
			printf("A�o de publicacion: %d\n",libro[i].publicacion);
		}
	}
	if(ba==0){
		printf("El titulo del libro no se encuentra en la lista.");
	}
}
//funcion para buscar por autor
void bautor(char *aut, int cl){
	int i,ba=0,cmp;
	for(i=0;i<cl;i++){
		cmp=strcmp(aut,libro[i].autor);
		if(cmp==0){
			ba=1;
			printf("\n\n");
			printf("Libro N�: %d\n", i);
			printf("Titulo: %s\n",libro[i].titulo);
			printf("Autor: %s\n",libro[i].autor);
			printf("A�o de publicacion: %d\n",libro[i].publicacion);
		}
	}
	if(ba==0){
		printf("El Autor no posee libros en la lista.\n\n");
	}
}
//funcion para buscar por ano
void bano(int a, int cl){
	int i,ba=0,cmp;
	for(i=0;i<cl;i++){
		if(a==libro[i].publicacion){
			ba=1;
			printf("\n\n");
			printf("Libro N�: %d\n", i);
			printf("Titulo: %s\n",libro[i].titulo);
			printf("Autor: %s\n",libro[i].autor);
			printf("A�o de publicacion: %d\n",libro[i].publicacion);
		}
	}
	if(ba==0){
		printf("No hay libros publicados en ese a�o en la lista.\n\n");
	}
}
//funcion para buscar un libro 
void buscar(int cl){
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
		btitulo(tit, cl);
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
		bautor(aut, cl);
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
		bano(a,cl);
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
			ingreso(&cl);//Por cada libro que se ingresa cl (Cantida libros) aumenta 
			break;
		case 2:
			mostrar(cl);//Muestra los libros almacenados
			break;
		case 3:
			buscar(cl);
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
