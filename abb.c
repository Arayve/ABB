#include <string.h>
#include <stdlib.h>
#include "abb.h"
#include "pila.h"

#define CANTIDAD_INICIAL_DE_NODO 0
#define IZQUIERDO -1
#define	DERECHO 1

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


char* _clave_copiar(const char* clave){
	
	char* clave_aux = malloc((strlen(clave)+1)*sizeof(char));
	if(!clave_aux) return NULL;
	strcpy(clave_aux, clave);
	return clave_aux;
}

abb_nodo_t* abb_nodo_crear(void){

	abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
	if (!nodo) return NULL;
	nodo->izquierdo = NULL;
	nodo->derecho = NULL;
    return nodo;
}
campo_t* campo_crear(const char* clave,void* dato){
	
	campo_t* campo = malloc(sizeof(campo_t));
	if(!campo) return NULL;
	
	char* clave_aux = _clave_copiar(clave);
	if(!clave_aux){
		free(campo);
		return NULL;
	}
	campo->clave = clave_aux;
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
abb_nodo_t* _construir_abb_nodo(const char* clave,void* dato){

	abb_nodo_t* nodo = abb_nodo_crear();
	if(!nodo) return NULL;
	campo_t* campo = campo_crear(clave,dato);
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
abb_nodo_t* _buscar_hijo(abb_nodo_t* nodo_actual){//necesariamente debe tener un solo hijo
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

}/*
bool _clave1_es_menor_clave2(const char* clave1,const char* clave2,abb_comparar_clave_t cmp){
	int comparacion = cmp(clave1,clave2);
	if( comparacion < 0 ) return true;
	return false;
}*/
abb_nodo_t* _buscar_elemento(abb_nodo_t* nodo_actual,const char* clave,abb_comparar_clave_t cmp){
	if(!nodo_actual) return NULL;
	int comparacion = cmp(nodo_actual->campo->clave,clave);
	if( comparacion == 0){
		return nodo_actual;
	}
	if(comparacion < 0){
		return _buscar_elemento(nodo_actual->derecho,clave,cmp);
	}
	return _buscar_elemento(nodo_actual->izquierdo,clave,cmp);
}
abb_nodo_t* _buscar_padre(abb_nodo_t* nodo_actual,const char* clave ,abb_comparar_clave_t cmp){
	if(!nodo_actual) return NULL;
	int comparacion = cmp(nodo_actual->campo->clave,clave);
	if( comparacion == 0) return NULL;
	
	if(nodo_actual->izquierdo){
		int comparacion_aux = cmp(nodo_actual->izquierdo->campo->clave,clave);
		if( comparacion_aux == 0){
			return nodo_actual;
		}
	}
	if(nodo_actual->derecho){
		int comparacion_aux = cmp(nodo_actual->derecho->campo->clave,clave);
		if(comparacion_aux == 0){
			return nodo_actual;
		}
	}
	if (comparacion < 0){
		return _buscar_padre(nodo_actual->derecho,clave,cmp);
	}
	return _buscar_padre(nodo_actual->izquierdo,clave,cmp);
}
/**************************************************************************/
size_t _abb_guardar(abb_nodo_t* nodo_padre,abb_nodo_t* nodo_hijo,abb_comparar_clave_t cmp,abb_destruir_dato_t destruir_dato){
	if(cmp(nodo_padre->campo->clave,nodo_hijo->campo->clave) < 0){
		if(nodo_padre->derecho == NULL){
			nodo_padre->derecho = nodo_hijo;
			return 1;
		}
		return _abb_guardar(nodo_padre->derecho,nodo_hijo,cmp,destruir_dato);
	}else if(cmp(nodo_padre->campo->clave,nodo_hijo->campo->clave) > 0){
		if(nodo_padre->izquierdo == NULL){
			nodo_padre->izquierdo = nodo_hijo;
			return 1;
		}
		return _abb_guardar(nodo_padre->izquierdo,nodo_hijo,cmp,destruir_dato);
	}
	_swap_abb_nodo(nodo_padre,nodo_hijo);
		void* dato = _destruir_abb_nodo(nodo_hijo);	
		if(destruir_dato){
			destruir_dato(dato);
		}
		return 0;
}
bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	abb_nodo_t* nodo = _construir_abb_nodo(clave,dato);
	if(!nodo) return false;

	if(arbol->cantidad == CANTIDAD_INICIAL_DE_NODO){	//otra posibilidad arbol->raiz == NULL
		arbol->raiz = nodo;
		++arbol->cantidad;
		return true;
	}
	size_t cant_nodo_guardado = _abb_guardar(arbol->raiz,nodo,arbol->cmp,arbol->destruir_dato);
	arbol->cantidad = arbol->cantidad + cant_nodo_guardado;
	return true;
}
/****************************************************************************/
void* borrar_nodo_dos_hijos(abb_nodo_t* nodo_hijo,abb_comparar_clave_t cmp, abb_t* arbol);
void* _borrar_hoja_invariantes_roto(abb_nodo_t* nodo_hijo, abb_nodo_t* nodo_padre, int ubicacion_hijo){

	if(ubicacion_hijo == IZQUIERDO){
		nodo_padre->izquierdo = NULL;
	}else{
		nodo_padre->derecho = NULL;
	}
	return _destruir_abb_nodo(nodo_hijo);
}
void* borrar_hoja(abb_nodo_t* nodo_hijo, abb_nodo_t* nodo_padre, abb_comparar_clave_t cmp, abb_t* arbol){

	if(nodo_padre == NULL){
		arbol->raiz = NULL;
	}else if(cmp(nodo_padre->campo->clave, nodo_hijo->campo->clave) < 0){
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
void* borrar_nodo_un_hijo(abb_nodo_t* nodo_padre, abb_comparar_clave_t cmp,abb_t* arbol){

	abb_nodo_t* nodo_hijo = _buscar_hijo(nodo_padre);
	int ubicacion_hijo = _ubicacion_del_hijo(nodo_padre,nodo_hijo);
	_swap_abb_nodo(nodo_padre, nodo_hijo);

	void* dato;

	if(_abb_nodo_es_hoja(nodo_hijo)){
		dato = _borrar_hoja_invariantes_roto(nodo_hijo,nodo_padre,ubicacion_hijo);
	}else if(_abb_nodo_tiene_un_hijo(nodo_hijo)){
		abb_nodo_t* nodo_nuevo_hijo = _buscar_hijo(nodo_hijo);
		int ubicacion_nuevo_hijo = _ubicacion_del_hijo(nodo_hijo,nodo_nuevo_hijo);
		if(ubicacion_nuevo_hijo == IZQUIERDO){
			_swap_abb_nodo(nodo_padre,nodo_nuevo_hijo);
		}
		dato = borrar_nodo_un_hijo(nodo_hijo,cmp,arbol);
	}else{
		abb_nodo_t* nodo_nuevo_hijo = _buscar_hijo(nodo_hijo);
		int ubicacion_nuevo_hijo = _ubicacion_del_hijo(nodo_hijo,nodo_nuevo_hijo);
		if(ubicacion_nuevo_hijo == IZQUIERDO){
			_swap_abb_nodo(nodo_padre,nodo_nuevo_hijo);
		}
		dato = borrar_nodo_dos_hijos(nodo_hijo,cmp,arbol);
	}
	return dato;
}
abb_nodo_t* buscar_reemplazante(abb_nodo_t* nodo_reemplazante){

	if(_abb_nodo_es_hoja(nodo_reemplazante)) return nodo_reemplazante;

	if(nodo_reemplazante->izquierdo == NULL) return nodo_reemplazante;

	return buscar_reemplazante(nodo_reemplazante->izquierdo);
}
void* borrar_nodo_dos_hijos(abb_nodo_t* nodo_hijo,abb_comparar_clave_t cmp,abb_t* arbol){

	void* dato;
	abb_nodo_t* nodo_nuevo_hijo = buscar_reemplazante(nodo_hijo->derecho);	//como tiene 2 hijos no puede ser NULL

	abb_nodo_t* nodo_padre = _buscar_padre(nodo_hijo->derecho,nodo_nuevo_hijo->campo->clave, cmp);
	if(!nodo_padre){
		nodo_padre = nodo_hijo;
	}
	int ubicacion_hijo =_ubicacion_del_hijo(nodo_padre,nodo_nuevo_hijo);
	_swap_abb_nodo(nodo_nuevo_hijo, nodo_hijo);
	
	if(_abb_nodo_es_hoja(nodo_nuevo_hijo)){
		dato = _borrar_hoja_invariantes_roto(nodo_nuevo_hijo, nodo_padre, ubicacion_hijo);
	
	}else if(_abb_nodo_tiene_un_hijo(nodo_nuevo_hijo)){	
		dato = borrar_nodo_un_hijo(nodo_nuevo_hijo, cmp,arbol);
	}else{//tiene sentido llabar nodo_dos_hijos , digo el reemplaante nunca va tener dos hijos
		dato = borrar_nodo_dos_hijos(nodo_nuevo_hijo, cmp,arbol);
	}
	return dato;
}
void* abb_borrar(abb_t *arbol, const char *clave){

	abb_nodo_t* nodo_hijo = _buscar_elemento(arbol->raiz, clave, arbol->cmp);

	if(!nodo_hijo) return NULL;

	abb_nodo_t* nodo_padre = _buscar_padre(arbol->raiz, clave, arbol->cmp);
	void* dato;

	if(_abb_nodo_es_hoja(nodo_hijo)){
		dato = borrar_hoja(nodo_hijo, nodo_padre, arbol->cmp, arbol);
	}else if(_abb_nodo_tiene_un_hijo(nodo_hijo)){
		dato = borrar_nodo_un_hijo(nodo_hijo, arbol->cmp,arbol);
	}else{
		dato = borrar_nodo_dos_hijos(nodo_hijo,arbol->cmp,arbol);
	}
	arbol->cantidad--;
	return dato;
}
/******************************************************************************/

void *abb_obtener(const abb_t *arbol, const char *clave){
	abb_nodo_t* nodo = _buscar_elemento(arbol->raiz,clave,arbol->cmp);
	if(!nodo) return NULL;
	return nodo->campo->dato;

}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	abb_nodo_t* nodo = _buscar_elemento(arbol->raiz,clave,arbol->cmp);
	if(!nodo) return false;
	return true;
}

size_t abb_cantidad(abb_t *arbol){

	return arbol->cantidad;
}

void abb_destruir(abb_t *arbol){
	while(arbol->raiz){
		void* dato = abb_borrar(arbol,arbol->raiz->campo->clave);
		if(arbol->destruir_dato){
			abb_destruir_dato_t destruir_dato = arbol->destruir_dato;
			destruir_dato(dato);
		}
	}
	free(arbol);
}

//ITERADOR INTERNO

void apilar_hijos_in_order(pila_t* pila_abb, abb_nodo_t* nodo){

	if(!nodo) return;

	pila_apilar(pila_abb, nodo);

	apilar_hijos_in_order(pila_abb, nodo->izquierdo);
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){

	pila_t* pila_abb = pila_crear();

	apilar_hijos_in_order(pila_abb, arbol->raiz);

	while(!pila_esta_vacia(pila_abb)){
		abb_nodo_t* nodo_actual = pila_desapilar(pila_abb);

		if(!visitar(nodo_actual->campo->clave, nodo_actual->campo->dato, extra)){
			pila_destruir(pila_abb);
			return;
		}

		apilar_hijos_in_order(pila_abb, nodo_actual->derecho);
	}

	pila_destruir(pila_abb);
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

	apilar_hijos_in_order(iter_nuevo->pila_abb, arbol->raiz->izquierdo);

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