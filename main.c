#include <stdio.h>
#include <stdlib.h>
#include "tdas/list.h"
#include "tdas/heap.h"
#include "tdas/extra.h"
#include "tdas/queue.h"
#include "tdas/stack.h"
#include <string.h>
// Definimos los movimientos junto con su numero correspondiente
#define ARRIBA 1       
#define ABAJO 2
#define IZQUIERDA 3
#define DERECHA 4

// Definición de la estructura para el estado del puzzle
typedef struct {
    int square[3][3]; // Matriz 3x3 que representa el tablero
    int x;    // Posición x del espacio vacío
    int y;    // Posición y del espacio vacío
    List* actions; //Secuencia de movimientos para llegar al estado
} State;

// Función que calcula la distancia L1 de un estado
int distancia_L1(State* state) {
    int ev=0;
    int k=1;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            int val=state->square[i][j];
            if (val==0) continue;
            int ii=(val)/3;
            int jj=(val)%3;
            ev+= abs(ii-i) + abs(jj-j);
        }
    return ev;
}

// Función para imprimir el estado del puzzle
void imprimirEstado(const State *estado) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (estado->square[i][j] == 0)
                printf("x "); // Imprime un espacio en blanco para el espacio vacío
            else
                printf("%d ", estado->square[i][j]);
        }
        printf("\n");
    }
}

// Función para verificar si el estado es el estado final
int is_final_state(State *estado)
{
    int aux = 0;  // Creamos un auxiliar que nos ayudará a validar el número

    // Ciclo que recorre el puzzle
    for(size_t i = 0; i < 3; i++)
    {
        for(size_t j = 0; j < 3; j++)
        {
            if(estado->square[i][j] != aux) return 0;
            aux++; 
        }
    }
    // Si todos los números coinciden, el estado es final y se retorna 1
    return 1;
}

// Función para copiar un estado 
void copyState(State *original, State *nuevoEstado) { 

    // Se copia la información del estado original en el nuevo estado
    *nuevoEstado = *original;

    // Se inicializa la lista del nuevo estado
    nuevoEstado->actions = list_create();

    // Se recorre la lista de acciones del estado original y se copia
    // nodo por nodo en la lista de acciones del nuevo estado
    void* aux = list_first(original->actions);
    while(aux != NULL){
        list_pushBack(nuevoEstado->actions, aux);
        aux=list_next(original->actions);
    }
}

//Funcion para validar que nuestro movimiento se encuentra dentro de los limites del tablero
int movimientoInvalido(int x, int y){
    return(x < 0 || x > 2 || y < 0 || y > 2);
}

//Funcion para realizar las transiciones de entre estados
State* transition(State* estado, int action)
{
    //Creamos variables auxiliares de la posicion vacía
    int xVacia = estado->x;
    int yVacia = estado->y;
    // Creamos las variables de la nueva posición vacía
    int nuevaX = xVacia;
    int nuevaY = yVacia;

    //Realizamos el movimiento según la acción indicada
    switch(action){
        case 1: // Acción ARRIBA
            nuevaX -= 1;    // Disminuimos el valor de la fila en 1
            break;
        case 2: // Acción ABAJO
            nuevaX += 1;    // Aumentamos el valor de la fila en 1
            break;
        case 3: // Acción IZQUIERDA
            nuevaY -= 1;    // Disminuimos el valor de la columna en 1
            break;
        case 4: // Acción DERECHA
            nuevaY += 1;   // Aumentamos el valor de la columna en 1
            break;
        default: // Si nos entregan una acción incorrecta, se retorna NULL
            return NULL;
    }

    // Comprobamos validez del movimiento
    if(movimientoInvalido(nuevaX, nuevaY)) return NULL;
    
    // Creamos y reservamos memoria para el nuevo estado
    State *nuevoEstado = (State *)malloc(sizeof(State));
    // Verificamos si la memoria se asignó correctamente
    if(nuevoEstado == NULL) exit(EXIT_FAILURE);
    // Copiamos el estado anterior en el nuevo estado
    copyState(estado, nuevoEstado);

    // Realizamos el cambio de posición de la casilla vacía
    nuevoEstado->square[xVacia][yVacia] = nuevoEstado->square[nuevaX][nuevaY];
    nuevoEstado->square[nuevaX][nuevaY] = 0;
    // Asignamos la nueva posición de la casilla vacía
    nuevoEstado->x = nuevaX;
    nuevoEstado->y = nuevaY;
    
    // Reservamos memoria para la acción realizada
    int *actionList = (int *)malloc(sizeof(int));
    if(actionList == NULL) exit(EXIT_FAILURE);

    // Se copia la acción recibida en la función
    *actionList = action;
    // Se agrega la acción a la lista correspondiente
    list_pushBack(nuevoEstado->actions, actionList);
    return nuevoEstado;
}

