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
  #include "cuad.h"
  #include "SymTabC.c"
  #include "TypeTabC.c"
  #include "SymTabStack.c"
  #include "TypeTabStack.c"
  #include "cuad.c"


  void yyerror(char* msg);
  void yyaccept();
  extern int yylex();
  extern int yylineno;

  int base_global; /*Variable global*/
  int tipo_b;
  int i_temp = 0;
  /*falta declarar todas las funciones*/
  int dir = 0;
  int max(int t1, int t2);
  void newTemp(char *dir);
  void amp(char *dir, int t1, int t2, char* res);
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
%type<num> tipo base tipo_arreglo variable

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
  //Se crea una nueva tabla de cadenas
  strtab* TC= crearStrTab();



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
    tipo_b=$1.tipo; 
    $$.tipo_=$2.tipo; //tipo.tipo=tipo_arreglo.tipo
  };

base:
  ENT {$$.tipo=0;}
| REAL {$$.tipo=1;}
| DREAL {$$.tipo=2;}
| CAR {$$.tipo=3;}
| SIN {$$.tipo=4;};

tipo_arreglo:
  RCOR NUM LCOR tipo_arreglo{
  if($2.tipo==0 && $2.valor.ival>0){ 
  $$.tipo=StackTT.getCima().addTipo(”array”,$2.valor.ival,$4.tipo)
  }else{
  yyerror(”El ındice tiene que ser entero y mayor que cero”)
  }
  }
| /*epsilon*/ {$$.tipo=tipo_b};

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
  expresion MAS expresion {
        $$.tipo = max($1.tipo, $3.tipo);        
        newTemp($$.dir);
        char dir1[20], dir2[20];   
        amp($1.dir, $1.tipo, $$.tipo, dir1);
        amp($3.dir, $3.tipo, $$.tipo, dir2);
        agregar_cuadrupla(code, ”+”,dir1,dir2, expresion.dir);
        //printf("E->E+E\n");
}
| expresion MENOS expresion {
        $$.tipo = max($1.tipo, $3.tipo);        
        newTemp($$.dir);
        char dir1[20], dir2[20];   
        amp($1.dir, $1.tipo, $$.tipo, dir1);
        amp($3.dir, $3.tipo, $$.tipo, dir2);
        agregar_cuadrupla(code, ”-”,dir1,dir2, expresion.dir);
        //printf("E->E-E\n");
}
| expresion MUL expresion {
        $$.tipo = max($1.tipo, $3.tipo);        
        newTemp($$.dir);
        char dir1[20], dir2[20];   
        amp($1.dir, $1.tipo, $$.tipo, dir1);
        amp($3.dir, $3.tipo, $$.tipo, dir2);
        agregar_cuadrupla(code, ”*”,dir1,dir2, expresion.dir);
        //printf("E->E*E\n");
}
| expresion DIV expresion {$$.tipo = max($1.tipo, $3.tipo);        
        newTemp($$.dir);
        char dir1[20], dir2[20];   
        amp($1.dir, $1.tipo, $$.tipo, dir1);
        amp($3.dir, $3.tipo, $$.tipo, dir2);
        agregar_cuadrupla(code, ”/”,dir1,dir2, expresion.dir);
        //printf("E->E/E\n");
}
| expresion MOD expresion {$$.tipo = max($1.tipo, $3.tipo);        
        newTemp($$.dir);
        char dir1[20], dir2[20];   
        amp($1.dir, $1.tipo, $$.tipo, dir1);
        amp($3.dir, $3.tipo, $$.tipo, dir2);
        agregar_cuadrupla(code, ”%”,dir1,dir2, expresion.dir);
        //printf("E->E%E\n");
}
| LPAR expresion RPAR {$$.dir = $2.dir;
$$.tipo=$2.tipo}
| variable {
  $$.dir=newTemp();
  $$.tipo=$1.tipo;
  //agregar_cuadrupla(code,"*",$1.base[$1.dir], "-", $$.dir);
}
| NUM {$$.tipo=$1.tipo;
  $$.dir=$1.valor;} 
| CADENA {$$.tipo=$1;
  $$.dir=insertarCadena(TC, $1);} 
| CARACTER {$$.tipo=$1;
  $$.dir=insertarCadena(TC, $1);} 
| ID LPAR parametros RPAR {};

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

void newTemp(char *dir){
    char temp[20];
    strcpy(temp , "t");
    char num[19];
    sprintf(num, "%d", i_temp); 
    i_temp++;
    strcat(temp,num);
    strcpy(dir, temp);
}

/*- int = 0
  - float= 1
  - double= 2
  - char= 3
*/
void *amp(char *dir, int t1, int t2, char* res){
    if(t1 == t2){
        strcpy(res, dir);
    }else if((t1==3 && t2==0) || (t1== 0 && t2 == 3)){
        char temp[20];
        newTemp(temp);
        fprintf(yyout, "%s = (int) %s\n", temp, dir);
        strcpy(res, temp);
    }else if((t1==0 && t2==1) || (t1== 1 && t2 == 0)){
        char temp[20];
        newTemp(temp);
        fprintf(yyout, "%s = (float) %s\n", temp, dir);
        strcpy(res, temp);
    }else if((t1==0 && t2==2) || (t1== 2 && t2 == 0)){
        char temp[20];
        newTemp(temp);
        fprintf(yyout, "%s = (double) %s\n", temp, dir);
        strcpy(res, temp);
    }else if((t1==1 && t2==2) || (t1== 2 && t2 == 1)){
        char temp[20];
        newTemp(temp);
        fprintf(yyout, "%s = (double) %s\n", temp, dir);
        strcpy(res, temp);
    }
    else{
        yyerror("Tipos incompatibles");
    }
}