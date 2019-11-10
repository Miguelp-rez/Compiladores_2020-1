#ifndef  TYPETAB_H
#define TYPETAB_H
#include "Global.h"

/* Retorna un apuntador a una variable type */
tipo *crearTipoPrimitivo(int id);

tipo *crearTipoStruct(symtab* estructura);

tipoBase *crearArqueTipo(bool is_struct, tipo* base_type);

type *crearTipoArray(int id, char* nombre, tipoBase* tb, int size, int num_elem);

type *crearTipoNativo(int id, char* nombre, tipoBase* tb, int size);

/* Borra type, libera memoria */
void borrarType(type *t);

/* Inserta al final de la lista en caso de insertar incrementa num
 * Retorna la posicion donde inserto en caso contrario retorna -1
 */
int insertarTipo(typetab *st, type *t);

/* Retorna el tipo base de un tipo
 * En caso de no encontrarlo retorna NULL
 */
tipoBase* getTipoBase(typetab *tt, int id);

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
