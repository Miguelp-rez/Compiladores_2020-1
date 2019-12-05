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
    printf("---------------PRUEBA DE TABLA DE SIMBOLOS---------------\n");
    symtab* st = crearSymTab();
    symbol* simbolo;
    param* parametro;
    
    //insercion de simbolo sin parametros, debe funcionar
    printf("\n * Se inserta un simbolo sin parametros valido\n");
    printf("Resultado esperado: EXITO\n");
    simbolo = crearSymbol("prueba", 1, 10, 1);
    exito = insertar(st, simbolo);
    if(exito == -1)
        printf("ERROR al insertar\n");
    else
        printf("EXITO\n");

    //insercion de simbolo sin parametros con id repetido, debe fallar
    printf("\n * Se inserta un simbolo sin parametros invalido\n");
    printf("Resultado esperado: ERROR\n");
    simbolo = crearSymbol("prueba", 1, 10, 1);
    exito = insertar(st, simbolo);
    if(exito == -1)
        printf("ERROR al insertar repetido\n");
    else
        printf("EXITO\n");

    //insercion de simbolo con parametros
    printf("\n * Se inserta un simbolo con parametros valido\n");
    printf("Resultado esperado: EXITO\n");
    simbolo = crearSymbol("prueba_param", 1, 10, 1);
    add(simbolo->params, 10);
    add(simbolo->params, 11);
    add(simbolo->params, 12);
    exito = insertar(st, simbolo);
    if(exito == -1)
        printf("Error al insertar\n");
    else
        printf("EXITO\n");

    imprimirTablaSym(st);

    //PRUEBA DE PILA DE TABLAS DE SIMBOLOS
    printf("---------------PRUEBA DE PILA TABLA DE SIMBOLOS---------------\n");
    symstack* sts = crearSymStack();
    symtab* aux_ts = crearSymTab();
    
    printf("\n * Se inserta una tabla de simbolos valida\n");
    insertarSymTab(sts,st);

    printf("\n * Se recupera el tope de la pila de TS\n");
    aux_ts = getCimaSym(sts);
    imprimirTablaSym(aux_ts);

    printf("\n * Se saca el ultimo elemento de la pila de TS\n");
    aux_ts = sacarSymTab(sts);
    imprimirTablaSym(aux_ts);

    printf("\n * Se recupera el tope de la pila de TS\n");
    //aux_ts = getCimaSym(sts);
    //imprimirTablaSym(aux_ts);
    borrarSymTab(aux_ts);

    //PRUEBA DE TABLA DE TIPOS
    printf("---------------PRUEBA DE TABLA DE TIPOS---------------\n");
    int size;
    tipo *tipo_base;
    tipoBase *arquetipo;
    type *nuevoTipo;
    typetab* tt = crearTypeTab();

    //insercion de tipo array
    printf("\n * Se inserta un tipo array valido\n");
    arquetipo = getTipoBase(tt, 0);  //Entero
    size = getTam(tt,0) * 2; //2 elementos
    nuevoTipo = crearTipoArray(tt->num, "array", arquetipo, size, 2);
    exito = insertarTipo(tt, nuevoTipo);
    if(exito == -1)
        printf("Error al insertar\n");
    else
        printf("EXITO\n");  

    //insercion de tipo struct
    printf("\n * Se inserta un tipo struct valido\n");
    symtab* st2 = crearSymTab();
    typetab* tt2 = crearTypeTab();
    tipo_base = crearTipoStruct(st2);
    arquetipo = crearArqueTipo(true, tipo_base);
    nuevoTipo = crearTipoNativo(tt->num, "struct", arquetipo, 20);
    exito = insertarTipo(tt, nuevoTipo);
    if(exito == -1)
        printf("Error al insertar\n");
    else
        printf("EXITO\n");

    imprimirTablaType(tt);

    //PRUEBA DE PILA DE TABLAS DE TIPOS
    printf("---------------PRUEBA DE PILA TABLA DE TIPOS---------------\n");
    typestack *tts = crearTypeStack();
    typetab *aux = crearTypeTab();

    printf("\n * Se inserta una tabla de tipos valida\n");
    insertarTypeTab(tts, tt);

    printf("\n * Se recupera el tope de la pila de TT\n");
    aux = getCimaType(tts);
    imprimirTablaType(aux);

    printf("\n * Se inserta una tabla de tipos valida\n");
    insertarTypeTab(tts, tt2);

    printf("\n * Se recupera el tope de la pila de TT\n");
    aux = getCimaType(tts);
    imprimirTablaType(aux);

    printf("\n * Se saca el ultimo elemento de la pila de TT\n");
    aux = sacarTypeTab(tts);
    imprimirTablaType(aux);

    printf("\n * Se recupera el tope de la pila de TT\n");
    aux = getCimaType(tts);
    imprimirTablaType(aux);
    borrarTypeTab(aux);

    printf("\n * Se destruye la pila de TT\n");
    borrarTypeStack(tts);
    printf("\n * Se destruye la pila de TS\n");
    borrarSymStack(sts);

  return 0;
}
