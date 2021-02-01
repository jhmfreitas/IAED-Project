#include "estrutura.h"
#include <stdlib.h>
#include "Item.h"

/* ****************************************************************************
    TIPO DE ESTRUTURA: Hashtable - Tabela de dispersão por encadeamento externo
******************************************************************************/

static link *heads;         // hashtable (tabela de listas ligadas)
static int M;               // número de listas ligadas da hashtable
static int size;            // número de elementos da hastable (produtos/items)

static Item biggestItem;    // item (produto) com maior stock

// ============================================================================


/* Obtenção do índice da hashtable (escolha de lista ligada) para um novo item,
de acordo com a sua chave (resto da divisão da chave por M) */

int hash(Key value, int M){
  return value % M;
}


// Iniciar a estrutura de hashtable

void STinit(int m) {
  int i;
  M = m;

  biggestItem = NULL;         // inicialmente, biggestItem ainda não é sabido

  heads = (link*)malloc(M*sizeof(link));
  for (i = 0; i < M; i++)
    heads[i] = NULL;
}


// Hashtable: inserir elemento (produto) na hashtable

void STinsert(Item item) {
  int i = hash(key(item), M);
  heads[i] = insertBeginList(heads[i], item);
  size++;
}


// Hashtable: eliminar elemento (produto)

void STdelete(Item item) {
  if(item != NULL){
    int i = hash(key(item), M);
    heads[i] = removeItemList(heads[i], item);
    size--;
  }
}


// Hashtable: procurar elemento (produto)

Item STsearch(Key v) {
  int i = hash(v, M);
  return searchList(heads[i], v);
}


// Hashtable: Limpar toda a hashtable (libertar todo o restante espaço usado)

int STFreeAll()
{
  
  link t, next_t;
  int i;
    for(i=0; i<M; i++)
      for(t = heads[i]; t!= NULL; t = next_t)
      {
        next_t = t->next; //preparar próximo elemento a limpar
        if(t->item != NULL)
          freeItem(t->item);
        free(t);
      }
  
  free(heads);
  return size;
}

// ============================================================================


// Inserir novo item (produto) no início duma lista ligada escolhida (a partir da sua chave) da hashtable

link insertBeginList(link head, Item item)
{
  link x = (link)malloc(sizeof(struct node));
  x->item = item;

  x->next = head;

  // para a funcao m: ver se este é novo máximo
  //quando se sabe o biggestItem ou quando a hashtable é vazia
  if((biggestItem != NULL &&
      (stock(item) > stock(biggestItem) ||
      (stock(item) == stock(biggestItem) && key(item) < key(biggestItem))))
      || size == 0)
        biggestItem = item;

  return x;
}


// searchList: Percorremos as listas ligadas da hashtable até se encontrar o item desejado:

Item searchList(link head, Key a)
{
  link x;
  for(x=head;x!=NULL;x=x->next)
    if(key(x->item) == a)
      return x->item;
  return NULL;
}


// Remover item (produto) numa lista ligada escolhida (a partir da sua chave) da hashtable

link removeItemList(link head, Item item)
{
  link prev, curr;
  prev = NULL;
  curr = head;

  // procurar o nó que correponde ao item desejado
  while (curr != NULL && key(curr->item) != key(item)) {
    prev = curr;
    curr = curr->next;
  }

  // Se se encontrou o item, então removemos o nó e o seu item:
  if (curr !=NULL && key(curr->item) == key(item)) {
    
    if (prev != NULL)
      prev->next = curr->next;
    else
      head = curr->next;


    if(item == biggestItem)
      biggestItem = NULL;

    freeItem(item);
    free(curr);
  }
      
  return head;
}



// ============================================================================
// Funções usadas para a escolha do biggestItem:


/* verificarMaiorStock: quando se sabe qual o biggestItem e alteramos um stock,
temos duas hipóteses:
    - se valor incrementado > 0 então item é comparado com o biggest item e pode vir a substitui-lo
    - valor incrementado < 0 e o item é o biggestItem então deixamos de saber o biggestItem (fica = NULL)
    */

void verificarMaiorStock(Item itemAlterado, short int valor)
{
  
  if(biggestItem != NULL)
  {

    //após aumentar um stock:

    if(valor > 0)
      if(stock(itemAlterado) > stock(biggestItem) ||
        (stock(itemAlterado) == stock(biggestItem) && key(itemAlterado) < key(biggestItem)))

        biggestItem = itemAlterado;

    //após diminuir um stock:

    if(valor < 0)
      /* se o itemAlterado for o biggestItem, mais tarde, terá de se escolher
      novamente o biggestItem */
      if(key(itemAlterado) == key(biggestItem))
        biggestItem = NULL;
  }
}



/* procurarMaiorStock: escolher o biggestItem (produto com maior stock; em caso de dois 
                       produtos com mesmo stock, dá-se prioridade ao que tem menor chave) */

void procurarMaiorStock()
{

  link x;
  int i;

  // percorre-se cada lista ligada da hashtable e escolhe-se o biggestItem:

  for(i = 0; i < M; i++)
    for(x = heads[i]; x != NULL; x = x->next)
      if(biggestItem == NULL ||
        stock(x->item) > stock(biggestItem) ||
        (stock(x->item) == stock(biggestItem) && key(x->item) < key(biggestItem)))
        
        biggestItem = x->item;
}



/* produtoMaiorStock: retorna para a funcao_m o biggestItem:
                      - se não se sabe, escolhe-se primeiro (procurarMaiorStock)
                      - se já é sabido, retorna diretamente o biggestItem */

Item produtoMaiorStock()
{

  if(biggestItem == NULL)
    procurarMaiorStock();

  return biggestItem;
}



// ============================================================================
// Funções usadas para a ordenação dos items:


/* sort: função principal que, após criar uma lista simples de items (HashTableToArray)
          e ordená-la (qsort), mostra no output os items ordenados (showItem) */

void sort(){

  int i;
  Item* myArray = HashTableToArray();

  qsort(myArray,size,sizeof(void *),compareItems);

  for(i = 0; i < size; i++)
    showItem(myArray[i]);

  free(myArray);
  
}



/* HashTableToArray: retorna uma lista simples dos items presentes na hashtable */

Item* HashTableToArray() {
  link x;
  int i,j=0;
  Item* arrayItems;
  arrayItems = (Item*)malloc(sizeof(Item)*size);
  
  for (i = 0; i < size; i++)
    arrayItems[i] = NULL;
  

  for(i = 0; i < M; i++)
    for(x = heads[i]; x!=NULL; x = x->next)
      arrayItems[j++] = x->item;

  return arrayItems;
}