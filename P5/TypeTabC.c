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

/* Borra la tabla de tipos, libera memoria */
void borrarTypeTab(typetab *tt){
	if(tt){
    type* aux;
    while(tt->root != NULL){
      aux = tt->root;
      tt->root = tt->root->next;
      free(aux);
    }
    free(tt);
  } else {
    printf("No existe la tabla de tipos");
  }
}

int buscarTipo(typetab* tt, char* nombre){
    if(tt){
        int posicion = 0;
        if(tt->root == NULL){
            return -1; //La tabla esta vacia
        }
        type* tipo_actual = tt->root;
        while (tipo_actual != NULL){
            posicion++;
            if (strcmp(nombre, tipo_actual->nombre) == 0)
                return posicion;
            else
                tipo_actual = tipo_actual->next;
        }
        return -1;	//El simbolo no existe
  	}else
  		printf("Error: la tabla de tipos no existe\n");
      return -1;
}

/* Inserta al final de la lista en caso de insertar incrementa num
 * Retorna la posicion donde inserto en caso contrario retorna -1
 */
int insertarTipo(typetab *tt, type *t){
if(tt){
        int posicion = buscarTipo(tt, t->nombre); //Falta programar esta funcion
        if(posicion == -1){
            tt->num++;
            if(tt->root == NULL){
                tt->root = t; //es el primer simbolo
            }
            else{
                type* tipo_actual = tt->root;
                while(tipo_actual->next != NULL){
                    tipo_actual = tipo_actual->next;
                }
                tipo_actual->next = t;
            }
            return (tt->num);
        }
        else{
            printf("No guardar nada\n");
            return -1;
        }
	}else
        printf("Error: la tabla de tipos no existe\n");
        return -1;
}

/* Retorna el tipo base de un tipo
 * En caso de no encontrarlo retorna NULL
 */
 /* Retorna el tipo base de un tipo
  * En caso de no encontrarlo retorna NULL
  */
 tipoBase* getTipoBase(typetab *tt, int id){
   if(tt){
   	if(tt->root){
       type* aux = tt->root;
       for(int i=0;i<id; i++)
         aux = aux->next;
       if(aux->tb)
         return aux->tb;
     }
     return NULL;
   }
   return NULL;
 }
 /* Retorna el numero de bytes de un tipo
  * En caso de no encontrarlo retorna -1
  */
 int getTam(typetab *tt, int id){
 	if(tt->root){
   	type* aux = tt->root;
     //Recorre la lista hasta que encuentre el id
   	for(int i=0;i<id; i++)
     	aux = aux->next;
   	if(aux->tamBytes)
     	return aux->tamBytes;
   }
 	return -1;
 }

 /* Retorna el numero de elementos de un tipo
  * En caso de no encontrarlo retorna -1
  */
 int getNumElem(typetab *tt, int id){
 	if(tt){
   	if(tt->root){
       type* aux = tt->root;
       //Recorre la lista hasta que encuentre el id
       for(int i=0;i<id; i++)
         aux = aux->next;
       if(aux->numElem)
         return aux->numElem;
     }
     return -1;
   }
   return -1;
 }

 /* Retorna el nombre de un tipo
  * En caso de no encontrarlo retorna NULL
  */
 char* getNombre(typetab *tt, int id){
 	if(tt){
     if(tt->root){
   		type* aux = tt->root;
     	//Recorre la lista hasta que encuentre el id
   		for(int i=0;i<id; i++)
     		aux = aux->next;
     	return aux->nombre;
   	}
   }
 	return NULL;
 }



int main(){
    tipo *tipo_base = crearTipoPrimitivo(0);
    tipoBase *arquetipo = crearArqueTipo(false, tipo_base);
    type *nuevoTipo = crearTipoNativo(0, "entero", arquetipo, 4);

    return 0;
}
