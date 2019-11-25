#ifndef CUAD_H
#define CUAD_H

#include <string.h>

typedef struct _quad quad;

struct _quad {
  char *op;
  char *arg1;
  char *arg2;
  char *res;
  quad *next;
};

typedef struct _code code ;
struct _code {
  quad *root;
  int num_instrucciones;
};


quad* crea_quad(char *op, char *arg1, char *arg2, char *res);
void elimina_quad(quad *q);
code* crea_code();
void elimina_code(code *c);
void agregar_cuadrupla(code *c, char *op, char *arg1, char *arg2, char *res);
//code* imprime(code *c);
void imprime(code *c);
#endif
