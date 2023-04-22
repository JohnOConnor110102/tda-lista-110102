<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA LISTA - PILA - COLA

## Repositorio de John O'Connor - 110102 - johnoc1712@gmail.com

- Para compilar:

```bash
Pruebas cátedra: gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g src/*.c pruebas_chanutron.o -o pruebas_chanutron

Pruebas alumno: gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g src/*.c pruebas_alumno.c -o pruebas_alumno
```

- Para ejecutar:

```bash
Pruebas cátedra: ./pruebas_chanutron

Pruebas alumno: ./pruebas_alumno
```

- Para ejecutar con valgrind:

```bash
Pruebas cátedra: valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes ./pruebas_chanutron

Pruebas alumno: valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes ./pruebas_alumno
```

---

## Funcionamiento

Las estructuras desarrolladas en el TP se basan en una LISTA DE NODOS SIMPLEMENTE ENLAZADOS.

En principio, se crea una lista mediante `lista_crear`, proceso representado en el siguiente diagrama de memoria:

![Diagrama memoria lista_crear](img/diagrama_lista_crear.jpeg)

A partir de esta lista, se pueden realizar diversas operaciones, siendo estas: insertar en cualquier posición de la lista, quitar en cualquier posición de la lista, obtener el elemento de cualquier posición de la lista, buscar dentro de los elementos el primero de ellos que cumpla cierta condición aplicada (lista_buscar_elemento), verificar si la lista está vacía, obtener el tamañod de la lista y liberar la memoria reservada por la lista, teniendo la opción de aplicar una función a parte a cada uno de los elementos de la lista en el mismo proceso.

Para la inserción de elementos se utiliza la función `crear_nodo`, cuyo proceso de utilización de memoria se ve representado en el siguiente esquema:

![Diagrama memoria crar_nodo](img/diagrama_crear_nodo.jpeg)

A su vez, se da la posibilidad de crear un iterador interno para poder recorrer la lista, mediante `lista_iterador_crear`. Dentro del mismo se pueden realizar distintas operaciones, en este caso siendo: verificar si el iterador tiene un elemento siguiente para iterar, avanzar el iterador, obtener el elemento actual en que está parado el iterador, y destruir el iterador.

El proceso de manejo de memoria dinámica de `lista_iterador_crear` se ve representado en el siguiente diagrama:

![Diagrama memoria lista_iterador_crear](img/diagrama_lista_iterador_crear.jpeg)

A parte de la estructura LISTA, se pueden crear tanto una COLA como una PILA. En ambos casos, se reutiliza totalmente la implementación de una LISTA, únicamente teniendo las consideraciones necesesarias en cada caso.

En cuanto a la COLA, las operaciones disponibles son las siguientes: crear la cola, encolar un elemento a la misma, desencolar un elemento, obtener el frente de la cola, obtener su tamaño, verificar si está vacía, y destruirla, es decir liberar la memoria que haya reservado.

Para su implementación, al haberse reutilizado las estructuras de LISTA, se realizaron los mismos manejos de memoria representados en los diagramas anteriores.

Por otro lado, en la PILA, las operaciones disponibles son las siguientes: crear una pila, apilar un elemento, desapilar un elemento, obtener el tope de la pila, obtener su tamaño, verificar si está vacía, y destruirla liberando su memoria reservada.

Para el desarrollo del TP, se crearon funciones auxiliares para ayudar con la modularización del código y lograr una visualización más prolija del mismo.

La función `insertar_en_lista_sin_nodos` se utiliza para el caso borde en que se quiera insertar el primer elemento a la lista, y se encarga de inicializar y actualizar los campos correspondientes de la lista, devolviendola al final de su ejecución.

La función `iterar_hasta_posicion` recorre los elementos de la lista hasta la posición indicada y devuelve el nodo en que finalizó la iteración.

La función `crear_nodo` se encarga de reservar la memoria dinámica necesaria para el nodo a crear, e inicializa los valores del mismo con los valores correspondientes, para finalmente devolver el nodo creado.

---

## Respuestas a las preguntas teóricas

