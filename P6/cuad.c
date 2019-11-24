#include "cuad.h"
#include <stdio.h>
#include <stdlib.h>



quad *crea_quad(char* op , char* arg1, char *arg2, char *res){
	quad* q = malloc(sizeof(q));
	if(q != NULL){
        q->op = op;
		q->arg1 = arg1;
		q->arg2 = arg2;
		q->res = res;
    }
    else{
        printf("No hay memoria disponible\n");  //ERROR
    }
    return q;
}

void agregar_cuadrupla(code* c, char *op, char* arg1, char *arg2, char* res){
	quad* q= crea_quad(op,arg1,arg2,res);
    if(c->root == NULL){
        c->root = q;
    }else{
        quad* puntero = c->root;
        while(puntero->next){
            puntero = puntero->next;
        }
        puntero->next = q;
    }
    c->num_instrucciones++;
}


code* crea_code(){
	code* c= malloc(sizeof(code));
    if(c != NULL){
        c->root = NULL;
		c->num_instrucciones = 0;
    }
    else{
        printf("No hay memoria disponible\n");  //ERROR
    }
    return c;
}

void elimina_quad(quad *q){
	while(q){
		elimina_quad(q->next);
	}
	free(q);
}

void elimina_code(code *c){
	free(c);
	elimina_quad(c->root);
}

code* imprime(code *c){
    printf("\t***CUADRUPLAS***\n");
    printf("OP\tARG1\tARG2\tRES\n");
    for(int i = 0; i < c->num_instrucciones; i++){
        printf("%s\t%s\t%s\t%s\n",c->root[i].op, c->root[i].arg1, c->root[i].arg2, c->root[i].res);
    }
}


int main(int argc, char const *argv[])
{
	code* cod= crea_code();
	agregar_cuadrupla(cod, "-", "a", "b", "t0" );
	imprime(cod);
	return 0;
}
