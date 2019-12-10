/*
 * Compiladores Proyecto final
 * Programado por:
 * Lopez Martinez Andres
 * Morales Tellez Carlos Gamaliel
 * Perez Quiroz Miguel Angel
 * Sanchez Diaz Maria Beatriz
 * Fecha: 09/11/19
*/

typedef struct _typestack typestack;

struct _typestack{
    typetab *root;
    int num;
};


typestack *crearTypeStack();
void borrarTypeStack(typestack *ptt);
void insertarTypeTab(typestack *ptt, typetab *type_tab);
typetab* getCimaType(typestack *ptt);
typetab* sacarTypeTab(typestack *ptt);

typestack *crearTypeStack(){
        printf("pt");
    typestack *nuevaPTT = malloc(sizeof(typestack));
    if(nuevaPTT){
        nuevaPTT->root = NULL;
        nuevaPTT->num = 0;
    }else{
        printf("No hay memoria disponible");
    }
    return nuevaPTT;
}

void borrarTypeStack(typestack *ptt){
    if(ptt){
        typetab* aux;
        while(ptt->root){
          aux = ptt->root;
          ptt->root = ptt->root->next;
          free(aux);
        }
        free(ptt);
  }else{
    printf("No existe la pila de tabla de tipos\n");
  }
}

typetab* getCimaType(typestack *ptt){
    typetab *aux = ptt->root;
    return aux;
}

void insertarTypeTab(typestack *ptt, typetab *type_tab){
    printf("insertar tt\n");
    if(ptt){    //Si existe la pila
        if (ptt->root == NULL){     //La pila esta vacia
            ptt->root = type_tab;
        }else{                      //La pila no esta vacia
            typetab *aux = getCimaType(ptt);
            type_tab->next = aux;
            ptt->root = type_tab;
        }
        ptt->num++;
    }else{
        printf("La pila de tabla de simbolos no existe");
    }
}

typetab* sacarTypeTab(typestack *ptt){
    if(ptt){    //Si existe la pila
        if (ptt->root == NULL){     //La pila esta vacia
            printf("ERROR: La pila de tabla de simbolos esta vacia");
        }else{                      //La pila no esta vacia
            typetab *cima = getCimaType(ptt);
            //typetab *aux = cima;
            ptt->root = cima->next;
            ptt->num--;
            //free(aux);
            return(cima);
        }
    }else{
        printf("La pila de tabla de simbolos no existe");
    }
}
