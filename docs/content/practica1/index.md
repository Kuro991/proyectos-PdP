+++
date = '2026-03-13T00:00:00-08:00'
draft = false
title = 'Practica 1: Cola de impresion en lenguaje C'
+++

# Practica 1: Cola de impresion en lenguaje C

# Subsecciones
- Sesiones:
    - Sesion 1
    - Sesion 2
    - Sesion 3
- Reporte
    - Introduccion
    - Diseño
    - Implementacion
    - Demostracion de conceptos
    - Simulacion
    - Analisis comparativo
    - Preguntas guias
    - Demostracion de conocimiento
    - Conclusiones
    - Referencias

# Sesiones:
## Sesion 1

```
#include <stdio.h>
#include <string.h>

#define MAX_JOBS 10

typedef enum{
    normal,
    urgente
}prioridad;

typedef enum{
    encola,
    imprimiendo,
    completado,
    cancelado
}estado;

typedef struct{
    int id;
    char usuario[32];
    char documento[42];
    int totalpgs;
    int restantepgs;
    int copias;
    prioridad prioridad;
    estado estado;
}trabajo;

typedef struct{
    trabajo data[MAX_JOBS];
    int size;
    int idCounter;
}cola;


void qs_init(cola *q);
int qs_is_empty(const cola *q);
int qs_is_full(const cola *q);
int qs_enqueue(cola *q, trabajo job);
int qs_peek(const cola *q, trabajo *out);
int qs_dequeue(cola *q, trabajo *out);
void qs_print(const cola *q);
void newJob(cola *q);
void menu();

int main(){

    cola impresora;
    qs_init(&impresora);

    int opcion;

    do{

        menu();
        printf("Seleccione una opcion: ");
        scanf("%d",&opcion);

        switch(opcion){

            case 1:
                newJob(&impresora);
                break;

            case 2:{
                trabajo t;
                if(qs_dequeue(&impresora,&t))
                    printf("Trabajo eliminado ID %d\n",t.id);
                else
                    printf("La cola esta vacia\n");
                break;
            }

            case 3:{
                trabajo t;
                if(qs_peek(&impresora,&t))
                    printf("Frente: %s (%s)\n",t.usuario,t.documento);
                else
                    printf("La cola esta vacia\n");
                break;
            }

            case 4:
                qs_print(&impresora);
                break;

        }

    }while(opcion!=5);

    return 0;
}

void qs_init(cola *q){
    q->size=0;
    q->idCounter=1;
}

int qs_is_empty(const cola *q){
    return q->size==0;
}

int qs_is_full(const cola *q){
    return q->size==MAX_JOBS;
}

int qs_enqueue(cola *q, trabajo job){

    if(qs_is_full(q))
        return 0;

    q->data[q->size]=job;
    q->size++;

    return 1;
}

int qs_peek(const cola *q, trabajo *out){

    if(qs_is_empty(q))
        return 0;

    *out=q->data[0];
    return 1;
}

int qs_dequeue(cola *q, trabajo *out){

    if(qs_is_empty(q))
        return 0;

    *out=q->data[0];

    for(int i=1;i<q->size;i++)
        q->data[i-1]=q->data[i];

    q->size--;

    return 1;
}

void qs_print(const cola *q){

    if(qs_is_empty(q)){
        printf("La cola esta vacia\n");
        return;
    }

    printf("\n--- COLA DE IMPRESION ---\n");

    for(int i=0;i<q->size;i++){

        trabajo t=q->data[i];

        printf("ID: %d\n",t.id);
        printf("Usuario: %s\n",t.usuario);
        printf("Documento: %s\n",t.documento);
        printf("Paginas: %d\n",t.totalpgs);
        printf("Copias: %d\n",t.copias);
        printf("Prioridad: %s\n",t.prioridad==normal?"Normal":"Urgente");

        printf("\n");
    }
}

void newJob(cola *q){

    if(qs_is_full(q)){
        printf("Cola llena\n");
        return;
    }

    trabajo nuevo;

    nuevo.id=q->idCounter++;

    printf("Usuario: ");
    scanf("%s",nuevo.usuario);

    printf("Documento: ");
    scanf("%s",nuevo.documento);

    printf("Total paginas: ");
    scanf("%d",&nuevo.totalpgs);

    nuevo.restantepgs=nuevo.totalpgs;

    printf("Copias: ");
    scanf("%d",&nuevo.copias);

    int p;
    printf("Prioridad (0 normal / 1 urgente): ");
    scanf("%d",&p);

    nuevo.prioridad = p?urgente:normal;
    nuevo.estado = encola;

    if(qs_enqueue(q,nuevo))
        printf("Trabajo agregado\n");
}

void menu(){

    printf("\n--- MENU ---\n");
    printf("1. Agregar trabajo\n");
    printf("2. Eliminar trabajo\n");
    printf("3. Ver frente\n");
    printf("4. Mostrar cola\n");
    printf("5. Salir\n");

}
```

