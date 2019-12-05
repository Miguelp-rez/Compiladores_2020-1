/*
 * Compiladores Proyecto final
 * Programado por:
 * Lopez Martinez Andres
 * Morales Tellez Carlos Gamaliel
 * Perez Quiroz Miguel Angel
 * Sanchez Diaz Maria Beatriz
 * Fecha: 04/12/19
*/

%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <stdbool.h>
  #include "SymTab.h"
  #include "TypeTab.h"
  #include "SymTabC.c"
  #include "TypeTabC.c"
  #include "SymTabStack.c"
  #include "TypeTabStack.c"

  void yyerror(char* msg);
  void yyaccept();
  extern int yylex();
  extern int yylineno;

  /*falta declarar todas las funciones*/
  int dir = 0;
  /*Falta crear pila de direcciones*/
%}

%union{  /*yylval*/
  struct{
    int tipo;
    union{
      int ival;
      float fval;
      double dval;
      char *sval;
    }valor;
  }terminal;
}

%token<terminal> TERMINAL
%token SL
%token ID
%token PC PUNTO COMA
%token ENT REAL DREAL CAR SIN
%token FUNC
%token SI
%token ENTONCES
%token SINO
%token MIENTRAS
%token HACER
%token MIENTRASQ
%token ESCRIBIR
%token LEER
%token DEVOLVER
%token VERDADERO
%token FALSO


/*precedencia de operadores*/
%left ASIGN
%left OO
%left YY
%left MAS MENOS
%left M MA MEQ MAEQ EQEQ MMA  /*operadores relacionales < > < >= == <> */
%left MUL DIV MOD
%left NO
%nonassoc LPAR RPAR LCOR RCOR  INICIO FIN TERMINAR


%start programa
%%


/*Estructura de la gramatica, falta agregar todas las reglas semanticas*/
programa: declaraciones SL funciones {
  dir = 0;
  //Se crea una nueva pila de tablas de tipos
  typestack *StackTT = crearTypeStack();
  //Se crea una nueva pila de tablas de símbolos
  symstack *StackTS = crearSymStack();
  //Se crea una nueva tabla de símbolos
  symtab *ts = crearSymTab();
  //Se crea una nueva tabla de tipos
  typetab *tt = crearTypeTab();
  //Acción semántica: StackTT.push(tt)
  insertarTypeTab(StackTT, tt);
  //Acción semántica: StackTS.push(ts)
  insertarSymTab(StackTS,ts);
  //¿Cuál es la tabla de cadenas?...


};

declaraciones:
  tipo lista_var SL declaraciones {}
| tipo_registro lista_var SL declaraciones {}
| /*epsilon*/ {};

tipo_registro:
  registro SL inicio declaraciones SL fin {
    //Se crea una nueva tabla de símbolos
    symtab *ts = crearSymTab();
    //Se crea una nueva tabla de tipos
    typetab *tt = crearTypeTab();
    //StackDir.push(dir) //FALTA PILA DE DIRECCIONES
    dir = 0;
    //insertarTypeTab(StackTT,tt); //No se ha declarado el stack ¿Qué debería ir aquí?
    //insertarSymTab(StackTS,ts);
    //dir = StackDir.pop() //FALTA PILA DE DIRECCIONES
    //tt1 = StackTT.pop() //
    //StackTS.getCima().setTT(tt1)
    //ts1 = StackTS.pop()
    //dir = StackDir.pop()
    //type = StackTT.getCima().addTipo(”registro”,0, ts1)
  }

tipo:
  base tipo_arreglo {}
base:
  ENT {}
| REAL {}
| DREAL {}
| CAR {}
| SIN {};

tipo_arreglo:
  RCOR NUM LCOR tipo_arreglo{}
| /*epsilon*/ {}
lista_var:
  lista_var COMA ID {}
| ID {};

funciones:
  FUNC tipo ID RPAR argumentos LPAR INICIO SL declaraciones sentencias SL FIN SL funciones {}
| /*epsilon*/ {};

argumentos:
  lista_arg {}
| SIN {};

lista_arg:
  lista_arg arg {}
| arg {};

arg:
  tipo_arg ID;

tipo_arg:
  base param_arr {};

