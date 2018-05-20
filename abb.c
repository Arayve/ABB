#include "abb.h"
#include "pila.h"

typedef struct campo{
	char* clave;
	void* dato;
}campo_t;	//Se puede cambiar a nombre más descriptivo

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

struct abb_iter{ //VERIFICAR
	pila_t* pila_abb;
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

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){


}

//ITERADOR EXTERNO

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){

	abb_iter_t* iter_nuevo = malloc(sizeof(abb_iter_t));

	if(!iter_nuevo) return NULL;

	iter_nuevo->pila_abb = pila_crear();

	if(!iter_nuevo->pila_abb){
		free(iter_nuevo);
		return NULL;
	}

	pila_apilar(iter_nuevo->pila_abb, arbol->raiz);

	//APILAR TODOS LOS HIJOS IZQ

	return iter_nuevo;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){

	if(abb_iter_in_al_final(iter)) return false;

	abb_nodo_t* nodo = pila_desapilar(iter->pila_abb);

	//APILO HIJOS DERECHOS DEL DESAPILADO

	return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){

	if(abb_iter_in_al_final(iter)) return NULL;

	abb_nodo_t* nodo = pila_ver_tope(iter->pila_abb);

	return nodo->campo->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){

	return (pila_esta_vacia(iter->pila_abb));
}

void abb_iter_in_destruir(abb_iter_t* iter){

	pila_destruir(iter->pila_abb);
	free(iter);
}