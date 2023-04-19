#include "pa2m.h"
#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"

void pruebas_lista_crear()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Se puede crar una lista.");
	pa2m_afirmar(lista_tamanio(lista) == 0, "La lista creada está vacía.");
	pa2m_afirmar(
		lista_primero(lista) == NULL && lista_ultimo(lista) == NULL,
		"Se inicializan en NULL los elementos principio y fin de la lista.");
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
		"Se actualizan correctamente el principio y fin de la lista.");
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
		"Se actualizan correctamente el principio y fin de la lista.");
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
		     "Se obtienen los elementos correctos.");
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
		     "Se obtiene el tamaño correcto.");

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
		     "Buscar un elemento invalido devuelve NULL.");
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
		     "Se eliminan elementos correctamente.");
	pa2m_afirmar(lista_tamanio(lista) == 5,
		     "Se actualiza correctamente el tamaño de la lista.");
	pa2m_afirmar(lista_ultimo(lista) == &cinco,
		     "Se actualiza correctamente el fin de la lista.");
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
		"Se actualizan correctamente el principio y fin de la lista.");
	lista_destruir(lista);
}

void pruebas_lista_primero_y_ultimo()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;
	lista_t *lista = lista_crear();
	pa2m_afirmar(
		lista_primero(NULL) == NULL,
		"No se puede acceder al primer elemento de una lista NULL.");
	pa2m_afirmar(
		lista_ultimo(NULL) == NULL,
		"No se puede acceder al último elemento de una lista NULL.");
	pa2m_afirmar(
		lista_primero(lista) == NULL,
		"No se puede acceder al primer elemento de una lista vacía");
	pa2m_afirmar(
		lista_ultimo(lista) == NULL,
		"No se puede acceder al último elemento de una lista vacía");
	lista_insertar_en_posicion(lista, &uno, 0);
	lista_insertar_en_posicion(lista, &dos, 1);
	lista_insertar_en_posicion(lista, &tres, 2);
	lista_insertar_en_posicion(lista, &cuatro, 3);
	pa2m_afirmar(lista_primero(lista) == &uno,
		     "El primer elemento de la lista es el correcto.");
	pa2m_afirmar(lista_ultimo(lista) == &cuatro,
		     "El último elemento de la lista es el correcto.");
	lista_destruir(lista);
}

void pruebas_lista_vacia()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_vacia(NULL) == true,
		     "Devuelve true si la lista es NULL.");
	pa2m_afirmar(lista_vacia(lista) == true,
		     "Devuelve true si la lista está vacía.");
	lista_insertar_en_posicion(lista, &uno, 0);
	pa2m_afirmar(lista_vacia(lista) == false,
		     "Devuelve false si la lista tiene un elemento.");
	lista_insertar_en_posicion(lista, &dos, 1);
	lista_insertar_en_posicion(lista, &tres, 2);
	lista_insertar_en_posicion(lista, &cuatro, 3);
	pa2m_afirmar(lista_vacia(lista) == false,
		     "Devuelve false si la lista tiene más de un elemento.");
	lista_destruir(lista);
}

void sumar_uno(void *_elemento)
{
	if (_elemento) {
		int *elemento = _elemento;
		(*elemento)++;
	}
}

void pruebas_lista_destuir_todo()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;
	lista_t *lista = lista_crear();
	lista_insertar(lista, &uno);
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);
	lista_insertar(lista, &cuatro);
	lista_destruir_todo(lista, sumar_uno);
	pa2m_afirmar(uno == 2 && dos == 3 && tres == 4 && cuatro == 5,
		     "Se aplicó la función a todos los elementos.");
	lista_destruir(lista);
}

