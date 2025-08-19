#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
//Declaracion de la estructura "libro"
struct libros{
	char titulo[100];
	char autor[50];
	int publicacion;
}libro[100];

///FUNCIONES///
//Funcion ingreso de libros
int ingreso(int cl) {
	printf("\nIngreso de nuevo libro:\n");
	printf("Ingrese el titulo del libro:(Sin espacios) ");
	scanf("%s",libro[cl].titulo);
	printf("Ingrese el Autor de libro:(Sin espacios) ");
	scanf("%s",libro[cl].autor);
	printf("Ingrese el a�o de publicacion del libro: ");
	scanf("%d",&libro[cl].publicacion);
	return cl++;
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
	char tit[100],aut[50]; 
	printf("Como desea buscar el archivo.\n");
	printf("1- Por titulo.");
	printf("2- Por autor.");
	printf("3- Por a�o de publicaci�n.");
	switch(opc){
	case 1:
		printf("Ingrese el titulo del libro:\n");
		scanf("%s",tit);
		btitulo(tit, cl);
		break;
	case 2:
		printf("Ingrese el autor del libro:\n");
		scanf("%s",aut);
		bautor(aut, cl);
		break;
	case 3:
		printf("Ingrese el a�o de publicaci�n del libro:\n");
		scanf("%d",&a);
		bano(a,cl);
	}
}
//funcion para guardar archivo
void guardara (int cl){
	FILE* lib;
	lib=fopen("libros.txt","w");
	if (lib == NULL){
		printf("Error al abrir el archivo.");
	}
	fprintf("\n\n");
	fprintf("Libro N�: %d\n", i);
	fprintf("Titulo: %s\n",libro[i].titulo);
	fprintf("Autor: %s\n",libro[i].autor);
	fprintf("A�o de publicacion: %d\n",libro[i].publicacion);
}

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
			cl = ingreso(cl);//Por cada libro que se ingresa cl (Cantida libros) aumenta 
			break;
		case 2:
			mostrar(cl);//Muestra los libros almacenados
			break;
		case 3:
			buscar(cl);
			break;
		case 4:
			guardara(cl);
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
