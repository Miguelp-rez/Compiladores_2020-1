#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "SymTab.h"
#include "TypeTab.h"

/* Retorna un apuntador a una variable type */

/*AGREGAR FUNCIONES QUE FALTAN*/

type *crearTipo(int id, char* nombre, tipoBase tb){
    type* tipo = malloc(sizeof(type));
    if(tipo != NULL){
        //se deben definir los tipos
        tipo->id = id;
        strcpy(tipo->nombre, nombre);
        tipo->tb = tb;
        //se deben definir los tamanos de los tipos
        tipo->tamBytes = 0; //depende del tipo (consultar tipo base)
        tipo->numElem = 0; //depende de si es arreglo o no
        tipo->next = NULL;
    }
    else{
        printf("No hay memoria disponible\n");  //ERROR
    }
    return tipo;
}

/* Borra type, libera memoria */
void borrarType(type *t){

}

/* Inserta al final de la lista en caso de insertar incrementa num
 * Retorna la posicion donde inserto en caso contrario retorna -1
 */
int insertarTipo(typetab *st, type *t){

}

/* Retorna el tipo base de un tipo
 * En caso de no encontrarlo retorna NULL
 */
tipoBase getTipoBase(typetab *tt, int id){

}

/* Retorna el numero de bytes de in tipo
 * En caso de no encontrarlo retorna -1
 */
int getTam(typetab *tt, int id){

}

/* Retorna el numero de elementos de un tipo
 * En caso de no encontrarlo retorna -1
 */
int getNumElem(typetab *tt, int id){

}

/* Retorna el nombre de un tipo
 * En caso de no encontrarlo retorna NULL
 */
char* getNombre(typetab *tt, int id){

}

int main(){
    return 0;
}