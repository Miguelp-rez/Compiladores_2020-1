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

typedef union _tipo tipo;
union _tipo{
    int type;   // Tipo simple
    symtab *estructura;  // Tipo estructura
};

typedef struct _tipoBase tipoBase;
struct _tipoBase{
    bool est;   // Si es verdadero es estructura si no es tipo simple
    tipo *t;
};

typedef struct _type type;
struct _type{
    int id;
    char nombre[10];    // Se puede sustituir por un entero tambien
    tipoBase *tb;
    int tamBytes;
    int numElem;
    type *next;
};

typedef struct _typetab typetab;
struct _typetab{
    type *root;
    int num;
    typetab* next;
};

#endif