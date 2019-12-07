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
        //Se agrega el espacio en bytes para los diferentes tipos
        if(strcmp(nombre, "ent") == 0){
            nuevo_type->tamBytes = 4;
            printf("entero");
        }else if(strcmp(nombre, "real") == 0){
            nuevo_type->tamBytes = 4;
            printf("real");
        }else if(strcmp(nombre, "dreal") == 0){
            nuevo_type->tamBytes = 8;
            printf("dreal");
        }else if(strcmp(nombre, "car") == 0){
            nuevo_type->tamBytes = 4;
            printf("car");
        }else if(strcmp(nombre, "void") == 0){
            nuevo_type->tamBytes = 4;
            printf("void");
        }else if(strcmp(nombre, "array") == 0){
            //Calcular tamBytes
            nuevo_type->tamBytes = 4;
            printf("array");
        }else if(strcmp(nombre, "registro") == 0){
            //Calcular tamBytes
            nuevo_type->tamBytes = 4;
            printf("registro");
        }else{
            printf("%s no existe", nombre);
        }
        return nuevo_type;
    }else{
        printf("No hay memoria disponible");
        return NULL;
    }
    return nuevo_type;
}

/*Crea una lista de tipos*/
typetab* crearTypeTab(){
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
        if(tt->root == NULL){  //Se inserta el primer imbolo
            tt->root = t;
        }else{      //Se insertan los siguientes simbolos
            type* tipo_actual = tt->root;
            printf("%s", tipo_actual->next);
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

    while(tipos < tt->num){  //del primer al ultimo nodo
        printf("Tipo #%i\n", tipos);
        printf("%i \t\t", tipo_actual->id);
        printf("%s\t\t", getNombre(tt, tipo_actual->id));
        base_actual = getTipoBase(tt, tipo_actual->id);
        if(base_actual->tabla){ //El tipo base es una tabla de simbolos
            printf("%d\t\t", base_actual->tabla);
        }
        else{ //El tipo base es un tipo nativo
            printf("%d\t\t", base_actual->simple);;
        }
        printf("%i\t\t", getTam(tt, tipo_actual->id));
        printf("%i\t\t", getNumElem(tt, tipo_actual->id));
        printf("\n");

        tipo_actual = tipo_actual->next;
        tipos++;
    }
}