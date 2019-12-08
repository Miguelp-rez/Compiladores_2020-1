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
static const char ADICION[] = "+";
static const char SUSTRACCION[] = "-";
static const char MULTIPLICACION[] = "*";
static const char DIVISION[] = "/";
static const char MODULO[] = "%";

//Costantes para operadores relacionales
static const char MENOR_QUE[] = "<";
static const char MAYOR_QUE[] = ">";
static const char MENOR_O_IGUAL[] = "<=";
static const char MAYOR_O_IGUAL[] = ">=";
static const char IGUAL[] = "==";
static const char DIFERENTE[] ="!=";

//Constantes para operadores de asignacion
static const char ASIGNACION[] =  "=";

//Constantes para operadores lógicos
static const char DISYUNCION[] = "oo";
static const char CONJUNCION[] = "yy";

//Constante para los parámetros de una función
static const char PARAM[] = "param";

//Constante para la llamada a una funcion
static const char CALL[] = "call";

//Constantes para hacer saltos
static const char GOTO[] = "goto";
static const char IF_GOTO[] = "if";

//Constante de retorno
static const char RETURN[] = "return";

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