- ¿Qué es una lista/pila/cola? Explicar con diagramas.
  Una lista es un tipo de TDA, que representa una sucesión de elementos ordenados. La misma se puede implementar de diferentes maneras, de las cuales se destacan tres: vector estático, vector dinámico y nodos simple o doblemente enlazados. Igualmente, una pila y una cola son tipos de lista, cuyos funcionamientos generales diferencian en algunas cuestiones con el de una lista.

Una lista permite tener una sucesión de elementos, y aplicar operaciones en torno a la misma cómo: crearla, insertar, eliminar y acceder a un elemento en cualquier posición de la lista, verificar si está vacía, verificar la cantidad de elementos que tiene, destruirla, entre otras.

Mientras tanto, una pila carece de algunas de estas operaciones. Visualmente una pila se podría representar como un conjunto de libros apilados uno encima del otro. En cuanto a las operaciones que no están presentes en la pila se encuentran por ejemplo insertar, eliminar y acceder a elementos en cualquier posición de la lista. En este caso, solo se puede apilar, desapilar y acceder al último elemento de la pila, el tope, que sería el libro de más arriba. De este modo, se dice que su manejo es del tipo FILO: "First In, Last Out".

Y por último una cola se podría representar como la fila que se hace para pagar en un supermercado. Las operaciones que cambian en este caso son: insertar, que únicamente se puede encolar un elemento en el final de la lista, quitar, que sólo se permite desencolar un elemento en el principio de la lista, y acceder al elemento, donde sólo se permite acceder al primer elemento de la lista, como quien está pasando sus productos por la caja del supermercado. Así, la cola tiene un manejo del tipo FIFO: "First In, Fist Out".

Una lista se vería representada con el siguiente diagrama:

![Diagrama Lista](img/diagrama_lista_vector_estatico.jpeg)
![Diagrama Lista](img/diagrama_lista_vector_dinamico.jpeg)
![Diagrama Lista](img/diagrama_lista_nodos.jpeg)

Una pila se vería representada con el siguiente diagrama:

![Diagrama Lista](img/diagrama_pila_vector_estatico.jpeg)
![Diagrama Lista](img/diagrama_pila_vector_dinamico.jpeg)
![Diagrama Lista](img/diagrama_pila_nodos.jpeg)

Una cola se vería representada con el siguiente diagrama:

![Diagrama Lista](img/diagrama_cola_vector_estatico.jpeg)
![Diagrama Lista](img/diagrama_cola_vector_dinamico.jpeg)
![Diagrama Lista](img/diagrama_cola_nodos.jpeg)

- Explica y analiza las diferencias de complejidad entre las implementaciones de lista simplemente enlazada, doblemente enlazada y vector dinámico para las operaciones:

En principio, la complejidad de las funciones en cada implementación de lista, dependerá de las diferentes maneras en las que se desarrolló cada algoritmo en su totalidad, la manera en que se define el stuct de lista, entre otras cuestiones.

- Insertar/obtener/eliminar al inicio
  Lista simplemente enlazada: en esta implementación, si se tiene en cuenta que dentro del struct lista existe un puntero al primer nodo de la lista, se asegura una complejidad de O(1), ya que las instrucciones del algoritmo consisten en asignasiones que dependen de la operación a reailzar, pero que en fin tienen complejidad O(1).

  Lista doblemente enlazada: con esta implementación el proceso es similar a aquel realizado en una lista simplemente enlazada. Teniendo en cuenta que en el desarrollo del algoritmo, se incluyó en el struct lista un puntero al primer elemento de la lista, la operación en cuestión tiene una complejidad de O(1), ya que las instrucciones a realizar consisten en asignasiones que dependen de la operación a realizar, que en fin tienen complejidad O(1).

  Vector dinámico: si se tiene un vector dinámico lineal, obtener el primer elemento de la lista conlleva una complejidad de O(1), al poder acceder fácilmente al mismo mediante su indice. En cuanto a eliminar e insertar el elemento al inicio, dichas operaciones conllevan una complejidad O(n), ya que en ambos casos es necesario recorrer todos los elementos del vector, sea para moverlos una posición atrás para poder insertar el elemento al inicio o para mover todos los elementos una posición adelante en el vector en caso de haberlo eliminado.

