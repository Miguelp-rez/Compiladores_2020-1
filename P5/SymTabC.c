#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymTab.h"

//FUNCIONES
/* Retorna un apuntador a una variable Param */
param* crearParam(int tipo){
    param* parametro= malloc(sizeof(param));
    if(parametro != NULL){
        parametro->tipo = tipo;
        parametro->next = NULL;
    }
    else{
        printf("No hay memoria disponible");  //ERROR
    }
    return parametro;
}

/* Retorna un apuntador a una variable listParam */
listParam *crearLP(){
    listParam* lista = malloc(sizeof(listParam));
    if(lista != NULL){
        lista->root = NULL;
        lista->num = 0;
    }
    else{
        printf("No hay memoria disponible");  //ERROR
    }
    return lista;
}
/* Agrega al final de la lista el parametro e incrementa num */
void add(listParam* lp, int tipo){
    param* parametro = crearParam(tipo);
    if(lp->root == NULL){
        lp->root = parametro;
    }else{
        param* puntero = lp->root;
        while(puntero->next){
            puntero = puntero->next;
        }
        puntero->next = parametro;
    }
    lp->num++;
}
/* Borra toda la lista, libera la memoria */
void borrarListParam(listParam* lp){
    if(lp){
        param* aux;
        while(lp->root){
          aux = lp->root;
          lp->root = lp->root->next;
          free(aux);
        }
        free(lp);
  }else{
    printf("No existe la lista de parametros");
  }
}

/* Cuenta el numero de parametros en la linea */
int getNumListParam(listParam *lp){
    return lp->num;
}

/* Retorna un apuntador a una variable symbol */
symbol* crearSymbol(char *id, int tipo, int dir, int tipoVar){
    symbol* sym_tmp= malloc(sizeof(symbol));
    if(sym_tmp != NULL)
    {
        strcpy(sym_tmp->id, id);
        sym_tmp->tipo = tipo;
        sym_tmp->dir = dir;
        sym_tmp->tipoVar = tipoVar;
        sym_tmp->params = crearLP();
        sym_tmp->next = NULL;
    }
    else
    {
        printf("No hay memoria disponible");  //ERROR
    }
 return sym_tmp;

}

/* Retorna un apuntador a una variable symtab,
 * inicia contador en 0
 */
symtab* crearSymTab(){
  symtab* st = malloc(sizeof(symtab));
  st->root = NULL;
  st->num = 0;
  st->next = NULL;
  return st;
}

/* Borra toda la lista, libera la memoria */
void borrarSymTab(symtab* st){
    if(st){
        symbol* aux;
        while(st->root){
          aux = st->root;
          st->root = st->root->next;
          borrarListParam(aux->params);
          free(aux);
        }
        free(st);
    }
    else{
        printf("No existe la tabla de simbolos");
    }
}

/* Inserta al final de la lista, en caso de insertar incrementa num
 * y retorna la posicion donde inserto. En caso contrario retorna -1
*/
int insertar(symtab* st, symbol* sym){
    if(st){
        int posicion = buscar(st, sym->id);
        if(posicion == -1){
            st->num++;
            if(st->root == NULL){
                st->root = sym; //es el primer simbolo
            }
            else{
                symbol* simbolo_actual = st->root;
                while(simbolo_actual->next != NULL){
                    simbolo_actual = simbolo_actual->next;
                }
                simbolo_actual->next = sym;                
            }
            return (st->num);
        }
        else{
            printf("Error: el simbolo ya existe");
            return -1;
        }
	}else
        printf("Error: la tabla de simbolos no existe");
}

/* Busca en la tabla de simbolos mediante el id
 * En caso de encontrar el id retorna la posicion
 * En caso contrario retorna -1
 */
int buscar(symtab* st, char* id){
    if(st){
        int posicion = 0;
        if(st->root == NULL){
            return -1; //La tabla esta vacia
        }
        symbol* simbolo_actual = st->root;
        while (simbolo_actual != NULL){
            posicion++;
            if (id == simbolo_actual->id)
                return posicion;
            else
                simbolo_actual = simbolo_actual->next;
        }
        return -1;	//El simbolo no existe
  	}else
  		printf("Error: la tabla de simbolos no existe");
}

/* Retorna el tipo de dato de un id
 * En caso no encontrarlo retorna -1
 */
int getTipo(symtab* st, char* id){
    int posicion = buscar(st, id);
    if (posicion == -1){
        printf("Tipo de dato no encontrado");
        return -1;
    }else{
        symbol* simbolo_actual = st->root;
        while(posicion != 1){
            posicion--;
            simbolo_actual = simbolo_actual->next;
        }
        return (simbolo_actual->tipo);
    }
}

/* Retorna el tipo de variable de un id
 * En caso no encontrarlo retorna -1
 */
int getTipoVar(symtab* st, char* id){
    int posicion = buscar(st, id);
    if (posicion == -1){
        printf("Tipo de variable no encontrado");
        return -1;
    }else{
        symbol* simbolo_actual = st->root;
        while(posicion != 1){
            posicion--;
            simbolo_actual = simbolo_actual->next;
        }
        return (simbolo_actual->tipoVar);
    }
}

/* Retorna la direccion
 * En caso de no encontrarlo retorna -1
 */
int getDir(symtab* st, char* id){
    int posicion = buscar(st, id);
    if (posicion == -1){
        printf("Direccion no encontrada");
        return -1;
    }else{
        symbol* simbolo_actual = st->root;
        while(posicion != 1){
            posicion--;
            simbolo_actual = simbolo_actual->next;
        }
        return (simbolo_actual->dir);
    }
}

/* Retorna la lista de parametros de un id
 * En caso de no encontrarlo retorna NULL
 */
listParam* getListParam(symtab* st, char* id){
    int posicion = buscar(st, id);
    if (posicion == -1){
        printf("Lista de parametros no encontrada");
        return NULL;
    }else{
        symbol* simbolo_actual = st->root;
        while(posicion != 1){
            posicion--;
            simbolo_actual = simbolo_actual->next;
        }
        return (simbolo_actual->params);
    }
}

/* Retorna el numero de parametros de un id
 * En caso de no encontrarlo retorna -1
 */
int getNumParam(symtab *st, char *id){
    int posicion = buscar(st, id);
    if (posicion == -1){
        printf("Numero de parametros no encontrados");
        return -1;
    }else{
        symbol* simbolo_actual = st->root;
        while(posicion != 1){
            posicion--;
            simbolo_actual = simbolo_actual->next;
        }
        return (simbolo_actual->params->num);
    }
}

void imprimirTabla(symtab *st){
    int nodos = 1;
    symbol* simbolo_actual = st->root;
    while(nodos != (st->num)+1){
        printf("Simbolo #%i\n", nodos);
        printf("ID:%s\n", simbolo_actual->id);
        printf("Tipo:%i\n", simbolo_actual->tipo);
        printf("Dir:%i\n", simbolo_actual->dir);
        printf("Tipo de variable:%i\n", simbolo_actual->tipoVar);
        printf("Numero de parametros:%i\n\n", getNumListParam(simbolo_actual->params));
        simbolo_actual = simbolo_actual->next;
        nodos++;
    }
}

//PRUEBA RAPIDA
int main()
{
    int exito;
    symtab* st = crearSymTab();
    symbol* simbolo = crearSymbol("prueba", 1, 10, 1);
    exito = insertar(st, simbolo);
    if(exito != -1)
        imprimirTabla(st);
    else
        printf("Error al insertar\n");
    borrarSymTab(st);
    return 0;
}
