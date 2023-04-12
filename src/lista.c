#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

#define ERROR -1
#define EXITO 0
#define MINIMA_POSICION_LISTA 0

const int LISTA_SIN_NODOS = 0;

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *inicio;
	nodo_t *fin;
	size_t cantidad_nodos;
};

struct lista_iterador {
	nodo_t *nodo_actual;
	lista_t *lista;
};

bool insertar_en_lista_sin_nodos(lista_t *lista, void *elemento, nodo_t *nodo)
{
	if (lista == NULL)
		return false;

	lista->inicio = nodo;
	lista->fin = nodo;
	lista->cantidad_nodos++;
	return true;
}

nodo_t *iterar_hasta_posicion(lista_t *lista, size_t posicion)
{
	size_t posicion_actual = 0;
	nodo_t *nodo_actual = lista->inicio;
	nodo_t *nodo_aux;
	while (posicion_actual < posicion) {
		nodo_aux = nodo_actual->siguiente;
		nodo_actual = nodo_aux;
		posicion_actual++;
	}
	return nodo_actual;
}

lista_t *lista_crear()
{
	return calloc(1, sizeof(lista_t));
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (lista == NULL)
		return NULL;

	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL)
		return NULL;
	nodo->elemento = elemento;
	nodo->siguiente = NULL;

	if (lista->cantidad_nodos == LISTA_SIN_NODOS) {
		insertar_en_lista_sin_nodos(lista, elemento, nodo);
		return lista;
	}
	lista->fin->siguiente = nodo;
	lista->fin = nodo;
	lista->cantidad_nodos++;
	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (lista == NULL)
		return NULL;

	if (posicion >= lista->cantidad_nodos &&
	    lista_insertar(lista, elemento) != NULL) {
		return lista;
	}
	nodo_t *nodo_a_agregar = malloc(sizeof(nodo_t));
	if (nodo_a_agregar == NULL)
		return NULL;

	nodo_a_agregar->elemento = elemento;
	nodo_a_agregar->siguiente = NULL;
	if (lista->cantidad_nodos == LISTA_SIN_NODOS) {
		insertar_en_lista_sin_nodos(lista, elemento, nodo_a_agregar);
		return lista;
	}
	nodo_t *nodo_posicion = iterar_hasta_posicion(lista, posicion);
	nodo_a_agregar->siguiente = nodo_posicion->siguiente;
	nodo_posicion->siguiente = nodo_a_agregar;

	return lista;
}

void *lista_quitar(lista_t *lista)
{
	return NULL;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	nodo_t *nodo = iterar_hasta_posicion(lista, posicion);
	return nodo->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	return NULL;
}

void *lista_ultimo(lista_t *lista)
{
	return NULL;
}

bool lista_vacia(lista_t *lista)
{
	return true;
}

size_t lista_tamanio(lista_t *lista)
{
	return 0;
}

void lista_destruir(lista_t *lista)
{
	int contador = 0;
	nodo_t *nodo_actual = lista->inicio;
	nodo_t *nodo_aux;
	while (contador < lista->cantidad_nodos) {
		nodo_aux = nodo_actual->siguiente;
		free(nodo_actual);
		nodo_actual = nodo_aux;
		contador++;
	}
	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	/* 
	* se crea con malloc
	* pos actual cero
	* lista es lista 
	*/
	return NULL;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	/* 
	* si posicion actual es < a cantidad de elementos se puede seguir 
	* sino no.
	*/
	return false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	/* 
	* posicion actual ++
	? nodo igual nodo siguiente
	*/
	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	/* 
	* it lista elementos sub it posicion actual
	*/
	return NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	return 0;
}
