#include <stdio.h>
#include <string.h>
#include "ventanas.h"

typedef enum prioridad{
    normal,
    urgente
}prioridad;

typedef enum estado{
    encola,
    imprimiendo,
    completado,
    cancelado
}estado;

typedef struct trabajo{
    int id;
    char usuario[32];
    char documento[42];
    int totalpgs;
    int restantepgs;
    int copias;
    prioridad prioridad;
    estado estado;
} trabajo;

typedef struct cola{
    trabajo trabajos[10];
    int frente;
    int final;
    int idCounter;
} cola;

void qInit(cola *c);
void qIsEmpty(cola *c);
void qIsFull(cola *c);
void newJob(cola *c);
void qEnQueue(cola *c, trabajo nuevo);
void qDeQueue(cola *c);
void qPeek(cola *c);
void qPrint(cola *c);
void menu();

void main(){




}

void qInit(){
    cola c;
    c.frente = 0;
    c.final = 0;
    c.idCounter = 0;
    return c;
}

void qIsEmpty(cola *c){
    if(c->frente == c->final){
        printf("La cola está vacía.\n");
    } else {
        printf("La cola no está vacía.\n");
    }
}

void qIsFull(cola *c){
    if(c->final == 10){
        printf("La cola está llena.\n");
    } else {
        printf("La cola no está llena.\n");
    }
}

void newJob(cola *c){
    if (c->final < 10)
    {
        trabajo nuevo;
        nuevo.id = c->idCounter++;
        printf("Ingrese el nombre del usuario: ");
        scanf("%s", nuevo.usuario);
        printf("Ingrese el nombre del documento: ");
        scanf("%s", nuevo.documento);
        printf("Ingrese el número total de páginas: ");
        scanf("%d", &nuevo.totalpgs);
        printf("Ingrese el número de copias: ");
        scanf("%d", &nuevo.copias);
        printf("Ingrese la prioridad (0 para normal, 1 para urgente): ");
        int p;
        scanf("%d", &p);
        nuevo.prioridad = (p == 0) ? normal : urgente;
        nuevo.estado = encola;
        qEnqueue(c, nuevo);
    } else {
        printf("No se pueden agregar más trabajos, la cola está llena.\n");
    }
    
}

void qEnQueue(cola *c, trabajo nuevo){
    if (c->final < 10)
    {
        c->trabajos[c->final] = nuevo;
        c->final++;
    } else {
        printf("No se pueden agregar más trabajos, la cola está llena.\n");
    }
}

void qDeQueue(cola *c){
    if (c->frente < c->final)
    {
        for (int i = c->frente; i < c->final - 1; i++)
        {
            c->trabajos[i] = c->trabajos[i + 1];
        }
        c->final--;
    } else {
        printf("No se pueden eliminar trabajos, la cola está vacía.\n");
    }
}

void qPeek(cola *c){
    if (c->frente < c->final)
    {
        printf("Trabajo en la cima de la cola:\n");
        printf("ID: %d\n", c->trabajos[c->frente].id);
        printf("Usuario: %s\n", c->trabajos[c->frente].usuario);
        printf("Documento: %s\n", c->trabajos[c->frente].documento);
        printf("Total páginas: %d\n", c->trabajos[c->frente].totalpgs);
        printf("Copias: %d\n", c->trabajos[c->frente].copias);
        printf("Prioridad: %s\n", (c->trabajos[c->frente].prioridad == normal) ? "Normal" : "Urgente");
        printf("Estado: %s\n", (c->trabajos[c->frente].estado == encola) ? "En cola" : (c->trabajos[c->frente].estado == imprimiendo) ? "Imprimiendo" : (c->trabajos[c->frente].estado == completado) ? "Completado" : "Cancelado");
    } else {
        printf("La cola está vacía.\n");
    }
}

void qPrint(cola *c){
    if (c->frente < c->final)
    {
        printf("Trabajos en la cola:\n");
        for (int i = c->frente; i < c->final; i++)
        {
            printf("ID: %d\n", c->trabajos[i].id);
            printf("Usuario: %s\n", c->trabajos[i].usuario);
            printf("Documento: %s\n", c->trabajos[i].documento);
            printf("Total páginas: %d\n", c->trabajos[i].totalpgs);
            printf("Copias: %d\n", c->trabajos[i].copias);
            printf("Prioridad: %s\n", (c->trabajos[i].prioridad == normal) ? "Normal" : "Urgente");
            printf("Estado: %s\n", (c->trabajos[i].estado == encola) ? "En cola" : (c->trabajos[i].estado == imprimiendo) ? "Imprimiendo" : (c->trabajos[i].estado == completado) ? "Completado" : "Cancelado");
            printf("\n");
        }
    } else {
        printf("La cola está vacía.\n");
    }
}

void menu(){
    printf("Menú de opciones:\n");
    printf("1. Agregar nuevo trabajo\n");
    printf("2. Eliminar trabajo en la cima de la cola\n");
    printf("3. Ver trabajo en la cima de la cola\n");
    printf("4. Imprimir todos los trabajos en la cola\n");
    printf("5. Salir\n");
}