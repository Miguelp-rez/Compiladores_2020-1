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
#include <string.h>
#include <stdlib.h>
#include "y.tab.h"
%}

%x comen1
%x comen2

%option yylineno
%option noyywrap

digito [0-9]
ent_def {digito}+
exp [Ee][+-]?{ent}
real_def ({ent}.?{ent}{exp}|{ent}?.{ent}{exp}?|{ent}.{ent}?{exp}?)[Ff]
dreal_def {ent}.?{ent}{exp}|{ent}?.{ent}{exp}?|{ent}.{ent}?{exp}?

letra [a-zA-Z]
id (_|{letra})(_|{letra}|{digito}){0,31}

car_def '([^'])'
cadena \"([^\"]*)\"

registro [Rr][Ee][Gg][Ii][Ss][Tt][Rr][Oo]
inicio [Ii][Nn][Ii][Cc][Ii][Oo]
fin [Ff][Ii][Nn]
ent [Ee][Nn][Tt]
real [Rr][Ee][Aa][Ll]
dreal [Dd][Rr][Ee][Aa][Ll]
car [Cc][Aa][Rr]
sin [Ss][Ii][Nn]
func [Ff][Uu][Nn][Cc]
si [Ss][Ii]
entonces [Ee][Nn][Tt][Oo][Nn][Cc][Ee][Ss]
sino [Ss][Ii][Nn][Oo]
mientras [Mm][Ii][Ee][Nn][Tt][Rr][Aa][Ss]
hacer [Hh][Aa][Cc][Ee][Rr]
mientrasq [Mm][Ii][Ee][Nn][Tt][Rr][Aa][Ss]" "[Qq][Uu][Ee]
escribir [Ee][Ss][Cc][Rr][Ii][Bb][Ii][Rr]
leer [Ll][Ee][Ee][Rr]
devolver [Dd][Ee][Vv][Oo][Ll][Vv][Ee][Rr]
terminar [Tt][Ee][Rr][Mm][Ii][Nn][Aa][Rr]
verdadero [Vv][Ee][Rr][Dd][Aa][Dd][Ee][Rr][Oo]
falso [Ff][Aa][Ll][Ss][Oo]

%%

""

{registro}  {
                return REGISTRO;
            }

{inicio}    {
                return INICIO;
            }

{fin}   {
            return FIN;
        }

{ent}   {
            return ENT;
        }

{real}  {
            return REAL;
        }

{dreal} {
            return DREAL;
        }

{car}   {
            return CAR;
        }

{sin}   {
            return SIN;
        }

{ent_def}   {
                //printf("entero\n");
                yylval.terminal.tipo = 0;
                yylval.terminal.valor.ival = atoi(yytext);
                return TERMINAL;
            }

{real_def}  {
                //printf("flotante\n");
                yylval.terminal.tipo = 1;
                yylval.terminal.valor.fval = atof(yytext);
                return TERMINAL;
            }

{dreal_def} {
                //printf("flotante\n");
                yylval.terminal.tipo = 2;
                yylval.terminal.valor.dval = atof(yytext);
                return TERMINAL;
            }

{car_def}   {
                //printf("caracter\n");
                yylval.terminal.tipo = 3;
                yylval.terminal.valor.sval = yytext;
                return TERMINAL;
            }

{cadena}    {
                //printf("cadena\n");
                yylval.terminal.tipo = 4;
                yylval.terminal.valor.sval = yytext;
                return TERMINAL;
            }

{func}  {
            return FUNC;
        }

{si}    {
            return SI;
        }

{entonces}  {
                return ENTONCES;
            }

{sino}  {
            return SINO;
        }

{mientras}  {
                return MIENTRAS;
            }

{hacer} {
            return HACER;
        }

{mientrasq}  {
                return MIENTRASQ;
            }

{escribir}  {
                return ESCRIBIR;
            }

{leer}  {
            return LEER;
        }

{devolver}  {
                return DEVOLVER;
            }

{terminar}  {
                return TERMINAR;
            }

{verdadero} {
                return VERDADERO;
            }

{falso} {
            return FALSO;
        }

"+" {
        //printf("+\n");
        return MAS;
    }

"-" {
        //printf("+\n");
        return MENOS;
    }

"*" {
        //printf("*\n");
        return MUL;
    }

"/" {
        //printf("+\n");
        return DIV;
    }

"%" {
        //printf("+\n");
        return MOD;
    }

"(" {
        //printf("(\n");
        return LPAR;
    }

")" {
        //printf(")\n");
        return RPAR;
    }

":="    {
            //printf("=\n");
            return ASIG;
        }

"," {
        //printf(",\n");
        return COMA;
    }

";" {
        ///printf(";\n");
        return PC;
    }

"[" {
        return LCOR;
    }

"]" {
        return RCOR;
    }

"oo"    {
            return OO;
        }

"yy"    {
            return YY;
        }

"no"    {
            return NO;
        }

">" {
        return MA;
    }

"<" {
        return M;
    }

">="    {
            return MAEQ;
        }

"<="    {
            return MEQ;
        }

"=="    {
            return EQEQ;
        }

"<>"    {
            return MMA;
        }

{id}    {
            //printf("id\n");
            yylval.terminal.tipo = 5;
            yylval.terminal.valor.sval = yytext;
            return TERMINAL;
        }

[ \t\r]+ {/*IGNORAR*/}

"\n" {return SL;}

<comen1>{
"*>" {BEGIN(INITIAL);}
<<EOF>> {printf("Ha ocurrido un error léxico: el comentario no finaliza\n"); exit(1);}
.|\n {/*Ignora todo lo que no es *>*/}
}

<comen2>{
. {/*Ignora todo lo que no sea un salto de linea*/}
\n {BEGIN (INITIAL);}
}

<INITIAL>{
"<*"  {BEGIN(comen1);}
"--"  {BEGIN(comen2);}
}

"*>" {printf("Ha ocurrido un error léxico en la linea : %i\nEl caracter de error es %s\n", yylineno, yytext); }
. {printf("Ha ocurrido un error léxico en la linea : %i\nEl caracter de error es %s\n", yylineno, yytext); }

%%

//***MOVER A MAIN GLOBAL***
int main(int argc, char **argv){

  //validacion de cantidad de argumentos
  if(argc < 2){
    printf("Falta el nombre del archivo.\n");
    exit(-1);
  }

  //validacion de archivo abierto
  yyin = fopen(argv[1], "r");
  if (yyin == NULL){
    printf("El archivo %s no se puede abrir\n", argv[1]);
    exit (-1);
  }

  //validacion de archivo creado
  yyout = fopen("salida.txt","w");
  if (yyout == NULL){
    printf("El archivo salida.txt no se puede crear.\n");
    exit (-1);
  }

  //validacion de primer token
  int token = yylex();
  if(token == -1){
    printf("No se pudo obtener el primer token.\n");
  }
  else{
    while(token!=0){
      printf("<%i, %s>\n", token, value);
      fprintf(yyout, "<%i, %s>\n", token, value);
      token = yylex();
    }
    printf("Se genera archivo: salida.txt\n");
  }

  fclose(yyin);
  fclose(yyout);
  return 0;
}
