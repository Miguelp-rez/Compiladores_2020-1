#include <stdio.h>
#include <stdlib.h>
#include "SymTab.h"
#include <string.h>
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


/* Borra param, libera la memoria */
/*void borraParam(listParam* lp, param *p){
//preguntar si sirve    
    if (lp->root){
        if(n==0){
            param* eliminado = lp->root;
            lp->root = lp->root->next;
            borraParam(eliminado);
            lp->num--;
    }else if(n<lp->num){
        param* puntero= lp->root;
        int posicion=0;
        while(posicion< (n-1)){
            puntero= puntero->next;
            posicion++;
        }
        param* eliminado= puntero->next;
        puntero->next = eliminado->next;
        borraParam(eliminado);
        lp->num--;
      }
    }
   p->next=NULL;
   free(p);
}*/

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
    while(lp->root){
      param* aux = lp->root;
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
symbol* crearSymbol(char *id, int tipo, int dir, int tipoVar, listParam* params){
    symbol* sym_tmp= malloc(sizeof(symbol));
    if(sym_tmp != NULL)
    {
        strcpy(sym_tmp->id, id);
        sym_tmp->tipo = tipo;
        sym_tmp->dir = dir;
        sym_tmp->tipoVar = tipoVar;
        sym_tmp->params = params;
        sym_tmp->next = NULL;
    }
    else
    {
        printf("No hay memoria disponible");  //ERROR
    }
 return sym_tmp;

}
/* Borra symbol, libera la memoria */
void borrarSymbol(symbol* s,symtab* st){
	if(st){
        if(s){
            st->num--;
            symbol* prev, current;
            if(st->root == s){
                st->root = st->root->next;
                free(s);
            }else{
                current = st->root;
                while(current->next != s){
                    current = current->next;
                }
            }
        }
    }
        /*symbol* aux = s;
        if (s->params)
        	borrarListParam(s->params);
        //int posicion;
        while (s->next){
        	st->num--;
        	s->next = s->next->next;
        }
        free(aux);
  }else{
  	printf("No existe el simbolo");
  }*/
}
/* Retorna un apuntador a una variable symtab,
 * inicia contador en 0
 */
symtab* crearSymTab(symbol* root, int num, symtab* next){
  symtab* ts = malloc(sizeof(symtab));
  ts->root = root;
  ts->num = num;
  ts->next = next;
}
/* Borra toda la lista, libera la memoria */
void borrarSymTab(symtab* st){
	  if(st){
      symbol* symbols = st->root;
      symbol* aux;
    	while(st->root != NULL){
        aux = st->root;
        st->root = st->next;
        st->num--; //Preguntar si num es el tamaño de la tabla de símbolos
      	borrarSymbol(aux); //borrarSymbol(borrarSymbol)
      }
  	}else{
    	printf("No existe la tabla de simbolos");
    }
}

/* inserta al final de la lista en caso de
 *  incrementa num
 * rentorna la posicion donde insero en caso contrario retorna -1
 */
int insertar(symtab* st, symbol* sym){
  	if(st){
    	if(st->num == 0){
      	//Se inserta el primer simbolo
        st->root = sym
        st->num++
      }else{
        //Se inserta a partir del segundo simbolo
        symbol *simbolo_actual = malloc(sizeof(symbol));
        symbolo_actual = st->root;
      	if (buscar(st, sym) == -1){
          while(simbolo_actual){
						if(simbolo_actual->next == NULL){
              simbolo_actual->next = sym;
            }else{
              simbolo_actual = simbolo_actual->next;
            }
          }
        }else
        printf("Error: el simbolo ya existe");
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
      symbol *simbolo_actual = malloc(sizeof(symbol));
      symbolo_actual = st->root;
    	while (simbolo_actual->next != NULL){
      		//printf("El id es: %c\n", &symbols.id);
      		if (id == simbolo_actual->id){
            return (simbolo_actual->posicion);
          }else{
            simbolo_actual = simbolo_actual->next;
          }
      }
      return -1;	//El simbolo no existe
  	}else
  		printf("Error: la tabla de simbolos no existe")
}


/* Retorna el tipo de dato de un id
 * En caso no encontrarlo retorna -1
 */
int getTipo(symtab* st, char* id){
  int v_encuentra=buscar(st,id);
  if (v_encuentra==-1){
      printf("No se puede retornar en tipo de dato");
  } else {
      return st->tipo;
  }

}

/* Retorna el tipo de de variable  id
 * En caso no encontrarlo retorna -1
 */
int getTipoVar(symtab* st, char* id){
  int v_encuentra=buscar(st,id);
  if (v_encuentra==-1){
      printf("No se puede retornar en tipo de variable");
  } else {
      return st->var;
  }
}
/* Retorna la direccion
 * En caso de no encontrarlo retorna -1
 */
int getDir(symtab* st, char* id){
	int v_encuentra=buscar(st,id);
	if (v_encuentra==-1){
    printf("No se puede retornar la direccion");
	} else{
    return st->dir;
	}
}

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
    do
    {
        printf( "\n   1. Agrega.", 163 );
        printf( "\n   2. Elimina.", 163 );
        printf( "\n   3. Borra lista.", 163 );
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


    } while ( opcion != 5 );

    return 0;
}
