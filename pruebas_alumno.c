#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h> 


void prueba_abb_vacio(){

	printf("PRUEBA ABB VACIO\n");

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

	printf("PRUEBA ABB GUARDAR Y BORRAR\n");

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

void prueba_abb_guardar_varios(){

	printf("PRUEBA ABB GUARDAR VARIOS\n");

	abb_t* abb = abb_crear(strcmp, NULL);
	char* clave1 = "Arg", *dato1 = "Messi";
	char* clave2 = "Bra", *dato2 = "Hulk";
	char* clave3 = "Bra", *dato3 = "Pato";
	char* clave4 = "Chi", *dato4 = "Vidal";
	char* clave5 = "Por", *dato5 = "Ronaldo";
	char* clave6 = "Esp", *dato6 = "Puyol";
	char* clave7 = "Col", *dato7 = "Falcao";
	char* clave8 = "Uru", *dato8 = "Suarez";


	print_test("Se creó abb", abb != NULL);
	print_test("abb_cantidad igual a 0", abb_cantidad(abb) == 0);
	print_test("Se guardó clave", abb_guardar(abb, clave1, dato1));
	print_test("Se guardó clave", abb_guardar(abb, clave2, dato2));
	print_test("Se guardó clave", abb_guardar(abb, clave3, dato3));
	print_test("Se guardó clave", abb_guardar(abb, clave4, dato4));
	print_test("Se guardó clave", abb_guardar(abb, clave5, dato5));
	print_test("Se guardó clave", abb_guardar(abb, clave6, dato6));
	print_test("Se guardó clave", abb_guardar(abb, clave7, dato7));
	print_test("Se guardó clave", abb_guardar(abb, clave8, dato8));
	print_test("abb_cantidad igual a 7", abb_cantidad(abb) == 7);



}

void pruebas_abb_alumno(){
	
	prueba_abb_vacio();
	prueba_abb_guardar_y_borrar();
	prueba_abb_guardar_varios();

}