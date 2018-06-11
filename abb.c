#define _POSIX_C_SOURCE 200809L
#include <string.h>
#include <stdlib.h>
#include "abb.h"
#include "pila.h"

#define CANTIDAD_INICIAL_DE_NODO 0
#define IZQUIERDO -1
#define	DERECHO 1
#define NO_PADRE -1
#define PADRE 1

typedef struct campo{
	char* clave;
	void* dato;
}campo_t;

typedef struct abb_nodo{
	campo_t* campo;
	struct abb_nodo* izquierdo;
	struct abb_nodo* derecho;
}abb_nodo_t;

struct abb{
	abb_nodo_t* raiz;
	size_t cantidad;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destruir_dato;
};

struct abb_iter{
	pila_t* pila_abb;
};

abb_nodo_t* abb_nodo_crear(void){

	abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
	if (!nodo) return NULL;
	nodo->izquierdo = NULL;
	nodo->derecho = NULL;
    return nodo;
}
campo_t* campo_crear(const char* clave, void* dato){
	
	campo_t* campo = malloc(sizeof(campo_t));
	if(!campo) return NULL;
	
	campo->clave = strdup(clave);
	campo->dato = dato;
	return campo;
}
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* abb = malloc(sizeof(abb_t));
	if(!abb) return NULL;
	abb->raiz = NULL;
	abb->cmp = cmp;
	abb->destruir_dato = destruir_dato;
	abb->cantidad = CANTIDAD_INICIAL_DE_NODO;
	return abb;
}
abb_nodo_t* _construir_abb_nodo(const char* clave, void* dato){

	abb_nodo_t* nodo = abb_nodo_crear();
	if(!nodo) return NULL;
	campo_t* campo = campo_crear(clave, dato);
	if(!campo){
		free(nodo);
		return NULL;
	}
	nodo->campo = campo;
	return nodo;
}
void* _destruir_abb_nodo(abb_nodo_t* nodo){
	free(nodo->campo->clave);
	void* dato = nodo->campo->dato;
	free(nodo->campo);
	free(nodo);
	return dato;
}
void _swap_abb_nodo(abb_nodo_t* nodo1, abb_nodo_t* nodo2){
	campo_t* campo_nodo_aux = nodo1->campo;
	nodo1->campo = nodo2->campo;
	nodo2->campo = campo_nodo_aux;
}
/*Si tiene dos hijos devuelve el izquierdo*/
abb_nodo_t* _buscar_hijo(abb_nodo_t* nodo_actual){
	if(nodo_actual->izquierdo)  return nodo_actual->izquierdo;
	return nodo_actual->derecho;
}

bool _abb_nodo_es_hoja(abb_nodo_t* nodo){
	if(!nodo->izquierdo && !nodo->derecho) return true;
	return false;
}
bool _abb_nodo_tiene_un_hijo(abb_nodo_t* nodo){
	if(!nodo->izquierdo && nodo->derecho) return true;
	if(nodo->izquierdo && !nodo->derecho) return true;
	return false;
}

