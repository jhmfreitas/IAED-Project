#ifndef ITEM_H
#define ITEM_H

typedef struct produto{
    unsigned long int chave;
    int stock;
} *Item;

typedef unsigned long int Key;                  // tipo da chave
#define key(a) (a->chave)

typedef int Stock;                              // tipo do stock
#define stock(a) (a->stock)

// ==============================
// Protótipos das funções do Item:

Item newItem(unsigned long int, int);           // cria um novo produto
void showItem(Item);                            // mostra as propriedades do produto
int compareItems(const void*, const void*);     // retorna um valor < 0 se a<b, 0 se forem iguais e um valor >0 se b>a
void freeItem(Item);                            // liberta o produto da memória

#endif