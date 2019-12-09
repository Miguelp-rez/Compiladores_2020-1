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
  #include "cuad.h"
  #include "cuad.c"
  #include "SymTab.h"
  #include "TypeTab.h"
  #include "SymTabC.c"
  #include "TypeTabC.c"
  #include "SymTabStack.c"
  #include "TypeTabStack.c"
  #include "backpatch_merge.c"
  #include "DirStack.c"
  #include "StrTab.c"

  int max(int t1, int t2);
  void newTemp(char *dir);
  void amp(char *dir, int t1, int t2, char* res);
  char *reducir(char *dir, int tipo_exp, int tipo_id);
  char* newLabel();
  void yyerror(char* msg);
  void yyaccept();
  extern int yylex();
  extern int yylineno;

  int base_global; /*Variable global*/
  int type_global;
  int tipo_b;
  int t;
  char nombre[10];
  int i_temp = 0;
	//Contador de etiquetas
	int labelCounter = 0;
  int dir = 0;
  int FuncType;
  int FuncReturn;

  char *label;
  char *reduccion;
  char aux[100] = "";
  etiqueta *nueva_etiqueta;

  //TIPOS
  typestack *StackTT;
  typetab *tt;
  typetab *tt1;
  base *base_type;
  type *nuevo_tipo;
  
  //SIMBOLOS
  symstack *StackTS;
  symtab *ts;
  symtab *ts1;
  symbol *nuevo_simbolo;
  param *nuevo_param;
  listParam *nueva_LP;

  //OTROS
  strtab* TC;
  dirstack* StackDir;
  code* cod;
%}

/*
  Tipos:
  - Numero entero      = 0
  - Numero real        = 1
  - Numero real doble  = 2
  - Caracter           = 3
  - Cadena             = 4
  - Identificador      = 5
  - Sin                = 6
*/

/* Para tipoVar:
  - var     = 0
  - funcion = 1
  - param   = 2
*/

