#ifndef  SYMTAB_H
#define SYMTAB_H
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

/* Retorna un apuntador a una variable Param */
param* crearParam(int tipo);
/* Borra param, libera la memoria */
void borraParam(param* p);
/* Retorna un apuntador a una variable listParam */
listParam* crearLP();
/* Agrega al final de la lista el parametro e incrementa num */
void add(listParam* lp, int tipo);
/* Borra toda la lista, libera la memoria */
void borrarListParam(listParam* lp);
/* Cuenta el numero de parametros en la linea */
int getNumListParam(listParam* lp);



typedef struct _symbol symbol;

struct _symbol{
    char id[32];
    int tipo;
    int dir;
    int tipoVar;
    listParam* params;
    symbol* next;
};

/* Retorna un apuntador a una variable symbol */
symbol* crearSymbol(char id[32], int tipo, int dir, int tipoVar, listParam* params);
/* Borra symbol, libera la memoria */

typedef struct _symtab symtab;

struct _symtab{
    symbol* root;
    int num;
    symtab* next;
};


/* Retorna un apuntador a una variable symtab,
 * inicia contador en 0
 */
symtab* crearSymTab(symbol* root, int num, symtab* next);

/* Borra toda la lista, libera la memoria */
void borrarSymTab(symtab*);

/* inserta al final de la lista en caso de insertar incrementa num
 * rentorna la posicion donde insero en caso contrario retorna -1
 */ 
int insertar(symtab* st, symbol* sym);
/* Busca en la tabla de simbolos mediante el id
 * En caso de encontrar el id retorna la posicion
 * En caso contrario retorna -1
 */
int buscar(symtab* st, char* id);
/* Retorna el tipo de dato de un id
 * En caso no encontrarlo retorna -1
 */
int getTipo(symtab* st, char* id);
/* Retorna el tipo de Variable de un id
 * En caso de no encontrarlo retorna -1
 */
int getTipoVar(symtab* st, char* id);

int getDir(symtab* st, char* id);
/* Retorna la lista de parametros de un id
 * En caso de no encontrarlo retorna NULL
 */
listParam* getListParam(symtab* st, char* id);
/* Retorna el numero de parametros de un id
 * En caso de no encontrarlo retorna -1
 */
int getNumListParam(symtab* st, char* id);
#endif