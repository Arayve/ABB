#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h> 

#define TAM 5000

void prueba_abb_vacio(){

	printf("\nPRUEBA ABB VACIO\n");

	abb_t* abb_vacio = abb_crear(strcmp, NULL);
	char* clave = "random";

	print_test("Se creó abb_vacio", abb_vacio != NULL);
	print_test("abb_cantidad igual a 0", abb_cantidad(abb_vacio) == 0);
	print_test("abb_borrar devuelve NULL", abb_borrar(abb_vacio, clave) == NULL);
	print_test("abb_obtener devuelve NULL", abb_obtener(abb_vacio, clave) == NULL);
	print_test("abb_pertenece devuelve false", !abb_pertenece(abb_vacio, clave));
	print_test("abb_cantidad igual a 0", abb_cantidad(abb_vacio) == 0);

	abb_destruir(abb_vacio);
}

void prueba_abb_guardar_y_borrar(){

	printf("\nPRUEBA ABB GUARDAR Y BORRAR\n");

	abb_t* abb = abb_crear(strcmp, NULL);
	char* clave = "Arg", *dato = "Messi";

	print_test("Se creó abb", abb != NULL);
	print_test("abb_cantidad igual a 0", abb_cantidad(abb) == 0);
	print_test("Se guardó clave", abb_guardar(abb, clave, dato));
	print_test("abb_cantidad igual a 1", abb_cantidad(abb) == 1);
	print_test("clave pertenece a abb", abb_pertenece(abb, clave));
	print_test("Datos iguales", abb_obtener(abb, clave) == dato);
	print_test("Se borró clave", abb_borrar(abb, clave) == dato);
	print_test("abb_cantidad igual a 0", abb_cantidad(abb) == 0);
	print_test("clave NO pertenece a abb", !abb_pertenece(abb, clave));

	abb_destruir(abb);
}
void prueba_abb_guardar_2_elementos(){

	printf("\nPRUEBA ABB GUARDAR 2 ELEMENTOS\n");

	abb_t* abb = abb_crear(strcmp, NULL);
	char* clave1 = "Arg", *dato1 = "Messi";
	char* clave2 = "Bra", *dato2 = "Hulk";

	print_test("Se creó abb", abb != NULL);
	print_test("abb_cantidad igual a 0", abb_cantidad(abb) == 0);
	print_test("Se guardó clave", abb_guardar(abb, clave1, dato1));
	print_test("abb_cantidad igual a 1", abb_cantidad(abb) == 1);
	print_test("clave pertenece a abb", abb_pertenece(abb, clave1));
	print_test("Se guardó clave", abb_guardar(abb, clave2, dato2));
	print_test("abb_cantidad igual a 2", abb_cantidad(abb) == 2);
	print_test("clave pertenece a abb", abb_pertenece(abb, clave2));

	abb_destruir(abb);
}
void prueba_abb_guardar_varios(){

	printf("\nPRUEBA ABB GUARDAR VARIOS\n");

	abb_t* abb = abb_crear(strcmp, NULL);

	char* clave1 = "Bra", *dato1 = "Hulk";
	char* clave2 = "Esp", *dato2 = "Puyol";
	char* clave3 = "Ing", *dato3 = "Kane";
	char* clave4 = "Chi", *dato4 = "Vidal";
	char* clave5 = "Uru", *dato5 = "Suarez";
	char* clave6 = "Por", *dato6 = "Ronaldo";
	char* clave7 = "Col", *dato7 = "Falcao";
	char* clave8 = "Arg", *dato8 = "Messi", *dato9 = "Di Maria";

	print_test("Se creó abb", abb != NULL);
	print_test("abb_cantidad igual a 0", abb_cantidad(abb) == 0);
	print_test("Se guardó clave1", abb_guardar(abb, clave1, dato1));
	print_test("abb_cantidad igual a 1", abb_cantidad(abb) == 1);
	print_test("Se guardó clave2", abb_guardar(abb, clave2, dato2));
	print_test("abb_cantidad igual a 2", abb_cantidad(abb) == 2);
	print_test("Se guardó clave3", abb_guardar(abb, clave3, dato3));
	print_test("abb_cantidad igual a 3", abb_cantidad(abb) == 3);
	print_test("Se guardó clave4", abb_guardar(abb, clave4, dato4));
	print_test("abb_cantidad igual a 4", abb_cantidad(abb) == 4);
	print_test("Se guardó clave5", abb_guardar(abb, clave5, dato5));
	print_test("abb_cantidad igual a 5", abb_cantidad(abb) == 5);
	print_test("Se guardó clave6", abb_guardar(abb, clave6, dato6));
	print_test("abb_cantidad igual a 6", abb_cantidad(abb) == 6);
	print_test("Se guardó clave7", abb_guardar(abb, clave7, dato7));
	print_test("abb_cantidad igual a 7", abb_cantidad(abb) == 7);
	print_test("Se guardó clave8", abb_guardar(abb, clave8, dato8));
	print_test("abb_cantidad igual a 8", abb_cantidad(abb) == 8);

	print_test("clave3 pertenece a abb", abb_pertenece(abb, clave3));
	print_test("clave8 obtener dato8", abb_obtener(abb, clave8) == dato8);
	print_test("Se borró clave4", abb_borrar(abb, clave4) == dato4);
	print_test("Se cambió clave8", abb_guardar(abb, clave8, dato9));
	print_test("clave8 obtener dato9", abb_obtener(abb, clave8) == dato9);

	abb_destruir(abb);
}/*
void prueba_abb_volumen(){

	printf("PRUEBA ABB VOLUMEN\n");

	abb_t* abb = abb_crear(strcmp, NULL);

	char** claves = malloc(TAM*sizeof(char*));
	unsigned long datos[TAM];

	for(unsigned long i = 0; i < TAM; i++){
		sprintf(claves[i], "%08lu", i);
		datos[i] = i;
		if(!abb_guardar(abb, claves[i], &datos[i])){
			print_test("NO se pudieron guardar todas las claves/datos", false);
		}
	}

	print_test("Se guardaron 5000 elementos", true);

	abb_destruir(abb);
}

void prueba_abb_iter(){

	abb_t* abb = abb_crear(strcmp, NULL);

	printf("\nPRUEBA ABB ITER\n");

	char* clave1 = "Bra", *dato1 = "Hulk";
	char* clave2 = "Esp", *dato2 = "Puyol";
	char* clave3 = "Ing", *dato3 = "Kane";
	char* clave4 = "Chi", *dato4 = "Vidal";
	char* clave5 = "Uru", *dato5 = "Suarez";
	char* clave6 = "Por", *dato6 = "Ronaldo";
	char* clave7 = "Col", *dato7 = "Falcao";
	char* clave8 = "Arg", *dato8 = "Messi";

	print_test("Se creó abb", abb != NULL);

	print_test("Se guardó clave1", abb_guardar(abb, clave1, dato1));
	print_test("Se guardó clave2", abb_guardar(abb, clave2, dato2));
	print_test("Se guardó clave3", abb_guardar(abb, clave3, dato3));
	print_test("Se guardó clave4", abb_guardar(abb, clave4, dato4));
	print_test("Se guardó clave5", abb_guardar(abb, clave5, dato5));
	print_test("Se guardó clave6", abb_guardar(abb, clave6, dato6));
	print_test("Se guardó clave7", abb_guardar(abb, clave7, dato7));
	print_test("Se guardó clave8", abb_guardar(abb, clave8, dato8));

	abb_iter_t* iter = abb_iter_in_crear(abb);

	print_test("Se creó iter", iter != NULL);

	print_test("Ver actual es clave8", strcmp(abb_iter_in_ver_actual(iter), clave8) == 0);
	print_test("Ver actual clave no es el mismo puntero", abb_iter_in_ver_actual(iter) != clave8);
	print_test("Avanzar es true", abb_iter_in_avanzar(iter));
	print_test("Ver actual es clave1", strcmp(abb_iter_in_ver_actual(iter), clave1) == 0);
	print_test("Ver actual clave no es el mismo puntero", abb_iter_in_ver_actual(iter) != clave1);
	print_test("Avanzar es true", abb_iter_in_avanzar(iter));
	print_test("Ver actual es clave4", strcmp(abb_iter_in_ver_actual(iter), clave4) == 0);
	print_test("Ver actual clave no es el mismo puntero", abb_iter_in_ver_actual(iter) != clave4);
	print_test("Avanzar es true", abb_iter_in_avanzar(iter));
	print_test("Ver actual es clave7", strcmp(abb_iter_in_ver_actual(iter), clave7) == 0);
	print_test("Ver actual clave no es el mismo puntero", abb_iter_in_ver_actual(iter) != clave7);
	print_test("Avanzar es true", abb_iter_in_avanzar(iter));
	print_test("Ver actual es clave2", strcmp(abb_iter_in_ver_actual(iter), clave2) == 0);
	print_test("Ver actual clave no es el mismo puntero", abb_iter_in_ver_actual(iter) != clave2);
	print_test("Avanzar es true", abb_iter_in_avanzar(iter));
	print_test("Ver actual es clave3", strcmp(abb_iter_in_ver_actual(iter), clave3) == 0);
	print_test("Ver actual clave no es el mismo puntero", abb_iter_in_ver_actual(iter) != clave3);
	print_test("Avanzar es true", abb_iter_in_avanzar(iter));
	print_test("Ver actual es clave6", strcmp(abb_iter_in_ver_actual(iter), clave6) == 0);
	print_test("Ver actual clave no es el mismo puntero", abb_iter_in_ver_actual(iter) != clave6);
	print_test("Avanzar es true", abb_iter_in_avanzar(iter));
	print_test("Ver actual es clave5", strcmp(abb_iter_in_ver_actual(iter), clave5) == 0);
	print_test("Ver actual clave no es el mismo puntero", abb_iter_in_ver_actual(iter) != clave5);
	print_test("Avanzar es true", abb_iter_in_avanzar(iter));
	print_test("Iter está al final", abb_iter_in_al_final(iter));

	abb_iter_in_destruir(iter);
	abb_destruir(abb);
}

bool imprimir_claves_datos(const char* clave, void* dato, void* extra){

	size_t* contador = extra;

	printf("%lu. Clave: %s\tDato: %s\n",(*contador), clave, (char*)dato);

	(*contador)++;

	return true;
}

void prueba_abb_iter_interno(){

	printf("\nPRUEBA ABB ITER INTERNO\n");

	abb_t* abb = abb_crear(strcmp, NULL);

	print_test("Se creó abb", abb != NULL);

	char* clave1 = "Bra", *dato1 = "Hulk";
	char* clave2 = "Esp", *dato2 = "Puyol";
	char* clave3 = "Ing", *dato3 = "Kane";
	char* clave4 = "Chi", *dato4 = "Vidal";
	char* clave5 = "Uru", *dato5 = "Suarez";
	char* clave6 = "Por", *dato6 = "Ronaldo";
	char* clave7 = "Col", *dato7 = "Falcao";
	char* clave8 = "Arg", *dato8 = "Messi";

	print_test("Se guardó clave1", abb_guardar(abb, clave1, dato1));
	print_test("Se guardó clave2", abb_guardar(abb, clave2, dato2));
	print_test("Se guardó clave3", abb_guardar(abb, clave3, dato3));
	print_test("Se guardó clave4", abb_guardar(abb, clave4, dato4));
	print_test("Se guardó clave5", abb_guardar(abb, clave5, dato5));
	print_test("Se guardó clave6", abb_guardar(abb, clave6, dato6));
	print_test("Se guardó clave7", abb_guardar(abb, clave7, dato7));
	print_test("Se guardó clave8", abb_guardar(abb, clave8, dato8));
	
	printf("\nImprimir claves y datos:\n");

	size_t contador = 1;

	abb_in_order(abb, imprimir_claves_datos, &contador);

	//AGREGAR OTROS CASOS

	abb_destruir(abb);
}
*/
void pruebas_abb_alumno(){
	
	prueba_abb_vacio();
	prueba_abb_guardar_y_borrar();
	prueba_abb_guardar_2_elementos();
	prueba_abb_guardar_varios();
//	prueba_abb_volumen();
//	prueba_abb_iter();
//	prueba_abb_iter_interno();
}