abb_nodo_t* _buscar_elemento(abb_nodo_t* nodo_actual, const char* clave, abb_comparar_clave_t cmp, int devuelvo_padre){
	if(!nodo_actual) return NULL;
	int comparacion = cmp(nodo_actual->campo->clave, clave);
		if( comparacion == 0){
			if (devuelvo_padre == PADRE)return NULL;
		return nodo_actual;
	}
	if(nodo_actual->izquierdo){
		int comparacion_aux = cmp(nodo_actual->izquierdo->campo->clave, clave);
		if( comparacion_aux == 0){
			if (devuelvo_padre == PADRE) return nodo_actual;
			return nodo_actual->izquierdo;
		}
	}
	if(nodo_actual->derecho){
		int comparacion_aux = cmp(nodo_actual->derecho->campo->clave, clave);
		if(comparacion_aux == 0){
			if (devuelvo_padre == PADRE) return nodo_actual;
			return nodo_actual->derecho;
		}
	}
	if (comparacion < 0){
		return _buscar_elemento(nodo_actual->derecho,clave, cmp, devuelvo_padre);
	}
	return _buscar_elemento(nodo_actual->izquierdo,clave, cmp, devuelvo_padre);
}
size_t _abb_guardar(abb_nodo_t* nodo_padre,abb_nodo_t* nodo_hijo, abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	if(cmp(nodo_padre->campo->clave, nodo_hijo->campo->clave) < 0){
		if(nodo_padre->derecho == NULL){
			nodo_padre->derecho = nodo_hijo;
			return 1;
		}
		return _abb_guardar(nodo_padre->derecho, nodo_hijo, cmp, destruir_dato);
	}else if(cmp(nodo_padre->campo->clave, nodo_hijo->campo->clave) > 0){
		if(nodo_padre->izquierdo == NULL){
			nodo_padre->izquierdo = nodo_hijo;
			return 1;
		}
		return _abb_guardar(nodo_padre->izquierdo, nodo_hijo, cmp, destruir_dato);
	}
	_swap_abb_nodo(nodo_padre, nodo_hijo);
		void* dato = _destruir_abb_nodo(nodo_hijo);	
		if(destruir_dato){
			destruir_dato(dato);
		}
		return 0;
}
bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	abb_nodo_t* nodo = _construir_abb_nodo(clave, dato);
	if(!nodo) return false;

	if(arbol->raiz == NULL){
		arbol->raiz = nodo;
		++arbol->cantidad;
		return true;
	}
	size_t cant_nodo_guardado = _abb_guardar(arbol->raiz, nodo, arbol->cmp, arbol->destruir_dato);
	arbol->cantidad = arbol->cantidad + cant_nodo_guardado;
	return true;
}

void* _borrar_hoja_invariante_roto(abb_nodo_t* nodo_hijo, abb_nodo_t* nodo_padre, int ubicacion_hijo){

	if(ubicacion_hijo == IZQUIERDO){
		nodo_padre->izquierdo = NULL;
	}else{
		nodo_padre->derecho = NULL;
	}
	return _destruir_abb_nodo(nodo_hijo);
}
void* borrar_hoja(abb_nodo_t* nodo_hijo, abb_nodo_t* nodo_padre, abb_t* arbol){
	if(nodo_padre == NULL){
		arbol->raiz = NULL;
	}else if(arbol->cmp(nodo_padre->campo->clave, nodo_hijo->campo->clave) < 0){
		nodo_padre->derecho = NULL;
	}else{
		nodo_padre->izquierdo = NULL;
	}
	return _destruir_abb_nodo(nodo_hijo);
}
int _ubicacion_del_hijo(abb_nodo_t* padre,abb_nodo_t*hijo){
	if(padre->derecho == hijo) return DERECHO;
	return IZQUIERDO;
}
void* borrar_nodo_un_hijo(abb_nodo_t* nodo_padre, abb_nodo_t* nodo_abuelo, abb_t* arbol){

	abb_nodo_t* nodo_hijo = _buscar_hijo(nodo_padre);

	if(nodo_abuelo == NULL){
		arbol->raiz = nodo_hijo;
	}else{
		int ubicacion_padre = _ubicacion_del_hijo(nodo_abuelo, nodo_padre);

		if(ubicacion_padre == DERECHO){
			nodo_abuelo->derecho = nodo_hijo;
		}else{
			nodo_abuelo->izquierdo = nodo_hijo;
		}
	}

	return _destruir_abb_nodo(nodo_padre);
}
abb_nodo_t* buscar_reemplazante(abb_nodo_t* nodo_reemplazante){

	if(_abb_nodo_es_hoja(nodo_reemplazante)) return nodo_reemplazante;

	if(nodo_reemplazante->izquierdo == NULL) return nodo_reemplazante;

	return buscar_reemplazante(nodo_reemplazante->izquierdo);
}
void* borrar_nodo_dos_hijos(abb_nodo_t* nodo_hijo, abb_t* arbol){

	abb_nodo_t* nodo_nuevo_hijo = buscar_reemplazante(nodo_hijo->derecho);
	abb_nodo_t* nodo_padre = _buscar_elemento(nodo_hijo, nodo_nuevo_hijo->campo->clave, arbol->cmp, PADRE);

	if(!nodo_padre){
		nodo_padre = nodo_hijo;
	}

	int ubicacion_hijo =_ubicacion_del_hijo(nodo_padre, nodo_nuevo_hijo);
	_swap_abb_nodo(nodo_nuevo_hijo, nodo_hijo);

	if(_abb_nodo_es_hoja(nodo_nuevo_hijo)){
		return _borrar_hoja_invariante_roto(nodo_nuevo_hijo, nodo_padre, ubicacion_hijo);
	}

	return borrar_nodo_un_hijo(nodo_nuevo_hijo, nodo_padre, arbol);
}
void* abb_borrar(abb_t *arbol, const char *clave){

	abb_nodo_t* nodo_hijo = _buscar_elemento(arbol->raiz, clave, arbol->cmp,NO_PADRE);

	if(!nodo_hijo) return NULL;

	abb_nodo_t* nodo_padre = _buscar_elemento(arbol->raiz, clave, arbol->cmp,PADRE);
	void* dato;
	if(_abb_nodo_es_hoja(nodo_hijo)){
		dato = borrar_hoja(nodo_hijo, nodo_padre, arbol);
	}else if(_abb_nodo_tiene_un_hijo(nodo_hijo)){
		dato = borrar_nodo_un_hijo(nodo_hijo, nodo_padre, arbol);
	}else{
		dato = borrar_nodo_dos_hijos(nodo_hijo, arbol);
	}
	arbol->cantidad--;
	return dato;
}

