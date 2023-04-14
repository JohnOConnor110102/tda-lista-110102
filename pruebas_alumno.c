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
	pa2m_afirmar(
		lista_insertar(NULL, 0) == NULL,
		"No se puede insertar mediante `lista_insertar` con una lista NULL.");
	lista_insertar(lista, NULL);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 0) == NULL,
		"Se puede insertar un elemento NULL mediante `lista_insertar`.");

	int uno = 1, dos = 2, tres = 3;
	lista_insertar(lista, &uno);
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 1) == &uno &&
			lista_elemento_en_posicion(lista, 2) == &dos &&
			lista_elemento_en_posicion(lista, 3) == &tres,
		"Se insertan elementos correctamente mediante `lista_insertar`.");
	pa2m_afirmar(
		lista_tamanio(lista) == 4,
		"Se actualiza correctamente el tamaño de la lista durante `lista_insertar`.");
	pa2m_afirmar(
		lista_primero(lista) == NULL && lista_ultimo(lista) == &tres,
		"Se actualizan correctamente el principio y fin de la lista durante `lista_insertar`.\n");
	lista_destruir(lista);
}

void pruebas_lista_insertar_en_posicion()
{
	int uno = 1, dos = 2, tres = 3;

	lista_t *lista = lista_crear();
	pa2m_afirmar(
		lista_insertar_en_posicion(NULL, &uno, 0) == NULL,
		"No se puede insertar mediante `lista_insertar_en_posicion` con una lista NULL.");

	pa2m_afirmar(lista_insertar_en_posicion(lista, NULL, 0) == lista,
		     "Agregar un elemento en el inicio devuelve la lista.");
	pa2m_afirmar(lista_insertar_en_posicion(lista, &uno, 1) == lista,
		     "Agregar un elemento en el inicio devuelve la lista.");
	lista_quitar_de_posicion(lista, 1);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 0) == NULL,
		"Se puede insertar un elemento NULL mediante `lista_insertar_en_posicion`.");
	lista_insertar(lista, &uno);
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);
	lista_insertar_en_posicion(lista, &tres, 2);
	lista_insertar_en_posicion(lista, &uno, 3);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 1) == &uno &&
			lista_elemento_en_posicion(lista, 2) == &tres &&
			lista_elemento_en_posicion(lista, 3) == &uno &&
			lista_elemento_en_posicion(lista, 4) == &dos &&
			lista_elemento_en_posicion(lista, 5) == &tres,
		"Se insertan elementos correctamente mediante `lista_insertar_en_posicion`.");
	lista_insertar_en_posicion(lista, &dos, 10);
	lista_insertar_en_posicion(lista, &uno, 16);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 6) == &dos &&
			lista_elemento_en_posicion(lista, 7) == &uno,
		"Se insertan elementos correctamente mediante `lista_insertar_en_posicion con posiciones inexistentes.");
	pa2m_afirmar(
		lista_tamanio(lista) == 8,
		"Se actualiza correctamente el tamaño de la lista durante `lista_insertar_en_posicion.");
	pa2m_afirmar(
		lista_primero(lista) == NULL && lista_ultimo(lista) == &uno,
		"Se actualizan correctamente el principio y fin de la lista durante `lista_insertar_en_posicion`.\n");
	lista_destruir(lista);
}

void pruebas_lista_elemento_en_posicion()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(
		lista_elemento_en_posicion(NULL, 0) == NULL,
		"No se puede obtener elementos mediante `lista_elementos_en_posicion` con una lista NULL.");
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 0) == NULL,
		"No se puede obtener elementos mediante `lista_elementos_en_posicion` con una lista vacía.");
	int uno = 1, dos = 2, tres = 3;
	lista_insertar(lista, &uno);
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 3) == NULL &&
			lista_elemento_en_posicion(lista, 4) == NULL,
		"No se puede obtener elementos mediante `lista_elementos_en_posicion` con posiciones inexistentes.");
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 0) == &uno &&
			lista_elemento_en_posicion(lista, 1) == &dos &&
			lista_elemento_en_posicion(lista, 2) == &tres,
		"Se obtienen los elementos correctos mediante `lista_elemento_en_posicion`.\n");
	lista_destruir(lista);
}

