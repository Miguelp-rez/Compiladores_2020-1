/*
 * Compiladores Proyecto final
 * Programado por:
 * Lopez Martinez Andres
 * Morales Tellez Carlos Gamaliel
 * Perez Quiroz Miguel Angel
 * Sanchez Diaz Maria Beatriz
 * Fecha: 08/12/19
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backpatch.h"

etiqueta* crear_etiqueta(char *valor){
    etiqueta* etiqueta = malloc(sizeof(etiqueta));
    if (etiqueta){
      etiqueta->valor = valor;
      etiqueta->next = NULL;
      return etiqueta;
    }
    printf("No hay memoria suficiente para crear una lista de etiquetas\n");
    return NULL;
}

l_etiquetas* crear_lista_etiquetas(){
    l_etiquetas* l_etis = malloc(sizeof(l_etiquetas));
    if (l_etis){
      l_etis->num = 0;
      //l_etis->num_codigo = 0;
      l_etis->root = NULL;
      l_etis->codigo = NULL;
      return l_etis;
    }
    printf("No hay memoria suficiente para crear una lista de etiquetas\n");
    return NULL;
}

void insertar_etiqueta(l_etiquetas* l_etis, etiqueta* eti){
    if(l_etis){
      eti->next = l_etis->root;
      l_etis->root = eti->next;
      l_etis->num++;
    } else {
      printf("No existe la lista de etiquetas\n");
    }
}

void elimina_etiqueta(etiqueta *eti){
      if(eti->next){
          elimina_etiqueta(eti->next);
      }
          free(eti);
}

void elimina_l_etiquetas(l_etiquetas *l_etis){
  if(l_etis->root){
    elimina_etiqueta(l_etis->root);
  }
  free(l_etis);
}



l_etiquetas* merge(l_etiquetas* l_etis_1, l_etiquetas* l_etis_2){
    l_etiquetas* l_etis = crear_lista_etiquetas();
    etiqueta* aux_l_etis = l_etis->root;
    etiqueta* aux_l_etis_1 = l_etis_1->root;
    etiqueta* aux_l_etis_2 = l_etis_2->root;
    for(int i = 0; i < l_etis_1->num; i++){
        //aux_l_etis_1->next = l_etis->root;
        l_etis->root = aux_l_etis_1;
        aux_l_etis_1 = aux_l_etis_1->next;
        l_etis->root = aux_l_etis->next;
    }
    for(int i =0; i< l_etis_2->num; i++){
        //aux_l_etis_2->next = l_etis->root;
        l_etis->root = aux_l_etis_2;
        aux_l_etis_2 = aux_l_etis_2->next;
        l_etis->root = aux_l_etis  ->next;
    }
    return l_etis;
}

void backpatch(code* c,l_etiquetas* l_etis, etiqueta* eti){
    quad *instruccion = c->root;
    etiqueta *eti_aux = l_etis->root;
    for(int i=0; i < l_etis->num; i++){
        for(int j=0; j < c->num_instrucciones; j++){
            if(strcmp(instruccion->res,eti_aux->valor) == 0){
              strcpy(instruccion->res,eti->valor);
            }
            instruccion = instruccion->next;
        }
        eti_aux = eti_aux->next;
    }
}



//PRUEBA
/*int main() {

  return 0;
}*/
