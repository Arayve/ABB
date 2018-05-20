#include "abb.h"

typedef struct campo{
	char* clave;
	void* dato;
}campo_t;	//Se puede cambiar a nombre más descriptivo/nodo_t

typedef struct abb_nodo{
	campo_t* campo;
	abb_nodo_t* izquierdo;
	abb_nodo_t* derecho;
}abb_nodo_t;

struct abb{	//VER DIAPOSITIVA DE ABB
	abb_nodo_t* raiz;
	size_t cantidad;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destruir_dato;
};

/*
typedef struct abb_hijo {
	struct abb_hijo* izq;
	struct abb_hijo* der;
}abb_hijo_t;
*/

/*
struct abb {
	abb_hijo_t* izq;
	abb_hijo_t* der;
	abb_comparar_clave_t // son punteros aca 
	abb_destruir_dato_t
};
*/
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){

}

void *abb_borrar(abb_t *arbol, const char *clave){

}

void *abb_obtener(const abb_t *arbol, const char *clave){

}

bool abb_pertenece(const abb_t *arbol, const char *clave){

}

size_t abb_cantidad(abb_t *arbol){

}

void abb_destruir(abb_t *arbol){

}

//ITERADOR INTERNO

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

//ITERADOR EXTERNO

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){

}

bool abb_iter_in_avanzar(abb_iter_t *iter){

}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){

}

bool abb_iter_in_al_final(const abb_iter_t *iter){

}

void abb_iter_in_destruir(abb_iter_t* iter){

}