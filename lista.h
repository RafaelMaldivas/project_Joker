/*---------------------------------LISTA GERAL----------------------------------*/
/*lista global*/
struct funcionarios{
    int ID;
    char nome[50];
    char endereco[50];
    int idade;
    float salario;
    int cargo;
};
typedef struct funcionarios FUNC;

typedef struct elemento{
    FUNC dados;
    struct elemento *prox;
}ELEM;

typedef struct elemento *Lista ;

Lista *li;


int listaVazia(Lista *li);


int insere_lista_ordenada(Lista *li, FUNC al);


Lista *criaLista();


int remove_lista(Lista *li, int ID);


int consultaID(Lista *li, int ID, FUNC *al);

int consultaSalario(Lista *li, int ID, float minimo,float maximo, FUNC *al);

void apaga_lista(Lista *li);

/*---------------------------------MENU----------------------------------*/

void titulo();


void limpa_buffer();

void menuPrincipal();


void escolha();


void adicionar();


void excluir();


void editar();

void exibir();

void sair();
/*---------------------------------CBO----------------------------------*/


typedef struct cargo{
    int codigocbo;
    char descricaocbo[100];
}CARGO;

typedef struct elementocbo* CBOLista;


struct elementocbo{
    CARGO dadoscbo;
    struct elementocbo *proxcbo;
};
typedef struct elementocbo ELEMCBO;


void implementa_cbo();

CBOLista *cb;


void inicializadorcbo(CBOLista *cb);


void separacao(char *frase, CARGO *funcionario);


CBOLista *cria_cbo_lista();

void apaga_cbo_lista(CBOLista *cbo);


int CBOListaVazia(CBOLista *cbo);


int tamCBOLista(CBOLista *cbo);


int insere_cbo_ordenada(CBOLista *cbo, CARGO al);


int remove_cbo_lista(CBOLista *cbo, int mat);


int exibicao_cbo(CBOLista *cbo, int posicao, CARGO *funcionario);


int exibicao_cbo_cod(CBOLista *cbo, int codigo, CARGO *funcionario);


int escolha_cargo_cbo(CBOLista *cb);


int mostra_codigo_cbo(CBOLista *cb, int p);