void pruebas_lista_iterador_crear()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_iterador_crear(NULL) == NULL,
		     "No se puede crear un iterador con una lista NULL.");
	lista_iterador_t *it = lista_iterador_crear(lista);
	pa2m_afirmar(it != NULL,
		     "Se puede crear un iterador con una lista vacía.");
	lista_iterador_destruir(it);
	lista_insertar_en_posicion(lista, &uno, 0);
	lista_insertar_en_posicion(lista, &dos, 1);
	lista_insertar_en_posicion(lista, &tres, 2);
	lista_insertar_en_posicion(lista, &cuatro, 3);
	lista_iterador_t *it_2 = lista_iterador_crear(lista);
	pa2m_afirmar(it_2 != NULL,
		     "Se puede crear un iterador con una lista con elementos.");
	lista_iterador_destruir(it_2);
	lista_destruir(lista);
}

void pruebas_lista_iterador_tiene_siguiente()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;
	lista_t *lista = lista_crear();
	lista_iterador_t *it = lista_iterador_crear(lista);
	pa2m_afirmar(lista_iterador_tiene_siguiente(NULL) == false,
		     "Devuelve false si el iterador es NULL.");
	pa2m_afirmar(lista_iterador_tiene_siguiente(it) == false,
		     "Devuelve false si la lista está vacía,");
	lista_iterador_destruir(it);
	lista_insertar_en_posicion(lista, &uno, 0);
	lista_insertar_en_posicion(lista, &dos, 1);
	lista_insertar_en_posicion(lista, &tres, 2);
	lista_insertar_en_posicion(lista, &cuatro, 3);
	lista_iterador_t *it_2 = lista_iterador_crear(lista);
	pa2m_afirmar(
		lista_iterador_tiene_siguiente(it_2) == true,
		"Devuelve true si el iterador está en el primer elemento.");
	lista_iterador_avanzar(it_2);
	pa2m_afirmar(
		lista_iterador_tiene_siguiente(it_2) == true,
		"Devuelve true si el iterador está en el segundo elemento.");
	lista_iterador_avanzar(it_2);
	pa2m_afirmar(
		lista_iterador_tiene_siguiente(it_2) == true,
		"Devuelve true si el iterador está en el tercer elemento.");
	lista_iterador_avanzar(it_2);
	pa2m_afirmar(
		lista_iterador_tiene_siguiente(it_2) == true,
		"Devuelve true si el iterador está en el último elemento.");
	lista_iterador_destruir(it_2);
	lista_destruir(lista);
}

void pruebas_lista_iterador_avanzar()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;
	lista_t *lista = lista_crear();
	lista_iterador_t *it = lista_iterador_crear(lista);
	pa2m_afirmar(lista_iterador_avanzar(NULL) == false,
		     "No se puede avanzar con un iterador NULL.");
	pa2m_afirmar(lista_iterador_avanzar(it) == false,
		     "No se puede avanzar en una lista vacía");
	lista_iterador_destruir(it);
	lista_insertar_en_posicion(lista, &uno, 0);
	lista_insertar_en_posicion(lista, &dos, 1);
	lista_insertar_en_posicion(lista, &tres, 2);
	lista_insertar_en_posicion(lista, &cuatro, 3);
	lista_iterador_t *it_2 = lista_iterador_crear(lista);
	pa2m_afirmar(
		lista_iterador_avanzar(it_2) == true,
		"Devuelve true si el iterador estaba en el primer elemento.");
	pa2m_afirmar(
		lista_iterador_avanzar(it_2) == true,
		"Devuelve true si el iterador estaba en el segundo elemento.");
	pa2m_afirmar(
		lista_iterador_avanzar(it_2) == true,
		"Devuelve true si el iterador estaba en el tercer elemento.");
	pa2m_afirmar(
		lista_iterador_avanzar(it_2) == false &&
			lista_iterador_elemento_actual(it_2) == NULL,
		"Devuelve false si el iterador estaba en el último elemento, pero igualmente avanza el iterador.");
	pa2m_afirmar(
		lista_iterador_avanzar(it_2) == false,
		"El iterador no avanza más allá de un elemento posterior al último de la lista, y no genera errores.");
	lista_iterador_destruir(it_2);
	lista_destruir(lista);
}

