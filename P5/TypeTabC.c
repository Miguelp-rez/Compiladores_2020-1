#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "SymTab.h"
#include "TypeTab.h"

/* Retorna un apuntador a una variable type */

/*AGREGAR FUNCIONES QUE FALTAN*/

tipo *crearTipoPrimitivo(int id){
    tipo* base_type = malloc(sizeof(tipo));
    if(base_type){
        base_type->type = id;
    }else{
        printf("No hay memoria disponible\n");
    }
    return base_type;
}

tipo *crearTipoStruct(symtab* estructura){
    tipo* base_type = malloc(sizeof(tipo));
    if(base_type){
        base_type->estructura = estructura;
    }else{
            printf("No hay memoria disponible\n");
    }
    return base_type;
}

tipoBase *crearArqueTipo(bool is_struct, tipo* base_type){
    tipoBase* nuevo = malloc(sizeof(tipoBase));
    if(nuevo){
        nuevo->est = is_struct;
        nuevo->t = base_type;
    }else{
        printf("No hay memoria disponible\n");
    }
    return nuevo;
}

/* Crear un tipo arreglo */
type *crearTipoArray(int id, char* nombre, tipoBase* tb, int size, int num_elem){
    type* tipo = malloc(sizeof(type));
    if(tipo != NULL){
        //se deben definir los tipos
        tipo->id = id;
        strcpy(tipo->nombre, nombre);
        tipo->tb = tb;
        //se deben definir los tamanos de los tipos
        tipo->tamBytes = size; //depende del tipo (consultar tipo base)
        tipo->numElem = num_elem; //depende de si es arreglo o no
        tipo->next = NULL;
    }
    else{
        printf("No hay memoria disponible\n");  //ERROR
    }
    return tipo;
}

/* Crear un tipo nativo */
type *crearTipoNativo(int id, char* nombre, tipoBase* tb, int size){
    type* tipo = malloc(sizeof(type));
    if(tipo != NULL){
        //se deben definir los tipos
        tipo->id = id;
        strcpy(tipo->nombre, nombre);
        tipo->tb = tb;
        //se deben definir los tamanos de los tipos
        tipo->tamBytes = size; //depende del tipo (consultar tipo base)
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
    printf("Hola");
}

/* Inserta al final de la lista en caso de insertar incrementa num
 * Retorna la posicion donde inserto en caso contrario retorna -1
 */
int insertarTipo(typetab *st, type *t){
    return 0;
}

/* Retorna el tipo base de un tipo
 * En caso de no encontrarlo retorna NULL
 */
tipoBase* getTipoBase(typetab *tt, int id){
    return NULL;
}

/* Retorna el numero de bytes de in tipo
 * En caso de no encontrarlo retorna -1
 */
int getTam(typetab *tt, int id){
    return 0;
}

/* Retorna el numero de elementos de un tipo
 * En caso de no encontrarlo retorna -1
 */
int getNumElem(typetab *tt, int id){
    return 0;
}

/* Retorna el nombre de un tipo
 * En caso de no encontrarlo retorna NULL
 */
char* getNombre(typetab *tt, int id){
    return NULL;
}

int main(){
    tipo *tipo_base = crearTipoPrimitivo(0);
    tipoBase *arquetipo = crearArqueTipo(false, tipo_base);
    type *nuevoTipo = crearTipoNativo(0, "entero", arquetipo, 4); 
    
    return 0;
}