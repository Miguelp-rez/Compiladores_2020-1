typedef struct _etiqueta etiqueta;
typedef struct _l_etiquetas l_etiquetas;
struct _etiqueta{
  char* valor;
  etiqueta* next;
};
struct _l_etiquetas{
  quad* codigo;
  etiqueta* root;
  int num;
  //int num_codigo;
};