void pruebas_lista_tamanio()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(
		lista_tamanio(NULL) == 0,
		"No se puede obtener el tamaño mediante `lista_tamanio` con una lista NULL.");
	int uno = 1, dos = 2, tres = 3;
	lista_insertar(lista, &uno);
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);
	pa2m_afirmar(
		lista_tamanio(lista) == 3,
		"Se obtiene el tamaño correcto mediante `lista_tamanio`.\n");

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
	pa2m_afirmar(
		lista_buscar_elemento(NULL, comparador, &aux) == NULL,
		"No se puede buscar mediante `lista_buscar_elemento` con una lista NULL.");
	pa2m_afirmar(
		lista_buscar_elemento(lista, NULL, &aux) == NULL,
		"No se puede buscar mediante `lista_buscar_elemento` con una lista vacía.");
	pa2m_afirmar(
		lista_buscar_elemento(lista, comparador, NULL) == NULL,
		"Se puede buscar mediante `lista_buscar_elemento` con contexto nulo.");
	lista_insertar_en_posicion(lista, &uno, 0);
	lista_insertar_en_posicion(lista, &dos, 1);
	lista_insertar_en_posicion(lista, &tres, 2);
	lista_insertar_en_posicion(lista, &cuatro, 3);
	pa2m_afirmar(
		lista_buscar_elemento(lista, comparador, &aux) == &dos &&
			lista_buscar_elemento(lista, comparador_es_par, NULL) ==
				&dos,
		"Se buscan elementos correctamente mediante `lista_buscar_elemento`.");
	pa2m_afirmar(
		lista_buscar_elemento(lista, comparador, &invalido) == NULL,
		"No se puede buscar un elemento inexistente mediante `lista_buscar_elemento`.\n");
	lista_destruir(lista);
}

void pruebas_lista_quitar()
{
	int uno = 1, dos = 2, tres = 3;

	lista_t *lista = lista_crear();
	pa2m_afirmar(
		lista_quitar(NULL) == NULL,
		"No se puede quitar mediante `lista_quitar` con una lista NULL.");
	pa2m_afirmar(
		lista_quitar(lista) == NULL,
		"No se puede quitar mediante `lista_quitar` con una lista vacía.");
	lista_insertar_en_posicion(lista, &uno, 0);
	pa2m_afirmar(lista_quitar(lista) == &uno,
		     "Puedo quitar un elemento de una lista con un elemento.");
	lista_insertar_en_posicion(lista, &uno, 0);
	lista_insertar_en_posicion(lista, &dos, 1);
	lista_insertar_en_posicion(lista, &tres, 2);
	pa2m_afirmar(
		lista_quitar(lista) == &tres &&
			lista_elemento_en_posicion(lista, 2) == NULL,
		"Se eliminan elementos correctamente mediante `lista_quitar`.\n");
	pa2m_afirmar(
		lista_tamanio(lista) == 2,
		"Se actualiza correctamente el tamanio de la lista durante `lista_quitar`.");
	pa2m_afirmar(
		lista_ultimo(lista) == &dos,
		"Se actualiza correctamente el fin de la lista durante `lista_quitar`.\n");
	lista_destruir(lista);
}

void pruebas_lista_quitar_de_posicion()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;

	lista_t *lista = lista_crear();
	pa2m_afirmar(
		lista_quitar_de_posicion(NULL, 0) == NULL,
		"No se puede quitar mediante `lista_quitar_de_posicion` con una lista NULL.");
	pa2m_afirmar(
		lista_quitar_de_posicion(lista, 0) == NULL,
		"No se puede quitar mediante `lista_quitar_de_posicion` con una lista vacía.");
	lista_insertar_en_posicion(lista, &uno, 0);
	pa2m_afirmar(
		lista_quitar_de_posicion(lista, 0) == &uno,
		"Se puede eliminar el primer elemento de la lista mediante `lista_quitar_de_posicion`.");
	lista_insertar_en_posicion(lista, &uno, 0);
	lista_insertar_en_posicion(lista, &dos, 1);
	lista_insertar_en_posicion(lista, &tres, 2);
	lista_insertar_en_posicion(lista, &cuatro, 3);
	pa2m_afirmar(
		lista_quitar_de_posicion(lista, 3) == &cuatro &&
			lista_elemento_en_posicion(lista, 3) == NULL &&
			lista_quitar_de_posicion(lista, 1) == &dos &&
			lista_elemento_en_posicion(lista, 1) == &tres,
		"Se eliminan elementos correctamente mediante `lista_quitar`.");
	pa2m_afirmar(
		lista_tamanio(lista) == 2,
		"Se actualiza correctamente el tamanio de la lista durante `lista_quitar_de_posicion`.");
	//lista_insertar_en_posicion(lista, &cuatro, 3);
	lista_quitar_de_posicion(lista, 0);
	pa2m_afirmar(
		lista_primero(lista) == &uno && lista_ultimo(lista) == &tres,
		"Se actualizan correctamente el principio y fin de la lista durante `lista_quitar_de_posicion`.\n");
	lista_destruir(lista);
}

void pruebas_de_lista()
{
	pa2m_nuevo_grupo("Pruebas `lista_crear`");
	pruebas_lista_crear();
	pa2m_nuevo_grupo("Pruebas `lista_insertar`");
	pruebas_lista_insertar();
	pruebas_lista_insertar_en_posicion();
	pruebas_lista_elemento_en_posicion();
	pruebas_lista_tamanio();
	pruebas_lista_buscar_elemento();
	pruebas_lista_quitar();
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
