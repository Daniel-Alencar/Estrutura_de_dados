#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INTGR 1
#define FLT 2
#define STRING 3

typedef struct nodo {
    int type;
    union values {
        int intValue;
        float floatValue;
        char stringValue[20];
    } VALUE;
    struct nodo *next;
    struct nodo *previous;
}NODO;
typedef NODO *HETEROGENEOUS_LIST;

void createList(HETEROGENEOUS_LIST *list);
void insertElement(HETEROGENEOUS_LIST *list, int position, int type, union values value);
int lengthOfList(HETEROGENEOUS_LIST list);
void printList(HETEROGENEOUS_LIST list);
int belongsToTheList(HETEROGENEOUS_LIST list, int type, union values value);

int main() {
    HETEROGENEOUS_LIST list;
    union values Valores;

    createList(&list);
    Valores.intValue = 22;
    insertElement(&list, 1, 1, Valores);
    Valores.floatValue = 1.75;
    insertElement(&list, 2, 2, Valores);
    Valores.floatValue = 2.89736;
    insertElement(&list, 3, 2, Valores);
    strcpy(Valores.stringValue, "Daniel Alencar");
    insertElement(&list, 4, 3, Valores);

    printList(list);

    Valores.intValue = 35;
    insertElement(&list, 2, 1, Valores);
    strcpy(Valores.stringValue, "consegue fazer");
    insertElement(&list, 2, 3, Valores);
    Valores.intValue = -65;
    insertElement(&list, 3, 1, Valores);
    Valores.floatValue = 2050.67;
    insertElement(&list, 1, 2, Valores);
    insertElement(&list, 1, 2, Valores);
    
    printList(list);
}

void createList(HETEROGENEOUS_LIST *list) {
    *list = NULL;
}

int lengthOfList(HETEROGENEOUS_LIST list) {
    if(list) {
        NODO *aux;
        int cont = 1;
        for(aux = list; aux != list->next; list = list->next) {
            cont++;
        }
        return cont;
    } else {
        return 0;
    }
}

void insertElement(HETEROGENEOUS_LIST *list, int position, int type, union values value) {
    NODO *alocado, *aux;
    int length = lengthOfList(*list);
    if(position < 1 || position > (length + 1)) {
        printf("\nPosition isn't valid\n\n");
        exit(1);
    }
    if(belongsToTheList(*list, type, value)) {
        printf("\nThe value already belongs to the list\n\n");
        exit(2);
    }
    alocado = (NODO *)malloc(sizeof(NODO));
    if(!alocado) {
        printf("\nUnfortunately, there is not store enough in list\n\n");
        exit(3);
    }

    if(type == INTGR) {
        alocado->VALUE.intValue = value.intValue;
        alocado->type = 1;
    } else if(type == FLT) {
        alocado->VALUE.floatValue = value.floatValue;
        alocado->type = 2;
    } else if(type == STRING) {
        strcpy(alocado->VALUE.stringValue, value.stringValue);
        alocado->type = 3;
    } else {
        printf("Error! Type not recognized\n");
        exit(4);
    }
    if((*list) == NULL) {
        alocado->next = alocado;
        alocado->previous = alocado;
        (*list) = alocado;

    } else if (position == (length + 1)) {
        alocado->next = (*list)->next;
        alocado->previous = (*list);

        (*list)->next = alocado;
        (alocado->next)->previous = alocado;

        (*list) = (*list)->next;
    } else {
        int i;
        for(i=1, aux = (*list); i<position; i++) {
            aux = aux->next;
        }
        alocado->next = aux->next;
        alocado->previous = aux;

        aux->next = alocado;
        (alocado->next)->previous = alocado;
    }
}

void printList(HETEROGENEOUS_LIST list) {
    if(list) {
        NODO *aux = list->next;
        printf("[");
        do {
            if(aux->type == 1) {
                printf("\n\t%d", aux->VALUE.intValue);
            } else if(aux->type == 2) {
                printf("\n\t%f", aux->VALUE.floatValue);
            } else if(aux->type == 3) {
                printf("\n\t%s", aux->VALUE.stringValue);
            } else {
                printf("Error! Type not recognized");
                exit(1);
            }
            aux = aux->next;

        } while(aux != list->next);
        
        printf("\n]\n");
    } else {
        printf("[]\n");
    }
}

int belongsToTheList(HETEROGENEOUS_LIST list, int type, union values value) {
    if(list) {
        NODO *aux = list;
        do {
            if(aux->type == type && 
            ((INTGR == type && list->VALUE.intValue == value.intValue) || 
            (FLT == type && list->VALUE.floatValue == value.floatValue) ||
            (STRING == type && !strcmp(list->VALUE.stringValue, value.stringValue))
            ))
                return 1;
            aux = aux->next;
        } while(aux != list);
        return 0;
    } else {
        return 0;
    }
}