## Sesion 2

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    normal,
    urgente
}prioridad;

typedef enum{
    encola,
    imprimiendo,
    completado,
    cancelado
}estado;

typedef struct{
    int id;
    char usuario[32];
    char documento[42];
    int totalpgs;
    int restantepgs;
    int copias;
    prioridad prioridad;
    estado estado;
}PrintJob_t;

typedef struct Node_t{
    PrintJob_t job;
    struct Node_t* next;
}Node_t;

typedef struct{
    Node_t* head;
    Node_t* tail;
    int size;
    int idCounter;
}QueueDynamic_t;

void qd_init(QueueDynamic_t* q){
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    q->idCounter = 1;
}

int qd_is_empty(const QueueDynamic_t* q){
    return q->size == 0;
}

int qd_enqueue(QueueDynamic_t* q, PrintJob_t job){

    Node_t* nuevo = (Node_t*) malloc(sizeof(Node_t));

    if(nuevo == NULL){
        printf("Error: no se pudo asignar memoria\n");
        return 0;
    }

    nuevo->job = job;
    nuevo->next = NULL;

    if(qd_is_empty(q)){
        q->head = nuevo;
        q->tail = nuevo;
    }
    else{
        q->tail->next = nuevo;
        q->tail = nuevo;
    }

    q->size++;

    return 1;
}

int qd_peek(const QueueDynamic_t* q, PrintJob_t* out){

    if(qd_is_empty(q))
        return 0;

    *out = q->head->job;

    return 1;
}

int qd_dequeue(QueueDynamic_t* q, PrintJob_t* out){

    if(qd_is_empty(q))
        return 0;

    Node_t* temp = q->head;

    *out = temp->job;

    q->head = temp->next;

    if(q->head == NULL)
        q->tail = NULL;

    free(temp);

    q->size--;

    return 1;
}