// Función para obtener los nodos adyacentes de un estado
List *get_adj_nodes(State *estado)
{
    // Creamos la lista de nodos adyacentes
    List *list = list_create();
    
    // Guardamos cada movimiento en la lista (en caso de ser jugadas validas)
    
    State *moverArriba = transition(estado, ARRIBA);
    if(moverArriba != NULL) list_pushBack(list, moverArriba);

    State *moverAbajo = transition(estado, ABAJO);
    if(moverAbajo != NULL) list_pushBack(list, moverAbajo);

    State *moverIzquierda = transition(estado, IZQUIERDA);
    if(moverIzquierda != NULL) list_pushBack(list, moverIzquierda);

    State *moverDerecha = transition(estado, DERECHA);
    if(moverDerecha != NULL) list_pushBack(list, moverDerecha);

    // Retornamos la lista
    return list;
}

// Función para obtener el largo de nuestra lista
int sizeLista(List *lista){
    int contador = 0;

    // Obtenemos el primer dato de la lista
    void *aux = list_first(lista);
    // Si la lista esta vacía, retornamos contador en 0
    if(aux == NULL) return contador;

    // Ciclo para recorrer la lista
    while(aux != NULL){
        contador++;
        aux = list_next(lista);
    }
    return contador;
}

// Función de busqueda en profundidad
State *dfs(State estado_inicial, int *cont){
       // Se crea la pila para realizar la busqueda
       Stack *pila = stack_create();
    
       // Copiamos el estado inicial para trabajarlo en nuestra pila
       State *initial_state = (State *)malloc(sizeof(State));
       *initial_state = estado_inicial;

       // Reservamos memoria para el estado auxiliar 'n'
       State *n = (State *) malloc(sizeof(State));
       // Lo ingresamos a la pila
       stack_push(pila, initial_state);

       // Ciclo para recorrer la pila mientras no este vacía
       while(stack_top(pila) != NULL){
          // Aumentamos el contador de la cantidad de iteraciones
          (*cont)++;
          n = stack_top(pila);
          stack_pop(pila);

          // Comprobamos si 'n' es el estado final
          if(is_final_state(n)) return n;
          // Comprobamos el largo de la lista de acciones para 
          // que no itere infinitamente
          if(sizeLista(n->actions) >= 12){
              free(n);
              continue;
          }

          // Obtenemos la lista de nodos adjuntos
          List *adj_nodes = get_adj_nodes(n);

          // Recorremos la lista y los añadimos a la pila
          State *aux = list_first(adj_nodes);
          while(aux){
             stack_push(pila, aux);
             aux = list_next(adj_nodes);
          }

          // Liberamos la memoria
          list_clean(adj_nodes);
          free(n);
       }
      printf("\nNo se pudo encontrar una solución con el límite de acciones 12\n");
      return NULL;
}

//Funcion de busqueda en anchura
State *bfs(State estado_inicial, int *cont){
       // Se crea la cola para realizar la busqueda
       Queue *cola = queue_create();

       // Copiamos el estado inicial para trabajarlo en nuestra cola
       State *initial_state = (State *)malloc(sizeof(State));
       *initial_state = estado_inicial;

       // Reservamos memoria para el estado auxiliar 'n'
       State *n = (State *) malloc(sizeof(State));
       // Lo ingresamos a la cola
       queue_insert(cola, initial_state);

       // Ciclo para correr la cola mientras no este vacía
       while(queue_front(cola) != NULL){
          // Aumentamos el contador de la cantidad de iteraciones
          (*cont)++;
          n = queue_front(cola);
          queue_remove(cola);

          // Comprobamos si 'n' es el estado final
          if(is_final_state(n)) return n;

          // Obtenemos la lista de nodos adjuntos
          List *adj_nodes = get_adj_nodes(n);

          // Recorremos la lista y los añadimos a la cola
          State *aux = list_first(adj_nodes);
          while(aux){
             queue_insert(cola, aux);
             aux = list_next(adj_nodes);
          }
           
          // Liberamos la memoria
          list_clean(adj_nodes);
          free(n);
       }
      return NULL;
}

