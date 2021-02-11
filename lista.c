#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include<conio.h>
#include "lista.h"

/*cabeçalho do programa*/
void titulo(){
    printf("\n                                                         # Joker Technologies #\n");
    printf("\n===============================================================================\n");
    printf("                            Wayne Corporation                              \n");
    printf("                         Cadastro de Funcionários                              \n");
    printf("===============================================================================\n");
}
/* limpa qualquer caractere q esteja na tela e funciona como pause */
void limpaBuffer(){
    char x;
     do {
        x = getchar();
     }while ((x != '\n')&&(x != EOF));
}

void menuPrincipal()
{setlocale(LC_ALL,"Portuguese");
    int x;
    system("cls");
    system("color 60");
    printf("=====================                ============================\n");
    printf("===================== Menu Principal ============================\n");
    printf("=====================                ============================\n");
    printf("    [ 1 ] . . . . Adicionar Funcionario\n");
    printf("    [ 2 ] . . . . Editar Funcionario\n");
    printf("    [ 3 ] . . . . Listar Funcionario por ID\n");
    printf("    [ 4 ] . . . . Listar Funcionario por Salário\n");
    printf("    [ 5 ] . . . . Excluir Funcionario\n");
    printf("    [ 6 ] . . . . Sair do Programa\n");
    printf("=================================================================\n");
    printf("=== Escolha a sua opcao:                                      ===\n");
    scanf("%d",&x);
    switch(x){
        case 1:
            adicionar();
            break;
        case 2:
            editar();
            break;
        case 3:
            exibir();
            break;
        case 4:
            exibirSalario();
            break;
        case 5:
            excluir();
            break;
        case 6:
            sair();
        default:
            printf("\n\n - Digite uma opçao valida !! -\n\n");
            break;

    }
}

void escolha(){
	int continuar;

    printf("\n Deseja Continuar? \n");
    printf(" Digite [1]SIM [2]NAO \n ");
    scanf("%d",&continuar);

	if(continuar==2){
        sair();
    }else{
        limpaBuffer();
        menuPrincipal();
    }
}

/* função que adicona funcionário*/
void adicionar(){
    system("cls");
    system("color 06");
    titulo();    /* chama o cabeçalho*/

    int confirma,i=0;
	FUNC fun;

    while(confirma!=2){
        system("cls");
        titulo();

        printf(" ID: ");
        scanf("%d",&fun.ID);
        getchar();

        printf(" Nome: ");
        fgets(fun.nome,49,stdin);

        printf(" Endereco: ");
        fgets(fun.endereco,49,stdin);

        printf(" Idade: ");
        scanf("%d",&fun.idade);

        printf(" Salario: ");
        scanf("%f",&fun.salario);

        fun.cargo = escolha_cargo_cbo(&cb);
        i++;
        int x;
        x = insere_lista_ordenada(&li, fun);

        if(x){
            printf("\n Operacao Efetuada com sucesso!");
        }else{
            printf("\n Falha na operacao");
        }

        system("cls");
        titulo();

        printf("\n Deseja inserir mais um registro? \n");
        printf(" [1]SIM [2]NAO \n ");
        scanf("%d",&confirma);
    }
    escolha();                             /* função para confirmar ação*/
}/*fim da função adicionar*/

int listaVazia(Lista *li){
    if(li == NULL){
        return 1;
    }
    if(*li == NULL){
        return 1;
    }
    return 0;
}

int insere_lista_ordenada(Lista *li, FUNC al){
    if(li == NULL){
        return 0;
    }
    ELEM *no = (ELEM*) malloc(sizeof(ELEM));
    if(no == NULL){
        return 0;
    }
    no->dados = al;
    if(listaVazia(li)){
        no->prox = (*li);
        *li = no;
        return 1;
    }else{
        ELEM *ant, *atual = *li;
        while(atual != NULL && atual->dados.ID < al.ID){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = ant->prox;
            ant->prox = no;
        }
    return 1;
    }
}

/*função para remover funcionário*/
int remove_lista(Lista *li, int ID){
    if(li == NULL){
        return 0;
    }
    ELEM *ant, *no = *li;
    while(no != NULL && no->dados.ID != ID){
        ant = no;
        no = no->prox;
    }
    if(no == NULL){
        return 0;
    }
    if(no == *li){
        *li = no->prox;
    }else{
        ant->prox = no->prox;
    }
    free(no);
    return 1;
} /* fim da função remover*/

