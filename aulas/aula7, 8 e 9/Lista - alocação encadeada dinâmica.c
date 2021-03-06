#include<stdio.h>
#include<stdlib.h>
#include"Lista - alocação encadeada dinâmica.h"

int main() {
    int number, position;
    char option;
    DYNAMIC_CHAINED_LIST list;
    createList(&list);
    printf("Lista criada!!!\n");
    
    printf("Deseja Adicionar[Y/n]? ");
    scanf(" %c", &option);

    if(option == 'Y' || option == 'y') {
        do {
            printf("Valor para adicionar: ");
            scanf("%i", &number);
            printf("Posição que quer colocar: ");
            scanf("%i", &position);
            insertElementIntoListWithRecursion(&list, position, number);

            printf("Deseja continuar adicionando[Y/n]? ");
            setbuf(stdin, NULL);
            scanf(" %c", &option);

        } while(option == 'Y' || option == 'y');
    }

    printf("Deseja remover[Y/n]? ");
    setbuf(stdin, NULL);
    scanf(" %c", &option);
    
    if(option == 'Y' || option == 'y') {
        do {
            printf("Posição que quer remover: ");
            scanf("%i", &position);
            deleteElementFromListWithRecursion(&list, position);

            printf("Deseja continuar removendo[Y/n]? ");
            setbuf(stdin, NULL);
            scanf(" %c", &option);

        } while(option == 'Y' || option == 'y');
    }

    printf("Deseja consultar um elemento[Y/n]? ");
    setbuf(stdin, NULL);
    scanf(" %c", &option);

    if(option == 'Y' || option == 'y') {
        do {
            printf("Posição que quer consultar: ");
            scanf("%i", &position);
            printf("Position of your element: %03i\n", returnElementWithRecursion(list, position));

            printf("Deseja continuar consultando[Y/n]? ");
            setbuf(stdin, NULL);
            scanf(" %c", &option);

        } while(option == 'Y' || option == 'y');
    }
    printf("Aqui está a sua lista!!!\n");
    printList(&list);
}

void createList(DYNAMIC_CHAINED_LIST *list) {
    (*list) = NULL;
}

int listIsEmpty(DYNAMIC_CHAINED_LIST list) {
    return list == NULL;
}

int lengthOfList(DYNAMIC_CHAINED_LIST list) {
    int length;
    for(length = 0; list != NULL; length++) {
        list = list->next;
    }
    return length;
}

void insertElementIntoList(DYNAMIC_CHAINED_LIST *list, int position, int value) {
    NODO *alocado;

    if(position < 0 || position > lengthOfList(*list)) {
        printf("\nPosition isn't valid\n\n");
        exit(1);
    }
    alocado = (NODO *) malloc(sizeof(NODO));
    if(!alocado) {
        printf("\nUnfortunately, there is not store enough in list\n\n");
        exit(2);
    }

    alocado->value = value;
    if(!position) {
        alocado->next = (*list);
        (*list) = alocado;
    } else {
        NODO *aux;
        int i=1;

        for(aux = (*list); position > i; aux = aux->next) {
            i++;
        }
        alocado->next = aux->next;
        aux->next = alocado;
    }
}

void printList(DYNAMIC_CHAINED_LIST *list) {
    NODO *aux;

    for(aux = (*list); aux != NULL; aux = aux->next) {
        printf("%i...", aux->value);
    }
    printf("\n");
}

void insertElementIntoListWithRecursion(DYNAMIC_CHAINED_LIST *list, int position, int value) {
    if(position < 1 || position > (lengthOfList((*list)) + 1)) {
        printf("\nPosition isn't valid\n\n");
        exit(1);
    }
    if(position == 1) {
        NODO *alocado;

        alocado = (NODO *) malloc(sizeof(NODO));
        if(!alocado) {
            printf("\nUnfortunately, there is not store enough in list\n\n");
            exit(2);
        }
        alocado->value = value;
        alocado->next = (*list);
        
        (*list) = alocado;
    } else {
        insertElementIntoListWithRecursion(&((*list)->next), position - 1, value);
    }
}

