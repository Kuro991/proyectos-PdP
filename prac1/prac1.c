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