void pruebas_lista_iterador_elemento_actual()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;
	lista_t *lista = lista_crear();
	lista_iterador_t *it = lista_iterador_crear(lista);
	pa2m_afirmar(
		lista_iterador_elemento_actual(NULL) == NULL,
		"No se puede acceder al elemento actual de un iterador NULL.");
	pa2m_afirmar(lista_iterador_elemento_actual(it) == NULL,
		     "Devuelve NULL si la lista está vacía.");
	lista_iterador_destruir(it);
	lista_insertar_en_posicion(lista, &uno, 0);
	lista_insertar_en_posicion(lista, &dos, 1);
	lista_insertar_en_posicion(lista, &tres, 2);
	lista_insertar_en_posicion(lista, &cuatro, 3);
	lista_iterador_t *it_2 = lista_iterador_crear(lista);
	pa2m_afirmar(
		lista_iterador_elemento_actual(it_2) == &uno,
		"El elemento actual en la primera posición es el correcto.");
	lista_iterador_avanzar(it_2);
	pa2m_afirmar(
		lista_iterador_elemento_actual(it_2) == &dos,
		"El elemento actual en la segunda posición es el correcto.");
	lista_iterador_avanzar(it_2);
	pa2m_afirmar(
		lista_iterador_elemento_actual(it_2) == &tres,
		"El elemento actual en la tercer posición es el correcto.");
	lista_iterador_avanzar(it_2);
	pa2m_afirmar(
		lista_iterador_elemento_actual(it_2) == &cuatro,
		"El elemento actual en la última posición es el correcto.");
	lista_iterador_avanzar(it_2);
	pa2m_afirmar(
		lista_iterador_elemento_actual(it_2) == NULL,
		"El elemento actual, habiendo invocado a `lista_iterador_avanzar` estando en la última posición es el correcto.");
	lista_iterador_destruir(it_2);
	lista_destruir(lista);
}

bool sumar_uno_recorriendo_todo(void *_elemento, void *ignorado)
{
	if (_elemento) {
		int *elemento = _elemento;
		(*elemento)++;
	}
	return true;
}

void pruebas_lista_con_cada_elemento()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4, contexto = 100;
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_con_cada_elemento(NULL, sumar_uno_recorriendo_todo,
					     &contexto) == 0,
		     "Devuelve 0 si la lista es NULL.");
	pa2m_afirmar(lista_con_cada_elemento(lista, NULL, &contexto) == 0,
		     "Devuelve 0 si la lista es NULL.");
	pa2m_afirmar(lista_con_cada_elemento(lista, sumar_uno_recorriendo_todo,
					     &contexto) == 0,
		     "Devuelve 0 si la lista está vacía.");
	lista_insertar(lista, &uno);
	lista_insertar(lista, &dos);
	lista_insertar(lista, &tres);
	lista_insertar(lista, &cuatro);
	size_t elementos_recorridos = 0;
	elementos_recorridos = lista_con_cada_elemento(
		lista, sumar_uno_recorriendo_todo, &contexto);
	pa2m_afirmar(elementos_recorridos == 4,
		     "Se recorren todos los elementos.");
	pa2m_afirmar(uno == 2 && dos == 3 && tres == 4 && cuatro == 5,
		     "Se aplicó la función a todos los elementos.");
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
	pa2m_nuevo_grupo("Pruebas `lista_primero` y `lista_ultimo`");
	pruebas_lista_primero_y_ultimo();
	pa2m_nuevo_grupo("Pruebas `lista_vacia`");
	pruebas_lista_vacia();
	pa2m_nuevo_grupo("Pruebas `lista_iterador_crear`");
	pruebas_lista_iterador_crear();
	pa2m_nuevo_grupo("Pruebas `lista_iterador_tiene_siguiente`");
	pruebas_lista_iterador_tiene_siguiente();
	pa2m_nuevo_grupo("Pruebas `lista_iterador_avanzar`");
	pruebas_lista_iterador_avanzar();
	pa2m_nuevo_grupo("Pruebas `lista_iterador_elemento_actual`");
	pruebas_lista_iterador_elemento_actual();
	pa2m_nuevo_grupo("Pruebas `lista_con_cada_elemento`");
	pruebas_lista_con_cada_elemento();
	pa2m_nuevo_grupo("Pruebas `lista_destuir_todo`");
	pruebas_lista_destuir_todo();
}

