#include "SymTab.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _symstack symstack;

struct _symstack{
    symtab *root;
    int num;
};


symstack *crearSymStack();
void borrarSymStack(symstack *pts);
void insertarSymTab(symstack *pts, symtab *sym_tab);
symtab* getCima(symstack *pts);
symtab* sacarSymTab(symstack *pts);

symstack *crearSymStack(){
    symstack *nuevaPTS = malloc(sizeof(symstack));
    if(nuevaPTS){
        nuevaPTS->root = NULL;
        nuevaPTS->num = 0;
    }else{
        printf("No hay memoria disponible");
    }
}

void borrarSymStack(symstack *pts){
    if(pts){
        symtab* aux;
        while(pts->root){
          aux = pts->root;
          pts->root = pts->root->next;
          free(aux);
        }
        free(pts);
  }else{
    printf("No existe la lista de parametros\n");
  }
}

symtab* getCima(symstack *pts){
    symtab *aux = pts->root;
    int size = pts->num;
    int i;
    for(i=0; i<size; i++){
        aux = aux->next;
    }
    return aux;
}

void insertarSymTab(symstack *pts, symtab *sym_tab){
    if(pts){    //Si existe la pila
        if (pts->root == NULL){     //La pila esta vacia
            pts->root = sym_tab;
        }else{                      //La pila no esta vacia
            symtab *aux = getCima(pts);
            aux->next = sym_tab;
        }
        pts->num++;
    }else{
        printf("La pila de tabla de simbolos no existe");
    }
}

symtab* sacarSymTab(symstack *pts){
    if(pts){    //Si existe la pila
        if (pts->root == NULL){     //La pila esta vacia
            printf("ERROR: La pila de tabla de simbolos esta vacia");
        }else{                      //La pila no esta vacia
            symtab *cima = getCima(pts);
            symtab *aux;
            int size = pts->num;
            int i;
            for(i=0; i<size-1; i++){
                aux = aux->next;
            }
            aux->next = NULL;
            free(aux);
            return(cima);
    return aux;
        }
        pts->num++;
    }else{
        printf("La pila de tabla de simbolos no existe");
    }
}

int main(){
    return 0;
}