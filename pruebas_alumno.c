#include "pa2m.h"
#include "src/lista.h"

void pruebas_lista_crear()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Se puede crar una lista.");
	pa2m_afirmar(lista_tamanio(lista) == 0, "La lista creada está vacía.");
	pa2m_afirmar(
		lista_primero(lista) == NULL && lista_ultimo(lista) == NULL,
		"Se inicializan en NULL los elementos principio y fin de la lista.\n");
	lista_destruir(lista);
}

void pruebas_lista_insertar()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_insertar(NULL, 0) == NULL,
		     "No se puede insertar con una lista NULL.");
	lista_insertar(lista, NULL);
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL,
		     "Se puede insertar un elemento NULL.");

	int uno = 1, dos = 2, tres = 3;
	pa2m_afirmar(lista_insertar(lista, &uno) == lista,
		     "Insertar un elemento devuelve la lista.");
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == &uno &&
			     lista_elemento_en_posicion(lista, 2) == &dos &&
			     lista_elemento_en_posicion(lista, 3) == &tres,
		     "Se insertan elementos correctamente.");
	pa2m_afirmar(lista_tamanio(lista) == 4,
		     "Se actualiza correctamente el tamaño de la lista.");
	pa2m_afirmar(
		lista_primero(lista) == NULL && lista_ultimo(lista) == &tres,
		"Se actualizan correctamente el principio y fin de la lista.\n");
	lista_destruir(lista);
}

void pruebas_lista_insertar_en_posicion()
{
	int cero = 0, uno = 1, dos = 2, tres = 3, siete = 8;

	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_insertar_en_posicion(NULL, &uno, 0) == NULL,
		     "No se puede insertar con una lista NULL.");

	pa2m_afirmar(lista_insertar_en_posicion(lista, NULL, 0) == lista,
		     "Agregar un elemento en el inicio devuelve la lista.");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL,
		     "Se puede insertar un elemento NULL mediante.");
	lista_insertar(lista, &uno);
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);
	lista_insertar_en_posicion(lista, &cero, 0);
	lista_insertar_en_posicion(lista, &tres, 2);
	lista_insertar_en_posicion(lista, &uno, 3);
	lista_insertar_en_posicion(lista, &siete, 7);
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == NULL &&
			     lista_elemento_en_posicion(lista, 2) == &tres &&
			     lista_elemento_en_posicion(lista, 3) == &uno &&
			     lista_elemento_en_posicion(lista, 4) == &uno &&
			     lista_elemento_en_posicion(lista, 5) == &dos &&
			     lista_elemento_en_posicion(lista, 6) == &tres &&
			     lista_elemento_en_posicion(lista, 7) == &siete,
		     "Se insertan elementos correctamente.");
	lista_insertar_en_posicion(lista, &dos, 10);
	lista_insertar_en_posicion(lista, &uno, 16);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 8) == &dos &&
			lista_elemento_en_posicion(lista, 9) == &uno,
		"Se insertan elementos correctamente con posiciones inexistentes.");
	pa2m_afirmar(lista_tamanio(lista) == 10,
		     "Se actualiza correctamente el tamaño de la lista.");
	pa2m_afirmar(
		lista_primero(lista) == &cero && lista_ultimo(lista) == &uno,
		"Se actualizan correctamente el principio y fin de la lista.\n");
	lista_destruir(lista);
}

void pruebas_lista_elemento_en_posicion()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_elemento_en_posicion(NULL, 0) == NULL,
		     "No se puede obtener elementos con una lista NULL.");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL,
		     "No se puede obtener elementos con una lista vacía.");
	int uno = 1, dos = 2, tres = 3;
	lista_insertar(lista, &uno);
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 3) == NULL &&
			lista_elemento_en_posicion(lista, 4) == NULL,
		"No se puede obtener elementos con posiciones inexistentes.");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &uno &&
			     lista_elemento_en_posicion(lista, 1) == &dos &&
			     lista_elemento_en_posicion(lista, 2) == &tres,
		     "Se obtienen los elementos correctos.\n");
	lista_destruir(lista);
}

void pruebas_lista_tamanio()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_tamanio(NULL) == 0,
		     "No se puede obtener el tamaño con una lista NULL.");
	int uno = 1, dos = 2, tres = 3;
	lista_insertar(lista, &uno);
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);
	pa2m_afirmar(lista_tamanio(lista) == 3,
		     "Se obtiene el tamaño correcto.\n");

	lista_destruir(lista);
}

int comparador(void *_elemento1, void *_elemento2)
{
	int *elemento1 = _elemento1;
	int *elemento2 = _elemento2;

	if (elemento1 && elemento2 && *elemento1 == *elemento2)
		return 0;

	return -1;
}

int comparador_es_par(void *_elemento, void *ignorado)
{
	int *elemento = _elemento;

	if (elemento && (*elemento) != 0 && (*elemento) % 2 == 0)
		return 0;

	return -1;
}