void pruebas_pila_crear()
{
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila != NULL, "Se puede crar una pila.");
	pa2m_afirmar(pila_tamanio(pila) == 0, "La pila creada está vacía.");
	pa2m_afirmar(
		lista_primero((lista_t *)pila) == NULL &&
			lista_ultimo((lista_t *)pila) == NULL,
		"Se inicializan en NULL los elementos principio y fin de la pila.");
	pa2m_afirmar(pila_tope(pila) == NULL, "El tope de la pila es NULL.");
	pila_destruir(pila);
}

void pruebas_pila_apilar()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila_apilar(NULL, &uno) == NULL,
		     "No se puede apilar con una pila NULL.");
	pa2m_afirmar(pila_apilar(pila, NULL) == pila,
		     "Se puede apilar un elemento NULL.");
	pa2m_afirmar(pila_apilar(pila, &dos) == pila &&
			     pila_apilar(pila, &tres) == pila &&
			     pila_apilar(pila, &cuatro) == pila,
		     "Se pueden apilar varios elementos");
	pa2m_afirmar(pila_tamanio(pila) == 4,
		     "Se actualiza correctamente el tamanio de la pila.");
	pila_destruir(pila);
}

void pruebas_pila_desapilar()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila_desapilar(NULL) == NULL,
		     "No se puede desapilar con una pula NULL.");
	pa2m_afirmar(pila_desapilar(pila) == NULL,
		     "No se puede desapilar un elemento de una lista vacía.");
	pila_apilar(pila, &uno);
	pila_apilar(pila, &dos);
	pila_apilar(pila, &tres);
	pila_apilar(pila, &cuatro);
	pa2m_afirmar(
		pila_desapilar(pila) == &cuatro,
		"Se puede desapilar un elemento, y devuelve el elemento correcto.");
	pa2m_afirmar(pila_tamanio(pila) == 3,
		     "Se actualiza correctamente el tamanio de la pila.");
	pila_desapilar(pila);
	pila_desapilar(pila);
	pila_desapilar(pila);
	pa2m_afirmar(pila_tamanio(pila) == 0,
		     "Se pueden desapilar todos los elementos de una pila.");
	pila_destruir(pila);
}

void pruebas_pila_tope()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila_tope(NULL) == NULL,
		     "No se puede saber el tope de una pila NULL.");
	pa2m_afirmar(pila_tope(pila) == NULL,
		     "No se puede saber el tope de una lista vacía.");
	pila_apilar(pila, &uno);
	pila_apilar(pila, &dos);
	pila_apilar(pila, &tres);
	pila_apilar(pila, &cuatro);
	pa2m_afirmar(pila_tope(pila) == &cuatro, "El tope es el correcto.");
	pila_desapilar(pila);
	pa2m_afirmar(pila_tope(pila) == &tres,
		     "El tope es el correcto luego de desapilar.");
	pila_desapilar(pila);
	pa2m_afirmar(pila_tope(pila) == &dos,
		     "El tope es el correcto luego de desapilar.");
	pila_desapilar(pila);
	pa2m_afirmar(pila_tope(pila) == &uno,
		     "El tope es el correcto luego de desapilar.");
	pila_destruir(pila);
}

void pruebas_pila_tamanio()
{
	int uno = 1, dos = 2, tres = 3;
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila_tamanio(NULL) == 0, "Devuelve 0 con una pila NULL.");
	pa2m_afirmar(pila_tamanio(pila) == 0,
		     "El tamaño de una pila vacía es 0.");
	pila_apilar(pila, &uno);
	pa2m_afirmar(pila_tamanio(pila) == 1,
		     "El tamaño es el correcto luego de apilar.");
	pila_apilar(pila, &dos);
	pa2m_afirmar(pila_tamanio(pila) == 2,
		     "El tamaño es el correcto luego de apilar.");
	pila_apilar(pila, &tres);
	pa2m_afirmar(pila_tamanio(pila) == 3,
		     "El tamaño es el correcto luego de apilar.");
	pila_desapilar(pila);
	pa2m_afirmar(pila_tamanio(pila) == 2,
		     "El tamaño es el correcto luego de desapilar.");
	pila_destruir(pila);
}

