#include "pila.h"
#include "lista.h"

const int POSICION_A_APILAR = 0;
const int POSICION_A_DESAPILAR = 0;

pila_t *pila_crear()
{
	return (pila_t *)lista_crear();
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{
	if (pila == NULL)
		return NULL;

	return (pila_t *)lista_insertar_en_posicion((lista_t *)pila, elemento,
						    POSICION_A_APILAR);
}

void *pila_desapilar(pila_t *pila)
{
	if (pila == NULL)
		return NULL;

	return lista_quitar_de_posicion((lista_t *)pila, POSICION_A_DESAPILAR);
}

void *pila_tope(pila_t *pila)
{
	if (pila == NULL)
		return NULL;

	return lista_primero((lista_t *)pila);
}

size_t pila_tamanio(pila_t *pila)
{
	if (pila == NULL)
		return 0;

	return lista_tamanio((lista_t *)pila);
}

bool pila_vacia(pila_t *pila)
{
	if (pila == NULL)
		return false;

	return lista_vacia((lista_t *)pila);
}

void pila_destruir(pila_t *pila)
{
	if (pila == NULL)
		return;

	lista_destruir((lista_t *)pila);
}