- Insertar/obtener/eliminar al final
  Lista simplemente enlazada: al igual que haciéndolo al inicio, si se tiene en cuenta que dentro del struct lista existe un puntero al nodo final de la lista, obtener el elemento del final tiene una complejidad de O(1), ya que las instrucciones a realizar son acceder a dicho nodo y devolver el elemento. En caso de insertar un elemento al final, ocupa una complejidad de O(1), ya que teniendo el puntero al último elemento, las instrucciones a realizar son la asignación del puntero siguiente del mismo al nodo a insertar, y la inicialización del último. Mientras tanto, al eliminar un elemento al final, inevitablemente se tendría que iterar hasta el nodo previo en la lista, para poder hacer la correcta asignación de los punteros siguiente de dicho nodo. Por lo tanto, esta operacion tiene complejidad O(n).

  Lista doblemente enlazada: en este caso, teniendo en cuenta que en cada nodo se tiene un puntero al anterior, las tres operaciones resultan tener complejidad O(1), ya que tanto en obtener como en insertar las instrucciones son la mismas que las explicadas en el caso de una lista simplemente enlazada, y además al eliminar el nodo al final, la asignasión de punteros del anterior se realiza utilizando el puntero disponible en el nodo final al anterior. Por lo tanto, en este caso las tres operaciones conllevan una complejidad de O(1).

  Vector dinámico: en este caso, si se tiene en cuenta que el realloc, a realizar a la hora de agrandar el tamaño del vector en 1 al insertar, no falla, las complejidades de las opereaciones en cuestión resultan O(1), ya que todas sus posiciones son fácilmente accesibles mediante el índice del vector y el resto de instrucciones a realizar son asignaciones o free. Si se tiene en cuenta que el realloc podría fallar, en ese caso se deben mover todos los elementos del vector a una nueva dirección de memoria, por lo que la complejidad escalaría a O(n).

- Insertar/obtener/eliminar al medio
  Lista simplemente enlazada: en el caso de realizar estas operaciones en los nodos del medio de la lista, se toma en cuenta que se deberá iterar N-veces para llegar a dicha posición, o a la anterior en caso de tener que eliminar. Por esto, el hecho de que una vez ya iterado hasta el nodo en cuestión, el resto de las instrucciones a realizar sean de complejidad O(1) por se asignaciones, la complejidad dependerá de ese N al que se debe llegar. Por lo tanto, la complejidad de las tres operaciones en cuestión resulta O(n).

  Lista doblemente enlazada: este caso resulta similar al de una lista simplemente enlazada. Igualmente se toma en cuenta que se realizarán (N sobre dos)-iteraciones hasta el nodo en cuestión, ya que se puede empezar a iterar desde el inicio o fin y como peor caso el nodo está en el medio. Esto en teoría, sí acorta la cantidad de iteraciones a realizar, pero al ser N/2 un tipo kN, se dice que para reailzar estas operaciones, se tiene una complejidad de O(n).

  Vector dinámico: para el caso de obtener en el medio, tendría una complejidad de O(1), ya que se puede acceder a dichos elementos mediante el índice del vector. Mientras que para las operaciones de insertar y eliminar, sería necesario mover los elementos posteriores a la posición a eliminar o insertar dentro del vector. Teniendo en cuenta que se toma en el peor de los casos que se hacen N-iteraciones para mover dichos elementos, la complejidad de estas operaciones resulta O(n).

- Explica la complejidad de las operaciones implementadas en tu trabajo para la pila y la cola.

Complejidad de operaciones en PILA:

- `pila_crear`
  Esta función presenta una complejidad O(1), ya que las instrucciones que realiza son invocar a la función `lista_crear`, y dentro de la misma invocar a la función `calloc`. Como esta última reserva espacio en memoria dinámica para el struct, e inicializa los campos del mismo en 0 y NULL dependiendo el caso, todas operaciones O(1), finalmente la función formaría O(k1), terminando en O(1).

