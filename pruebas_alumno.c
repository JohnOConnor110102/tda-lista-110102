#include "pa2m.h"
#include "src/lista.h"

void pruebas_lista_crear()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "la lista creada es distinto de NULL");
	lista_destruir(lista);
}

void pruebas_lista_insertar()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(
		lista_insertar(NULL, 0) == NULL,
		"No se puede insertar mediante `lista_insertar` con una lista NULL");
	lista_insertar(lista, NULL);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 0) == NULL,
		"Se puede ingresar un elemento NULL mediante `lista_insertar`");

	int uno = 1, dos = 2, tres = 3;
	lista_insertar(lista, &uno);
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 1) == &uno &&
			lista_elemento_en_posicion(lista, 2) == &dos &&
			lista_elemento_en_posicion(lista, 3) == &tres,
		"Se ingresan elementos correctamente mediante `lista_insertar`");
	lista_destruir(lista);
}

void pruebas_lista_insertar_en_posicion()
{
	int uno = 1, dos = 2, tres = 3;

	lista_t *lista = lista_crear();
	pa2m_afirmar(
		lista_insertar_en_posicion(NULL, &uno, 0) == NULL,
		"No se puede insertar mediante `lista_insertar_en_posicion` con una lista NULL");

	lista_insertar_en_posicion(lista, NULL, 0);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 0) == NULL,
		"Se puede ingresar un elemento NULL mediante `lista_insertar_en_posicion`");
	lista_insertar_en_posicion(lista, &uno, 1);
	lista_insertar_en_posicion(lista, &dos, 2);
	lista_insertar_en_posicion(lista, &tres, 3);
	lista_insertar_en_posicion(lista, &tres, 2);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 1) == &uno &&
			lista_elemento_en_posicion(lista, 2) == &tres &&
			lista_elemento_en_posicion(lista, 3) == &dos &&
			lista_elemento_en_posicion(lista, 4) == &tres,
		"Se ingresan elementos correctamente mediante `lista_insertar_en_posicion`");
	lista_destruir(lista);
}

void pruebas_lista_quitar()
{
	int uno = 1, dos = 2, tres = 3;

	lista_t *lista = lista_crear();
	pa2m_afirmar(
		lista_quitar(lista) == NULL,
		"No se puede quitar mediante `lista_quitar` con una lista vacía");
	pa2m_afirmar(
		lista_quitar(NULL) == NULL,
		"No se puede quitar mediante `lista_quitar` con una lista NULL");
	lista_insertar_en_posicion(lista, &uno, 0);
	lista_insertar_en_posicion(lista, &dos, 1);
	lista_insertar_en_posicion(lista, &tres, 2);
	pa2m_afirmar(
		lista_quitar(lista) == &tres &&
			lista_elemento_en_posicion(lista, 2) == NULL,
		"Se eliminan elementos correctamente mediante `lista_quitar`");
	lista_destruir(lista);
}

void pruebas_lista_quitar_de_posicion()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;

	lista_t *lista = lista_crear();
	pa2m_afirmar(
		lista_quitar_de_posicion(lista, 0) == NULL,
		"No se puede quitar mediante `lista_quitar_de_posicion` con una lista vacía");
	pa2m_afirmar(
		lista_quitar_de_posicion(NULL, 0) == NULL,
		"No se puede quitar mediante `lista_quitar_de_posicion` con una lista NULL");
	lista_insertar_en_posicion(lista, &uno, 0);
	lista_insertar_en_posicion(lista, &dos, 1);
	lista_insertar_en_posicion(lista, &tres, 2);
	lista_insertar_en_posicion(lista, &cuatro, 3);
	pa2m_afirmar(
		lista_quitar_de_posicion(lista, 3) == &cuatro &&
			lista_elemento_en_posicion(lista, 3) == NULL &&
			lista_quitar_de_posicion(lista, 1) == &dos &&
			lista_elemento_en_posicion(lista, 1) == &tres,
		"Se eliminan elementos correctamente mediante `lista_quitar`");
	lista_destruir(lista);
}

void pruebas_de_lista()
{
	pruebas_lista_crear();
	pruebas_lista_insertar();
	pruebas_lista_insertar_en_posicion();
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
