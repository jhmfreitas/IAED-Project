/*================================================
    Projeto 2 IAED - 2016/17 2ºsemestre
    ***********************************
    GRUPO tg037:
        -> João Henrique Marques de Freitas, 87671 - LEIC-T
        -> Pedro Amaral Soares, 87693 - LEIC-T
==================================================*/

#include <stdio.h>
#include <stdlib.h>

#include "Item.h"
#include "estrutura.h"


void funcao_a(unsigned long int ,int );
void funcao_l();
void funcao_r(Key);
void funcao_m();
void funcao_x();

int main(){
  char command;
  unsigned long int chave;
  int valor;
  STinit(7043);
    while(1){
        command=getchar();
        switch(command)
        {
        case 'a':
            scanf("%lx %d",&chave,&valor);      // input: chave (hexadecimal) e stock (inteiro)
            getchar();
            funcao_a(chave,valor);
            break;
        case 'l':
            getchar();
            funcao_l();
            break;
        case 'r':
            scanf("%lx",&chave);                // input: chave (hexadecimal)
            getchar();
            funcao_r(chave);
            break;
        case 'm':
            getchar();
            funcao_m();
            break;
        case 'x':
            funcao_x();
            return EXIT_SUCCESS;
        default:
            fprintf(stderr,"erro: comando desconhecido: %c\n", command);
            return 1;
        }
    }
    return EXIT_FAILURE;
}

//==========================================================================================

/* funcao_a: Incrementa ou reduz o número de unidades associadas ao produto com o código dado.
Se o código não existir deverá ser criado um novo produto com esse código.*/

void funcao_a(unsigned long int chave,int valor){
  Item new_item;
  Item x;
  x=STsearch(chave);                        // procura a chave na estrutura de dados
  
    if (x==NULL){                           // se a chave não é encontrada

        if(valor<0)
            valor = 0;                      // se o valor de stock desejado é negativo, valor = 0
        new_item=newItem(chave,valor);      // cria um novo produto
        STinsert(new_item);                 // insere-o na estrutura de dados
    }
    else{
        x->stock+=valor;                    // se encontra a chave
        if (x->stock<0)                     //adiciona o valor pretendido ao produto
            x->stock=0;                     // se o valor de stock desejado é negativo, valor = 0
        
        if(valor > 0)
            //verificar se este item passa a ser o novo biggestItem (c/ maior stock)
            verificarMaiorStock(x,1);
        if(valor < 0)
            //definir possível novo biggestItem (produto com maior stock)
            verificarMaiorStock(x,-1);
    }
    
    
}


/* funcao_l: lista alfabeticamente todos os produtos, de acordo com as suas chaves*/

void funcao_l(){
    sort();
}


/* funcao_m: escreve o produto com maior número de unidades em stock */

void funcao_m(){
    Item maior = produtoMaiorStock();   //encontra o produto com maior stock
    showItem(maior);                    //mostra o produto com maior stock
}


/* funcao_r: remove o produto com o código dado */

void funcao_r(Key v){
    STdelete(STsearch(v));              //procura o produto na estrutura de dados e remove-o
}


/* funcao_x: Retorna o número de elementos/produtos na estrutura e termina o programa */

void funcao_x(){
    printf("%d\n",STFreeAll());
}