param_arr:
  LCOR RCOR param_arr {}
| /*epsilon*/ {};

sentencias:
  sentencias SL sentencia {}
| sentencia  {};

sentencia:
  SI expresion_booleana ENTONCES SL sentencias SL FIN {}
| SI expresion_booleada SL sentencias SL SINO SL sentencias SL FIN {}
| MIENTRAS SL expresion_booleana HACER SL sentencias SL FIN {}
| HACER SL sentencia SL MIENTRASQ expresion_booleana {}
| ID ASIGN expresion {}
| ESCRIBIR expresion {}
| LEER variable {}
| DEVOLVER {}
| DEVOLVER expresion {}
| TERMINAR {};

expresion_booleana:
  expresion_booleana OO expresion_booleana {}
| expresion_booleana YY expresion_booleana {}
| NO expresion_booleana {}
| relacional {}
| VERDADERO {}
| FALSE {};

relacional:
  relacional M relacional {}
| relacional MA relacional {}
| relacional MEQ relacional {}
| relacional MAEQ relacional {}
| relacional EQEQ relacional {}
| relacional MMA relacional {}
| expresion {};

expresion:
  expresion MAS expresion {if($1.tipo == $3.tipo){
                                        $$.tipo = $1.tipo;
                                        if($1.tipo = 0){
                                            $$.valor.ival = $1.valor.ival + $3.valor.ival;
                                            printf("%d = %d + %d\n", $$.valor.ival, $1.valor.ival, $3.valor.ival);
                                        }else{
                                            $$.valor.fval = $1.valor.fval + $3.valor.fval;
                                        }
                                     }
                                     //printf("E-> E+E\n");
}
| expresion MENOR expresion {if($1.tipo == $3.tipo){
                                            $$.tipo = $1.tipo;
                                            if($1.tipo = 0){
                                                $$.valor.ival = $1.valor.ival - $3.valor.ival;
                                            }else{
                                                $$.valor.fval = $1.valor.fval - $3.valor.fval;
                                            }
                                        }
                                        //printf("E-> E-E\n");
}
| expresion MUL expresion {if($1.tipo == $3.tipo){
                                        $$.tipo = $1.tipo;
                                        if($1.tipo = 0){
                                            $$.valor.ival = $1.valor.ival * $3.valor.ival;
                                        }else{
                                            $$.valor.fval = $1.valor.fval * $3.valor.fval;
                                        }
                                     }
                                     //printf("E-> E*E\n");
}
| expresion DIV expresion {if($1.tipo == $3.tipo){
                                        $$.tipo = $1.tipo;
                                        if($1.tipo = 0){
                                            if($3.valor.ival != 0)
                                                $$.valor.ival = $1.valor.ival / $3.valor.ival;
                                            else
                                                yyerror("No se puede hacer la división entre cero");
                                        }else{
                                            if($3.valor.fval != 0)
                                                $$.valor.fval = $1.valor.fval / $3.valor.fval;
                                            else
                                                yyerror("No se puede hacer la división entre cero");

                                        }
                                     }
                                     //printf("E-> E/E\n");
}
| expresion MOD expresion {if($1.tipo == $3.tipo){
                                        $$.tipo = $1.tipo;
                                        if($1.tipo = 0){
                                            $$.valor.ival = $1.valor.ival % $3.valor.ival;
                                        }else{
                                            $$.valor.fval = $1.valor.fval % $3.valor.fval;
                                        }
                                     }
                                     //printf("E-> E%E\n");
}
| LPAR expresion RPAR {$$ = $2;
                                //printf("E-> (E)\n");
}
| variable {}| NUM {} | CADENA {} | CARACTER {} | ID LPAR parametros RPAR {};

variable:
  ID arreglo {}
| ID PUNTO ID {};

arreglo:
  ID LCOR expresion RCOR arreglo {}
| /*epsilon*/ {};

parametros:
  lista_param {}
| /*epsilon*/ {};

lista_param:
  lista_param COMA expresion {}
| expresion {};

%%
void yyerror(char *msg){
  printf("%s en la linea %d\n", msg, yylineno);
}

void yyaccept(){
  printf("ACEPTA");
}
