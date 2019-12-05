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
id (_|{letra})((_|{letra}|{digito})){0,31}

car_def '([^'])'
cadena \"([^"]*)\"

registro [Rr][Ee][Gg][Ii][Ss][Tt][Rr][Oo]
inicio [Ii][Nn][Ii][Cc][Ii][Oo]
fin [Ff][Ii][Nn]
ent [Ee][Nn][Tt]
real [Rr][Ee][Aa][Ll]
dreal [Dd][Rr][Ee][Aa][Ll]
car [Cc][Aa][Rr]
sin [Ss][Ii][Nn]
base {ent}|{real}|{dreal}|{car}|{sin}
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

{func}  {
            yylval.line = yylineno;
            return FUNC;
        }

{si}    {
            yylval.line = yylineno;
            return SI;
        }

{verdadero} {
                yylval.line = yylineno;
                return VERDADERO;
            }

{falso} {
            yylval.line = yylineno;
            return FALSO;
        }

{mientras}  {
                yylval.line = yylineno;
                return MIENTRAS;
            }

{id}    {
            //printf("id\n");
            yylval.line = yylineno;
            strcpy(yylval.sval, yytext);
            //printf("se hizo la copia \n");
            return ID;
        }

{sin}   {
            yylval.line = yylineno;
            return SIN;
        }

{car_def}   {
            //printf("caracter\n");
            yylval.line = yylineno;
            yylval.terminal.tipo = 1;
            strcpy(yylval.terminal.valor.sval, yytext);
            yylval.terminal.valor.sval = atoi(yytext);
            return TERMINAL;
        }

{ent_def}   {
            //printf("entero\n");
            yylval.line = yylineno;
            yylval.terminal.tipo = 2;
            strcpy(yylval.terminal.valor.sval, yytext);
            yylval.terminal.valor.ival = atoi(yytext);
            return TERMINAL;
        }

{real_def}  {
            //printf("flotante\n");
            yylval.line = yylineno;
            yylval.terminal.tipo = 3;
            strcpy(yylval.terminal.valor.sval, yytext);
            yylval.terminal.valor.fval = atoi(yytext);
            return TERMINAL;
        }

{dreal_def}     {
                //printf("dflotante\n");
                yylval.line = yylineno;
                yylval.terminal.tipo = 4;
                strcpy(yylval.terminal.valor.sval, yytext);
                yylval.terminal.valor.dval = atoi(yytext);
                return TERMINAL;
            }

"+" {
        //printf("+\n");
        yylval.line = yylineno;
        return MAS;
    }

"-" {
        //printf("+\n");
        yylval.line = yylineno;
        return MENOS;
    }

"*" {
        //printf("*\n");
        yylval.line = yylineno;
        return MUL;
    }

"/" {
        //printf("+\n");
        yylval.line = yylineno;
        return DIV;
    }

"%" {
        //printf("+\n");
        yylval.line = yylineno;
        return MOD;
    }

"(" {
        //printf("(\n");
        yylval.line = yylineno;
        return LPAR;
    }

")" {
        //printf(")\n");
        yylval.line = yylineno;
        return RPAR;
    }

":="    {
            //printf("=\n");
            yylval.line = yylineno;
            return ASIG;
        }

"," {
        //printf(",\n");
        yylval.line = yylineno;
        return COMA;
    }

";" {
        ///printf(";\n");
        yylval.line = yylineno;
        return PC;
    }

"[" {
        yylval.line = yylineno;
        return LCOR;
    }

"]" {
        yylval.line = yylineno;
        return RCOR;
    }

"oo"    {
            yylval.line = yylineno;
            return OO;
        }

"yy"    {
            yylval.line = yylineno;
            return YY;
        }

"no"    {
            yylval.line = yylineno;
            return NO;
        }

">" {
        yylval.line = yylineno;
        return MA;
    }

"<" {
        yylval.line = yylineno;
        return M;
    }

">="    {
            yylval.line = yylineno;
            return MAEQ;
        }

"<="    {
            yylval.line = yylineno;
            return MEQ;
        }

"=="    {
            yylval.line = yylineno;
            return EQEQ;
        }

"<>"    {
            yylval.line = yylineno;
            return MMA;
        }

[ \n\t]+ {}

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
