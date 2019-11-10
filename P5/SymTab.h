#ifndef  SYMTAB_H
#define SYMTAB_H
#include "Global.h"

/* Retorna un apuntador a una variable Param */
param* crearParam(int tipo);

/* Retorna un apuntador a una variable listParam */
listParam* crearLP();

/* Agrega al final de la lista el parametro e incrementa num */
void add(listParam* lp, int tipo);

/* Borra toda la lista, libera la memoria */
void borrarListParam(listParam* lp);

/* Cuenta el numero de parametros en la linea */
int getNumListParam(listParam* lp);

/* Retorna un apuntador a una variable symbol */
symbol* crearSymbol(char *id, int tipo, int dir, int tipoVar);

/* Retorna un apuntador a una variable symtab,
 * inicia contador en 0
 */
symtab* crearSymTab();

/* Borra toda la lista, libera la memoria */
void borrarSymTab(symtab*);

/* Inserta al final de la lista, en caso de insertar incrementa num
 * y retorna la posicion donde inserto. En caso contrario retorna -1
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

/* Retorna la direccion de un id
 * En caso de no encontrarlo retorna -1
*/
int getDir(symtab* st, char* id);

/* Retorna la lista de parametros de un id
 * En caso de no encontrarlo retorna NULL
 */
listParam* getListParam(symtab* st, char* id);

/* Retorna el numero de parametros de un id
 * En caso de no encontrarlo retorna -1
 */
int getNumParam(symtab *st, char *id);
#endif