/*Função responsável pela consulta através do ID*/
int consultaID(Lista *li, int ID, FUNC *al){
    if(li == NULL){
        return 0;
    }
    ELEM *no = *li;
    while(no != NULL && no->dados.ID != ID){
        no = no->prox;
    }
    if(no == NULL){
        return 0;
    }else{
        *al = no->dados;
        return 1;
    }
}/*fim da função consultaID*/

int consultaSalario(Lista *li, int pos,float minimo, float maximo, FUNC *fun){
    if(li == NULL || pos <= 0){
        return 0;
    }
    ELEM *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }if(no == NULL){
        return 0;
    }else{
        if(no ->dados.salario >= minimo && no->dados.salario <= maximo){
            *fun = no->dados;
        }
        return 1;
    }
} /*fim da função consulta_pos*/


/*função para excluir dados*/
void excluir(){
    system("cls");
    system("color 40");
    titulo();
    int ID;
    printf("\n Digite o ID que deseja excluir: ");
    scanf("%d",&ID);

    FUNC func;
    int cont;
    int x;
    x = consultaID(&li, ID, &func);

    if(x){
        printf("\n ID :%d",func.ID);
        printf("\n Nome : %s",func.nome);
        printf(" Endereco: %s",func.endereco);
        printf(" Idade: %d anos",func.idade);
        printf("\n Salario: R$ %.2f",func.salario);
        mostra_codigo_cbo(&cb,func.cargo);


    printf("\n Deseja MESMO excluir: \n");
    printf(" [1]SIM [2]NAO \n ");
    scanf("%d",&cont);

    }else{
		printf("\n ID nao cadastrado ");
	}


	if(cont == 1){
        x = remove_lista(&li,ID);
        if(x){
            printf("\n Removido elemento com sucesso!");
        }else{
            printf("\n Nao foi possivel remover o elemento!!");
        }
    }
    escolha();
} /*fim da função excluir */

/*função para editar o funcionário */

void editar(){
    system("cls");
    system("color 04");
    titulo();

	int registros;
    while(registros!=2){
    int id;
    int x, i, y,opc;
    FUNC fun;
	y = tamLista(&li);

	if(y>0){
        for(i = 1; i <= y; i++){
            x = consulta_lista_pos(&li , i , &fun);
            if(x){
                 printf("\n ID :%d",fun.ID);
                 printf("\n Nome : %s",fun.nome);
                 printf(" Endereco: %s",fun.endereco);
                 printf(" Idade: %d anos",fun.idade);
                 printf("\n Salario: R$ %.2f",fun.salario);
                 mostra_codigo_cbo(&cb, fun.cargo);
                 printf("\n ---------------------------------------------------------------- ");
            }
        }
    }else{
        printf("\n Nao há registros no sistema \n");
    }

    printf("\n-------------------------------------------------");
    printf("\n\n Digite o id do funcionario que deseja editar: ");
    scanf("%d", &id);

    x = consultaID(&li, id, &fun);
    if(x){
        printf("\n ID :%d",fun.ID);
        printf("\n Nome : %s",fun.nome);
        printf(" Endereco: %s",fun.endereco);
        printf(" Idade: %d anos",fun.idade);
        printf("\n Salario: %.2f",fun.salario);
        mostra_codigo_cbo(&cb, fun.cargo);

        system("cls");
        titulo();

        int tempid = fun.ID;

        remove_lista(&li, id);
        system("cls");
        titulo();

        fun.ID = tempid;

        printf(" ID: %d \n",fun.ID);
        getchar();

        printf(" Nome: ");
        fgets(fun.nome,49,stdin);

        printf(" Endereco: ");
        fgets(fun.endereco,49,stdin);

        printf(" Idade: ");
        scanf("%d",&fun.idade);

        printf(" Salario:  R$ ");
        scanf("%f",&fun.salario);

        fun.cargo = escolha_cargo_cbo(&cb);
        getchar();

        int i, x;
        i++;

        x = insere_lista_ordenada(&li,fun);

        if(x){
            printf("\n Operacao Efetuada com sucesso! \n");
        }else{
            printf("\n Falha na operacao \n");
        }

    }else{
        printf("\n Registro nao existe !");
        }
    printf("\n Deseja editar mais um registro? \n");
    printf(" [1]SIM [2]NAO \n ");
    scanf("%d",&registros);

    system("cls");
    titulo();
}
    escolha();
}/*fim da função editar */

