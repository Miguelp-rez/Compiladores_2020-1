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
	char* content;
	item* next;
};

strtab* crearStrTab(){
	strtab *nuevaStrTab = malloc(sizeof(strtab));
	if(strtab){
		nuevaStrTab->root = NULL;
		nuevaStrTab->num = 0;
	}else{
		printf("No hay memoria disponible\n");
	}
	return nuevaStrTab;
}

void borarStrTab(strtab *strTab){
	if(strTab){
		strTab* aux;
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

void insertarCadena(strtab *strTab, string cadena){
	if(strTab){
		item* nuevaCadena;
		nuevaCadena->content = cadena;
		if(strlen(cadena) == 1){
			nuevaCadena->tipo = "caracter";
		}else if(strlen(cadena) > 1){
			nuevaCadena->tipo = "cadena";
		}else{
			nuevaCadena->tipo = "vacio";
		}
		insertarItem(strTab,nuevaCadena);)
	}else{
		printf("No existe la tabla de cadenas\n")
	}
}


symtab* sacarSymTab(symstack *pts){
    if(pts){    //Si existe la pila
        if (pts->root == NULL){     //La pila esta vacia
            printf("ERROR: La pila de tabla de simbolos esta vacia");
        }else{                      //La pila no esta vacia
            symtab *cima = getCimaSym(pts);
            //symtab *aux = cima;
            pts->root = cima->next;
            pts->num--;
            //free(aux);
            return cima;
        }
    }else{
        printf("La pila de tabla de simbolos no existe");
    }
}