void pruebas_lista_buscar_elemento()
{
	lista_t *lista = lista_crear();
	int uno = 1, dos = 2, tres = 3, cuatro = 4, aux = 2, invalido = 7;
	pa2m_afirmar(lista_buscar_elemento(NULL, comparador, &aux) == NULL,
		     "No se puede buscar con una lista NULL.");
	pa2m_afirmar(lista_buscar_elemento(lista, NULL, &aux) == NULL,
		     "Devuelve NULL con una lista vacía.");
	pa2m_afirmar(lista_buscar_elemento(lista, comparador, NULL) == NULL,
		     "Se puede buscar con contexto nulo.");
	lista_insertar_en_posicion(lista, &uno, 0);
	lista_insertar_en_posicion(lista, &dos, 1);
	lista_insertar_en_posicion(lista, &tres, 2);
	lista_insertar_en_posicion(lista, &cuatro, 3);
	pa2m_afirmar(lista_buscar_elemento(lista, comparador, &aux) == &dos &&
			     lista_buscar_elemento(lista, comparador_es_par,
						   NULL) == &dos,
		     "Se buscan elementos correctamente.");
	pa2m_afirmar(lista_buscar_elemento(lista, comparador, &invalido) ==
			     NULL,
		     "Buscar un elemento invalido devuelve NULL.\n");
	lista_destruir(lista);
}

void pruebas_lista_quitar()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4, cinco = 5, seis = 6,
	    siete = 7;

	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_quitar(NULL) == NULL,
		     "No se puede quitar con una lista NULL.");
	pa2m_afirmar(lista_quitar(lista) == NULL,
		     "No se puede quitar con una lista vacía.");
	lista_insertar_en_posicion(lista, &uno, 0);
	pa2m_afirmar(
		lista_quitar(lista) == &uno,
		"Se puede quitar un elemento de una lista con un elemento.");
	lista_insertar(lista, &uno);
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);
	lista_insertar(lista, &cuatro);
	lista_insertar(lista, &cinco);
	lista_insertar(lista, &seis);
	lista_insertar(lista, &siete);
	pa2m_afirmar(lista_quitar(lista) == &siete &&
			     lista_quitar(lista) == &seis &&
			     lista_elemento_en_posicion(lista, 5) == NULL,
		     "Se eliminan elementos correctamente.\n");
	pa2m_afirmar(lista_tamanio(lista) == 5,
		     "Se actualiza correctamente el tamaño de la lista.");
	pa2m_afirmar(lista_ultimo(lista) == &cinco,
		     "Se actualiza correctamente el fin de la lista.\n");
	lista_destruir(lista);
}

void pruebas_lista_quitar_de_posicion()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;

	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_quitar_de_posicion(NULL, 0) == NULL,
		     "No se puede quitar con una lista NULL.");
	pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == NULL,
		     "No se puede quitar con una lista vacía.");
	lista_insertar_en_posicion(lista, &uno, 0);
	pa2m_afirmar(
		lista_quitar_de_posicion(lista, 0) == &uno,
		"Se puede eliminar el elemento de una lista con un elemento.");
	pa2m_afirmar(
		lista_primero(lista) == NULL && lista_ultimo(lista) == NULL,
		"El primero y ultimo de la lista son NULL al eliminar el unico elemento de la lista.");
	lista_insertar_en_posicion(lista, &uno, 0);
	lista_insertar_en_posicion(lista, &dos, 1);
	lista_insertar_en_posicion(lista, &tres, 2);
	lista_insertar_en_posicion(lista, &cuatro, 3);
	pa2m_afirmar(lista_quitar_de_posicion(lista, 3) == &cuatro &&
			     lista_elemento_en_posicion(lista, 3) == NULL &&
			     lista_quitar_de_posicion(lista, 1) == &dos &&
			     lista_elemento_en_posicion(lista, 1) == &tres,
		     "Se eliminan elementos correctamente.");
	lista_insertar_en_posicion(lista, &cuatro, 20);
	pa2m_afirmar(
		lista_quitar_de_posicion(lista, 16) == &cuatro,
		"Se quita el último elemento si la posición es inexistente.");
	pa2m_afirmar(lista_tamanio(lista) == 2,
		     "Se actualiza correctamente el tamanio de la lista.");
	pa2m_afirmar(
		lista_primero(lista) == &uno && lista_ultimo(lista) == &tres,
		"Se actualizan correctamente el principio y fin de la lista.\n");
	lista_destruir(lista);
}

void pruebas_de_lista()
{
	pa2m_nuevo_grupo("Pruebas `lista_crear`");
	pruebas_lista_crear();
	pa2m_nuevo_grupo("Pruebas `lista_insertar`");
	pruebas_lista_insertar();
	pa2m_nuevo_grupo("Pruebas 'lista_insertar_en_posicion`");
	pruebas_lista_insertar_en_posicion();
	pa2m_nuevo_grupo("Pruebas `lista_elemento_en_posicion`");
	pruebas_lista_elemento_en_posicion();
	pa2m_nuevo_grupo("Pruebas `lista_tamanio`");
	pruebas_lista_tamanio();
	pa2m_nuevo_grupo("Pruebas `lista_buscar_elemento`");
	pruebas_lista_buscar_elemento();
	pa2m_nuevo_grupo("Pruebas `lista_quitar`");
	pruebas_lista_quitar();
	pa2m_nuevo_grupo("Pruebas `lista_quitar_de_posicion`");
	pruebas_lista_quitar_de_posicion();
}

int main()
{
	pa2m_nuevo_grupo(
		"================= PRUEBAS TDA LISTA =================");

	pa2m_nuevo_grupo("------------- PRUEBAS DE LISTA --------------");
	pruebas_de_lista();

	return pa2m_mostrar_reporte();
}