/*função que consulta lista pela posição */
int consulta_lista_pos(Lista *li, int pos, FUNC *fun){
    if(li == NULL || pos <= 0){
        return 0;
    }
    ELEM *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }if(no == NULL){
        return 0;
    }else{
        *fun = no->dados;
        return 1;
    }
} /*fim da função consulta_pos*/

/* função para ler o tamanho da lista */
int tamLista(Lista *li){
    if(li == NULL){
        return 0;
    }
    int acum = 0;
    ELEM *no = *li;
    while(no != NULL){
        acum++;
        no = no->prox;
    }
    return acum;
} /* fim da função tamanho da lista */

/* função que exibe os valores na lista */
void exibir(){
    system("color 02");
	int x, i, y,opc;
    FUNC fun;
	y = tamLista(&li);

	if(y>0){
        for(i = 1; i <= y; i++){
            x = consulta_lista_pos(&li , i , &fun);
            if(x){
                 printf("\n ID :%d",fun.ID);
                 printf("\n Nome : %s",fun.nome);
                 printf(" Endereco: %s",fun.endereco);
                 printf(" Idade: %d anos",fun.idade);
                 printf("\n Salario: R$ %.2f",fun.salario);
                 mostra_codigo_cbo(&cb, fun.cargo);
                 printf("\n ---------------------------------------------------------------- ");
            }
        }
    }else{
        printf("\n Nao há registros no sistema \n");
    }
    escolha();
    } /* fim da função exibir lista */

void exibirSalario(){
    system("color 01");
	int x, i, y,opc;
    FUNC fun;
	y = tamLista(&li);
	float minimo, maximo;
    printf("\n  Digite o valor minimo da faixa salarial : R$ ");
    scanf("%f",&minimo);
    printf("\n  Digite o valor maximo da faixa salarial : R$ ");
    scanf("%f",&maximo);
	if(y>0){
        for(i = 1; i <= y; i++){
            consultaSalario(&li , i ,minimo, maximo, &fun);
            if(x){
                 printf("\n ID :%d",fun.ID);
                 printf("\n Nome : %s",fun.nome);
                 printf(" Endereco: %s",fun.endereco);
                 printf(" Idade: %d anos",fun.idade);
                 printf("\n Salario: R$ %.2f",fun.salario);
                 mostra_codigo_cbo(&cb, fun.cargo);
                 printf("\n ---------------------------------------------------------------- ");
            }
        }
    }else{
        printf("\n Nao ha registros no sistema \n");
    }
    escolha();

} /* fim da função exibir lista */



