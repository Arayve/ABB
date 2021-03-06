#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#define TAM_CLAVE 21

bool clave_repetida(char* clave, char** claves, size_t n){

	for(size_t i = 0; i < n; i++){
		if(strcmp(clave, claves[i]) == 0) return true;
	}

	return false;
}

char* generador_de_claves(size_t n, char** claves){

	char* clave = malloc(TAM_CLAVE*sizeof(char));

	if(!clave) return "random";

	char* letras_minus = "abcdefghijklmnopqrstuvwxyz";
	char* letras_mayus = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for(size_t i = 0; i < TAM_CLAVE-1; i++){
		if(((i+n)%3) == 0){
			clave[i] = letras_minus[rand()%26];
		}else{
			clave[i] = letras_mayus[rand()%26];
		}
	}

	clave[TAM_CLAVE-1] = '\0';

	return clave;
}

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

void prueba_abb_guardar_y_borrar_2(){

	printf("\nPRUEBA ABB GUARDAR Y BORRAR 2\n");

	abb_t* abb = abb_crear(strcmp, NULL);

	char* clave1 = "1", *dato1 = "Arg";
	char* clave2 = "2", *dato2 = "Bra";
	char* clave3 = "5", *dato3 = "Uru";
	char* clave4 = "3", *dato4 = "Per";
	char* clave5 = "4", *dato5 = "Col";

	print_test("Se guardó clave1 (1)", abb_guardar(abb, clave1, dato1));
	print_test("Se guardó clave2 (2)", abb_guardar(abb, clave2, dato2));
	print_test("Se guardó clave3 (5)", abb_guardar(abb, clave3, dato3));
	print_test("Se guardó clave4 (3)", abb_guardar(abb, clave4, dato4));
	print_test("Se guardó clave5 (4)", abb_guardar(abb, clave5, dato5));

	print_test("Se borró clave1 (1)", abb_borrar(abb, clave1) == dato1);
	print_test("Se borró clave2 (2)", abb_borrar(abb, clave2) == dato2);
	print_test("Se borró clave4 (3)", abb_borrar(abb, clave4) == dato4);
	print_test("Se borró clave5 (4)", abb_borrar(abb, clave5) == dato5);
	print_test("Se borró clave3 (5)", abb_borrar(abb, clave3) == dato3);

	abb_destruir(abb);

	printf("\n");

	abb = abb_crear(strcmp, NULL);

	print_test("Se guardó clave1 (1)", abb_guardar(abb, clave1, dato1));
	print_test("Se guardó clave2 (2)", abb_guardar(abb, clave2, dato2));
	print_test("Se guardó clave3 (5)", abb_guardar(abb, clave3, dato3));
	print_test("Se guardó clave5 (4)", abb_guardar(abb, clave5, dato5));
	print_test("Se guardó clave4 (3)", abb_guardar(abb, clave4, dato4));

	print_test("Se borró clave1 (1)", abb_borrar(abb, clave1) == dato1);
	print_test("Se borró clave2 (2)", abb_borrar(abb, clave2) == dato2);
	print_test("Se borró clave4 (3)", abb_borrar(abb, clave4) == dato4);
	print_test("Se borró clave5 (4)", abb_borrar(abb, clave5) == dato5);
	print_test("Se borró clave3 (5)", abb_borrar(abb, clave3) == dato3);

	abb_destruir(abb);

	printf("\n");

	abb = abb_crear(strcmp, NULL);

	print_test("Se guardó clave2 (2)", abb_guardar(abb, clave2, dato2));
	print_test("Se guardó clave1 (1)", abb_guardar(abb, clave1, dato1));
	print_test("Se guardó clave3 (5)", abb_guardar(abb, clave3, dato3));
	print_test("Se guardó clave4 (3)", abb_guardar(abb, clave4, dato4));
	print_test("Se guardó clave5 (4)", abb_guardar(abb, clave5, dato5));
	
	print_test("Se borró clave2 (2)", abb_borrar(abb, clave2) == dato2);
	print_test("Se borró clave1 (1)", abb_borrar(abb, clave1) == dato1);
	print_test("Se borró clave4 (3)", abb_borrar(abb, clave4) == dato4);
	print_test("Se borró clave5 (4)", abb_borrar(abb, clave5) == dato5);
	print_test("Se borró clave3 (5)", abb_borrar(abb, clave3) == dato3);

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
void prueba_abb_guardar_3_elementos(){
	printf("\nPRUEBA ABB GUARDAR 3 ELEMENTOS\n");

	abb_t* abb = abb_crear(strcmp, NULL);
	char* clave1 = "Bra", *dato1 = "Hulk";
	char* clave2 = "Arg", *dato2 = "Messi";
	char* clave3 = "Chi", *dato3 = "Vidal";

	print_test("Se creó abb", abb != NULL);
	print_test("abb_cantidad igual a 0", abb_cantidad(abb) == 0);
	print_test("Se guardó clave", abb_guardar(abb, clave1, dato1));
	print_test("abb_cantidad igual a 1", abb_cantidad(abb) == 1);
	print_test("clave pertenece a abb", abb_pertenece(abb, clave1));
	print_test("Se guardó clave", abb_guardar(abb, clave2, dato2));
	print_test("abb_cantidad igual a 2", abb_cantidad(abb) == 2);
	print_test("clave pertenece a abb", abb_pertenece(abb, clave2));
	print_test("Se guardó clave", abb_guardar(abb, clave3, dato3));
	print_test("abb_cantidad igual a 3", abb_cantidad(abb) == 3);
	print_test("clave pertenece a abb", abb_pertenece(abb, clave3));

	print_test("Se borró clave1", abb_borrar(abb, clave1) == dato1);
	print_test("clave no pertenece a abb", !abb_pertenece(abb, clave1));
	print_test("abb_cantidad igual a 2", abb_cantidad(abb) == 2);

	abb_destruir(abb);
}
void prueba_abb_guardar_5_elementos_part1(){
	printf("\nPRUEBA ABB GUARDAR 5 ELEMENTOS\n");

	abb_t* abb = abb_crear(strcmp, NULL);
	char* clave1 = "Arg", *dato1 = "Messi";
	char* clave2 = "Bra", *dato2 = "Hulk";
	char* clave3 = "Chi", *dato3 = "Vidal";
	char* clave4 = "Ecu", *dato4 = "Valencia";
	char* clave5 = "Din", *dato5 = "Eriksen";
	
	print_test("Se creó abb", abb != NULL);
	
	print_test("Se guardó clave", abb_guardar(abb, clave1, dato1));
	print_test("Se guardó clave", abb_guardar(abb, clave2, dato2));
	print_test("Se guardó clave", abb_guardar(abb, clave3, dato3));
	print_test("Se guardó clave", abb_guardar(abb, clave4, dato4));
	print_test("Se guardó clave", abb_guardar(abb, clave5, dato5));
	print_test("Se borró clave1", abb_borrar(abb, clave1) == dato1);
	print_test("Se borró clave2", abb_borrar(abb, clave2) == dato2);
	print_test("Se borró clave3", abb_borrar(abb, clave3) == dato3);
	print_test("Se borró clave5", abb_borrar(abb, clave5) == dato5);

	abb_destruir(abb);

}
void prueba_abb_guardar_5_elementos_part2(){
	printf("\nPRUEBA ABB GUARDAR 5 ELEMENTOS PARTE 2\n");

	abb_t* abb = abb_crear(strcmp, NULL);
	char* clave1 = "Arg", *dato1 = "Messi";
	char* clave2 = "Bra", *dato2 = "Hulk";
	char* clave3 = "Din", *dato3 = "Eriksen";
	char* clave4 = "Chi", *dato4 = "Vidal";
	char* clave5 = "Ecu", *dato5 = "Valencia";

	print_test("Se guardó clave", abb_guardar(abb, clave1, dato1));
	print_test("Se guardó clave", abb_guardar(abb, clave2, dato2));
	print_test("Se guardó clave", abb_guardar(abb, clave3, dato3));
	print_test("Se guardó clave", abb_guardar(abb, clave4, dato4));
	print_test("Se guardó clave", abb_guardar(abb, clave5, dato5));
	print_test("Se borró clave1", abb_borrar(abb, clave1) == dato1);
	print_test("Se borró clave2", abb_borrar(abb, clave2) == dato2);
	print_test("Se borró clave4", abb_borrar(abb, clave4) == dato4);

	abb_destruir(abb);
}
void prueba_abb_guardar_5_elementos_part3(){
	printf("\nPRUEBA ABB GUARDAR 5 ELEMENTOS PARTE 3\n");

	abb_t* abb = abb_crear(strcmp, NULL);
	char* clave1 = "Arg", *dato1 = "Messi";
	char* clave2 = "Bra", *dato2 = "Hulk";
	char* clave3 = "Din", *dato3 = "Eriksen";
	char* clave4 = "Chi", *dato4 = "Vidal";
	char* clave5 = "Ecu", *dato5 = "Valencia";
	print_test("Se guardó clave", abb_guardar(abb, clave1, dato1));
	print_test("Se guardó clave", abb_guardar(abb, clave2, dato2));
	print_test("Se guardó clave", abb_guardar(abb, clave3, dato3));
	print_test("Se guardó clave", abb_guardar(abb, clave4, dato4));
	print_test("Se guardó clave", abb_guardar(abb, clave5, dato5));
	
	print_test("Se borró clave1", abb_borrar(abb, clave1) == dato1);
	print_test("Se borró clave2", abb_borrar(abb, clave2) == dato2);
	print_test("Se borró clave4", abb_borrar(abb, clave4) == dato4);
	print_test("Se borró clave5", abb_borrar(abb, clave5) == dato5);

	abb_destruir(abb);
}
void prueba_abb_guardar_5_elementos_part4(){

	printf("\nPRUEBA ABB GUARDAR 5 ELEMENTOS PARTE 4\n");
	abb_t* abb = abb_crear(strcmp, NULL);
	char* clave1 = "A", *dato1 = "a";
	char* clave2 = "B", *dato2 = "b";
	char* clave3 = "C", *dato3 = "c";
	char* clave4 = "D", *dato4 = "d";
	char* clave5 = "E", *dato5 = "e";

	print_test("Se guardó clave", abb_guardar(abb, clave1, dato1));
	print_test("Se guardó clave", abb_guardar(abb, clave2, dato2));
	print_test("Se guardó clave", abb_guardar(abb, clave5, dato5));
	print_test("Se guardó clave", abb_guardar(abb, clave3, dato3));
	print_test("Se guardó clave", abb_guardar(abb, clave4, dato4));

	print_test("Se borró clave1", abb_borrar(abb, clave5) == dato5);
	print_test("Se borró clave2", abb_borrar(abb, clave1) == dato1);
	print_test("Se borró clave3", abb_borrar(abb, clave2) == dato2);
	print_test("Se borró clave4", abb_borrar(abb, clave3) == dato3);

	abb_destruir(abb);
}	
void prueba_abb_guardar_8_elementos(){

	printf("\nPRUEBA ABB GUARDAR 8 ELEMENTOS\n");

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
	print_test("Se borró clave5", abb_borrar(abb, clave5) == dato5);

	abb_destruir(abb);
}
void prueba_abb_guardar_11_elementos(){

	printf("\nPRUEBA ABB GUARDAR 11 ELEMENTOS\n");
	abb_t* abb = abb_crear(strcmp, NULL);

	char* clave1 = "Ger", *dato1 = "Kroos";
	char* clave2 = "Bra", *dato2 = "Hulk";
	char* clave3 = "Esp", *dato3 = "Puyol";
	char* clave4 = "Ing", *dato4 = "Kane";
	char* clave5 = "Chi", *dato5 = "Vidal";
	char* clave6 = "Uru", *dato6 = "Suarez", *dato6_1 = "Cavani";
	char* clave7 = "Por", *dato7 = "Ronaldo";
	char* clave8 = "Col", *dato8 = "Falcao";
	char* clave9 = "Arg", *dato9 = "Messi", *dato9_1 = "Di Maria";
	char* clave10 = "Fra", *dato10 = "Griezmann";
	char* clave11 = "Jpn", *dato11 = "Oliver Atom";

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

	print_test("Se guardó clave6", abb_guardar(abb, clave6, dato6_1));
	print_test("abb_cantidad igual a 6", abb_cantidad(abb) == 6);
	print_test("clave8 obtener dato6_1", abb_obtener(abb, clave6) == dato6_1);

	print_test("Se guardó clave7", abb_guardar(abb, clave7, dato7));
	print_test("abb_cantidad igual a 7", abb_cantidad(abb) == 7);
	print_test("Se guardó clave8", abb_guardar(abb, clave8, dato8));
	print_test("abb_cantidad igual a 8", abb_cantidad(abb) == 8);
	print_test("Se guardó clave9", abb_guardar(abb, clave9, dato9));
	print_test("abb_cantidad igual a 9", abb_cantidad(abb) == 9);
	print_test("Se guardó clave10", abb_guardar(abb, clave10, dato10));
	print_test("abb_cantidad igual a 10", abb_cantidad(abb) == 10);

	print_test("Se borró clave6", abb_borrar(abb, clave6) == dato6_1);

	print_test("Se guardó clave11", abb_guardar(abb, clave11, dato11));
	print_test("abb_cantidad igual a 10", abb_cantidad(abb) == 10);
	print_test("Se guardó clave9", abb_guardar(abb, clave9, dato9_1));
	print_test("abb_cantidad igual a 10", abb_cantidad(abb) == 10);
	print_test("No se puede obtener clave6, por que no existe ", !abb_obtener(abb, clave6));

	abb_destruir(abb);
}
void prueba_abb_guardar_20_elementos(){

	printf("\nPRUEBA ABB GUARDAR 20 ELEMENTOS\n");
	abb_t* abb = abb_crear(strcmp, NULL);
	
	char* clave1 = "Nigeria", *dato1 = "Abuya";
	char* clave2 = "Peru", *dato2 = "Lima";
	char* clave3 = "Alemania", *dato3 = "Berlin";
	char* clave4 = "Francia", *dato4 = "Paris";
	char* clave5 = "España", *dato5 = "Madrid";
	char* clave6 = "Bolivia", *dato6 = "La Paz";
	char* clave7 = "Paraguay", *dato7 = "Asuncion";
	char* clave8 = "Uruguay", *dato8 = "Montevideo";
	char* clave9 = "Argentina", *dato9 = "Buenos aires";
	char* clave10 = "Rusia", *dato10 = "Moscu";
	char* clave11 = "Brazil", *dato11 = "Brazilia";
	char* clave12 = "Ecuador", *dato12 = "Quito";
	char* clave13 = "Venezuela", *dato13 = "Caracas";
	char* clave14 = "Colombia", *dato14 = "Bogota";
	char* clave15 = "China", *dato15 = "Pekin";
	char* clave16 = "Israel", *dato16 = "Jerusalen";
	char* clave17 = "Japon", *dato17 = "Tokio";
	char* clave18 = "Salvador", *dato18 = "Salvador";
	char* clave19 = "Ucrania", *dato19 = "Kiev";
	char* clave20 = "Pakistan", *dato20 = "Kabul";

	print_test("Se guardó clave1", abb_guardar(abb, clave1, dato1));
	print_test("Se guardó clave2", abb_guardar(abb, clave2, dato2));
	print_test("Se guardó clave3", abb_guardar(abb, clave3, dato3));
	print_test("Se guardó clave4", abb_guardar(abb, clave4, dato4));
	print_test("Se guardó clave5", abb_guardar(abb, clave5, dato5));
	print_test("Se guardó clave6", abb_guardar(abb, clave6, dato6));
	print_test("Se guardó clave7", abb_guardar(abb, clave7, dato7));
	print_test("Se guardó clave8", abb_guardar(abb, clave8, dato8));
	print_test("Se guardó clave9", abb_guardar(abb, clave9, dato9));
	print_test("Se guardó clave10", abb_guardar(abb, clave10, dato10));
	print_test("Se guardó clave11", abb_guardar(abb, clave11, dato11));
	print_test("Se guardó clave12", abb_guardar(abb, clave12, dato12));
	print_test("Se guardó clave13", abb_guardar(abb, clave13, dato13));
	print_test("Se guardó clave14", abb_guardar(abb, clave14, dato14));
	print_test("Se guardó clave15", abb_guardar(abb, clave15, dato15));
	print_test("Se guardó clave16", abb_guardar(abb, clave16, dato16));
	print_test("Se guardó clave17", abb_guardar(abb, clave17, dato17));
	print_test("Se guardó clave18", abb_guardar(abb, clave18, dato18));
	print_test("Se guardó clave19", abb_guardar(abb, clave19, dato19));
	print_test("Se guardó clave20", abb_guardar(abb, clave20, dato20));

	print_test("Se borró clave12", abb_borrar(abb, clave12) == dato12);
	print_test("Se borró clave17", abb_borrar(abb, clave17) == dato17);
	print_test("No se puede obtener clave12, por que no existe ", !abb_obtener(abb, clave12));
	print_test("No se puede obtener clave17, por que no existe ", !abb_obtener(abb, clave17));
	print_test("No  pertenece clave12", !abb_pertenece(abb,clave12));
	print_test("No  pertenece clave17", !abb_pertenece(abb,clave17));
	print_test("abb_cantidad igual a 18", abb_cantidad(abb) == 18);

	print_test("clave1 obtener dato1", abb_obtener(abb, clave1) == dato1);
	print_test("clave2 obtener dato2", abb_obtener(abb, clave2) == dato2);
	print_test("clave3 obtener dato3", abb_obtener(abb, clave3) == dato3);
	print_test("clave4 obtener dato4", abb_obtener(abb, clave4) == dato4);
	print_test("clave5 obtener dato5", abb_obtener(abb, clave5) == dato5);
	print_test("clave6 obtener dato6", abb_obtener(abb, clave6) == dato6);
	print_test("clave7 obtener dato7", abb_obtener(abb, clave7) == dato7);
	print_test("clave8 obtener dato8", abb_obtener(abb, clave8) == dato8);
	print_test("clave9 obtener dato9", abb_obtener(abb, clave9) == dato9);
	print_test("clave10 obtener dato10", abb_obtener(abb, clave10) == dato10);
	print_test("clave11 obtener dato11", abb_obtener(abb, clave11) == dato11);
	print_test("clave13 obtener dato13", abb_obtener(abb, clave13) == dato13);
	print_test("clave14 obtener dato14", abb_obtener(abb, clave14) == dato14);
	print_test("clave15 obtener dato15", abb_obtener(abb, clave15) == dato15);
	print_test("clave16 obtener dato16", abb_obtener(abb, clave16) == dato16);
	print_test("clave18 obtener dato18", abb_obtener(abb, clave18) == dato18);
	print_test("clave19 obtener dato19", abb_obtener(abb, clave19) == dato19);
	print_test("clave20 obtener dato20", abb_obtener(abb, clave20) == dato20);
	
	abb_destruir(abb);
}

void liberar_claves(char** claves, const size_t max){

	for(size_t i = 0; i < max; i++) free(claves[i]);

	free(claves);
}

int buscar_clave(char** claves, const char* clave_buscada, size_t max){

	for(int i = 0; i < max; i++){
		if(strcmp(claves[i], clave_buscada) == 0) return i;
	}

	return -1;
}

void prueba_abb_volumen(const size_t max){

	printf("\nPRUEBA ABB GUARDAR VOLUMEN\n");

	abb_t* abb = abb_crear(strcmp, NULL);

	char** claves = malloc(max*sizeof(char*));

	if(!claves) return;

	for(size_t i = 0; i < max; i++){
		claves[i] = generador_de_claves(i, claves);
		abb_guardar(abb, claves[i], &i);
		if(!(abb_cantidad(abb) == i+1)) break;
	}

	print_test("Prueba de volumen", abb_cantidad(abb) == max);

	abb_iter_t* iter = abb_iter_in_crear(abb);

	const char* clave_actual;
	int indice = 0;

	clave_actual = abb_iter_in_ver_actual(iter);
	indice = buscar_clave(claves, clave_actual, max);

	print_test("Clave actual es clave valida", indice != -1);
	print_test("Clave actual es distinto puntero", clave_actual != claves[indice]);
	print_test("Clave actual pertenece", abb_pertenece(abb, clave_actual));

	print_test("Iter avanzar", abb_iter_in_avanzar(iter));
	print_test("Iter avanzar", abb_iter_in_avanzar(iter));
	print_test("Iter avanzar", abb_iter_in_avanzar(iter));

	clave_actual = abb_iter_in_ver_actual(iter);
	indice = buscar_clave(claves, clave_actual, max);

	print_test("Clave actual es clave valida", indice != -1);
	print_test("Clave actual es distinto puntero", clave_actual != claves[indice]);

	while(!abb_iter_in_al_final(iter)) abb_iter_in_avanzar(iter);

	print_test("Iter al final", abb_iter_in_al_final(iter));

	abb_destruir(abb);
	abb_iter_in_destruir(iter);

	liberar_claves(claves, max);
}

void prueba_abb_dynamic(){

	printf("\nPRUEBA ABB DYNAMIC\n");

	char* clave1 = "Arg";
	char* clave2 = "Bra";
	char* clave3 = "Din";
	char* clave4 = "Chi";
	char* clave5 = "Ecu";

	char* dato1 = malloc(10*sizeof(char));
	char* dato2 = malloc(10*sizeof(char));
	char* dato3 = malloc(10*sizeof(char));
	char* dato4 = malloc(10*sizeof(char));
	char* dato5 = malloc(10*sizeof(char));

	abb_t* abb = abb_crear(strcmp, free);

	print_test("Se creó abb", abb != NULL);

	print_test("Se guardó clave1", abb_guardar(abb, clave1, dato1));
	print_test("Se guardó clave2", abb_guardar(abb, clave2, dato2));
	print_test("Se guardó clave3", abb_guardar(abb, clave3, dato3));
	print_test("Se guardó clave4", abb_guardar(abb, clave4, dato4));
	print_test("Se guardó clave5", abb_guardar(abb, clave5, dato5));

	print_test("Cantidad es 5", abb_cantidad(abb) == 5);

	print_test("clave1 obtener dato1", abb_obtener(abb, clave1) == dato1);
	print_test("clave2 obtener dato2", abb_obtener(abb, clave2) == dato2);
	print_test("clave3 obtener dato3", abb_obtener(abb, clave3) == dato3);
	print_test("clave4 obtener dato4", abb_obtener(abb, clave4) == dato4);
	print_test("clave5 obtener dato5", abb_obtener(abb, clave5) == dato5);

	abb_destruir(abb);
}

void prueba_abb_iter_vacio(){

	printf("\nPRUEBA ABB ITER VACIO\n");

	abb_t* abb_vacio = abb_crear(strcmp, NULL);
	abb_iter_t* iter = abb_iter_in_crear(abb_vacio);

	print_test("Se creó iter", iter != NULL);
	print_test("Iter avanzar es false", !abb_iter_in_avanzar(iter));
	print_test("Iter ver actual es false", !abb_iter_in_ver_actual(iter));
	print_test("Iter está al final", abb_iter_in_al_final(iter));

	abb_iter_in_destruir(iter);
	abb_destruir(abb_vacio);
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

bool imprimir_rama_izq(const char* clave, void* dato, void* extra){

	size_t* contador = extra;

	printf("Selección: %s\tJugador: %s\n", clave, (char*)dato);

	(*contador)++;

	if((*contador) == 2) return false;

	return true;
}

bool imprimir_una_clave(const char* clave, void* dato, void* extra){

	printf("Selección: %s\tJugador: %s\n", clave, (char*)dato);

	return false;
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
	char* clave9 = "Ale", *dato9 = "Neuer";

	print_test("Se guardó clave1", abb_guardar(abb, clave1, dato1));
	print_test("Se guardó clave2", abb_guardar(abb, clave2, dato2));
	print_test("Se guardó clave3", abb_guardar(abb, clave3, dato3));
	print_test("Se guardó clave4", abb_guardar(abb, clave4, dato4));
	print_test("Se guardó clave5", abb_guardar(abb, clave5, dato5));
	print_test("Se guardó clave6", abb_guardar(abb, clave6, dato6));
	print_test("Se guardó clave7", abb_guardar(abb, clave7, dato7));
	print_test("Se guardó clave8", abb_guardar(abb, clave8, dato8));
	print_test("Se guardó clave9", abb_guardar(abb, clave9, dato9));
	
	printf("\nImprimir claves y datos:\n");

	size_t contador = 1;

	abb_in_order(abb, imprimir_claves_datos, &contador);

	printf("\n");

	abb_in_order(abb, imprimir_una_clave, NULL);

	printf("\n");

	contador = 0;

	abb_in_order(abb, imprimir_rama_izq, &contador);

	abb_destruir(abb);
}
void pruebas_abb_alumno(){
	
	prueba_abb_vacio();
	prueba_abb_guardar_y_borrar();
	prueba_abb_guardar_y_borrar_2();
	prueba_abb_guardar_2_elementos();
	prueba_abb_guardar_3_elementos();
	prueba_abb_guardar_5_elementos_part1();
	prueba_abb_guardar_5_elementos_part2();
	prueba_abb_guardar_5_elementos_part3();
	prueba_abb_guardar_5_elementos_part4();
	prueba_abb_guardar_8_elementos();
	prueba_abb_guardar_11_elementos();
	prueba_abb_guardar_20_elementos();
	prueba_abb_volumen(300000);
	prueba_abb_dynamic();
	prueba_abb_iter_vacio();
	prueba_abb_iter();
	prueba_abb_iter_interno();
}
