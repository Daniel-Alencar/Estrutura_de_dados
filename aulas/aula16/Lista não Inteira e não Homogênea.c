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
    if(type > STRING || type < INTGR) {
        printf("Error! Type not recognized\n");
        exit(4);
    }
    alocado->type = type;
    alocado->VALUE = value;
    
    if((*list) == NULL) {
        alocado->next = alocado;
        alocado->previous = alocado;
        (*list) = alocado;

    } else {
        int p = position;
        if(position <= length / 2) {
            for(aux = (*list); position > 1; aux = aux->next, position--);
        } else {
            for(aux = (*list); position <= length; aux = aux->previous, position++);
        }
        alocado->previous = aux;
        alocado->next = aux->next;
        aux->next = alocado;
        if(p == length + 1) {
            *list = alocado;
        }
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
    NODO *aux = list->next;
    int retorno = 0;
    do {
        if(aux->type == type) {
            if(type == INTGR) {
                if(value.intValue == aux->VALUE.intValue) {
                    retorno = 1;
                    break;
                }
            } else if(type == FLT) {
                if(value.floatValue == aux->VALUE.floatValue) {
                    retorno = 1;
                    break;
                }
            } else if(type == STRING) {
                if(strcmp(value.stringValue, aux->VALUE.stringValue) == 0) {
                    retorno = 1;
                    break;
                }
            }
        }
        aux = aux->next;
    } while(aux != list->next);
    return retorno;
}