int returnElementWithRecursion(DYNAMIC_CHAINED_LIST list, int position) {
    if(position < 1 || position > lengthOfList(list)) {
        printf("\nPosition isn't valid\n\n");
        exit(1);
    }
    if(position == 1) {
        return (*list).value;
    } else {
        returnElementWithRecursion(list->next, position - 1);
    }
}

void deleteElementFromListWithRecursion(DYNAMIC_CHAINED_LIST *list, int position) {
    if(position < 1 || position > lengthOfList((*list))) {
        printf("\nPosition isn't valid\n\n");
        exit(1);
    }
    if(position == 1) {
        NODO *aux = (*list);
        (*list) = (*list)->next;
        free(aux);
    } else {
        deleteElementFromListWithRecursion(&((*list)->next), position - 1);
    }
}

void deleteElementFromList(DYNAMIC_CHAINED_LIST *list, int position) {
    NODO *aux;

    if(position < 1 || position > lengthOfList((*list))) {
        printf("\nPosition isn't valid\n\n");
        exit(1);
    }
    if(position == 1) {
        aux = (*list);
        (*list) = (*list)->next;
        free(aux);
    } else {
        NODO *aux2;
        int i=2;
        for(aux = (*list); position > i; aux = aux->next) {
            i++;
        }
        aux2 = aux->next;
        aux->next = (aux->next)->next;
        free(aux2);
    }
}

void brokeListWithRecursion(DYNAMIC_CHAINED_LIST list) {
    if(!list) {
        brokeListWithRecursion(list->next);
        free(list);
    }
}

void brokeList(DYNAMIC_CHAINED_LIST list) {
    NODO *aux;
    while (list)
    {
        aux = list;
        list = list->next;
        free(aux);
    }
}

int lengthOfListWithRecursion(DYNAMIC_CHAINED_LIST list) {
    int counter = 0;
    if(!list) {
        return counter;
    } else {
        counter = lengthOfListWithRecursion(list->next);
        counter++;
        return counter;
    }
}

int belongToList(DYNAMIC_CHAINED_LIST list, int value) {
    while(list) {
        if(list->value == value) {
            return 1;
        }
        list = list->next;
    }
    return 0;
}

int belongToListWithRecursion(DYNAMIC_CHAINED_LIST list, int value) {
    if(!list) {
        return 0;
    }
    if(list->value == value) {
        return 1;
    }
    return belongToListWithRecursion(list->next, value);
}

int isOrdered(DYNAMIC_CHAINED_LIST list) {
    while(list && list->next) {
        if(list->value > (list->next)->value) {
            return 0;
        }
        list = list->next;
    }
    return 1;
}

int isOrderedWithRecursion(DYNAMIC_CHAINED_LIST list) {
    if(list && list->next) {
        if(list->value > (list->next)->value)
            return 0;
        return isOrderedWithRecursion(list->next);
    } else {
        return 1;
    }
}

int generateList(DYNAMIC_CHAINED_LIST *list, int firstElement, int lastElement) {
    if(firstElement > lastElement) {
        printf("\nError! Invalid range\n\n");
        return 0;
    }
    createList(list);
    while(lastElement >= firstElement) {
        insertElementIntoListWithRecursion(list, 1, lastElement);
        lastElement--;
    }
    return 1;
}

int generateListWithRecursion(DYNAMIC_CHAINED_LIST *list, int firstElement, int lastElement) {
    if(firstElement > lastElement) {
        printf("\nError! Invalid range\n\n");
        return 0;
    } else {
        if(firstElement == lastElement) {
            createList(list);
            insertElementIntoListWithRecursion(list, 1, firstElement);
        } else {
            generateListWithRecursion(list, firstElement + 1, lastElement);
            insertElementIntoListWithRecursion(list, 1, firstElement);
        }
    }
    return 1;
}
