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