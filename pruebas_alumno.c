#include "pa2m.h"
#include "src/lista.h"

void pruebas_de_lista()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "la lista creada es distinto de NULL");

	pa2m_afirmar(
		lista_insertar(NULL, 0) == NULL,
		"No se puede insertar mediante `lista_insertar` con una lista NULL");
	lista_insertar(lista, NULL);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 0) == NULL,
		"Se puede ingresar un elemento NULL mediante `lista_ingresar`");
	lista_destruir(lista);

	lista_t *lista1 = lista_crear();
	int uno = 1, dos = 2, tres = 3;
	lista_insertar(lista1, &uno);
	lista_insertar(lista1, &dos);
	lista_insertar(lista1, &tres);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista1, 0) == &uno &&
			lista_elemento_en_posicion(lista1, 1) == &dos &&
			lista_elemento_en_posicion(lista1, 2) == &tres,
		"Se ingresan elementos correctamente mediante `lista_insertar`");
	lista_destruir(lista1);

	lista_t *lista2 = lista_crear();
	pa2m_afirmar(
		lista_insertar_en_posicion(NULL, &uno, 0) == NULL,
		"No se puede insertar mediante `lista_insertar_en_posicion` con una lista NULL");

	lista_insertar_en_posicion(lista2, NULL, 0);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista2, 0) == NULL,
		"Se puede ingresar un elemento NULL mediante `lista_insertar_en_posicion`");
	lista_insertar_en_posicion(lista2, &uno, 1);
	lista_insertar_en_posicion(lista2, &dos, 2);
	lista_insertar_en_posicion(lista2, &tres, 3);
	pa2m_afirmar(
		lista_elemento_en_posicion(lista2, 1) == &uno &&
			lista_elemento_en_posicion(lista2, 2) == &dos &&
			lista_elemento_en_posicion(lista2, 3) == &tres,
		"Se ingresan elementos correctamente mediante `lista_insertar_en_posicion`");
	lista_destruir(lista2);
}

int main()
{
	pa2m_nuevo_grupo(
		"================= PRUEBAS TDA LISTA =================");

	pa2m_nuevo_grupo("------------- PRUEBAS DE LISTA --------------");
	pruebas_de_lista();

	return pa2m_mostrar_reporte();
}
