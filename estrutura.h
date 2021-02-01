#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#include "Item.h"

typedef struct node{
    Item item;
    struct node*next;
} *link;


void STinit(int m);                             // Iniciar a estrutura de hashtable
void STinsert(Item item);                       // inserir elemento (produto) na estrutura
void STdelete(Item item);                       // eliminar elemento (produto)
Item STsearch(Key v);                           // procurar elemento (produto)
int STFreeAll();                                /* Limpar toda a estrutura (libertar todo o restante espaço usado)
                                                    e retornar o número de elementos (size) */

link insertBeginList(link, Item);               // Inserir novo item (produto) no início duma lista ligada escolhida
Item searchList(link, Key);                     // Percorrer as listas ligadas da hashtable até encontrar o item desejado
link removeItemList(link, Item);                // Remover item (produto) numa lista ligada escolhida

void verificarMaiorStock(Item,short int);       // Obtenção/escolha rápida do biggestItem
void procurarMaiorStock();                      // Procura (escolha) aprofundada do biggestItem
Item produtoMaiorStock();                       // Retornar o biggestItem

void sort();                                    // Ordenar e mostrar uma lista ordenada de todos os produtos
Item* HashTableToArray();                       // retorna uma lista simples dos items (produtos) presentes na hashtable


#endif