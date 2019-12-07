/*
 * Compiladores Practica 5
 * Programado por:
 * Lopez Martinez Andres
 * Morales Tellez Carlos Gamaliel
 * Perez Quiroz Miguel Angel
 * Sanchez Diaz Maria Beatriz
 * Fecha: 09/11/19
*/

#ifndef  TYPETAB_H
#define TYPETAB_H
#include "Global.h"

/* Retorna un apuntador a una variable type */
type *crearType(char*, base* tb, int);

/* Borra type, libera memoria */
void borrarType(type *t);

/*Crea tabla de tipos*/
typetab* crearTypeTab();

/* Borra la tabla de tipos, libera memoria */
void borrarTypeTab(typetab *tt);

/* Inserta al final de la lista en caso de insertar incrementa num
 * Retorna la posicion donde inserto en caso contrario retorna -1
 */
int insertarTipo(typetab *tt, type *t);

/* Retorna el tipo base de un tipo
 * En caso de no encontrarlo retorna NULL
 */
base* getTipoBase(typetab *tt, int id);

/* Retorna el numero de bytes de in tipo
 * En caso de no encontrarlo retorna -1
 */
int getTam(typetab* tt, int id);

/* Retorna el numero de elementos de un tipo
 * En caso de no encontrarlo retorna -1
 */
int getNumElem(typetab* tt, int id);

/* Retorna el nombre de un tipo
 * En caso de no encontrarlo retorna NULL
 */
char* getNombre(typetab* tt, int id);

void imprimirTablaType(typetab *tt);
#endif