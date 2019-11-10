/*
 * Compiladores Practica 5
 * Programado por:
 * Lopez Martinez Andres
 * Morales Tellez Carlos Gamaliel
 * Perez Quiroz Miguel Angel
 * Sanchez Diaz Maria Beatriz
 * Fecha: 09/11/19
*/

/* Retorna un apuntador a una variable tipo */
tipo *crearTipoPrimitivo(int id){
    tipo* base_type = malloc(sizeof(tipo));
    if(base_type){
        base_type->type = id;
    }else{
        printf("No hay memoria disponible\n");
    }
    return base_type;
}

/* Retorna un apuntador a una variable tipo */
tipo *crearTipoStruct(symtab* estructura){
    tipo* base_type = malloc(sizeof(tipo));
    if(base_type){
        base_type->estructura = estructura;
    }else{
            printf("No hay memoria disponible\n");
    }
    return base_type;
}

/* Retorna un apuntador a una variable tipoBase */
tipoBase *crearArqueTipo(bool is_struct, tipo* base_type){
    tipoBase* nuevo = malloc(sizeof(tipoBase));
    if(nuevo){
        nuevo->est = is_struct;
        nuevo->t = base_type;
    }else{
        printf("No hay memoria disponible\n");
    }
    return nuevo;
}

/* Crear un tipo arreglo */
type *crearTipoArray(int id, char* nombre, tipoBase* tb, int size, int num_elem){
    type* tipo = malloc(sizeof(type));
    if(tipo != NULL){
        tipo->id = id;
        strcpy(tipo->nombre, nombre);
        tipo->tb = tb;
        tipo->tamBytes = size;
        tipo->numElem = num_elem;
        tipo->next = NULL;
    }
    else{
        printf("No hay memoria disponible\n");  //ERROR
    }
    return tipo;
}

/* Crear un tipo nativo */
type *crearTipoNativo(int id, char* nombre, tipoBase* tb, int size){
    type* tipo = malloc(sizeof(type));
    if(tipo != NULL){
        tipo->id = id;
        strcpy(tipo->nombre, nombre);
        tipo->tb = tb;
        tipo->tamBytes = size;
        tipo->numElem = 0;
        tipo->next = NULL;
    }
    else{
        printf("No hay memoria disponible\n");  //ERROR
    }
    return tipo;
}

/*Crea una lista de tipos*/
typetab* crearTypeTab(){
    typetab* tt= malloc(sizeof(typetab));
    tt->root=NULL;
    tt->num=0;
    tt->next = NULL;
    return tt;
}

/* Borra la tabla de tipos, libera memoria */
void borrarTypeTab(typetab *tt){
    if(tt){
    type* aux;
    while(tt->root != NULL){
      aux = tt->root;
      tt->root = tt->root->next;
      free(aux->tb->t);
      free(aux->tb);
      free(aux);
    }
    free(tt);
  } else {
    printf("No existe la tabla de tipos");
  }
}

int buscarTipo(typetab* tt, char* nombre){
    if(tt){
        int posicion = 0;
        if(tt->root == NULL){
            return -1; //La tabla esta vacia
        }
        type* tipo_actual = tt->root;
        while (tipo_actual != NULL){
            posicion++;
            if (strcmp(nombre, tipo_actual->nombre) == 0)
                return posicion;
            else
                tipo_actual = tipo_actual->next;
        }
        return -1;  //El simbolo no existe
    }else
        printf("Error: la tabla de tipos no existe\n");
      return -1;
}

/* Inserta al final de la lista en caso de insertar incrementa num
 * Retorna la posicion donde inserto en caso contrario retorna -1
 */
int insertarTipo(typetab *tt, type *t){
    if(tt){
        int posicion = buscarTipo(tt, t->nombre);
        if(posicion == -1){
            tt->num++;
            if(tt->root == NULL){
                tt->root = t; //es el primer simbolo
            }
            else{
                type* tipo_actual = tt->root;
                while(tipo_actual->next != NULL){
                    tipo_actual = tipo_actual->next;
                }
                tipo_actual->next = t;
            }
            return (tt->num);
        }
        else{
            printf("No guardar nada\n");
            return -1;
        }
    }else
        printf("Error: la tabla de tipos no existe\n");
        return -1;
}

 /* Retorna el tipo base de un tipo
  * En caso de no encontrarlo retorna NULL
  */
 tipoBase* getTipoBase(typetab *tt, int id){
   if(tt){
    if(tt->root){
       type* aux = tt->root;
       int i;
       for(i=0;i<id; i++)
         aux = aux->next;
       if(aux->tb)
         return aux->tb;
     }
     return NULL;
   }
   return NULL;
 }
 /* Retorna el numero de bytes de un tipo
  * En caso de no encontrarlo retorna -1
  */
 int getTam(typetab *tt, int id){
    if(tt->root){
    type* aux = tt->root;
    //Recorre la lista hasta que encuentre el id
    int i;
    for(i=0;i<id; i++)
        aux = aux->next;
    if(aux->tamBytes)
        return aux->tamBytes;
   }
    return -1;
 }

 /* Retorna el numero de elementos de un tipo
  * En caso de no encontrarlo retorna -1
  */
 int getNumElem(typetab *tt, int id){
    if(tt){
        if(tt->root){
            type* aux = tt->root;
            //Recorre la lista hasta que encuentre el id
            int i;
            for(i=0;i<id; i++)
                aux = aux->next;
            return aux->numElem;
        }
        return -1;
    }
    return -1;
 }

/* Imprime toda la tabla de tipos,
 * distingue entre estructuras, arrays y tipos nativos
*/
char* getNombre(typetab *tt, int id){
    if(tt){
     if(tt->root){
        type* aux = tt->root;
        //Recorre la lista hasta que encuentre el id
        int i;
        for(i=0;i<id; i++)
            aux = aux->next;
        return aux->nombre;
    }
   }
    return NULL;
}


void imprimirTablaType(typetab *tt){
    int tipos = 1; //contador de tipos
    type* tipo_actual = tt->root;
    tipoBase* tb;

    printf("###TABLA DE TIPOS###\n");

    while(tipos != (tt->num)+1){  //del primer al ultimo nodo
        printf("Tipo #%i\n", tipos);
        //se usa id para probar funciones get, puede ser directo
        printf("ID:%i\n", tipo_actual->id);
        printf("Nombre:%s\n", getNombre(tt, tipo_actual->id));
        tb = getTipoBase(tt, tipo_actual->id);
        if(tb->est){ //El tipo base es una tabla de simbolos
            printf("El tipo base es una tabla de simbolos\n");
        }
        else{ //El tipo base es un tipo nativo
            printf("El tipo base es de tipo nativo:%i\n", tb->t->type);
        }
        printf("Tamano en bytes:%i\n", getTam(tt, tipo_actual->id));
        printf("Numero de elementos:%i\n", getNumElem(tt, tipo_actual->id));
        printf("\n");

        tipo_actual = tipo_actual->next;
        tipos++;
    }
}