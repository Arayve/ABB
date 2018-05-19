#include "abb.h"


typedef struct abb_hijo {
	struct abb_hijo* izq;
	struct abb_hijo* der;
}abb_hijo_t;

struct abb {
	abb_hijo_t* izq;
	abb_hijo_t* der;
	abb_comparar_clave_t // son punteros aca 
	abb_destruir_dato_t
};

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

}