/*
 * Compiladores Proyecto final
 * Programado por:
 * Lopez Martinez Andres
 * Morales Tellez Carlos Gamaliel
 * Perez Quiroz Miguel Angel
 * Sanchez Diaz Maria Beatriz
 * Fecha: 04/12/19
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _strtab strtab;
typedef struct _item item;
typedef union _strorchar strorchar;

struct _strtab{
	int num;
	item* root;
};

//union _strorchar{
//	string cadena;
//	char caracter;
//};

struct _item{
	char* tipo;
	char* content;
	item* next;
};

strtab* crearStrTab();
void borrarStrTab(strtab*);
item* getCimaStr(strtab*);
void insertarItem(strtab*, item*);
void insertarCadena(strtab*, char*);
item* sacarItem(strtab*);

strtab* crearStrTab(){
	strtab *nuevaStrTab = malloc(sizeof(strtab));
	if(nuevaStrTab){
		nuevaStrTab->root = NULL;
		nuevaStrTab->num = 0;
	}else{
		printf("No hay memoria disponible\n");
	}
	return nuevaStrTab;
}

void borrarStrTab(strtab *strTab){
	if(strTab){
		item* aux;
		while(strTab->root){
			aux = strTab->root;
			strTab->root = strTab->root->next;
			free(aux);
		}
		free(strTab);
	}else{
		printf("No existe la tabla de cadenas\n");
	}
}

item* getCimaStr(strtab *strTab){
	item *aux = strTab->root;
	return aux;
}

void insertarItem(strtab *strTab, item *itemcc){
	if(strTab){
		if(strTab->root == NULL){
			strTab->root = itemcc;
		}else{
			item *aux = getCimaStr(strTab);
			itemcc->next = aux;
			strTab->root = itemcc;
		}
		strTab->num++;
	}else{
		printf("No existe la tabla de cadenas\n");
	}
}

void insertarCadena(strtab *strTab, char* cadena){
	if(strTab){
		item* nuevaCadena = malloc(sizeof(item));
		nuevaCadena->content = cadena;
		if(strlen(cadena) == 1){
			nuevaCadena->tipo = "caracter";
		}else if(strlen(cadena) > 1){
			nuevaCadena->tipo = "cadena";
		}else{
			nuevaCadena->tipo = "vacio";
		}
		insertarItem(strTab,nuevaCadena);
	}else{
		printf("No existe la tabla de cadenas\n");
	}
}


item* sacarItem(strtab *strTab){
    if(strTab){    //Si existe la tabla de cadenas
        if (strTab->root == NULL){     //La tabla de cadenas esta vacia
            printf("ERROR: La tabla de cadenas está vacía");
        }else{                      //La tabla de cadenas no esta vacía
            item *cima = getCimaStr(strTab);
            strTab->root = cima->next;
            strTab->num--;
            return cima;
        }
    }else{
        printf("La pila de tabla de simbolos no existe");
    }
}

// PRUEBA
/*
int main(){
	strtab* nuevaTabla = crearStrTab();
	insertarCadena(nuevaTabla,"Hola, mundo");
	insertarCadena(nuevaTabla,"C");
	insertarCadena(nuevaTabla,"");
	item *vacio = sacarItem(nuevaTabla);
	item *caracter = sacarItem(nuevaTabla);
	item *cadena = sacarItem(nuevaTabla);
	printf("%s: %s\n",cadena->tipo,cadena->content);
	printf("%s: %s\n",caracter->tipo,caracter->content);
	printf("%s: %s\n",vacio->tipo,vacio->content);
	borrarStrTab(nuevaTabla);
}
*/
