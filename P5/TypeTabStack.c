/*
 * Compiladores Practica 5
 * Programado por:
 * Lopez Martinez Andres
 * Morales Tellez Carlos Gamaliel
 * Perez Quiroz Miguel Angel
 * Sanchez Dias Maria Beatriz
 * Fecha: 09/11/19
*/

#include "TypeTab.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _typestack typestack;

struct _typestack{
    typetab *root;
    int num;
};


typestack *crearTypeStack();
void borrarTypeStack(typestack *ptt);
void insertarTypeTab(typestack *ptt, typetab *type_tab);
typetab* getCima(typestack *ptt);
typetab* sacarTypeTab(typestack *ptt);

typestack *crearTypeStack(){
    typestack *nuevaPTT = malloc(sizeof(typestack));
    if(nuevaPTT){
        nuevaPTT->root = NULL;
        nuevaPTT->num = 0;
    }else{
        printf("No hay memoria disponible");
    }
    return nuevaPTT;
}

void borrarTypeStack(typestack *ptt){
    if(ptt){
        typetab* aux;
        while(ptt->root){
          aux = ptt->root;
          ptt->root = ptt->root->next;
          free(aux);
        }
        free(ptt);
  }else{
    printf("No existe la lista de parametros\n");
  }
}

typetab* getCima(typestack *ptt){
    typetab *aux = ptt->root;
    return aux;
}

void insertarTypeTab(typestack *ptt, typetab *type_tab){
    if(ptt){    //Si existe la pila
        if (ptt->root == NULL){     //La pila esta vacia
            ptt->root = type_tab;
        }else{                      //La pila no esta vacia
            typetab *aux = getCima(ptt);
            type_tab->next = aux;
            ptt->root = type_tab;
        }
        ptt->num++;
    }else{
        printf("La pila de tabla de simbolos no existe");
    }
}

typetab* sacarTypeTab(typestack *ptt){
    if(ptt){    //Si existe la pila
        if (ptt->root == NULL){     //La pila esta vacia
            printf("ERROR: La pila de tabla de simbolos esta vacia");
        }else{                      //La pila no esta vacia
            typetab *cima = getCima(ptt);
            typetab *aux = cima;
            ptt->root = cima->next;
            free(aux);
            return(cima);
        }
        ptt->num--;
    }else{
        printf("La pila de tabla de simbolos no existe");
    }
}

int main(){
    return 0;
}
