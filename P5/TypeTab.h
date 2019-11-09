#ifndef  TYPETAB_H
#define TYPETAB_H
typedef struct _type type;
typedef struct _tipoBase tipoBase;
typedef union _tipo tipo;

union _tipo{
    int type;   // Tipo simple
    symtab *estructura;  // Tipo estructura
};

struct _tipoBase{
    bool est;   // Si es verdadero es estructura si no es tipo simple
    tipo t;
};

struct _type{
    int id;
    char nombre[10];    // Se puede sustituir por un entero tambien
    tipoBase tb;
    int tamBytes;
    int numElem;
    type *next;
};

typedef struct _typetam typetab;

struct _typetab{
    type *root;
    int num;
};

/* Retorna un apuntador a una variable type */
type *crearTipo();

/* Borra type, libera memoria */
void borrarType(type *t);

/* Inserta al final de la lista en caso de insertar incrementa num
 * Retorna la posicion donde inserto en caso contrario retorna -1
 */
int insertarTipo(typetab *st, type *t);

/* Retorna el tipo base de un tipo
 * En caso de no encontrarlo retorna NULL
 */
tipoBase getTipoBase(typetab *tt, int id);

/* Retorna el numero de bytes de in tipo
 * En caso de no encontrarlo retorna -1
 */
int getTam(typetab *tt, int id);

/* Retorna el numero de elementos de un tipo
 * En caso de no encontrarlo retorna -1
 */
int getNumElem(typetab *tt, int id);

/* Retorna el nombre de un tipo
 * En caso de no encontrarlo retorna NULL
 */
char* getNombre(typetab *tt, int id);
#endif