State *best_first(State estado_inicial, int *cont){
       // Se crea el heap para realizar la busqueda
       Heap *colaPrioridad = heap_create();

       // Copiamos el estado inicial para trabajarlo en nuestro heap
       State *initial_state = (State *)malloc(sizeof(State));
       *initial_state = estado_inicial;

       // Reservamos memoria para el estado auxiliar 'n'
       State *n = (State *) malloc(sizeof(State));
       // Lo ingresamos al heap
       heap_push(colaPrioridad, initial_state, -1);

       // Ciclo para recorrer el heap mientras no este vacío
       while(heap_top(colaPrioridad) != NULL){
          // Aumentamos el contador de la cantidad de iteraciones
          (*cont)++;
          n = heap_top(colaPrioridad);
          heap_pop(colaPrioridad);
           
          // Comprobamos si 'n' es el estado final
          if(is_final_state(n)) return n;

          // Obtenemos la lista de nodos adjuntos
          List *adj_nodes = get_adj_nodes(n);

          // Recorremos la lista y los añadimos al heap
          State *aux = list_first(adj_nodes);
          while(aux){
             heap_push(colaPrioridad, aux, -(sizeLista(n->actions) + distancia_L1(aux)));
             aux = list_next(adj_nodes);
          }

          // Liberamos la memoria
          list_clean(adj_nodes);
          free(n);
       }
      return NULL;
}

// Función para mostrar los pasos realizador para llegar a un estado
void mostrarPasos(State *estado_inicial, List *actions){
    // Creamos la variable estado y copiamos estado_inicial en el
    State *estado = estado_inicial;
    // Obtenemos la primera acción a realizar
    int *action = list_first(actions);
    int contador = 0; // Auxiliar para contar las acciones

    printf("\n");
    puts("=============================================");
    puts(" Acciones realizadas para resolver el puzzle");
    puts("=============================================");
    
    printf("\nEstado inicial: \n");
    imprimirEstado(estado);   // Mostramos el estado inicial
    printf("\n");
    
    // Ciclo para recorrer la lista de acciones
    while(action != NULL){
        contador++;
        estado = transition(estado, *action);  // Realizamos el movimiento correspondiente
        action = list_next(actions);  // Avanzamos a la siguiente accion
        printf("Accion %d:\n", contador);
        imprimirEstado(estado);  // Mostramos el estado tras el movimiento
        printf("\n");
    }
}

// Función para mostrar la resolución final del puzzle
void mostrarResolucion(State *inicial, State *resuelto, int *cont){
    printf("\nIteraciones realizadas: %d\n", *cont);
    mostrarPasos(inicial, resuelto->actions);

    puts("=============================================");
    printf("¡Puzzle resuelto!: \n");
    imprimirEstado(resuelto);
    puts("=============================================");
    printf("\n");
}

// Función para mostrar la búsqueda DFS
void mostrarDFS(State estado_inicial, int *cont){
    *cont = 0; // Iniciamos el contador de iteraciones en 0
    State *state_final = dfs(estado_inicial, cont); 
    mostrarResolucion(&estado_inicial, state_final, cont);
}

// Función para mostrar la búsqueda BFS
void mostrarBFS(State estado_inicial, int *cont){
    *cont = 0; // Iniciamos el contador de iteraciones en 0
    State *state_final = bfs(estado_inicial, cont);
    mostrarResolucion(&estado_inicial, state_final, cont);
}

// Función para mostrar la búsqueda Best-First
void mostrarBestFirst(State estado_inicial, int *cont){
    *cont = 0; // Iniciamos el contador de iteraciones en 0
    State *state_final = best_first(estado_inicial, cont);
    mostrarResolucion(&estado_inicial, state_final, cont);
}

int main() {
    // Estado inicial del puzzle
    State estado_inicial = {
        {{0, 2, 8}, // Primera fila (0 representa espacio vacío)
         {1, 3, 4}, // Segunda fila
         {6, 5, 7}, // Tercera fila
         },  
        0, 0   // Posición del espacio vacío (fila 0, columna 0)
    };
    estado_inicial.actions = list_create();

    // Creamos las variables a utilizar
    char opcion;
    int contador;
    
    do {
        puts("========================================");
        puts("     Escoge método de búsqueda");
        puts("========================================");

        puts("1) Búsqueda en Profundidad");
        puts("2) Buscar en Anchura");
        puts("3) Buscar Mejor Primero");
        puts("4) Salir");

        printf("Ingrese su opción: ");
        scanf(" %c", &opcion);

        switch (opcion) {
        case '1':  // Busqueda en profundidad
          mostrarDFS(estado_inicial, &contador);
          break;
            
        case '2':  // Busqueda en anchura
          mostrarBFS(estado_inicial, &contador);
          break;
            
        case '3': // Busqueda best_first
          mostrarBestFirst(estado_inicial, &contador);
          break;

        case '4': // Salir
          printf("Saliendo del sistema de resolución de 8-Puzzle... \n");
          return 0;
        }

        presioneTeclaParaContinuar();
        limpiarPantalla();

  } while (opcion != '4');
  return 0;
}