%union{  /*yylval*/
  struct{ /*Numero enteros, reales y reales dobles*/
    int tipo;
    char sval[20];
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

  /*PARA ATRIBUTOS EN REGLAS SEMANTICAS*/

  struct{ /*Tipo*/
    int tipo;
  }tipo;

  struct{ /*Tipo registro*/
    int tipo;
  }tipo_registro;

  struct{ /*Base*/
    int tipo;
  }base;

  struct{ /*Tipo arreglo*/
    int tipo;
  }tipo_arreglo;

  struct{ /*Expresiones*/
    int tipo;
    char dir[20];
    union{
      int ival;
      float fval;
      double dval;
      char *sval;
    }valor;
  }expresion;

  struct{ /*Variable*/
    int tipo;
    int base;
    char dir[20];
  }variable;

  struct{ /*Sentencias*/
    l_etiquetas *listnext;
  }sentencias;

  struct{ /*Sentencia*/
    l_etiquetas *listnext;
  }sentencia;

  struct{ /*Argumentos*/
    listParam *lista;
  }argumentos;

  struct{ /*Lista de argumentos*/
    listParam *lista;
  }lista_arg;

  struct{ /*Arg*/
    int tipo;
  }arg;

  struct{ /*Tipo arg*/
    int tipo;
  }tipo_arg;

  struct{ /*Param arr*/
    int tipo;
  }param_arr;

  struct{ /*Expresiones booleanas*/
    l_etiquetas *listtrue;
    l_etiquetas *listfalse;
  }expresion_booleana;

  struct{ /*Relacional*/
    l_etiquetas *listtrue;
    l_etiquetas *listfalse;
  }relacional;

  struct{ /*Parametros*/
    listParam *lista;
  }parametros;
  
  struct{ /*Lista de parametros*/
    listParam *lista;
  }lista_param;
  
  struct{ /*Arreglo*/
      int base;
      int tipo;
      int tam;
      char dir[20];
  }arreglo;

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
%type<tipo> tipo
%type<tipo_registro> tipo_registro
%type<base> base
%type<tipo_arreglo> tipo_arreglo
%type<variable> variable
%type<sentencias> sentencias
%type<sentencia> sentencia
%type<argumentos> argumentos
%type<lista_arg> lista_arg
%type<arg> arg
%type<tipo_arg> tipo_arg
%type<param_arr> param_arr
%type<expresion_booleana> expresion_booleana
%type<relacional> relacional
%type<parametros> parametros
%type<lista_param> lista_param
%type<arreglo> arreglo

%start programa
%%

/*Estructura de la gramatica, falta agregar todas las reglas semanticas*/
programa: declaraciones SL funciones {
  dir = 0;
  //Se crea una nueva pila de tablas de tipos
  StackTT = crearTypeStack();
  //Se crea una nueva pila de tablas de símbolos
  StackTS = crearSymStack();
  //Se crea una nueva tabla de símbolos
  ts = crearSymTab();
  //Se crea una nueva tabla de tipos
  tt = crearTypeTab();
  //Acción semántica: StackTT.push(tt)
  insertarTypeTab(StackTT, tt);
  //Acción semántica: StackTS.push(ts)
  insertarSymTab(StackTS,ts);
  //Se crea una nueva tabla de cadenas
  TC = crearStrTab();
  //Se crea una nueva pila de direcciones
  StackDir = crearDirStack();
};

declaraciones:
  tipo lista_var SL declaraciones {type_global = $1.tipo;}
| tipo_registro lista_var SL declaraciones {type_global = $1.tipo;}
| /*epsilon*/ {};

tipo_registro:
  REGISTRO SL INICIO declaraciones {
    //Se crea una nueva tabla de símbolos
    ts = crearSymTab();
    //Se crea una nueva tabla de tipos
    tt = crearTypeTab();
    //Se guarda la direccion en la Pila
    insertarDireccion(StackDir,dir);
    //Se reinicia la direccion
    dir = 0;
    //Se guarda la nueva tabla de tipos en la pila
    insertarTypeTab(StackTT, tt);
    //Se guarda la nueva tabla de simbolos en la pila
    insertarSymTab(StackTS, ts);
    }
    SL FIN {
    //Se recupera la direccion de la pila
    dir = sacarDireccion(StackDir);
    //Se recupera
    tt1 = sacarTypeTab(StackTT);
    setTT(getCimaSym(StackTS), tt1);
    ts1 = sacarSymTab(StackTS);
    //Se recupera la direccion de la pila
    dir = sacarDireccion(StackDir);
    //Todo lo de abajo es: type = StackTT.getCima().addTipo(”registro”,0, ts1)
    base_type->tabla = ts1;
    nuevo_tipo = crearType("struct", base_type, -1);
    type_global = insertarTipo(getCimaType(StackTT), nuevo_tipo) - 1;
    }
tipo:
base tipo_arreglo {
    tipo_b=$1.tipo;
    $$.tipo=$2.tipo; //tipo.tipo=tipo_arreglo.tipo
  };

base:
  ENT {$$.tipo=0;}
| REAL {$$.tipo=1;}
| DREAL {$$.tipo=2;}
| CAR {$$.tipo=3;}
| SIN {$$.tipo=6;};

tipo_arreglo:
  RCOR NUM LCOR tipo_arreglo {
    if($2.tipo==0 && $2.valor.ival>0){
    //$$.tipo=StackTT.getCima().addTipo(”array”,$2.valor.ival,$4.tipo)
      base_type->simple = $4.tipo;
      nuevo_tipo = crearType("array", base_type, $2.valor.ival);
      $$.tipo = insertarTipo(getCimaType(StackTT), nuevo_tipo) - 1;      
    }else{
      yyerror("El indice tiene que ser entero y mayor que cero");
    }
  }
| /*epsilon*/ {$$.tipo=tipo_b;};

lista_var:
  lista_var COMA ID {
    if(buscar(getCimaSym(StackTS), $3.id) != -1){
      nuevo_simbolo = crearSymbol($3.id, base_global, dir, 0);
      insertar(getCimaSym(StackTS), nuevo_simbolo);
      dir = dir + getTam(getCimaType(StackTT), base_global);
    }else{
      yyerror("El identificador ya fue declarado");
    }
  }
| ID {
    if(buscar(getCimaSym(StackTS), $1.id) != -1){
      nuevo_simbolo = crearSymbol($1.id, base_global, dir, 0);
      insertar(getCimaSym(StackTS), nuevo_simbolo);
      dir = dir + getTam(getCimaType(StackTT), base_global);
    }else{
      yyerror("El identificador ya fue declarado");
    }
};

funciones:
  FUNC tipo ID RPAR argumentos LPAR INICIO SL declaraciones sentencias SL FIN SL funciones {
    if(buscar(StackTS->root, $3.id) != -1){
      nuevo_simbolo = crearSymbol($3.id, base_global, -1, 1);
      insertar(StackTS->root, nuevo_simbolo);
      insertarDireccion(StackDir,dir);
      FuncType = $2.tipo;
      FuncReturn = 0;
      dir = 0;
      insertarTypeTab(StackTT, tt);
      insertarSymTab(StackTS, ts);
      dir = sacarDireccion(StackDir);
      agregar_cuadrupla(cod, "label", "", "", $3.id);
      label = newLabel();
      nueva_etiqueta = crear_etiqueta(label); 
      backpatch(cod, $10.listnext, nueva_etiqueta);
      agregar_cuadrupla(cod, "label", "", "", label);
      sacarTypeTab(StackTT);
      sacarSymTab(StackTS);
      dir = sacarDireccion(StackDir);
      asociarLP(getListParam(getCimaSym(StackTS), $3.id), $5.lista);
      if($2.tipo != 6 && FuncReturn == 0){
        yyerror("La funcion no tiene valor de retorno");
      }
    }else{
      yyerror("El identificador ya fue declarado");
    }
  }
| /*epsilon*/ {};

argumentos:
  lista_arg {$$.lista = $1.lista;}
| SIN {$$.lista = NULL;};

lista_arg:
  lista_arg arg {
    $$.lista = $1.lista;
    add($$.lista, $2.tipo);
  }
| arg {
    $$.lista = crearLP();
    add($$.lista, $1.tipo);
};

arg:
  tipo_arg ID {
    if(buscar(getCimaSym(StackTS), $2.id) != -1){
      nuevo_simbolo = crearSymbol($2.id, base_global, dir, 0);
      insertar(getCimaSym(StackTS), nuevo_simbolo);
      dir = dir + getTam(getCimaType(StackTT), base_global);
    }else{
      yyerror("El identificador ya fue declarado");
    }
    $$.tipo = $1.tipo;
};

tipo_arg:
  base param_arr {
    base_global = $1.tipo;
    $$.tipo = $2.tipo;
  };

param_arr:
  LCOR RCOR param_arr {
    base_type->simple = $3.tipo;
    nuevo_tipo = crearType("array", base_type, 0);
    $$.tipo = insertarTipo(getCimaType(StackTT), nuevo_tipo) - 1;  
  }
| /*epsilon*/ {$$.tipo = base_global;};

sentencias:
  sentencias SL sentencia {
    label = newLabel();
    nueva_etiqueta = crear_etiqueta(label);
    backpatch(cod, $1.listnext, nueva_etiqueta);
    $$.listnext = $3.listnext;
  }
| sentencia  {$$.listnext = $1.listnext;};

sentencia:
  SI expresion_booleana ENTONCES SL sentencias SL FIN {
    label = newLabel();
    nueva_etiqueta = crear_etiqueta(label);
    backpatch(cod, $2.listtrue, nueva_etiqueta);
    $$.listnext = merge($2.listfalse, $5.listnext);
  }
| SI expresion_booleana SL sentencias SL SINO SL sentencias SL FIN {
    label = newLabel();
    nueva_etiqueta = crear_etiqueta(label);
    backpatch(cod, $2.listtrue, nueva_etiqueta);
    label = newLabel();
    nueva_etiqueta = crear_etiqueta(label);
    backpatch(cod, $2.listfalse, nueva_etiqueta);
    $$.listnext = merge($4.listnext, $8.listnext);
}
| MIENTRAS SL expresion_booleana HACER SL sentencias SL FIN {
    label = newLabel();
    nueva_etiqueta = crear_etiqueta(label);
    backpatch(cod, $6.listnext, nueva_etiqueta);
    agregar_cuadrupla(cod, "goto", "", "", label);
    label = newLabel();
    nueva_etiqueta = crear_etiqueta(label);
    backpatch(cod, $3.listtrue, nueva_etiqueta);
    $$.listnext = $3.listfalse;
    //la cuadrupla se agrega antes de este punto
}
| HACER SL sentencia SL MIENTRASQ expresion_booleana {
    label = newLabel();
    nueva_etiqueta = crear_etiqueta(label);
    backpatch(cod, $6.listtrue, nueva_etiqueta);
    agregar_cuadrupla(cod, "label", "", "", label);
    label = newLabel();
    nueva_etiqueta = crear_etiqueta(label);
    backpatch(cod, $3.listnext, nueva_etiqueta);
    $$.listnext = $6.listfalse;
}
| ID ASIGN expresion {
    if(buscar(getCimaSym(StackTS), $1.id) != -1){
      sprintf(aux, "Id %d", getDir(getCimaSym(StackTS), $1.id));
      reduccion = reducir($3.dir, $3.tipo, getTipo(getCimaSym(StackTS), $1.id));
      agregar_cuadrupla(cod, "=", reduccion, "", aux);
      insertar(getCimaSym(StackTS), nuevo_simbolo);
      dir = dir + getTam(getCimaType(StackTT), base_global);
    }else{
      yyerror("El identificador ya fue declarado");
    }
    $$.listnext = NULL;
}
| ESCRIBIR expresion {
    agregar_cuadrupla(cod, "print", $2.dir, "", "");
    $$.listnext = NULL;
}
| LEER variable {
    agregar_cuadrupla(cod, "scan", $2.dir, "", $2.dir);
    $$.listnext = NULL;
}
| DEVOLVER {
    if(FuncType == 6){
      agregar_cuadrupla(cod, "return", "", "", "");
    }
    else{
      yyerror("La funcion debe retornar algun valor de tipo");
    }
    $$.listnext = NULL;
}
| DEVOLVER expresion {
    if(FuncType == 6){
      reduccion = reducir($2.dir, $2.tipo, FuncType);
      agregar_cuadrupla(cod, "return", reduccion, "", "");
      FuncReturn = 1;
    }
    else{
      yyerror("La funcion debe retornar algun valor de tipo");
    }
    $$.listnext = NULL;
}
| TERMINAR {
    //I = newIndex();
    //agregar_cuadrupla(cod, "goto", "", "", I);
    //$$.listnext = newList();
    //add($$.listnext, I);
};

expresion_booleana:
  expresion_booleana OO expresion_booleana {
    label = newLabel();
    nueva_etiqueta = crear_etiqueta(label);
    backpatch(cod, $1.listfalse, nueva_etiqueta);
    $$.listtrue = merge($1.listtrue,$3.listtrue);
    $$.listfalse = $3.listfalse;
    agregar_cuadrupla(cod, "label", "", "", label);
  }
| expresion_booleana YY expresion_booleana {
    label = newLabel();
    nueva_etiqueta = crear_etiqueta(label);
    backpatch(cod, $3.listtrue, nueva_etiqueta);
    $$.listtrue = $3.listtrue;
    $$.listfalse = merge($1.listfalse,$3.listfalse);
    agregar_cuadrupla(cod, "label", "", "", label);
}
| NO expresion_booleana {
    $$.listtrue = $2.listfalse;
    $$.listfalse = $2.listtrue;
}
| relacional {
    $$.listtrue = $1.listtrue;
    $$.listfalse = $1.listfalse;
}
| VERDADERO {
    //I = newIndex();
    //$$.listtrue = newList();
    //$$.listtrue.add(I)
    //add quad(code, ”goto”, -, -, I)
    //expresion booleana.listfalse = nulo
}
| FALSO {
    //I = newIndex()
    //expresion booleana.listtrue = nulo
    //expresion booleana.listfalse = newList()
    //expresion booleana.listfalse.add(I)
    //add quad(code, ”goto”, -, -, I)
};

relacional:
  relacional M relacional {
    //relacional.listtrue = newList()
    //relacional.listfalse = newList()
    //I= newIndex(), I1 = newIndex()
    //relacional.listtrue.add(I)
    //relacional.listfalse.add(I1)
    //relacional.tipo = max(relacional1.tipo, relacional2.tipo)
    //α1 = ampliar(relacional1.dir, relacional1.tipo, relacional.tipo)
    //α2 = ampliar(relacional2.dir, relacional2.tipo, relacional.tipo)
    //add quad(code, ”<”,α1 ,α2, I)
    //add quad(code, ”goto”, -, -, I1)  
  }
| relacional MA relacional {
    //relacional.listtrue = newList()
    //relacional.listfalse = newList()
    //I= newIndex(), I1 = newIndex()
    //relacional.listtrue.add(I)
    //relacional.listfalse.add(I1)
    //relacional.tipo = max(relacional1.tipo, relacional2.tipo)
    //α1 = ampliar(relacional1.dir, relacional1.tipo, relacional.tipo)
    //α2 = ampliar(relacional2.dir, relacional2.tipo, relacional.tipo)
    //add quad(code, ”>”,α1 ,α2, I)
    //add quad(code, ”goto”, -, -, I1)
}
| relacional MEQ relacional {
    //relacional.listtrue = newList()
    //relacional.listfalse = newList()
    //I= newIndex(), I1 = newIndex()
    //relacional.listtrue.add(I)
    //relacional.listfalse.add(I1)
    //relacional.tipo = max(relacional1.tipo, relacional2.tipo)
    //α1 = ampliar(relacional1.dir, relacional1.tipo, relacional.tipo)
    //α2 = ampliar(relacional2.dir, relacional2.tipo, relacional.tipo)
    //add quad(code, ”<=”,α1 ,α2, I)
    //add quad(code, ”goto”, -, -, I1)
}
| relacional MAEQ relacional {
    //relacional.listtrue = newList()
    //relacional.listfalse = newList()
    //I= newIndex(), I1 = newIndex()
    //relacional.listtrue.add(I)
    //relacional.listfalse.add(I1)
    //relacional.tipo = max(relacional1.tipo, relacional2.tipo)
    //α1 = ampliar(relacional1.dir, relacional1.tipo, relacional.tipo)
    //α2 = ampliar(relacional2.dir, relacional2.tipo, relacional.tipo)
    //add quad(code, ”>=”,α1 ,α2, I)
    //add quad(code, ”goto”, -, -, I1)
}
| relacional EQEQ relacional {
    //relacional.listtrue = newList()
    //relacional.listfalse = newList()
    //I= newIndex(), I1 = newIndex()
    //relacional.listtrue.add(I)
    //relacional.listfalse.add(I1)
    //relacional.tipo = max(relacional1.tipo, relacional2.tipo)
    //α1 = ampliar(relacional1.dir, relacional1.tipo, relacional.tipo)
    //α2 = ampliar(relacional2.dir, relacional2.tipo, relacional.tipo)
    //add quad(code, ”==”,α1 ,α2, I)
    //add quad(code, ”goto”, -, -, I1)
}
| relacional MMA relacional {
    //relacional.listtrue = newList()
    //relacional.listfalse = newList()
    //I= newIndex(), I1 = newIndex()
    //relacional.listtrue.add(I)
    //relacional.listfalse.add(I1)
    //relacional.tipo = max(relacional1.tipo, relacional2.tipo)
    //α1 = ampliar(relacional1.dir, relacional1.tipo, relacional.tipo)
    //α2 = ampliar(relacional2.dir, relacional2.tipo, relacional.tipo)
    //add quad(code, ”<>”,α1 ,α2, I)
    //add quad(code, ”goto”, -, -, I1)
}
| expresion {
    //relacional.tipo = expresion.tipo
    //relacional.dir = expresion.dir
};

expresion:
  expresion MAS expresion {
        $$.tipo = max($1.tipo, $3.tipo);
        newTemp($$.dir);
        char dir1[20], dir2[20];
        amp($1.dir, $1.tipo, $$.tipo, dir1);
        amp($3.dir, $3.tipo, $$.tipo, dir2);
        agregar_cuadrupla(cod,"+",dir1,dir2,$$.dir);
        //printf("E->E+E\n");
}
| expresion MENOS expresion {
        $$.tipo = max($1.tipo, $3.tipo);
        newTemp($$.dir);
        char dir1[20], dir2[20];
        amp($1.dir, $1.tipo, $$.tipo, dir1);
        amp($3.dir, $3.tipo, $$.tipo, dir2);
        agregar_cuadrupla(cod,"-",dir1,dir2,$$.dir);
        //printf("E->E-E\n");
}
| expresion MUL expresion {
        $$.tipo = max($1.tipo, $3.tipo);
        newTemp($$.dir);
        char dir1[20], dir2[20];
        amp($1.dir, $1.tipo, $$.tipo, dir1);
        amp($3.dir, $3.tipo, $$.tipo, dir2);
        agregar_cuadrupla(cod,"*",dir1,dir2,$$.dir);
        //printf("E->E*E\n");
}
| expresion DIV expresion {$$.tipo = max($1.tipo, $3.tipo);
        newTemp($$.dir);
        char dir1[20], dir2[20];
        amp($1.dir, $1.tipo, $$.tipo, dir1);
        amp($3.dir, $3.tipo, $$.tipo, dir2);
        agregar_cuadrupla(cod,"/",dir1,dir2,$$.dir);
        //printf("E->E/E\n");
}
| expresion MOD expresion {$$.tipo = max($1.tipo, $3.tipo);
        newTemp($$.dir);
        char dir1[20], dir2[20];
        amp($1.dir, $1.tipo, $$.tipo, dir1);
        amp($3.dir, $3.tipo, $$.tipo, dir2);
        agregar_cuadrupla(cod,"%",dir1,dir2,$$.dir);
        //printf("E->E%E\n");
}
| LPAR expresion RPAR {
    strcpy($$.dir, $2.dir);
    $$.tipo = $2.tipo;
  }
| variable {
    newTemp($$.dir);
    $$.tipo = $1.tipo;
    //agregar_cuadrupla(cod,"*", $1.base[$1.dir], "", $$.dir);
}
| NUM {
  $$.tipo=$1.tipo;
  strcpy($$.dir, $1.sval);
}
| CADENA {$$.tipo = 4;
  insertarCadena(TC, $1.sval);
}
| CARACTER {
    char auxiliar [2] = "\0";
    auxiliar[0] = $1.cval;
    $$.tipo = 3;
    insertarCadena(TC, auxiliar);
}
| ID LPAR parametros RPAR {};

variable:
  ID arreglo {
    strcpy($$.dir, $2.dir);
    $$.base = $2.base;
    $$.tipo = $2.tipo;
  }
| ID PUNTO ID {
  /*if( buscar(StackTS->root, $1.id) != -1 ){
      t = getTipo(getCimaSym(StackTS), $1.id);
      nombre = getNombre(buscar(StackTS->root), t);
      if(strcmp(nombre, "registro")){
        base_type = getTipoBase(StackTT->root, t);
        if( buscar(base_type.tabla, $3.id) != -1 ){
          $$.tipo = getTipo(base_type.tabla, $3.id);
          $$.dir = $3;
          $$.base = $1;
        }else{
          yyerror("El id no existe en la estructura");
        }
      }else{
        yyerror("El id no es una estructura");
      }
    }else
    yyerror("El identifador no ha sido declarado");*/
};

arreglo:
  ID LCOR expresion RCOR {/*
    if( buscar(StackTS->root, $3.id) != -1 ){
      t = getTipo(getCimaSym(StackTS), id.id);
      nombre = getNombre(buscar(StackTS->root), t);
      if(strcmp(nombre, "array")){
        if( $3.tipo == 0 ){
          $$.base = $1.id;
          $$.tipo = getTipoBase(getCimaTT(StackTT), t);
          $$.tam = getTam(getCimaTT(StackTT), $$.tipo);
          $$.dir = newTemp();
          add(cod, "*", $3.dir, $$.tam, $$.dir);
        }else{
          yyerror("La expresion para un indice debe de ser de tipo entero");
        }
      }else{
        yyerror("El identificador no es un arreglo");
      }
    }else
    yyerror("El identifador no ha sido declarado");*/
  }
| arreglo LCOR expresion RCOR {/*
  if(getNombre(getCima(StackTT),$1.tipo)){
    if($3.tipo = 0){
      $$.base = $1.base;
      $$.tipo = getTipoBase(getCimaTT(StackTT), $1.tipo);
      $$.tam = getTam(getCimaTT(StackTT), $$.tipo);
      temp = newTemp();
      $$.dir = newTemp();
      add(cod, "*", $3.dir, $$.tam, temp);
      add(cod, "+", $1.dir, temp, $$.dir);
    }else{
      yyerror("La expresion para un indice debe ser de tipo entero");
    }
  }else{
    yyerror("El arreglo no tiene tantas dimensiones");
  }
*/}
| /*epsilon*/ {};

parametros:
  lista_param { $$.lista = $1.lista; }
| /*epsilon*/ { $$.lista = NULL; };

lista_param:
  lista_param COMA expresion { 
    $$.lista = $1.lista;
    add($$.lista, $3.tipo);
    agregar_cuadrupla(cod, "param", $3.dir, "", "");
  }
| expresion { 
    $$.lista = crearLP();
    add($$.lista, $1.tipo);
    agregar_cuadrupla(cod, "param", $1.dir, "", "");
  };

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
int max(int t1, int t2){
    if(t1 == t2)
        return t1;
    else if(t1==3 && t2 == 0){    //char int
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

/*- int = 0
  - float= 1
  - double= 2
  - char= 3
*/
char *reducir(char *dir, int tipo_exp, int tipo_id){
    if(tipo_exp == tipo_id)
        return dir;
    else if(tipo_exp == 3 && tipo_id == 0){    //char a int
        return dir;
    //int a char --> error
    }else if(tipo_exp == 0 && tipo_id == 1){   //int a float
        return dir;
    //float a int --> error
    }else if(tipo_exp == 0 && tipo_id == 2){   //int a double
        return dir;
    //double a int --> error
    }else if(tipo_exp == 1 && tipo_id == 2){  //float a double
        return dir;
    //double a float --> error
    }else{
        yyerror("Error");
        return "";
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

char* newLabel(){
    char* label = malloc(10*sizeof(char)); //Puede haber hasta 999999999 temp
		strcpy(label,"L");
		char num[10];
		//Se guarda en num el valor de labelCounter como un str
		sprintf(num,"%d",labelCounter);
		strcat(label,num);
		labelCounter++;
		return label;
}

/*- int = 0
  - float= 1
  - double= 2
  - char= 3
*/
void amp(char *dir, int t1, int t2, char* res){
    if(t1 == t2){
        strcpy(res, dir);
    }else if((t1==3 && t2==0) || (t1== 0 && t2 == 3)){
        char temp[20];
        newTemp(temp);
        //fprintf(yyout, "%s = (int) %s\n", temp, dir);
        strcpy(res, temp);
    }else if((t1==0 && t2==1) || (t1== 1 && t2 == 0)){
        char temp[20];
        newTemp(temp);
        //fprintf(yyout, "%s = (float) %s\n", temp, dir);
        strcpy(res, temp);
    }else if((t1==0 && t2==2) || (t1== 2 && t2 == 0)){
        char temp[20];
        newTemp(temp);
        //fprintf(yyout, "%s = (double) %s\n", temp, dir);
        strcpy(res, temp);
    }else if((t1==1 && t2==2) || (t1== 2 && t2 == 1)){
        char temp[20];
        newTemp(temp);
        //fprintf(yyout, "%s = (double) %s\n", temp, dir);
        strcpy(res, temp);
    }
    else{
        yyerror("Tipos incompatibles");
    }
}
