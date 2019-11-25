/*
 * Compiladores Practica 6
 * Programado por:
 * Lopez Martinez Andres
 * Morales Tellez Carlos Gamaliel
 * Perez Quiroz Miguel Angel
 * Sanchez Diaz Maria Beatriz
 * Fecha: 24/11/19
*/

#ifndef CUAD_H
#define CUAD_H
#include <string.h>

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
<<<<<<< HEAD

//se imprime el codigo
void imprime(code *c);
#endif
