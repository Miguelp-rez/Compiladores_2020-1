 
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

id [a-zA-Z_][a-zA-Z0-9_]*
ent [0-9]+
real [0-9]+("."[0-9]+)?([Ee][+-]?[0-9]+)?[fF]
dreal [0-9]+("."[0-9]+)?([Ee][+-]?[0-9]+)?
car '([^\']*)'

%%

        
"func" {
            yylval.line = yylineno;
            return FUNC;
        }
        
"si" {
            yylval.line = yylineno;
            return SI;
        }
        
"verdadero" {
            yylval.line = yylineno;
            return VERDADERO;
        }
   
"falso" {
            yylval.line = yylineno;
            return FALSO;
        }
    
"mientras" {
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

"sin"    {  
            yylval.line = yylineno;
            return SIN;
        }
        
{car}    {
            //printf("caracter\n");
                yylval.line = yylineno;
                yylval.num.tipo = 1;                
                strcpy(yylval.num.sval, yytext);
                yylval.num.ival = atoi(yytext);
                return CAR;
        }
        

{ent}    {   
                //printf("entero\n");
                yylval.line = yylineno;
                yylval.num.tipo = 2;                
                strcpy(yylval.num.sval, yytext);
                yylval.num.ival = atoi(yytext);
                return NUM;
            }

{real}  {   
                //printf("flotante\n");
                yylval.line = yylineno;
                yylval.num.tipo = 4;                
                strcpy(yylval.num.sval, yytext);
                yylval.num.dval = atof(yytext);
                return NUM;
            }
            
{dreal}  {   
                //printf("flotante\n");
                yylval.line = yylineno;
                yylval.num.tipo = 3;                
                strcpy(yylval.num.sval, yytext);
                yylval.num.dval = atof(yytext);
                return NUM;
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
    
":=" {
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
   
"oo" {
        yylval.line = yylineno;
        return OO;
   }

"yy" {
        yylval.line = yylineno;
        return YY;
   }
   
"no" {
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
   
">=" {
        yylval.line = yylineno;
        return MAEQ;
   }
   
"<=" {
        yylval.line = yylineno;
        return MEQ;
   }
   
"==" {
        yylval.line = yylineno;
        return EQEQ;
   }
    
"<>" {
        yylval.line = yylineno;
        return MMA;
   }
   

    
[ \n\t]+ {}


<comen1>{
\n {/*Ignora saltos de linea∗*/}
[^*\n]*       {/* come todo lo que no sea '*' */}
"*"+[^*>\n]*  {/* come '*'s no seguidos por '>' */}
(.)*("*>")(.)*("*>") {printf("Ha ocurrido un error léxico en la linea : %i\nEl caracter de error es %s\n", yylineno, yytext); }
<<EOF>> {printf("Ha ocurrido un error léxico: el comentario no finaliza\n"); exit(1);}
"*>" {BEGIN(INITIAL);}

}

<comen2>{
\n {BEGIN (INITIAL);}
}


<INITIAL>{
"<*"  {BEGIN(comen1);}
"--"  {BEGIN(comen2);}
}


. {printf("Ha ocurrido un error léxico en la linea : %i\nEl caracter de error es %s\n", yylineno, yytext); }


%%

int main(int argc, char **argv)
{
    FILE *f, *o;
    f=fopen(argv[1], "r");
    yyin= f;

     if (yyin == NULL)    {      
     printf("El fichero %s no se puede abrir\n", argv[1]);      
     exit (-1);    
    }
    else{
      o= fopen("salidaP4.txt","w");
      int token=yylex();
      fprintf(o, "<%i %s>\n", token, value);
      while(token!=0){  
        token=yylex();  
        fprintf(o, "<%i %s>", token, value);
        }
        fprintf(o, "%i", token);
        printf("Se genero archivo de salidaṔ4.txt'\n");   
        fclose(yyin);
        fclose(yyout);
        return 0;    
        }
  }