void pruebas_pila_vacia()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila_vacia(NULL) == false,
		     "Devuelve false con una pila NULL.");
	pa2m_afirmar(pila_vacia(pila) == true,
		     "Devuelve true con una pila sin elementos.");
	pila_apilar(pila, &uno);
	pa2m_afirmar(pila_vacia(pila) == false,
		     "Devuelve false con una pila con un elemento.");
	pila_apilar(pila, &dos);
	pila_apilar(pila, &tres);
	pila_apilar(pila, &cuatro);
	pa2m_afirmar(pila_vacia(pila) == false,
		     "Devuelve false con una pila con varios elementos.");
	pila_destruir(pila);
}

void pruebas_de_pila()
{
	pa2m_nuevo_grupo("Pruebas `pila_crear`");
	pruebas_pila_crear();
	pa2m_nuevo_grupo("Pruebas `pila_apilar`");
	pruebas_pila_apilar();
	pa2m_nuevo_grupo("Pruebas `pila_desapilar`");
	pruebas_pila_desapilar();
	pa2m_nuevo_grupo("Pruebas `pila_tope`");
	pruebas_pila_tope();
	pa2m_nuevo_grupo("Pruebas `pila_tamanio`");
	pruebas_pila_tamanio();
	pa2m_nuevo_grupo("Pruebas `pila_vacia`");
	pruebas_pila_vacia();
}

void pruebas_cola_crear()
{
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola != NULL, "Se puede crear una cola.");
	pa2m_afirmar(cola_tamanio(cola) == 0, "La cola creada está vacía.");
	pa2m_afirmar(
		lista_primero((lista_t *)cola) == NULL &&
			lista_ultimo((lista_t *)cola) == NULL,
		"Se inicializan en NULL los elementos principio y fin de la cola.");
	pa2m_afirmar(cola_frente(cola) == NULL,
		     "El frente de la cola es NULL.");
	cola_destruir(cola);
}

void pruebas_cola_encolar()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;
	cola_t *cola = (cola_t *)lista_crear();
	pa2m_afirmar(cola_encolar(NULL, 0) == NULL,
		     "No se puede encolar en una cola NULL.");
	pa2m_afirmar(cola_encolar(cola, NULL) == cola,
		     "Se puede encolar un elemento NULL.");
	pa2m_afirmar(cola_encolar(cola, &uno) == cola &&
			     cola_encolar(cola, &dos) == cola &&
			     cola_encolar(cola, &tres) == cola &&
			     cola_encolar(cola, &cuatro) == cola,
		     "Se pueden encolar varios elementos.");
	pa2m_afirmar(cola_tamanio(cola) == 5,
		     "Se actualiza correctamente el tamaño de la cola.");
	cola_destruir(cola);
}

void pruebas_cola_desencolar()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola_desencolar(NULL) == NULL,
		     "No se puede desencolar de una cola NULL.");
	pa2m_afirmar(cola_desencolar(cola) == NULL,
		     "No se puede desencolar de una cola vacía");
	cola_encolar(cola, &uno);
	cola_encolar(cola, &dos);
	cola_encolar(cola, &tres);
	cola_encolar(cola, &cuatro);
	pa2m_afirmar(
		cola_desencolar(cola) == &uno,
		"Se puede desencolar un elemento y devuelve el elemento correcto.");
	pa2m_afirmar(cola_tamanio(cola) == 3,
		     "Se actualiza correctamente el tamaño de la cola.");
	cola_desencolar(cola);
	cola_desencolar(cola);
	cola_desencolar(cola);
	pa2m_afirmar(cola_tamanio(cola) == 0,
		     "Se pueden desencolar todos los elementos.");
	cola_destruir(cola);
}

