#include "abb.h"

struct abb {
	
	abb_t* izq;
	abb_t* der;
	abb_comparar_clave_t // son punteros aca 
	abb_destruir_dato_t
};

typedef struct abb_hijo {
    void* valor;
    struct nodo* prox;
}abb_hijo_t;

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

}