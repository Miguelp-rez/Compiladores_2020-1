#include <stdio.h>
extern void yyerror(char* msg);
extern int yylex();
extern int yyparse();
extern FILE *yyin;
extern FILE *yyout;

/*int main(int argc, char **argv){

  //validacion de cantidad de argumentos
  if(argc < 2){
    printf("Falta el nombre del archivo.\n");
    return 0;
  }

  //validacion de archivo abierto
  yyin = fopen(argv[1], "r");
  if (yyin == NULL){
    printf("El archivo %s no se puede abrir\n", argv[1]);
    return 0;
  }

  //validacion de archivo creado
  yyout = fopen("salida.txt","w");
  if (yyout == NULL){
    printf("El archivo salida.txt no se puede crear.\n");
    return 0;
  }

  //validacion de primer token
  int token = yylex();
  if(token == -1){
    printf("No se pudo obtener el primer token.\n");
  }
  else{
    while(token!=0){
      printf("<%i>\n", token);
      //fprintf(yyout, "<%i, %s>\n", token, value);
      token = yylex();
    }
    //printf("Se genera archivo: salida.txt\n");
  }

  fclose(yyin);
  fclose(yyout);
  return 0;
}*/

int main(int argc, char **argv){
  int exit_status = 0;
  FILE *f = fopen(argv[1], "r");
  if (argc < 2) return -1;
  if (!f) return -1;
  yyin = f;
  exit_status = yyparse();
  if (exit_status == 0)
    printf("Aceptado\n");
  else
    printf("No Aceptado\n");
  fclose(f);  
  return 0;
}