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

typedef struct _direc direc;

struct _direc{
  int direccion;
  direc *next;
};

typedef struct _dirstack dirstack;

struct _dirstack{
  int num;
  direc *root;
};


dirstack *crearDirStack();
void borrarDirStack(dirstack*);
void insertarDir(dirstack*, direc*);
void insertarDireccion(dirstack*,int);
direc* getCimaDir(dirstack*);
int sacarDireccion(dirstack*);

dirstack* crearDirStack(){
  dirstack* newDirStack = malloc(sizeof(dirstack));
  newDirStack->root = NULL;
  newDirStack->num = 0;
  return newDirStack;
}

void borrarDirStack(dirstack *pilaDir){
    if(pilaDir){
        direc* aux;
        while(pilaDir->root){
          aux = pilaDir->root;
          pilaDir->root = pilaDir->root->next;
          free(aux);
        }
        free(pilaDir);
  }else{
    printf("No existe la pila de tabla de simbolos\n");
  }
}


direc* getCimaDir(dirstack *pilaDir){
    direc *aux = pilaDir->root;
    return aux;
}

void insertarDir(dirstack* pilaDir, direc* nuevaDireccion){
  if(pilaDir){    //Si existe la pila
      if (pilaDir->root == NULL){     //La pila esta vacia
          pilaDir->root = nuevaDireccion;
      }else{                      //La pila no esta vacia
          direc *aux = getCimaDir(pilaDir);
          nuevaDireccion->next = aux;
          pilaDir->root = nuevaDireccion;
      }
      pilaDir->num++;
  }else{
      printf("La pila de direcciones no existe\n");
  }
}

void insertarDireccion(dirstack* pilaDir,int direccion){
	if(pilaDir){
		direc* nuevaDireccion = malloc(sizeof(direc));
		nuevaDireccion->direccion = direccion;
		insertarDir(pilaDir,nuevaDireccion);
	}else{
		printf("La pila de direcciones no existe\n");
	}

}

int sacarDireccion(dirstack *pilaDir){
    if(pilaDir){    //Si existe la pila
        if (pilaDir->root == NULL){     //La pila esta vacia
            printf("ERROR: La pila de direcciones esta vacia");
        }else{                      //La pila no esta vacia
            direc *cima = getCimaDir(pilaDir);
            pilaDir->root = cima->next;
            pilaDir->num--;
            return cima->direccion;
        }
    }else{
        printf("La pila de tabla de simbolos no existe");
    }
}


//PRUEBA
/*int main(){
        dirstack* nuevaDirStack = crearDirStack();
        insertarDireccion(nuevaDirStack,10);
        insertarDireccion(nuevaDirStack,20);
        direc *dir1 = sacarDireccion(nuevaDirStack);
        direc *dir2 = sacarDireccion(nuevaDirStack);
        printf("%i\n",dir1->direccion);
        printf("%i\n",dir2->direccion);
        borrarDirStack(nuevaDirStack);
}*/
