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
    //PRUEBA DE TABLA DE SIMBOLOS
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
        printf("Error al insertar repetido\n");

    //insercion de simbolo con parametros
    simbolo = crearSymbol("prueba_param", 1, 10, 1);
    add(simbolo->params, 10);
    add(simbolo->params, 11);
    add(simbolo->params, 12);
    exito = insertar(st, simbolo);
    if(exito == -1)
        printf("Error al insertar\n");

    imprimirTablaSym(st);

    //PRUEBA DE PILA DE TABLAS DE SIMBOLOS
    symstack* sts = crearSymStack();
    insertarSymTab(sts,st);
    st = getCimaSym(sts);
    sacarSymTab(sts);
    borrarSymStack(sts);
    
    //PRUEBA DE TABLA DE TIPOS
    tipo *tipo_base;
    tipoBase *arquetipo;
    type *nuevoTipo;
    typetab* tt = crearTypeTab();

    //insercion de tipo int
    tipo_base = crearTipoPrimitivo(0);
    arquetipo = crearArqueTipo(false, tipo_base);
    nuevoTipo = crearTipoNativo(0, "entero", arquetipo, 4);
    exito = insertarTipo(tt, nuevoTipo);
    if(exito == -1)
        printf("Error al insertar\n");

    //insercion de tipo array
    tipo_base = crearTipoPrimitivo(0);
    arquetipo = crearArqueTipo(false, tipo_base);
    nuevoTipo = crearTipoArray(1, "array", arquetipo, 8, 2);
    exito = insertarTipo(tt, nuevoTipo);
    if(exito == -1)
        printf("Error al insertar\n");    

    //insercion de tipo struct
    symtab* st2 = crearSymTab();
    tipo_base = crearTipoStruct(st2);
    arquetipo = crearArqueTipo(true, tipo_base);
    nuevoTipo = crearTipoNativo(2, "struct", arquetipo, 20);
    exito = insertarTipo(tt, nuevoTipo);
    if(exito == -1)
        printf("Error al insertar\n");

    imprimirTablaType(tt);
    borrarSymTab(st2);
    borrarTypeTab(tt);

    //PRUEBA DE PILA DE TABLAS DE TIPOS

  return 0;
}
