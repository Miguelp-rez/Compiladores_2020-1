/*
 * Compiladores Practica 5
 * Programado por:
 * Lopez Martinez Andres
 * Morales Tellez Carlos Gamaliel
 * Perez Quiroz Miguel Angel
 * Sanchez Diaz Maria Beatriz
 * Fecha: 09/11/19
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "SymTab.h"
#include "TypeTab.h"
#include "SymTabC.c"
#include "TypeTabC.c"
#include "SymTabStack.c"
#include "TypeTabStack.c"

int main(){
    
    int exito;
    symstack* sts = crearSymStack();
    symtab* st = crearSymTab();
    symbol* simbolo;
    param* parametro;
    
    //insercion de simbolo sin parametros, debe funcionar
    simbolo = crearSymbol("prueba", 1, 10, 1);
    exito = insertar(st, simbolo);
    if(exito == -1)
        printf("Error al insertar\n");

    //insercion de simbolo sin parametros con id repetido, debe fallar
    simbolo = crearSymbol("prueba", 1, 10, 1);
    exito = insertar(st, simbolo);
    if(exito == -1)
        printf("Error al insertar\n");

    //insercion de simbolo con parametros
    simbolo = crearSymbol("prueba_param", 1, 10, 1);
    add(simbolo->params, 10);
    add(simbolo->params, 11);
    add(simbolo->params, 12);
    exito = insertar(st, simbolo);
    if(exito == -1)
        printf("Error al insertar\n");

    imprimirTabla(st);
    insertarSymTab(sts,st);
    st = getCimaSym(sts);
    sacarSymTab(sts);
    borrarSymStack(sts);
    

    tipo *tipo_base = crearTipoPrimitivo(0);
    tipoBase *arquetipo = crearArqueTipo(false, tipo_base);
    type *nuevoTipo = crearTipoNativo(0, "entero", arquetipo, 4);

  return 0;
}
