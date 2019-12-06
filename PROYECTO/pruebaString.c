#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char* saludo;
	saludo = "Hola, mundo";
	printf("Saludo: %s. Tamanio: %lu",saludo,strlen(saludo));
	return 0;
}
