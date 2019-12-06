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

  int base_global; /*Variable global*/

  /*falta declarar todas las funciones*/
  int dir = 0;
  int max(int t1, int t2);
  /*Falta crear pila de direcciones*/
%}

/*
  Tipos:
  - Numero entero      = 0
  - Numero real        = 1
  - Numero real doble  = 2
  - Caracter           = 3
  - Cadena             = 4
  - Identificador      = 5
*/

%union{  /*yylval*/
  struct{ /*Numero enteros, reales y reales dobles*/
    int tipo;
    union{
      int ival;
      float fval;
      double dval;
    }valor;
  }num;

  struct{ /*Caracteres*/
    char cval;
  }caracter;

  struct{ /*Cadenas*/
    char *sval;
  }cadena;

  struct{ /*Identificadores*/
    char id[32];
  }id;

  struct{ /*Expresiones*/
    int tipo;
    int dir;
    union{
      int ival;
      float fval;
      double dval;
      char *sval;
    }valor;
  }expresion;
}

%token<num> NUM
%token<caracter> CARACTER
%token<cadena> CADENA
%token<id> ID
%token SL /*Salto de linea*/
%token REGISTRO
%token INICIO FIN
%token ENT REAL DREAL CAR SIN
%token PC PUNTO COMA
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
%token TERMINAR
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
%nonassoc LPAR RPAR LCOR RCOR

%type<expresion> expresion

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
  REGISTRO SL INICIO declaraciones SL FIN {
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
  base tipo_arreglo {
    base_global=base.tipo;  //base=base.tipo
    tipo.tipo=tipo_arreglo.tipo; //tipo.tipo=tipo_arreglo.tipo
  };

base:
  ENT {base.tipo=0;}
| REAL {base.tipo=1;}
| DREAL {base.tipo=2;}
| CAR {base.tipo=3;}
| SIN {base.tipo=4;};

tipo_arreglo:
  RCOR NUM LCOR tipo_arreglo{
  //if($2.tipo==0 && $2.valor.ival>0){ 
  //$$.tipo=StackTT.getCima().addTipo(”array”,$2.valor.ival,$4.tipo)
  //}else{
  //yyerror(”El ındice tiene que ser entero y mayor que cero”)
  //}
  }
| /*epsilon*/ {tipo_arreglo.tipo=base_global};

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
| SI expresion_booleana SL sentencias SL SINO SL sentencias SL FIN {}
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
| FALSO {};

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
| expresion MENOS expresion {if($1.tipo == $3.tipo){
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
                                        }/*else{
                                            $$.valor.fval = $1.valor.fval % $3.valor.fval;
                                        }*/
                                     }
                                     //printf("E-> E%E\n");
}
| LPAR expresion RPAR {$$ = $2;}
| variable {}
| NUM {$$.tipo=$1.tipo;
      $$.dir=$1.valor;} 
| CADENA {} | CARACTER {} | ID LPAR parametros RPAR {};

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

//DEFINIENDO FUNCIONES NECESARIAS max, amp, backpatch, newLabel, newTemp

/*- int = 0
  - float= 1
  - double= 2
  - char= 3
*/
int  max(int t1, int t2){
    if(t1 == t2)
        return t1;
    else if(t1==3 && t2 == 0){    //float   int
        return t2;
    }else if( t1 == 0 && t2==3){  //int char
        return t1;
    }else if(t1==0 && t2 == 1){   //int  float
        return t2;
    }else if( t1 == 1 && t2==0){  //float int
        return t1;
    }else if(t1==0 && t2 == 2){   //int  double
        return t2;
    }else if(t1 == 2 && t2==0){  //double int
        return t1;
    }
    else if(t1==1 && t2 == 2){  //float double
        return t2;
    }else if(t1 == 2 && t2==1){ //double float
        return t1;
    }
    else{
        yyerror("Error");
        return -1;
    }
}
