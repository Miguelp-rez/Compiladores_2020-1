/*
 * Compiladores Proyecto final
 * Programado por:
 * Lopez Martinez Andres
 * Morales Tellez Carlos Gamaliel
 * Perez Quiroz Miguel Angel
 * Sanchez Diaz Maria Beatriz
 * Fecha: 04/12/19
*/

/* Archivo de definiciones globales */

#ifndef GLOBAL_H
#define GLOBAL_H

typedef struct _param param;
struct _param{
    int tipo;
    param* next;
};

typedef struct _listParam listParam;
struct _listParam{
    param* root;
    int num;
};

typedef struct _symbol symbol;
struct _symbol{
    char id[32];
    int tipo;
    int dir;
    int tipoVar;
    listParam* params;
    symbol* next;
};

typedef struct _symtab symtab;
struct _symtab{
    symbol* root;
    int num;
    symtab* next;
};

typedef union _base base;
union _base{
    int simple;   // Base de tipo array
    symtab *tabla;  // Base de tipo registro
};

typedef struct _type type;
struct _type{
    int id;
    char nombre[10];
    int tamBytes;
    int numElem;
    type *next;
    base* tb;
};

typedef struct _typetab typetab;
struct _typetab{
    type *root;
    int num;
    typetab* next;
};

#endif