/* funçao que destrói a lista completamente*/
void apaga_lista(Lista *li){
    if(*li != NULL){
        ELEM *no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
} /*fim da função apaga lista */

void sair(){
	system("cls");
	system("color 60");
	titulo();
    mata_listas();

    printf("\n Ate breve, volte sempre !! \n\n ");
    system("pause");
    exit(0);
}

void mata_listas(){
     apaga_cbo_lista(&cb);
     apaga_lista(&li);
}

/* funções que correspondem a lista ligada de CBO */

void implementa_cbo(){
    inicializadorcbo(&cb);
}
/* função que captura lê a lista.txt */
void inicializadorcbo(CBOLista *cb){
    char capturar[100];
    CARGO func;
    char x;
    int i = 0,j = 0;
    FILE *cbo;

    cbo = fopen("lista.txt","r");
    if(cbo == NULL){
        printf("Erro Porra\n"); /*essa expressão é pq sempre dava erro qndo testava*/
        system("pause");
        exit(1);
    }
    do{
        x = fgetc(cbo);
        if(x != '\n'){
            capturar[i] = x;
            i++;
        }else{
            j = strlen(capturar);
            separacao(capturar, &func);
            insere_cbo_ordenada(cb,func);
            for(i = 0;i <= j;i++){
                capturar[i] = '\0';
            }
            j = 0;
            i = 0;   /*reposiciona os cursores*/
        }
    }while(!feof(cbo));
    fclose(cbo);
}

CBOLista *cria_cbo_lista(){
    CBOLista *cbo;
    cbo = (CBOLista*) malloc(sizeof(CBOLista));
    if(cbo != NULL){
        *cbo = NULL;
    }
    return cbo;
}

void apaga_cbo_lista(CBOLista *cbo){
    if(cbo != NULL){
        ELEMCBO *no;
        while((*cbo) != NULL){
            no = *cbo;
            *cbo = (*cbo)->proxcbo;
            free(no);
        }
        free(cbo);
    }
}

int CBOListaVazia(CBOLista *cbo){
    if(cbo == NULL){
        return 1;
    }
    if(*cbo == NULL){
        return 1;
    }
    return 0;
}

int tamCBOLista(CBOLista *cbo){
    if(cbo == NULL){
        return 0;
    }
    int acum = 0;
    ELEMCBO *no = *cbo;
    while(no != NULL){
        acum++;
        no = no -> proxcbo;
    }
    return acum;
}

int insere_cbo_ordenada(CBOLista *cbo, CARGO al){
    if(cbo == NULL){
        return 0;
    }
    ELEMCBO *no = (ELEMCBO*) malloc(sizeof(ELEMCBO));
    if(no == NULL){
        return 0;
    }
    no -> dadoscbo = al;
    if(CBOListaVazia(cbo)){
        no -> proxcbo = (*cbo);
        *cbo = no;
        return 1;
    }else{
        ELEMCBO *ant, *atual = *cbo;
        while(atual != NULL && atual -> dadoscbo.codigocbo < al.codigocbo){
            ant = atual;
            atual = atual -> proxcbo;
        }
        if(atual == *cbo){
            no -> proxcbo = (*cbo);
            *cbo = no;
        }else{
            no -> proxcbo = ant -> proxcbo;
            ant -> proxcbo = no;
        }

        return 1;
    }
}

int exibicao_cbo(CBOLista *cbo, int posicao, CARGO *func){
    if(cbo == NULL || posicao <= 0){
        return 0;
    }
    ELEMCBO *no = *cbo;
    int i = 1;
    while (no != NULL && i < posicao){
        no = no -> proxcbo;
        i++;
    }
    if(no == NULL){
        return 0;
    }else{
        *func = no -> dadoscbo;
        return 1;
    }
}

int exibicao_cbo_cod(CBOLista *cbo, int codigo, CARGO *func){
    if(cbo == NULL){
        return 0;
    }
    ELEMCBO *no = *cbo;
    while(no != NULL && no -> dadoscbo.codigocbo != codigo){
        no = no -> proxcbo;
    }
    if(no == NULL){
        return 0;
    }else{
        *func = no -> dadoscbo;
        return 1;
    }
}

int escolha_cargo_cbo(CBOLista *cb){
    int x = 0, i = 0, crg = 0;
    CARGO exibir,escolha;
    x = tamCBOLista(cb);
    printf("\n Escolha o cargo do funcionario: \n");
    for(i = 1;i <= x;i++){
        exibicao_cbo(cb , i , &exibir);
        printf(" Escolher %d |Cargo: %s\n", i , exibir.descricaocbo);
    }

    do{
        printf("\n Escolha a opcao de cargo desejado: ");
        scanf("%d",&crg);
        if(crg < 1 || crg > x){
            printf("\n Valor nao existente tente novamente");
        }else{
           exibicao_cbo(cb , crg , &escolha);
        }
    }while(crg < 1 || crg > x);
    return escolha.codigocbo;
}

int mostra_codigo_cbo(CBOLista *cb, int p){
    CARGO exibir,escolha;

    exibicao_cbo_cod(cb , p, &exibir);
    printf("\n Cargo: %s \n", exibir.descricaocbo);
}

void separacao(char *frase, CARGO *funcionario){
    char *codicbo;
    char *cargocbo;
    int NumCodCbo;
    codicbo = strtok(frase,";");
    cargocbo = strtok('\0',";");
    NumCodCbo = atoi(codicbo);
    funcionario->codigocbo = NumCodCbo;
    strcpy(funcionario->descricaocbo,cargocbo);
}


