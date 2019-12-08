/*
 * Compiladores Proyecto final
 * Programado por:
 * Lopez Martinez Andres
 * Morales Tellez Carlos Gamaliel
 * Perez Quiroz Miguel Angel
 * Sanchez Diaz Maria Beatriz
 * Fecha: 04/12/19
*/

#include "cuad.h"
#include <stdio.h>
#include <stdlib.h>

/*Comentarios de funciones en cuad.h*/
quad *crea_quad(char* op , char* arg1, char *arg2, char *res){
	quad* q = malloc(sizeof(quad));
	if(q){
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
	code* c = malloc(sizeof(code));
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
	if(q->next){
		elimina_quad(q->next);
	}
	free(q);
}

void elimina_code(code *c){
  if(c->root){
    elimina_quad(c->root);
  }
  free(c);
}

/*
void imprime(code *c){
  quad *aux = c->root;
  while(aux){
    printf("%s\t%s\t%s\t%s\n",
      aux->op,
      aux->arg1,
      aux->arg2,
      aux->res);
      aux = aux->next;
  }

}*/


void imprime(code *c){
		FILE *codigo_intermedio = fopen("codigo_intermedio.txt","w");
		quad *instruccion = c->root;
		for(int i = 0 ; i < c->num_instrucciones ; i++){
      printf("%s\t%s\t%s\t%s\n",
              instruccion->op,
              instruccion->arg1,
              instruccion->arg2,
             	instruccion->res);
			//strcmp retorna 0 si son iguales los argumentos
			if(strcmp(instruccion->op, ADICION) == 0){
				//Validación de la forma de la instrucción
				//if (instruccion->res && instruccion->arg1 && instruccion->arg2){
					fprintf(codigo_intermedio,
									"%s = %s + %s\n",
									instruccion->res,
									instruccion->arg1,
									instruccion->arg2);
				//} else
					//printf("Instruccion mal formada.");
			} else if(strcmp(instruccion->op, SUSTRACCION) == 0) {
				//if (instruccion->res && instruccion->arg1 && instruccion->arg2){
					fprintf(codigo_intermedio,
									"%s = %s - %s\n",
									instruccion->res,
									instruccion->arg1,
									instruccion->arg2);
				//} else
					//printf("Instruccion mal formada.");

			} else if(strcmp(instruccion->op, MULTIPLICACION) == 0) {
				fprintf(codigo_intermedio,
								"%s = %s * %s\n",
								instruccion->res,
								instruccion->arg1,
								instruccion->arg2);
			} else if(strcmp(instruccion->op, DIVISION) == 0) {
				fprintf(codigo_intermedio,
								"%s = %s / %s\n",
								instruccion->res,
								instruccion->arg1,
								instruccion->arg2);
			} else if(strcmp(instruccion->op, MODULO) == 0) {
				fprintf(codigo_intermedio,
								"%s = %s mod %s\n",
								instruccion->res,
								instruccion->arg1,
								instruccion->arg2);
			} else if(strcmp(instruccion->op, MENOR_QUE) == 0) {
				fprintf(codigo_intermedio,
								"%s = %s < %s\n",
								instruccion->res,
								instruccion->arg1,
								instruccion->arg2);
			} else if(strcmp(instruccion->op, MAYOR_QUE) == 0) {
				fprintf(codigo_intermedio,
								"%s = %s > %s\n",
								instruccion->res,
								instruccion->arg1,
								instruccion->arg2);
			} else if(strcmp(instruccion->op, MENOR_O_IGUAL) == 0) {
				fprintf(codigo_intermedio,
								"%s = %s <= %s\n",
								instruccion->res,
								instruccion->arg1,
								instruccion->arg2);
			} else if(strcmp(instruccion->op, MAYOR_O_IGUAL) == 0) {
				fprintf(codigo_intermedio,
								"%s = %s >= %s\n",
								instruccion->res,
								instruccion->arg1,
								instruccion->arg2);
			} else if(strcmp(instruccion->op, IGUAL) == 0) {
				fprintf(codigo_intermedio,
								"%s = %s == %s\n",
								instruccion->res,
								instruccion->arg1,
								instruccion->arg2);
			} else if(strcmp(instruccion->op, DIFERENTE) == 0) {
				fprintf(codigo_intermedio,
								"%s = %s != %s\n",
								instruccion->res,
								instruccion->arg1,
								instruccion->arg2);
			} else if(strcmp(instruccion->op, ASIGNACION) == 0) {
				fprintf(codigo_intermedio,
								"%s = %s\n",
								instruccion->res,
								instruccion->arg1);
			} else if(strcmp(instruccion->op, DISYUNCION) == 0) { //OR
				fprintf(codigo_intermedio,
								"%s = %s || %s\n",
								instruccion->res,
								instruccion->arg1,
								instruccion->arg2);
			} else if(strcmp(instruccion->op, CONJUNCION) == 0) { //AND
				fprintf(codigo_intermedio,
								"%s = %s && %s\n",
								instruccion->res,
								instruccion->arg1,
								instruccion->arg2);
			} else if(strcmp(instruccion->op, PARAM) == 0) {
				fprintf(codigo_intermedio,
								"param %s\n",
								instruccion->arg1);
			} else if(strcmp(instruccion->op, CALL) == 0) {
				fprintf(codigo_intermedio,
								"%s = call %s\n",
								instruccion->res,
								instruccion->arg1);
			} else if(strcmp(instruccion->op, GOTO) == 0) {
				fprintf(codigo_intermedio,
								"goto %s\n",
								instruccion->arg1);
			} else if(strcmp(instruccion->op, IF_GOTO) == 0) {
				fprintf(codigo_intermedio,
								"if %s goto %s\n",
								instruccion->arg1,
								instruccion->arg2);
			} else if(strcmp(instruccion->op, RETURN) == 0) {
				fprintf(codigo_intermedio,
								"return %s\n",
								instruccion->arg1);
			} else {
				printf("Error: El operador no existe");
			}
			instruccion = instruccion->next;
		}
}



//PRUEBA

/*
int main(int argc, char const *argv[])
{
	printf("\t***CUADRUPLAS***\n");
	printf("OP\tARG1\tARG2\tRES\n");
	code* cod = crea_code();
	agregar_cuadrupla(cod, "=","a",NULL,"t0");
	agregar_cuadrupla(cod,"param","a",NULL,NULL);
	agregar_cuadrupla(cod,"+","a","b","res");
	//Instrucción mal formada
	//agregar_cuadrupla(cod,"+","a",NULL,NULL);
	agregar_cuadrupla(cod,"*","a","b","t1");
	agregar_cuadrupla(cod,"call","L3",NULL,"t2");
	agregar_cuadrupla(cod,"oo","a","b","t3");
	imprime(cod);
  	elimina_code(cod);
	return 0;
}
*/
