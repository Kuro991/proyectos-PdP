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