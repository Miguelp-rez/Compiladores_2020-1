#include <stdio.h>
#include <stdlib.h>

typedef struct _typetab typetab;
struct _typetab {
    type ∗root; 
    //int num; //Aún no sé para que es ésto
    type ∗next;
};
typedef struct _typestack typestack;
struct _typestack{
    typetab ∗root;
    int num;
} ;


typestack∗ crearTypeStack();
void borrarTypeStack( typestack ∗ts );
void insertarTypeTab( typetab ∗sym );
typetab∗ getCimaType( typestack ∗ts );
typetab* sacarTypeTab( typetack ∗ts );


typestack∗ crearTypeStack(){
    typestack* ts = malloc(sizeof(typetab)); //PILA de tipos.
    //Se inicializa el contador que nos va a dar el tamaño actual de la PILA
    ts->num = 0;
    //Se inicia con un apuntador a NULL
    ts->root = NULL;
    return ts; 
}

void insertarTypeTab( typetab *sym, typeStack *ts ){
    if (sym){
        typetab* typeTab = malloc(sizeof(typetab));
        //Aquí va la función que retorna el apuntador a la tabla de tipos
        typeTab->root = NULL; //Reemplazar NULL con funcion()  
        //El nodo siguiente va a ser el tope de la pila
        typeTab->next = ts->root;
        //El tope de la pila va a ser el nodo que se acaba de insertar
        ts->root = typeTab;
        //Se incrementa el tamaño de la pila en una unidad. 
        ts->num++;
    }
}

void borrarTypeStack( typestack *ts ){
    //Mientras haya algo en la pila.
    while (ts->num > 0){
        //Creamos un apuntador auxiliar que sea igual al tope actual de la pila
        typetab* aux = ts->root;
        //El tope de la pila se va a recorrer al siguiente nodo
        ts->root = ts->root->next;
        //Se decrementa el tamaño de la pila en una unidad. 
        ts->num--;
        //Se libera la memoria.
        free(aux);
    }
}

typetab∗ sacarTypeTab( typetack ∗ts ){
    //Si existe una tabla de tipos 
    if (ts){
        if(ts->num){
            //Se crea un apuntador auxiliar que va a ser igual al tope actual de la pila
            typetab* aux = ts->root;
            //El tope de la pila se recorre al nodo siguiente. 
            ts->root = ts->root->next;
            //Se decrementa en una unidad el tamaño de la pila.
            ts->num--;
            //Retornamos la tabla de tips que sacamos de la pila. 
            return aux;
        }
    }
}

typetab∗ getCimaType( typestack ∗ts ){
    //Aún no sé qué deba hacer esta funcion. 
}

