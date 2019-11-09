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
        lista->root =NULL;
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
  symtab* ts = malloc(sizeof(symtab));
  ts->root = NULL;
  ts->num = 0;
  ts->next = NULL;
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

/* Retorna el tipo de de variable  id
 * En caso no encontrarlo retorna -1
 */
/*int getTipoVar(symtab* st, char* id){
  int v_encuentra=buscar(st,id);
  if (v_encuentra==-1){
      printf("No se puede retornar en tipo de variable");
  } else {
      return st->var;
  }
}*/
/* Retorna la direccion
 * En caso de no encontrarlo retorna -1
 */
/*int getDir(symtab* st, char* id){
	int v_encuentra=buscar(st,id);
	if (v_encuentra==-1){
    printf("No se puede retornar la direccion");
	} else{
    return st->dir;
	}
}*/

/* Retorna la lista de parametros de un id
 * En caso de no encontrarlo retorna NULL
 */
/*listParam* getListParam(symtab* st, char* id){
int v_encuentra=buscar(st,id);
	if (v_encuentra==-1){
    return st->
  }
}*/

//PRUEBA RAPIDA
int main()
{
    int n, opcion;
    int lp[100];
    /*do
    {
        printf( "\n   1. Agrega.");
        printf( "\n   2. Elimina.");
        printf( "\n   3. Borra lista.");
        printf( "\n   4. numero de elem." );
        printf( "\n   5.-salir ");

        scanf( "%d", &opcion );


        switch ( opcion )
        {
            case 1: printf( "\n   Introduzca un n%cmero entero: ", 163 );
                    scanf( "%d", &n );
                    add(lp,n);
                    break;
            case 2: printf( "\n   Introduzca un n%cmero entero: ", 163 );
                    scanf( "%d", &n );
                   EliminaParam(n, lp);
                    break;
            case 3: printf( "\n   Introduzca un n%cmero entero: ", 163 );
                    borrarListParam(lp);
                    break;
            case 4: printf("Num elementos %i", getNumListParam(lp));
                    break;

         }


    } while ( opcion != 5 );*/

    return 0;
}
