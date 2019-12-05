#include <stdio.h>
#include <stdlib.h>

typedef struct _dir dir;

struct _dir{
  int direccion;
  dir *next;
};

typedef struct _dirstack dirstack;

struct _dirstack{
  int num;
  dir *root;
};


dirstack *crearDirStack();
void borrarDirStack(dirstack*);
void insertarDireccion(dirstack*, dir*);
dir* getCimaDir(dirstack*);
dir* sacarDireccion(dirstack*);

dirstack* crearDirStack(){
  dirstack* newDirStack = malloc(sizeof(dirstack));
  newDirStack->root = NULL;
  newDirStack->num = 0;
  return newDirStack;
}

void borrarDirStack(dirstack *pilaDir){
    if(pilaDir){
        dir* aux;
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


dir* getCimaDir(dirstack *pilaDir){
    dir *aux = pilaDir->root;
    return aux;
}

void insertarDireccion(dirstack* pilaDir, dir* nuevaDireccion){
  if(pilaDir){    //Si existe la pila
      if (pilaDir->root == NULL){     //La pila esta vacia
          pilaDir->root = nuevaDireccion;
      }else{                      //La pila no esta vacia
          dir *aux = getCimaDir(pilaDir);
          nuevaDireccion->next = aux;
          pilaDir->root = nuevaDireccion;
      }
      pilaDir->num++;
  }else{
      printf("La pila de direcciones no existe");
  }
}

dir* sacarDireccion(dirstack *pilaDir){
    if(pilaDir){    //Si existe la pila
        if (pilaDir->root == NULL){     //La pila esta vacia
            printf("ERROR: La pila de direcciones esta vacia");
        }else{                      //La pila no esta vacia
            dir *cima = getCimaDir(pilaDir);
            pilaDir->root = cima->next;
            pilaDir->num--;
            return cima;
        }
    }else{
        printf("La pila de tabla de simbolos no existe");
    }
}