void qd_destroy(QueueDynamic_t* q){

    Node_t* actual = q->head;

    while(actual != NULL){

        Node_t* temp = actual;
        actual = actual->next;

        free(temp);
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

void qd_print(const QueueDynamic_t* q){

    if(qd_is_empty(q)){
        printf("La cola esta vacia\n");
        return;
    }

    Node_t* actual = q->head;

    printf("\n--- COLA DE IMPRESION ---\n");

    while(actual != NULL){

        PrintJob_t t = actual->job;

        printf("ID: %d\n", t.id);
        printf("Usuario: %s\n", t.usuario);
        printf("Documento: %s\n", t.documento);
        printf("Paginas: %d\n", t.totalpgs);
        printf("Copias: %d\n", t.copias);
        printf("Prioridad: %s\n", t.prioridad == normal ? "Normal" : "Urgente");

        printf("\n");

        actual = actual->next;
    }
}

void newJob(QueueDynamic_t* q){

    PrintJob_t nuevo;

    nuevo.id = q->idCounter++;

    printf("Usuario: ");
    scanf("%s", nuevo.usuario);

    printf("Documento: ");
    scanf("%s", nuevo.documento);

    printf("Total paginas: ");
    scanf("%d",&nuevo.totalpgs);

    nuevo.restantepgs = nuevo.totalpgs;

    printf("Copias: ");
    scanf("%d",&nuevo.copias);

    int p;

    printf("Prioridad (0 normal / 1 urgente): ");
    scanf("%d",&p);

    nuevo.prioridad = p ? urgente : normal;
    nuevo.estado = encola;

    qd_enqueue(q,nuevo);
}

void menu(){

    printf("\n--- MENU ---\n");
    printf("1. Agregar trabajo\n");
    printf("2. Eliminar trabajo\n");
    printf("3. Ver frente\n");
    printf("4. Mostrar cola\n");
    printf("5. Salir\n");
}

int main(){

    QueueDynamic_t impresora;
    qd_init(&impresora);

    int opcion;

    do{

        menu();
        scanf("%d",&opcion);

        switch(opcion){

            case 1:
                newJob(&impresora);
                break;

            case 2:{
                PrintJob_t t;
                if(qd_dequeue(&impresora,&t))
                    printf("Trabajo eliminado ID %d\n",t.id);
                else
                    printf("Cola vacia\n");
                break;
            }

            case 3:{
                PrintJob_t t;
                if(qd_peek(&impresora,&t))
                    printf("Frente: %s - %s\n",t.usuario,t.documento);
                else
                    printf("Cola vacia\n");
                break;
            }

            case 4:
                qd_print(&impresora);
                break;

        }

    }while(opcion!=5);

    qd_destroy(&impresora);

    return 0;
}
```

## Sesion 3

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "ventanas.h"

/*==================================================
 ENUMERACIONES
==================================================*/

typedef enum{
    normal,
    urgente
}prioridad;

typedef enum{
    encola,
    imprimiendo,
    completado,
    cancelado
}estado;

/*==================================================
 ESTRUCTURA DE TRABAJO DE IMPRESION
==================================================*/

typedef struct{
    int id;
    char usuario[32];
    char documento[42];
    int totalpgs;
    int restantepgs;
    int copias;
    prioridad prioridad;
    estado estado;
}PrintJob_t;

/*==================================================
 NODO DE LISTA ENLAZADA
==================================================*/

typedef struct Node_t{
    PrintJob_t job;
    struct Node_t* next;
}Node_t;

/*==================================================
 COLA DINAMICA
==================================================*/

typedef struct{
    Node_t* head;
    Node_t* tail;
    int size;
    int idCounter;
}QueueDynamic_t;

/*==================================================
 ESTADISTICAS GLOBALES
==================================================*/

int trabajos_completados = 0;
int paginas_totales_impresas = 0;

/*==================================================
 FUNCION DE PAUSA
==================================================*/

void pausa(){

    printf("\nPresione ENTER para continuar...");
    fflush(stdout);

    int c;
    while((c = getchar()) != '\n' && c != EOF);
    getchar();
}

/*==================================================
 INICIALIZAR COLA
==================================================*/

void qd_init(QueueDynamic_t* q){
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    q->idCounter = 1;
}

int qd_is_empty(const QueueDynamic_t* q){
    return q->size == 0;
}

/*==================================================
 ENQUEUE (AGREGAR TRABAJO)
==================================================*/

int qd_enqueue(QueueDynamic_t* q, PrintJob_t job){

    Node_t* nuevo = (Node_t*) malloc(sizeof(Node_t));

    if(nuevo == NULL){
        printf("Error: no se pudo asignar memoria\n");
        return 0;
    }

    nuevo->job = job;
    nuevo->next = NULL;

    if(qd_is_empty(q)){
        q->head = nuevo;
        q->tail = nuevo;
    }
    else{
        q->tail->next = nuevo;
        q->tail = nuevo;
    }

    q->size++;

    return 1;
}

/*==================================================
 PEEK
==================================================*/

int qd_peek(const QueueDynamic_t* q, PrintJob_t* out){

    if(qd_is_empty(q))
        return 0;

    *out = q->head->job;
    return 1;
}

/*==================================================
 DEQUEUE
==================================================*/

int qd_dequeue(QueueDynamic_t* q, PrintJob_t* out){

    if(qd_is_empty(q))
        return 0;

    Node_t* temp = q->head;

    *out = temp->job;

    q->head = temp->next;

    if(q->head == NULL)
        q->tail = NULL;

    free(temp);

    q->size--;

    return 1;
}

/*==================================================
 LIBERAR MEMORIA
==================================================*/

void qd_destroy(QueueDynamic_t* q){

    Node_t* actual = q->head;

    while(actual != NULL){

        Node_t* temp = actual;
        actual = actual->next;

        free(temp);
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

/*==================================================
 MOSTRAR COLA
==================================================*/

void qd_print(const QueueDynamic_t* q){

    cls();

    if(qd_is_empty(q)){
        printf("La cola esta vacia\n\n");
        pausa();
        return;
    }

    Node_t* actual = q->head;

    printf("\n--- COLA DE IMPRESION ---\n\n");

    while(actual != NULL){

        PrintJob_t t = actual->job;

        printf("ID: %d\n", t.id);
        printf("Usuario: %s\n", t.usuario);
        printf("Documento: %s\n", t.documento);
        printf("Paginas: %d\n", t.totalpgs);
        printf("Copias: %d\n", t.copias);

        printf("Estado: ");

        if(t.estado==encola) printf("EN COLA\n");
        if(t.estado==imprimiendo) printf("IMPRIMIENDO\n");
        if(t.estado==completado) printf("COMPLETADO\n");
        if(t.estado==cancelado) printf("CANCELADO\n");

        printf("\n");

        actual = actual->next;
    }

    pausa();
}

/*==================================================
 CREAR NUEVO TRABAJO
==================================================*/

void newJob(QueueDynamic_t* q){

    PrintJob_t nuevo;

    nuevo.id = q->idCounter++;

    printf("Usuario: ");
    scanf("%s", nuevo.usuario);

    printf("Documento: ");
    scanf("%s", nuevo.documento);

    printf("Total paginas: ");
    scanf("%d",&nuevo.totalpgs);

    nuevo.restantepgs = nuevo.totalpgs;

    printf("Copias: ");
    scanf("%d",&nuevo.copias);

    int p;

    printf("Prioridad (0 normal / 1 urgente): ");
    scanf("%d",&p);

    nuevo.prioridad = p ? urgente : normal;
    nuevo.estado = encola;

    qd_enqueue(q,nuevo);
}

/*==================================================
 CANCELAR TRABAJO (MEJORA 1)
==================================================*/

int cancelar_trabajo(QueueDynamic_t* q, int id){

    Node_t* actual = q->head;

    while(actual != NULL){

        if(actual->job.id == id){

            if(actual->job.estado == completado){
                printf("El trabajo ya fue completado\n\n");
                pausa();
                return 0;
            }

            actual->job.estado = cancelado;

            printf("Trabajo %d cancelado\n\n", id);
            pausa();

            return 1;
        }

        actual = actual->next;
    }

    printf("No existe un trabajo con ese ID\n\n");
    pausa();

    return 0;
}

/*==================================================
 BARRA DE PROGRESO VISUAL
==================================================*/

void barra_progreso(int total, int restante){

    int progreso = total - restante;

    int porcentaje = (progreso * 100) / total;

    int bloques = (progreso * 10) / total;

    gotoxy(5,12);

    printf("[");

    for(int i = 0; i < 10; i++){

        if(i < bloques)
            printf("█");
        else
            printf("░");
    }

    printf("] %d%%", porcentaje);
}

/*==================================================
 SIMULACION DE IMPRESION
==================================================*/

void simular_impresion(QueueDynamic_t* q){

    cls();
    recuadro(2,2,78,25);
    PonMensaje(30,3,"SIMULADOR DE IMPRESION");

    while(!qd_is_empty(q)){

        PrintJob_t trabajo;
        qd_peek(q,&trabajo);

        /* saltar trabajos cancelados */
        if(trabajo.estado == cancelado){
            qd_dequeue(q,&trabajo);
            continue;
        }

        Node_t* actual = q->head;
        actual->job.estado = imprimiendo;

        char buffer[100];

        sprintf(buffer,"Imprimiendo: %s (%s)",
                trabajo.usuario,
                trabajo.documento);

        PonMensaje(5,6,buffer);

        /* === CICLO POR COPIAS === */

        for(int copia = 1; copia <= actual->job.copias; copia++){

            actual->job.restantepgs = actual->job.totalpgs;

            sprintf(buffer,"Copia %d de %d",
                    copia,
                    actual->job.copias);

            PonMensaje(5,8,buffer);

            while(actual->job.restantepgs > 0){

                sprintf(buffer,"Pagina %d / %d",
                        actual->job.totalpgs - actual->job.restantepgs + 1,
                        actual->job.totalpgs);

                PonMensaje(5,9,buffer);

                barra_progreso(actual->job.totalpgs,
                               actual->job.restantepgs);

                actual->job.restantepgs--;

                paginas_totales_impresas++;

                Sleep(400);
            }

            /* asegurar barra al 100% */
            barra_progreso(actual->job.totalpgs,0);

            Sleep(500);
        }

        actual->job.estado = completado;

        trabajos_completados++;

        PonMensaje(5,15,"Trabajo completado");

        Sleep(1000);

        qd_dequeue(q,&trabajo);

        cls();
        recuadro(2,2,78,25);
        PonMensaje(30,3,"SIMULADOR DE IMPRESION");
    }

    PonMensaje(5,22,"Simulacion terminada");

    gotoxy(5,24);
    pausa();
}

/*==================================================
 ESTADISTICAS (MEJORA 2)
==================================================*/

void mostrar_estadisticas(){

    cls();

    recuadro(10,5,70,20);

    PonMensajeCentrado(7,40,"ESTADISTICAS DE IMPRESION");

    char buffer[100];

    sprintf(buffer,"Trabajos completados: %d",
            trabajos_completados);

    PonMensaje(15,10,buffer);

    sprintf(buffer,"Paginas totales impresas: %d",
            paginas_totales_impresas);

    PonMensaje(15,12,buffer);

    gotoxy(15,16);

    pausa();
}

/*==================================================
 MENU
==================================================*/

void menu(){

    cls();

    printf("\n--- MENU ---\n");

    printf("1. Agregar trabajo\n");
    printf("2. Eliminar trabajo\n");
    printf("3. Ver frente\n");
    printf("4. Mostrar cola\n");
    printf("5. Cancelar trabajo\n");
    printf("6. Simular impresion\n");
    printf("7. Estadisticas\n");
    printf("8. Salir\n");
}

/*==================================================
 MAIN
==================================================*/

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    QueueDynamic_t impresora;

    qd_init(&impresora);

    int opcion;

    do{

        menu();

        scanf("%d",&opcion);

        switch(opcion){

            case 1:
                newJob(&impresora);
                break;

            case 2:{
                PrintJob_t t;

                if(qd_dequeue(&impresora,&t))
                    printf("Trabajo eliminado ID %d\n\n",t.id);
                else
                    printf("Cola vacia\n\n");

                pausa();
                break;
            }

            case 3:{
                PrintJob_t t;

                if(qd_peek(&impresora,&t))
                    printf("Frente: %s - %s\n\n",
                           t.usuario,
                           t.documento);
                else
                    printf("Cola vacia\n\n");

                pausa();
                break;
            }

            case 4:
                qd_print(&impresora);
                break;

            case 5:{
                int id;

                printf("Ingrese ID a cancelar: ");

                scanf("%d",&id);

                cancelar_trabajo(&impresora,id);
                break;
            }

            case 6:
                simular_impresion(&impresora);
                break;

            case 7:
                mostrar_estadisticas();
                break;

        }

    }while(opcion!=8);

    qd_destroy(&impresora);

    return 0;
}
```

# Reporte de practica

## Introduccion

En los sistemas informáticos es común que múltiples usuarios envíen trabajos de impresión a un mismo dispositivo. Para organizar estos trabajos se utiliza una cola de impresión, donde los documentos se procesan en el mismo orden en que fueron solicitados.

El objetivo de esta práctica fue desarrollar un simulador de cola de impresión en lenguaje C, aplicando estructuras de datos, manejo de memoria y control de flujo. El sistema implementa el comportamiento FIFO (First In, First Out), donde el primer trabajo que entra a la cola es el primero en ser procesado.

El desarrollo se realizó en tres sesiones progresivas:

Sesión 1: Implementación de la cola utilizando memoria estática mediante un arreglo.

Sesión 2: Migración a una estructura de memoria dinámica usando listas enlazadas.

Sesión 3: Implementación de una simulación de impresión, incluyendo progreso por páginas, retrasos y mejoras al sistema.

Esta práctica permite comprender conceptos fundamentales como:

Manejo de memoria estática y dinámica.

Uso de estructuras (struct) y enumeraciones (enum).

Diseño de subprogramas con contratos claros.

Implementación de estructuras de datos tipo cola.

## Diseño

### Estructura PrintJob_t

El sistema maneja trabajos de impresión representados mediante una estructura que almacena información relevante de cada solicitud.

```
typedef enum{
    normal,
    urgente
} prioridad;

typedef enum{
    encola,
    imprimiendo,
    completado,
    cancelado
} estado;

typedef struct{
    int id;
    char usuario[32];
    char documento[42];
    int totalpgs;
    int restantepgs;
    int copias;
    prioridad prioridad;
    estado estado;
} PrintJob_t;
```

Explcacion de los campos
| Campo       | Descripción                                  |
| ----------- | -------------------------------------------- |
| id          | Identificador único del trabajo              |
| usuario     | Nombre del usuario que solicita la impresión |
| documento   | Nombre del archivo a imprimir                |
| totalpgs    | Número total de páginas                      |
| restantepgs | Páginas restantes durante la simulación      |
| copias      | Número de copias solicitadas                 |
| prioridad   | Nivel de prioridad del trabajo               |
| estado      | Estado actual del trabajo                    |

El campo restantepgs permite simular el progreso de impresión página por página.

### Cola con memoria estatica

En la primera sesión se implementó la cola utilizando un arreglo de tamaño fijo.

```
#define MAX_JOBS 10

typedef struct{
    PrintJob_t data[MAX_JOBS];
    int size;
} QueueStatic_t;
```

En este diseño:

- data almacena los trabajos.
- size indica la cantidad actual de elementos.

El frente de la cola siempre es data[0].

### Cola con memoria dinamica

En la segunda sesión se migró la cola a una lista enlazada.

```
typedef struct Node_t{
    PrintJob_t job;
    struct Node_t* next;
} Node_t;

typedef struct{
    Node_t* head;
    Node_t* tail;
    int size;
} QueueDynamic_t;
```

Aquí:

- head apunta al primer nodo (frente).
- tail apunta al último nodo.
- Cada nodo se reserva dinámicamente en memoria mediante malloc.

Este diseño elimina el límite fijo de la cola.

## Implementacion

El programa se divide en varias funciones que implementan las operaciones principales de la cola.

### Inicializacion de la cola

```
void qd_init(QueueDynamic_t* q){
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    q->idCounter = 1;
}
```

Inicializa la cola sin elementos.

### Intertar trabajo (enqueue)

```
int qd_peek(const QueueDynamic_t* q, PrintJob_t* out)
```

Permite conocer el siguiente trabajo sin modificar la cola.

### Liberar memoria (destroy)

```
void qd_destroy(QueueDynamic_t* q)
```

Recorre la lista liberando todos los nodos restantes para evitar fugas de memoria.

## Demostracion de conceptos
### Alcance y duracion de variables

**Variable global**

```
int trabajos_completados = 0;
```

Esta variable es global porque debe estar disponible para todas las funciones del programa y almacenar estadísticas generales.

**Variable local**

```
PrintJob_t nuevo;
```

Se utiliza dentro de la función newJob() y solo existe durante la ejecución de esa función.

**Variable dentro de una estructura**

```
int idCounter;
```

Esta variable pertenece a la estructura de la cola y mantiene el control del identificador de trabajos.

### Memoria: Stack vs Heap
**Stack**

Variables como:

```
PrintJob_t nuevo;
```

Se almacenan en el stack, ya que son variables locales.

**Heap**

Los nodos de la cola dinámica se almacenan en el heap:

```
Node_t* nuevo = (Node_t*) malloc(sizeof(Node_t));
```

Posteriormente se liberan con:

```
free(temp);
```

Esto ocurre en la función qd_dequeue() o qd_destroy().

### Subprogramas y punteros
Las funciones que modifican la cola reciben un puntero:
```
int qd_enqueue(QueueDynamic_t* q, PrintJob_t job)
```
Mientras que funciones que solo consultan usan const:
```
int qd_peek(const QueueDynamic_t* q, PrintJob_t* out)
```
Esto evita modificaciones accidentales.

### Uso de struct y enum

Las estructuras permiten agrupar datos relacionados en una sola entidad.

Las enumeraciones (enum) facilitan representar estados del sistema:

```
encola
imprimiendo
completado
cancelado
```

Esto mejora la legibilidad y mantenimiento del código.

## Simulacion

En la tercera sesión se implementó una simulación del proceso de impresión.

La simulación realiza:
1. Tomar el trabajo del frente.
2. Cambiar su estado a IMPRIMIENDO.
3. Reducir las páginas restantes.
4. Mostrar progreso por página.
5. Aplicar un retraso con Sleep().

Ejemplo de código:
```
while(actual->job.restantepgs > 0){

    printf("Pagina %d / %d\n",
           actual->job.totalpgs - actual->job.restantepgs + 1,
           actual->job.totalpgs);

    actual->job.restantepgs--;

    Sleep(400);
}
```
También se implementó una barra de progreso para visualizar el avance de impresión.

## Simulacion
Durante la tercera sesión se implementaron varias mejoras al sistema.

### Cancelación de trabajos

Permite cancelar un trabajo usando su identificador.
```
cancelar_trabajo(&impresora,id);
```
Los trabajos cancelados cambian su estado a CANCELADO y no se imprimen.

### Estadísticas de impresión

El sistema registra:

- Trabajos completados.
- Total de páginas impresas.
```
int trabajos_completados = 0;
int paginas_totales_impresas = 0;
```
Estas estadísticas se muestran al final de la simulación.


## Analisis comparativos

### Cola estática

**Ventajas:**

- Implementación simple.
- No requiere manejo manual de memoria.

**Desventajas:**

- Capacidad limitada.
- Operación dequeue requiere desplazar elementos (O(n)).

### Cola dinámica

**Ventajas:**

- No tiene límite fijo de tamaño.
- enqueue y dequeue tienen complejidad O(1).

**Desventajas:**

- Requiere manejo manual de memoria.
- Riesgo de fugas de memoria si no se libera correctamente.


## Preguntas guia

### ¿Dónde guardaste el contador de id y por qué?

El contador de identificadores (idCounter) se almacenó dentro de la estructura de la cola dinámica QueueDynamic_t.
```
typedef struct{
    Node_t* head;
    Node_t* tail;
    int size;
    int idCounter;
}QueueDynamic_t;
```
Este contador se utiliza para generar identificadores únicos para cada trabajo de impresión que se agrega a la cola.

Se decidió almacenarlo dentro de la estructura de la cola por las siguientes razones:

Permite que cada instancia de la cola mantenga su propio control de identificadores.

Evita depender de variables globales adicionales.

Facilita la encapsulación del comportamiento de la cola dentro de su propia estructura de datos.

El contador se incrementa cada vez que se crea un nuevo trabajo:
```
nuevo.id = q->idCounter++;
```
De esta manera se garantiza que cada trabajo tenga un ID único y consecutivo.

### En tu versión dinámica: ¿qué función es responsable de liberar memoria? ¿cómo lo verificas?

En la versión dinámica, la función responsable de liberar memoria es qd_destroy().

Esta función recorre todos los nodos de la cola y libera la memoria reservada dinámicamente con malloc.
```
void qd_destroy(QueueDynamic_t* q){

    Node_t* actual = q->head;

    while(actual != NULL){

        Node_t* temp = actual;
        actual = actual->next;

        free(temp);
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}
```
Esta función se ejecuta al final del programa:
```
qd_destroy(&impresora);
```
**Verificación**

Se puede verificar que la memoria se libera correctamente mediante:

- Observación del flujo del programa (la cola termina vacía).
- Revisando que cada nodo creado con malloc sea liberado con free.

Si esta función no se ejecutara, los nodos permanecerían en memoria después de terminar el programa, provocando una fuga de memoria (memory leak).

### ¿Qué invariantes mantiene tu cola?

Un invariante es una condición que siempre debe mantenerse verdadera durante la ejecución del programa.

En la implementación de la cola dinámica se mantienen los siguientes invariantes:

1. Tamaño de la cola
```
q->size >= 0
```
El tamaño de la cola nunca puede ser negativo.

2. Cola vacía

Cuando la cola está vacía:
```
q->head == NULL
q->tail == NULL
q->size == 0
```
Esto garantiza que no existen nodos almacenados.

3. Cola con elementos

Si la cola contiene elementos:
```
q->head != NULL
q->tail != NULL
```
El nodo head siempre representa el frente de la cola y tail el último elemento.

4. Orden FIFO

Los trabajos se procesan en el mismo orden en que se agregan:
```
Primer trabajo agregado → primer trabajo procesado
```
Esto se garantiza porque:
- enqueue inserta al final.
- dequeue elimina del frente.

### ¿Por qué peek no debe modificar la cola?

La función peek tiene como objetivo consultar el elemento del frente sin eliminarlo.
```
int qd_peek(const QueueDynamic_t* q, PrintJob_t* out){

    if(qd_is_empty(q))
        return 0;

    *out = q->head->job;

    return 1;
}
```
No modificar la cola es importante porque:

Permite visualizar el siguiente trabajo sin alterar el orden.

Mantiene la integridad de la estructura FIFO.

Separa claramente las operaciones de consulta y modificación.

Si peek modificara la cola, entonces su comportamiento sería equivalente a dequeue, lo cual rompería el diseño lógico del sistema.

### Si el programa falla al agregar trabajos, ¿cómo distingues entre “cola llena” y “entrada inválida”?

En la versión estática, la cola tiene una capacidad máxima (MAX_JOBS), por lo que se valida antes de insertar.
```
if(q->size == MAX_JOBS){
    printf("La cola esta llena\n");
    return 0;
}
```
Si la cola está llena, el programa muestra un mensaje indicando que no es posible agregar más trabajos.

Por otro lado, las entradas inválidas se detectan mediante validaciones en los datos ingresados por el usuario, por ejemplo:
```
if(nuevo.totalpgs <= 0){
    printf("Numero de paginas invalido\n");
}
```
De esta forma el programa puede diferenciar claramente entre:
| Error            | Causa                          |
| ---------------- | ------------------------------ |
| Cola llena       | Se alcanzó la capacidad máxima |
| Entrada inválida | Datos incorrectos del usuario  |

## Evidencia de conceptos en el codigo

1. Alcance y duración de variables
**Variable global**
```
int trabajos_completados = 0;
```
Esta variable tiene alcance global, ya que debe ser accesible desde diferentes funciones del programa para registrar estadísticas de impresión.

**Variable local**
```
PrintJob_t nuevo;
```
Esta variable se define dentro de la función newJob() y solo existe durante la ejecución de dicha función.

**Variable dentro de estructura**
```
int idCounter;
```
Esta variable pertenece a la estructura de la cola y mantiene el control de identificadores de trabajos.

2. Manejo de memoria dinámica
**Reserva de memoria (heap)**

Cuando se agrega un nuevo trabajo, se crea un nodo dinámicamente.
```
Node_t* nuevo = (Node_t*) malloc(sizeof(Node_t));
```
Este nodo se almacena en el heap.

**Liberación de memoria**

La memoria se libera cuando se elimina un nodo o cuando se destruye la cola.
```
free(temp);
```
Esto ocurre dentro de las funciones:

- qd_dequeue()
- qd_destroy()

3. Contratos de funciones

**Función que modifica la cola**
```
int qd_enqueue(QueueDynamic_t* q, PrintJob_t job)
```
Esta función recibe un puntero a la cola (*q), ya que necesita modificar su contenido agregando un nuevo nodo.

**Función que solo consulta**
```
int qd_peek(const QueueDynamic_t* q, PrintJob_t* out)
```
Esta función usa const para indicar que no modificará la cola, únicamente leerá el valor del frente.

Esto permite mantener una separación clara entre:
- Funciones de modificación
- Funciones de consulta

## Evidencia de ejecucion

### Sesion 1 Cola estatica

![cola vacia](/docs/content/practica1/images/vacia.png)

![cola llena](/docs/content/practica1/images/colallena.png)

### Sesion 2 Cola dinamica

![FIFO](/docs/content/practica1/images/FIFO.png)

### Sesion 3 

![Progreso](/docs/content/practica1/images/progreso.png)

## Conclusion

Durante el desarrollo de esta práctica se logró comprender el funcionamiento de las estructuras de datos tipo cola y su aplicación en problemas reales como la administración de trabajos de impresión.

La implementación inicial con memoria estática permitió comprender la lógica básica de la estructura FIFO. Posteriormente, la migración a memoria dinámica permitió eliminar la limitación de tamaño y mejorar la eficiencia de ciertas operaciones.

Además, la implementación de una simulación de impresión permitió visualizar el comportamiento del sistema en tiempo real, incluyendo el progreso por páginas y el cambio de estados de los trabajos.

Finalmente, el análisis comparativo permitió identificar las ventajas y desventajas de cada enfoque, así como la importancia de administrar correctamente la memoria en programas escritos en lenguaje C.

## Referencias

Aho, A., Hopcroft, J., & Ullman, J. (1983). Data Structures and Algorithms. Addison-Wesley.

Kernighan, B., & Ritchie, D. (1988). The C Programming Language. Prentice Hall.

Gallegos Mariscal, J. C. (2026). Práctica 01: Cola de impresión en lenguaje C. Universidad Autónoma de Baja California.