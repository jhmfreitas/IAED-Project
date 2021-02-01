#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

// newItem: cria um novo produto

Item newItem(unsigned long int chave, int stock){
    
    Item new = (Item)malloc(sizeof(struct produto));
    new->chave = chave;
    new->stock = stock;
    return new;
}


//showItem: mostra as propriedades do produto

void showItem(Item a){

    if(a != NULL)
        printf("%08lx %d\n",key(a),stock(a));
}



// compareItems: retorna um valor < 0 se a<b, 0 se forem iguais e um valor >0 se b>a

int compareItems(const void* a, const void* b){
    const Item *A = a;
    const Item *B = b;

    long int dif = (*A)->chave - (*B)->chave;

    if(dif > 0)
        return 1;

    if(dif < 0)
        return -1;

    if(dif == 0)
        return 0;

    return 0;
}



// freeItem: liberta o produto da memória

void freeItem(Item item){
    if(item != NULL)
        free(item);
}