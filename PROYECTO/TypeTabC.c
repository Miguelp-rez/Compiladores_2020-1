/*
 * Compiladores Practica 5
 * Programado por:
 * Lopez Martinez Andres
 * Morales Tellez Carlos Gamaliel
 * Perez Quiroz Miguel Angel
 * Sanchez Diaz Maria Beatriz
 * Fecha: 09/11/19
*/

/* En caso de insertar:
 * Array - crearType(Nombre, TipoBase, NULL, NumElem)
 * Struct - crearType(Nombre, -1, SymTab*, -1)
 * Nativo - crearType(Nombre, -1, NULL, -1)
 */
type *crearType(char* nombre, base* tb, int numElem){
    type* nuevo_type = malloc(sizeof(type));
    if(nuevo_type){
        //El id se agrega al momento de insertar a la tabla de tipos 
        strcpy(nuevo_type->nombre, nombre);
        nuevo_type->tb = tb;
        nuevo_type->numElem = numElem;
        //El espacio en bytes se agrega al momento de insertar a la tabla de tipos
        return nuevo_type;
    }else{
        printf("No hay memoria disponible");
        return NULL;
    }
    return nuevo_type;
}

/*Crea una lista de tipos*/
typetab* crearTypeTab(){
    printf("tt");
    typetab* tt= malloc(sizeof(typetab));
    if(tt){
        tt->root = NULL;
        tt->num = 0;
        tt->next = NULL;

        //inicializa la tabla
        type *aux;
        int posicion;
        //Se crea el tipo entero
        aux = crearType("ent", NULL, -1);
        posicion = insertarTipo(tt, aux);

        //Se crea el tipo real
        aux = crearType("real", NULL, -1);
        posicion = insertarTipo(tt, aux);

        //Se crea el tipo dreal
        aux = crearType("dreal", NULL, -1);
        posicion = insertarTipo(tt, aux);

        //Se crea el tipo car
        aux = crearType("car", NULL, -1);
        posicion = insertarTipo(tt, aux);

        //Se crea el tipo void
        aux = crearType("void", NULL, -1);
        posicion = insertarTipo(tt, aux);

        return tt;
    }else{
        printf("No hay memoria disponible");
        return NULL;
    }  
}

/* Borra la tabla de tipos, libera memoria */
void borrarTypeTab(typetab *tt){
    if(tt){
    type* aux;
    while(tt->root != NULL){
      aux = tt->root;
      tt->root = tt->root->next;
      free(aux->tb);
      free(aux);
    }
    free(tt);
  } else {
    printf("No existe la tabla de tipos");
  }
}

/* Inserta al final de la lista en caso de insertar incrementa num
 * Retorna la posicion donde inserto en caso contrario retorna -1
 */
int insertarTipo(typetab *tt, type *t){
    if(tt){
        //Llena el campo correspondiente al id
        t->id = tt->num;
        //Se agrega el espacio en bytes para los diferentes tipos
        int size;
        if(strcmp(t->nombre, "ent") == 0){
            t->tamBytes = 4;
        }else if(strcmp(t->nombre, "real") == 0){
            t->tamBytes = 4;
        }else if(strcmp(t->nombre, "dreal") == 0){
            t->tamBytes = 8;
        }else if(strcmp(t->nombre, "car") == 0){
            t->tamBytes = 1;
        }else if(strcmp(t->nombre, "void") == 0){
            t->tamBytes = 0;
        }else if(strcmp(t->nombre, "array") == 0){
            //Calcular tamBytes
            t->tamBytes = getTam(tt, t->tb->simple) * t->numElem;
        }else if(strcmp(t->nombre, "registro") == 0){
            //Calcular tamBytes
            t->tamBytes = 0;
        }else{
            printf("Espacio no definido");
        }
        if(tt->root == NULL){  //Se inserta el primer imbolo
            tt->root = t;
        }else{      //Se insertan los siguientes simbolos
            type* tipo_actual = tt->root;
            while(tipo_actual->next != NULL){
                tipo_actual = tipo_actual->next;
            }
            tipo_actual->next = t;
        }
        return (tt->num++);
    }else{
        printf("Error: la tabla de tipos no existe\n");
        return -1;
    }
}

 /* Retorna el tipo base de un tipo
  * En caso de no encontrarlo retorna NULL
  */
 base* getTipoBase(typetab *tt, int id){
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
        return aux->tamBytes;
   }
    return -1;
 }

 /* Retorna el numero de elementos de un tipo
  * En caso de no encontrarlo retorna -1
  */
 int getNumElem(typetab *tt, int id){
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

/* Imprime toda la tabla de tipos,
 * distingue entre estructuras, arrays y tipos nativos
*/
char* getNombre(typetab *tt, int id){
     if(tt->root){
        type* aux = tt->root;
        //Recorre la lista hasta que encuentre el id
        int i;
        for(i=0;i<id; i++)
            aux = aux->next;
        return aux->nombre;
    }
    return NULL;
}


void imprimirTablaType(typetab *tt){
    int tipos = 0; //contador de tipos
    type* tipo_actual = tt->root;
    base* base_actual;

    printf("###TABLA DE TIPOS###\n");
    printf("ID \t\tName \t\tBase \t\tSize \t\tNum_elem\n");

    while(tipos < (tt->num)){  //del primer al ultimo nodo
        printf("%i \t\t", tipo_actual->id);
        printf("%s \t\t", getNombre(tt, tipo_actual->id));
        base_actual = getTipoBase(tt, tipo_actual->id);
        if(base_actual){ //El tipo base es una tabla de simbolos
            if(base_actual->tabla){
                printf("Tabla\t\t");
            }else{
                printf("%i \t\t", base_actual->simple);
            }
        }
        else{ //El tipo base es un tipo nativo
            printf("NULL\t\t");
        }
        printf("%i\t\t", getTam(tt, tipo_actual->id));
        printf("%i\t\t", getNumElem(tt, tipo_actual->id));
        printf("\n");
        tipo_actual = tipo_actual->next;
        tipos++;
    
    }
}