- `pila_apilar`
  Esta función devuelve el valor que recibe una vez finalizada la función `lista_insertar_en_posicion`. Si bien esta última, en el peor de los casos tiene una complejidad O(n), ya que sería necesario iterar hasta el (n-1)-ésimo elemento de la lista, todas las veces que `pila_apilar` invoque a dicha función, la invocará indicando la posición 0 de la lista, lo que quiere decir que nunca deberá hacer alguna iteración. Luego, teniendo en cuenta que al no tener que iterar, las instrucciones restantes son asignasiones con complejidad O(1), la función `pila_apilar` resulta tener una complejidad O(1).

- `pila_desapilar`
  Esta función devuelve el valor que recibe una vez finalizada la función `lista_quitar_de_posicion`. Si bien esta última, en el peor de los casos tiene una complejidad O(n), ya que sería necesario iterar hasta el (n-1)-ésimo elemento de la lista, todas las veces que `pila_desapilar` invoque a dicha función, la invocará indicando la posición 0 de la lista, lo que quiere decir que nunca deberá hacer alguna iteración. Luego, teniendo en cuenta que al no tener que iterar, las instrucciones restantes son asignasiones con complejidad O(1), la función `pila_desapilar` resulta tener una complejidad O(1).

- `pila_tope`
  Esta función devuelve el valor que recibe una vez finalizada la función `lista_primero`, cuya complejidad resulta O(1), ya que solo verifica parámetros y devuelve el elemento del primer nodo de la lista, instrucciones con complejidad O(1). Por lo tanto, la complejidad de esta función resulta O(1).

- `pila_tamanio`
  Esta función devuelve el valor que recibe una vez finalizada la función `lista_tamanio`, cuya complejidad resulta O(1), ya que únicamente verifica el parámetro y devuelve la cantidad de elementos de la lista. Por lo tanto, la complejidad de esta función resulta O(1).

- `pila_vacia`
  Esta función devuelve el valor que recibe una vez finalizada la función `lista_vacia`, cuya complejidad es O(1) ya que solo realiza verificaciones O(1) y devuelve true o false en función de los mismos. Por lo tanto, la complejidad de esta función resulta O(1).

Complejidad de operaciones en COLA:

- `cola_crear`
  Esta función presenta una complejidad O(1), ya que las instrucciones que realiza son invocar a la función `lista_crear`, y dentro de la misma invocar a la función `calloc`. Como esta última reserva espacio en memoria dinámica para el struct, e inicializa los campos del mismo en 0 y NULL dependiendo el caso, todas operaciones O(1), finalmente la función formaría O(k1), terminando en O(1).

- `cola_encolar`
  Esta función devuelve el valor que recibe una vez finalizada la función `lista_insertar`, cuya complejidad en el peor de los casos es O(1), al ser todas las instrucciones que realiza asignasiones con complejidad O(1). Por lo tanto, la complejidad de esta función resulta O(1).

- `cola_desencolar`
  Esta función devuelve el valor que recibe una vez finalizada la función `lista_quitar_de_posicion`. Si bien esta última, en el peor de los casos tiene una complejidad O(n), ya que sería necesario iterar hasta el (n-1)-ésimo elemento de la lista, todas las veces que `cola_desencolar` invoque a dicha función, la invocará indicando la posición 0 de la lista, lo que quiere decir que nunca deberá hacer alguna iteración. Luego, teniendo en cuenta que al no tener que iterar, las instrucciones restantes son asignasiones con complejidad O(1), la función `cola_desencolar` resulta tener una complejidad O(1).

- `cola_frente`
  Esta función devuelve el valor que recibe una vez finalizada la función `lista_primero`, cuya complejidad resulta O(1), ya que solo verifica parámetros y devuelve el elemento del primer nodo de la lista, instrucciones con complejidad O(1). Por lo tanto, la complejidad de esta función resulta O(1).

- `cola_tamanio`
  Esta función devuelve el valor que recibe una vez finalizada la función `lista_tamanio`, cuya complejidad resulta O(1), ya que únicamente verifica el parámetro y devuelve la cantidad de elementos de la lista. Por lo tanto, la complejidad de esta función resulta O(1).

- `cola_vacia`
  Esta función devuelve el valor que recibe una vez finalizada la función `lista_vacia`, cuya complejidad es O(1) ya que solo realiza verificaciones O(1) y devuelve true o false en función de los mismos. Por lo tanto, la complejidad de esta función resulta O(1).