void *abb_obtener(const abb_t *arbol, const char *clave){
	abb_nodo_t* nodo = _buscar_elemento(arbol->raiz, clave, arbol->cmp, NO_PADRE);
	if(!nodo) return NULL;
	return nodo->campo->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	abb_nodo_t* nodo = _buscar_elemento(arbol->raiz, clave, arbol->cmp, NO_PADRE);
	if(!nodo) return false;
	return true;
}

size_t abb_cantidad(abb_t *arbol){

	return arbol->cantidad;
}
void abb_destruir(abb_t *arbol){

	if(!arbol->raiz){
		free(arbol);
		return;
	}	

	void* dato = abb_borrar(arbol, arbol->raiz->campo->clave);

	if(arbol->destruir_dato){
		arbol->destruir_dato(dato);
	}

	abb_destruir(arbol);
}
//ITERADOR INTERNO

void _abb_in_order(abb_nodo_t* nodo, bool visitar(const char *, void *, void *), void* extra){

	if(!nodo) return;

	_abb_in_order(nodo->izquierdo, visitar, extra);
	if(!visitar(nodo->campo->clave, nodo->campo->dato, extra)) return;
	_abb_in_order(nodo->derecho, visitar, extra);
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){

	_abb_in_order(arbol->raiz, visitar, extra);
}

//ITERADOR EXTERNO

void apilar_hijos_in_order(pila_t* pila_abb, abb_nodo_t* nodo){

	if(!nodo) return;

	pila_apilar(pila_abb, nodo);

	apilar_hijos_in_order(pila_abb, nodo->izquierdo);
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){

	abb_iter_t* iter_nuevo = malloc(sizeof(abb_iter_t));

	if(!iter_nuevo) return NULL;

	iter_nuevo->pila_abb = pila_crear();

	if(!iter_nuevo->pila_abb){
		free(iter_nuevo);
		return NULL;
	}

	if(arbol->raiz){
		pila_apilar(iter_nuevo->pila_abb, arbol->raiz);

		apilar_hijos_in_order(iter_nuevo->pila_abb, arbol->raiz->izquierdo);
	}
	
	return iter_nuevo;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){

	if(abb_iter_in_al_final(iter)) return false;

	abb_nodo_t* nodo_aux = pila_desapilar(iter->pila_abb);

	apilar_hijos_in_order(iter->pila_abb, nodo_aux->derecho);

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