#include <stdio.h>
#include <stdlib.h>
#include "SymTab.h"
//FUNCIONES
/* Retorna un apuntador a una variable Param */
param* crearParam(int tipo){
     param* param_tmp= (param *) malloc(sizeof(param));
    if(param_tmp != NULL){
        param_tmp->tipo = tipo;
        param_tmp->next = NULL;
    }
    else{
        printf("No hay memoria disponible");  //ERROR  
    } 
 return param_tmp;
}

/* Borra param, libera la memoria */
void borraParam(param *p){
   p->next=NULL;
   free(p);
}

/* Retorna un apuntador a una variable listParam */
listParam *crearLP(){
    listParam* LP_tmp= (listParam *) malloc(sizeof(listParam));
    if(LP_tmp != NULL){
        LP_tmp->root =NULL;
    }
    else{
        printf("No hay memoria disponible");  //ERROR
    }
    return LP_tmp;
}
/* Agrega al final de la lista el parametro e incrementa num */
void add(listParam* lp, int tipo){
    param* param_tmp=crearParam(tipo);
    if(lp->root == NULL){
        lp->root=param_tmp;
    }else{
        param* puntero= lp->root;
        while(puntero->next){
            puntero= puntero->next;
        }
        puntero->next=param_tmp;
    }
    lp->num++;
}
/* Borra toda la lista, libera la memoria */
void borrarListParam(listParam* lp){
   free(lp);
}


//Agrego funcion para eliminar elemento de la lista

void EliminaParam(int n, listParam* lp){
    if (lp->root){
            if(n==0){
                param* eliminado= lp->root;
                lp->root= lp->root->next;
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
        sym_tmp->id = id;
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
void borrarSymTab(symtab* st);
/* Retorna un apuntador a una variable symtab,
 * inicia contador en 0
 */
symtab* crearSymTab(){


}
/* Borra toda la lista, libera la memoria */
void borrarSymTab(symtab* st);
/* inserta al final de la lista en caso de insertar incrementa num
 * rentorna la posicion donde insero en caso contrario retorna -1
 */
int insertar(symtab* st, symbol* sym){
symtab* symtab_tmp=crearParam(sym);
    if(st->root == NULL){
        st->root=symtab_tmp;
    }else{
        symtab* puntero= st->root;
        while(puntero->next){
            puntero= puntero->next;
        }
        puntero->next=symtab_tmp;
    }
    st->num++;


}
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
int getDir(symtab* st, char* ide;
/* Retorna la lista de parametros de un id
 * En caso de no encontrarlo retorna NULL
 */
listParam* getListParam(symtab* st, char* id);
/* Retorna el numero de parametros de un id
 * En caso de no encontrarlo retorna -1
 */
int getNumListParam(symtab* st, char* id);
//PRUEBA RAPIDA
int main(){
    int n, opcion;
    int lp[100];
    do{
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