void pruebas_cola_frente()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola_frente(NULL) == NULL,
		     "No se puede saber el frente de una cola NULL.");
	pa2m_afirmar(cola_frente(cola) == NULL,
		     "No se puede saber el frente de una cola vacía.");
	cola_encolar(cola, &uno);
	cola_encolar(cola, &dos);
	cola_encolar(cola, &tres);
	cola_encolar(cola, &cuatro);
	pa2m_afirmar(cola_frente(cola) == &uno, "El frente es el correcto.");
	cola_desencolar(cola);
	pa2m_afirmar(cola_frente(cola) == &dos,
		     "El frente es el correcto luego de desencolar.");
	cola_desencolar(cola);
	pa2m_afirmar(cola_frente(cola) == &tres,
		     "El frente es el correcto luego de desencolar.");
	cola_desencolar(cola);
	pa2m_afirmar(cola_frente(cola) == &cuatro,
		     "El frente es el correcto luego de desencolar.");
	cola_destruir(cola);
}

void pruebas_cola_tamanio()
{
	int uno = 1, dos = 2, tres = 3;
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola_tamanio(NULL) == 0, "Devuelve 0 con una cola NULL.");
	pa2m_afirmar(cola_tamanio(cola) == 0,
		     "El tamaño de una cola vacía es 0.");
	cola_encolar(cola, &uno);
	pa2m_afirmar(cola_tamanio(cola) == 1,
		     "El tamaño es el correcto luego de encolar.");
	cola_encolar(cola, &dos);
	pa2m_afirmar(cola_tamanio(cola) == 2,
		     "El tamaño es el correcto luego de encolar.");
	cola_encolar(cola, &tres);
	pa2m_afirmar(cola_tamanio(cola) == 3,
		     "El tamaño es el correcto luego de encolar.");
	cola_desencolar(cola);
	pa2m_afirmar(cola_tamanio(cola) == 2,
		     "El tamaño es el correcto luego de desencolar.");
	cola_destruir(cola);
}

void pruebas_cola_vacia()
{
	int uno = 1, dos = 2, tres = 3, cuatro = 4;
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola_vacia(NULL) == false,
		     "Devuelve false con una cola NULL.");
	pa2m_afirmar(cola_vacia(cola) == true,
		     "Devuelve true con una cola sin elementos.");
	cola_encolar(cola, &uno);
	pa2m_afirmar(cola_vacia(cola) == false,
		     "Devuelve false con una cola con un elemento.");
	cola_encolar(cola, &dos);
	cola_encolar(cola, &tres);
	cola_encolar(cola, &cuatro);
	pa2m_afirmar(cola_vacia(cola) == false,
		     "Devuelve false con una cola con varios elementos.");
	cola_destruir(cola);
}

void pruebas_de_cola()
{
	pa2m_nuevo_grupo("Pruebas `cola_crear`");
	pruebas_cola_crear();
	pa2m_nuevo_grupo("Pruebas `cola_encolar`");
	pruebas_cola_encolar();
	pa2m_nuevo_grupo("Pruebas `cola_desencolar`");
	pruebas_cola_desencolar();
	pa2m_nuevo_grupo("Pruebas `cola_frente`");
	pruebas_cola_frente();
	pa2m_nuevo_grupo("Pruebas `cola_tamanio`");
	pruebas_cola_tamanio();
	pa2m_nuevo_grupo("Pruebas `cola_vacia`");
	pruebas_cola_vacia();
}

int main()
{
	pa2m_nuevo_grupo(
		"================= PRUEBAS TDA LISTA =================");

	pa2m_nuevo_grupo("------------- PRUEBAS DE LISTA --------------");
	pruebas_de_lista();

	pa2m_nuevo_grupo("-------------- PRUEBAS DE PILA --------------");
	pruebas_de_pila();

	pa2m_nuevo_grupo("-------------- PRUEBAS COLA --------------");
	pruebas_de_cola();

	return pa2m_mostrar_reporte();
}
