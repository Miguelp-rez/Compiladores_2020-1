/*
 * Compiladores Proyecto final
 * Programado por:
 * Lopez Martinez Andres
 * Morales Tellez Carlos Gamaliel
 * Perez Quiroz Miguel Angel
 * Sanchez Diaz Maria Beatriz
 * Fecha: 04/12/19
*/

#ifndef CUAD_H
#define CUAD_H
#include <string.h>

//Constantes para operadores aritméticos
#define ADICION 1000
#define	SUSTRACCION 1001
#define	MULTIPLICACION 1002
#define	DIVISION 1003
#define MODULO 1004

//Costantes para operadores relacionales
#define MENOR 2000
#define MAYOR 2001
#define MENOR_O_IGUAL 2002
#define IGUAL 2003
#define DIFERENTE 2004

//Constantes para operadores logicos
#define AND 3000
#define OR 3001
#define NOT 3002
#define XOR 3003

//Constantes para operadores de asignacion
#define ASIGNACION 4000

//Constante para los parámetros de una función
#define PARAM 5000

//Constantes para hacer saltos
#define GOTO 6000
#define IF_GOTO 6001

//Constante para llamar a una funcion
#define CALL 7000


//Estructura que almacenara las partes de la instruccion de tres direcciones
typedef struct _quad quad;
struct _quad {
  char *op;
  char *arg1;
  char *arg2;
  char *res;
  quad *next;
};

//Estructura que almacenara cada instruccion de codigo
typedef struct _code code ;
struct _code {
  quad *root;
  int num_instrucciones;
};

//retorna un apuntador a una instruccion de codigo de tres direcciones
quad* crea_quad(char *op, char *arg1, char *arg2, char *res);

//se eliminan todas las instrucciones
void elimina_quad(quad *q);

//retorna un apuntador a la estructura que almacenara todo el codigo
code* crea_code();

//elimina la estructura que contiene todas las instrucciones
void elimina_code(code *c);

//se agrega una cuadrupla a la estructura code
void agregar_cuadrupla(code *c, char *op, char *arg1, char *arg2, char *res);

//se imprime el codigo
void imprime(code *c);
#endif
