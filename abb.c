#include <string.h>
#include "abb.h"
#include "pila.h"

#define CANTIDAD_INICIAL_DE_NODO 0

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
void*  _destruir_abb_nodo(abb_nodo_t* nodo){
	free(nodo->campo->clave);
	void* dato = nodo->campo->dato;
	free(nodo->campo);
	free(nodo);
	return dato;
}

abb_nodo_t* _buscar_padre(abb_nodo_t* nodo_actual,const char* clave ,abb_comparar_clave_t cmp){
	if(!nodo_actual) return NULL;
	int comparacion = cmp(nodo_actual->campo->clave,clave);
	if( comparacion == 0) return NULL;
	
	if(nodo_actual->izquierdo){
		int comparacion = cmp(nodo_actual->izquierdo->campo->clave,clave);
		if( comparacion == 0){
			return nodo_actual;
		}
	}
	if(nodo_actual->derecho){
		int comparacion = cmp(nodo_actual->derecho->campo->clave,clave);
		if(comparacion == 0){
			return nodo_actual;
		}
	}
	if (comparacion < 0){
		return _buscar_padre(nodo_actual->derecho,clave,cmp);
	}
	return _buscar_padre(nodo_actual->izquierdo,clave,cmp);
}

void _swap_abb_nodo(abb_nodo_t* nodo1, abb_nodo_t* nodo2){
	campo_t* campo_nodo_1 = nodo1->campo;
	nodo1->campo = nodo2->campo;
	nodo2->campo = campo_nodo_1;
}
size_t _abb_guardar(abb_nodo_t* nodo_actual,abb_nodo_t* nodo_nuevo,abb_nodo_t* nodo_padre,abb_comparar_clave_t cmp,abb_destruir_dato_t destruir_dato){
	if(!nodo_actual){
		int comparacion = cmp(nodo_padre->campo->clave,nodo_nuevo->campo->clave);
		if(comparacion < 0){
			nodo_padre->derecho = nodo_nuevo;
		}
		else{
			nodo_padre->izquierdo = nodo_nuevo;
		}
		return 1;
	}
	int comparacion = cmp(nodo_actual->campo->clave,nodo_nuevo->campo->clave);

	if( comparacion == 0){//Supose que si guardo algo con la misma clave borro el dato anterior
		_swap_abb_nodo(nodo_actual,nodo_nuevo);
		void* dato = _destruir_abb_nodo(nodo_nuevo);	
		if(destruir_dato){
			destruir_dato(dato);
		}
		return 0;
	}
	if(comparacion < 0){//si actual es menor a nuevo
		return _abb_guardar(nodo_actual->derecho,nodo_nuevo,nodo_actual,cmp,destruir_dato);
	}
	return _abb_guardar(nodo_actual->izquierdo,nodo_nuevo,nodo_actual,cmp,destruir_dato);
}
/* //IDEA DE _ABB_GUARDAR
void _abb_guardar(nodo, nodo_hijo, cmp, destruir){

	if(cmp(nodo->clave, clave) < 0){
		if(nodo->izquierdo == NULL){
			nodo->izquierdo = nodo_hijo;
			return;
		}
	return _abb_guardar(nodo->izquierdo, nodo_hijo, cmp, destruir); //VERIFICAR SI ES VÁLIDO
	}else if(cmp(nodo->clave, clave) > 0){
		if(nodo->derecho == NULL){
			nodo->derecho = nodo_hijo;
			return;
		}
	return _abb_guardar(nodo->derecho, nodo_hijo, cmp, destruir);
	}
	if(destruir){
		void* dato = nodo->dato;
		destruir(dato);
	}
	nodo->dato = nodo_hijo->dato;	//faltaría free(nodo_hijo->clave) y free(nodo->hijo)
}
*/

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	abb_nodo_t* nodo = _construir_abb_nodo(clave,dato);
	if(!nodo) return false;

	if(arbol->cantidad == CANTIDAD_INICIAL_DE_NODO){	//otra posibilidad arbol->raiz == NULL
		arbol->raiz = nodo;
		++arbol->cantidad;
		return true;
	}
	size_t cant_nodo_guardado = _abb_guardar(arbol->raiz,nodo,NULL,arbol->cmp,arbol->destruir_dato);
	arbol->cantidad = arbol->cantidad + cant_nodo_guardado;
	//arbol->cantidad++;
	return true;
}

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

}
bool _clave_esta_en_la_derecha(abb_nodo_t* nodo,const char* clave,abb_comparar_clave_t cmp){
	int comparacion = cmp(nodo->campo->clave,clave);
	if( comparacion < 0 ) return true;
	return false;
}
abb_nodo_t* _abb_nodo_ultimo_izquierdo(abb_nodo_t* nodo_actual){
	if(!nodo_actual->izquierdo)return nodo_actual;
	return _abb_nodo_ultimo_izquierdo(nodo_actual->izquierdo);
}
void* _abb_borrar_hoja(abb_nodo_t* nodo_act,abb_t* arbol, const char *clave,abb_nodo_t* nodo_padre_act){
	void* dato = _destruir_abb_nodo(nodo_act);
	if(!nodo_padre_act){// es decir nodo_act es la raiz y ademas hoja , unico elemento
		arbol->raiz = NULL;
	}else if(_clave_esta_en_la_derecha(nodo_padre_act,clave,arbol->cmp)){
		nodo_padre_act->derecho = NULL;
	}else{
		nodo_padre_act->izquierdo = NULL;
	}

	--arbol->cantidad;
	return dato;
}
void* _abb_borrar_hijo_unico(abb_nodo_t* nodo_act,abb_t* arbol, const char *clave,abb_nodo_t* nodo_padre_act){
	abb_nodo_t* nodo_hijo_act = _buscar_hijo(nodo_act);
	if(!nodo_padre_act){//estoy en la raiz 
		arbol->raiz = nodo_hijo_act;
	}else if(_clave_esta_en_la_derecha(nodo_padre_act,clave,arbol->cmp)){// quiere decir que nodo act esta en el derecho 
		nodo_padre_act->derecho = nodo_hijo_act;
	}else{
		nodo_padre_act->izquierdo = nodo_hijo_act;
	}
	
	void* dato = _destruir_abb_nodo(nodo_act);
	--arbol->cantidad;
	return dato;
}
void* abb_borrar(abb_t *arbol, const char *clave){
	abb_nodo_t* nodo_act =_buscar_elemento(arbol->raiz,clave,arbol->cmp);//cambiar a un nombre mas especifico
	if(!nodo_act) return NULL;
	abb_nodo_t* padre_nodo_act = _buscar_padre(arbol->raiz,clave,arbol->cmp);
	
	if(_abb_nodo_es_hoja(nodo_act)){
		return _abb_borrar_hoja(nodo_act,arbol,clave,padre_nodo_act);
	}
	if(_abb_nodo_tiene_un_hijo(nodo_act)){
		return _abb_borrar_hijo_unico(nodo_act,arbol,clave,padre_nodo_act);
	}
	
	abb_nodo_t* nodo_aux = _abb_nodo_ultimo_izquierdo(nodo_act->derecho);
	abb_nodo_t* padre_nodo_aux = _buscar_padre(arbol->raiz,nodo_aux->campo->clave,arbol->cmp);//tengo qu ebuscar al padre antes del swap
	_swap_abb_nodo(nodo_act,nodo_aux);
	if(_abb_nodo_es_hoja(nodo_aux)){
		return _abb_borrar_hoja(nodo_aux,arbol,nodo_act->campo->clave,padre_nodo_aux);//aux apunta al campo que quiero eliminar
	}
	else{
		return _abb_borrar_hijo_unico(nodo_aux,arbol,nodo_act->campo->clave,padre_nodo_aux);
	}
}

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