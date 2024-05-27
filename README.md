
## Descripción del Programa

Este programa permite a los usuarios encontrar resoluciones para el 8-puzzle, recorriendo sus estados posibles y entregando 3 tipos de búsqueda para escoger (por profundidad, por anchura, o por mejor solución posible). Cabe destacar que se nos entrega un estado específico como estado inicial.

## Cómo compilar y ejecutar

Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar [Repl.it](http://repl.it/) para una rápida configuración y ejecución. 

Sigue estos pasos para comenzar:

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `https://github.com/nicolas00r/Soluciones8puzzle`.
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
6. En la pestaña "Configurate Repl", sección "Configure the Compile Command", pegar el siguiente comando "gcc tdas/*.c main.c -Wno-unused-result -o main" y presionar "done".
7. Presione el boton "Run" para compilar y ejecutar la aplicación.

## Funcionalidades

### Funcionando correctamente:

- Generar estados del puzzle a través de movimientos.
- Búsqueda DFS (Depth First Search) o búsqueda por profundidad con límite de acciones.
- Búsqueda BFS (Breadth First Search) o búsqueda por anchura.
- Búsqueda Best First o búsqueda mejor-primero
- Recorrer y mostrar acciones hasta llegar al estado final deseado para el puzzle.

### Problemas conocidos:

- Al cambiar el estado inicial base entregado por el código, este podría no funcionar como se desea en caso de que se entreguen posiciones más complejas. Esto debido a que se necesitaría una gran cantidad de iteraciones que aún no puede manejar el programa, o a restricciones internas del mismo codigo, como por ejemplo el límite de 12 acciones para la búsqueda DFS.

### A mejorar:

- Implementar una interfaz de usuario más trabajada y estética, que entregue una mejor experiencia.
- Lograr manejar distintos casos de mayor complejidad.

## Ejemplo de uso


**Paso 1: Búsqueda en profundidad**

````
========================================
     Escoge método de búsqueda
========================================
1) Búsqueda en Profundidad
2) Buscar en Anchura
3) Buscar Mejor Primero
4) Salir
Ingrese su opción: 1
````

Seleccionada la opción 1, buscamos en profundidad:

````
Iteraciones realizadas: 165654

=============================================
 Acciones realizadas para resolver el puzzle
=============================================

Estado inicial: 
x 2 8 
1 3 4 
6 5 7 

Accion 1:
1 2 8 
x 3 4 
6 5 7 

Accion 2:
1 2 8 
3 x 4 
6 5 7 

Accion 3:
1 2 8 
3 4 x 
6 5 7 

Accion 4:
1 2 x 
3 4 8 
6 5 7 

Accion 5:
1 x 2 
3 4 8 
6 5 7 

Accion 6:
1 4 2 
3 x 8 
6 5 7 

Accion 7:
1 4 2 
3 5 8 
6 x 7 

Accion 8:
1 4 2 
3 5 8 
6 7 x 

Accion 9:
1 4 2 
3 5 x 
6 7 8 

Accion 10:
1 4 2 
3 x 5 
6 7 8 

Accion 11:
1 x 2 
3 4 5 
6 7 8 

Accion 12:
x 1 2 
3 4 5 
6 7 8 

=============================================
¡Puzzle resuelto!: 
x 1 2 
3 4 5 
6 7 8 
=============================================

Presione enter para continuar...
````

**Paso 2: Buscar en Anchura**

````
========================================
     Escoge método de búsqueda
========================================
1) Búsqueda en Profundidad
2) Buscar en Anchura
3) Buscar Mejor Primero
4) Salir
Ingrese su opción: 2
````

Seleccionada la opción 2, buscamos en anchura:

````
Iteraciones realizadas: 190887

=============================================
 Acciones realizadas para resolver el puzzle
=============================================

Estado inicial: 
x 2 8 
1 3 4 
6 5 7 

Accion 1:
1 2 8 
x 3 4 
6 5 7 

Accion 2:
1 2 8 
3 x 4 
6 5 7 

Accion 3:
1 2 8 
3 4 x 
6 5 7 

Accion 4:
1 2 x 
3 4 8 
6 5 7 

Accion 5:
1 x 2 
3 4 8 
6 5 7 

Accion 6:
1 4 2 
3 x 8 
6 5 7 

Accion 7:
1 4 2 
3 5 8 
6 x 7 

Accion 8:
1 4 2 
3 5 8 
6 7 x 

Accion 9:
1 4 2 
3 5 x 
6 7 8 

Accion 10:
1 4 2 
3 x 5 
6 7 8 

Accion 11:
1 x 2 
3 4 5 
6 7 8 

Accion 12:
x 1 2 
3 4 5 
6 7 8 

=============================================
¡Puzzle resuelto!: 
x 1 2 
3 4 5 
6 7 8 
=============================================

Presione enter para continuar...
````

**Paso 3: Buscar Mejor Primero**

````
========================================
     Escoge método de búsqueda
========================================
1) Búsqueda en Profundidad
2) Buscar en Anchura
3) Buscar Mejor Primero
4) Salir
Ingrese su opción: 3
````

Seleccionada la opción 3, buscamos el mejor primero:

````
Iteraciones realizadas: 68
=============================================
 Acciones realizadas para resolver el puzzle
=============================================

Estado inicial: 
x 2 8 
1 3 4 
6 5 7 

Accion 1:
1 2 8 
x 3 4 
6 5 7 

Accion 2:
1 2 8 
3 x 4 
6 5 7 

Accion 3:
1 2 8 
3 4 x 
6 5 7 

Accion 4:
1 2 x 
3 4 8 
6 5 7 

Accion 5:
1 x 2 
3 4 8 
6 5 7 

Accion 6:
1 4 2 
3 x 8 
6 5 7 

Accion 7:
1 4 2 
3 5 8 
6 x 7 

Accion 8:
1 4 2 
3 5 8 
6 7 x 

Accion 9:
1 4 2 
3 5 x 
6 7 8 

Accion 10:
1 4 2 
3 x 5 
6 7 8 

Accion 11:
1 x 2 
3 4 5 
6 7 8 

Accion 12:
x 1 2 
3 4 5 
6 7 8 

=============================================
¡Puzzle resuelto!: 
x 1 2 
3 4 5 
6 7 8 
=============================================

Presione enter para continuar...
````

**Paso 4: Salir del programa**

````
========================================
     Escoge método de búsqueda
========================================
1) Búsqueda en Profundidad
2) Buscar en Anchura
3) Buscar Mejor Primero
4) Salir
Ingrese su opción: 4
````

Al haber encontrado la solución deseada para el 8-Puzzle, simplemente salimos del programa con la opción 4:

````
Saliendo del sistema de resolución de 8-Puzzle...
````

## Contribuciones individuales

### Nicolas Reed:
- Rol asumido: Conductor
- Implementación y modularización del código
- Documentación y comentarios en el código
- Auto-evaluación : 3 (Aporte excelente)

### Joaquín Garrido:
- Rol asumido : Navegador
- Revisión y corrección de errores
- Sugerencia de cambios y enfoque en las respuestas
- Diseño y redacción del README.
- Auto-evaluación : 3 (Aporte excelente)
