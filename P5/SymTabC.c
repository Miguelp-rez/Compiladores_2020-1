#include <stdio.h>
#include <stdlib.h>
#include "SymTab.h"
//FUNCIONES
/* Retorna un apuntador a una variable Param */
param*crearParam(int tipo){
     param* param_tmp= (param *) malloc(sizeof(param));
     param_tmp-> tipo = tipo;
     param_tmp->next = NULL;
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
     LP_tmp->root =NULL;
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
