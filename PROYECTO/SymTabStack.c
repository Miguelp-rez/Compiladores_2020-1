/*
 * Compiladores Proyecto final
 * Programado por:
 * Lopez Martinez Andres
 * Morales Tellez Carlos Gamaliel
 * Perez Quiroz Miguel Angel
 * Sanchez Diaz Maria Beatriz
 * Fecha: 09/11/19
*/

typedef struct _symstack symstack;

struct _symstack{
    symtab *root;
    int num;
};


symstack *crearSymStack();
void borrarSymStack(symstack *pts);
void insertarSymTab(symstack *pts, symtab *sym_tab);
symtab* getCimaSym(symstack *pts);
symtab* sacarSymTab(symstack *pts);

symstack *crearSymStack(){
    printf("ps");
    symstack *nuevaPTS = malloc(sizeof(symstack));
    if(nuevaPTS){
        nuevaPTS->root = NULL;
        nuevaPTS->num = 0;
    }else{
        printf("No hay memoria disponible");
    }
    return nuevaPTS;
}

void borrarSymStack(symstack *pts){
    if(pts){
        symtab* aux;
        while(pts->root){
          aux = pts->root;
          pts->root = pts->root->next;
          free(aux);
        }
        free(pts);
  }else{
    printf("No existe la pila de tabla de simbolos\n");
  }
}

symtab* getCimaSym(symstack *pts){
    symtab *aux = pts->root;
    return aux;
}

void insertarSymTab(symstack *pts, symtab *sym_tab){
    printf("insertar ts \n");
    if(pts){    //Si existe la pila
        if (pts->root == NULL){     //La pila esta vacia
            pts->root = sym_tab;
        }else{                      //La pila no esta vacia
            symtab *aux = getCimaSym(pts);
            sym_tab->next = aux;
            pts->root = sym_tab;
        }
        pts->num++;
    }else{
        printf("La pila de tabla de simbolos no existe");
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
