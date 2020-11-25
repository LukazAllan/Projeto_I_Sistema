#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(_WIN32) || defined(_WIN64)
        const char* os = "cls";
#else
#ifdef __linux
        const char* os = "clear";
#else
        const char* os = "clear";
#endif
#endif

#define QTOBRAS 5 // Quantidade de Obras

typedef struct{
    int func1;
    int func2;
    int func3;
} funcs;

typedef struct {
    int result;
    // Estados
    // 999: Nada aqui
    // 0: Enviado aguardando resposta
    // 2: Visto
    //-1: Rejeitado
    // 1: Aceito;
    int f1;
    int f2;
    int f3;
} request;

typedef struct {
    int result;
    // Estados
    // 999: Nada aqui
    // 0: Enviado aguardando resposta
    // 2: Visto
    //-1: Rejeitado
    // 1: Aceito;
    int response;
    // Estados
    //-1: Não enviado
    // 0: Enviado aguardando resposta
    // 1: Retorno;
    char mat[20];
    int escolha;
    float precos[3]; // Contém preços de 3 fornecedores
} reqfor;

typedef struct{
    int on;
    // Estados:
    // 0: não obra,
    // 1: Obra em andamento,
    // 2: Obra finalizada e aguardando encerramento
    funcs func; // numero de funcionários
    int prog; 
    // Referente ao progresso;
    // Estados:
    // -1             = esperando inicialização dos trabalhos,
    // 0              = iniciado, 
    // 0 < prog < 100 = progresso,
    // 100            = finalizado;
    float custoInicial;
    float custoFinal;
    float orc; // Orçamento, teto do gasto
    reqfor mobra;
    request fobra;
} obras;

// typedef struct{
//     obras obra[QTOBRAS];
// } state;

typedef struct{
    char email[24];
    char* senha[3];
    char nome[10];
    int func;
} log;

void clear(void);
void titulo(char* texto);
void imprime(char* msg, char* limiters, int spaces);
void msgput(char* msg, char* end);
int getTemObra(); //==> Retorna inteiro
int getArrayTemObra(int n);
int getNaoTemObra();
int getObraOn(int index);
int nao(int inteiro);
float getBalanco(int n);
float getfuncsalario(int n);
char* getInfo(int n);
obras obra[QTOBRAS];
FILE *fp;

int main() {
    // void setup()
    void clear(void);
    //state estado; // Guarda o estado do applicativo, independendo de usuário
    int i; // Iterador
    int iput; // Guarda input do usuario em int
    int iput1; // Guarda input do usuario em int
    int iput2; // Guarda input do usuario em int
    int iput3; // Guarda input do usuario em int
    int answ; // Guarda resposta do usuario em int
    int menu3 = 0;
    int menu2 = 0;
    int sel = 0; // Iterador
    int logado = 0; // Estados: 0 == não logado; 1 == logado;
    int not_email = 1;
    int senha_aceita = 0; // Estados: 0 == senha não aceita/processo de verificação; 1 == senha aceita;
    int email_aceito = 0; // Estados: 0 == email não aceito/processo de verificação; 1 == email aceito;
    int key = 0; // guarda o índice da conta para login, quando logado para operações na conta;
    int on[] = {1,0};
    // on[0]: Estados: 0 == fora do main loop/fim do programa; 1 == retorna ao login;
    // on[1]: Estados: 0 == dentro do loop das funções/logado; 1 == fora do loop/logout;
    int so = -1; // Se encarrega do inteiro que vai no índice do "sis[so]";
    float fput; // Guarda input do usuario em float 
    float fput1; // Guarda input do usuario em float 
    float fput2; // Guarda input do usuario em float 
    float fput3; // Guarda input do usuario em float 
    char email[24];
    char senha[24];
    char file_name[20];
    char q = 'z'; // Guarda o caractere dos menus 
    char* sis[2] = {"cls", "clear"}; //Limpa o prompt Estados: 0 -> "cls" == para WIN; 1 -> "clear" == para UNIX & BSD;
    log login[4];

    // Def
    strcpy(login[1].email, "allanlucas@empresa.com");
    strcpy(login[3].email, "alanamorais@empresa.com");
    strcpy(login[2].email, "lirielterto@empresa.com");
    strcpy(login[0].email, "lucaslins@iesp.edu.br");

    strcpy(login[1].senha, "123");
    strcpy(login[3].senha, "321");
    strcpy(login[2].senha, "012");
    strcpy(login[0].senha, "000");

    login[1].func = 1; //"Engenheiro"
    login[3].func = 3; //"Fornecedor"
    login[2].func = 2; //"Mestre de Obras"
    login[0].func = 0; //"Gestor UNIESP"

    strcpy(login[1].nome, "Allan");
    strcpy(login[3].nome, "Alana");
    strcpy(login[2].nome, "Liriel");
    strcpy(login[0].nome, "Lucas");

    for (i = 0; i < QTOBRAS; i++){
        obra[i].on = 0;
        obra[i].fobra.result = 999;
        obra[i].mobra.result = 999;
        obra[i].mobra.response = -1;
    }

    
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= TESTES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=--
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // for (i = 0; i < 4; i++)
    //     printf("%d.\n\t%s\n\t%s\n\t%d\n\t%s\n", i, login[i].email, login[i].senha, login[i].func, login[i].nome);
    
    // obra[0].on = 1;   
    // obra[0].prog = -1.0;
    // obra[0].func.func1 = 40;
    // obra[0].func.func2 = 40;
    // obra[0].func.func3 = 40;
    // obra[0].custoInicial = getfuncsalario(1)*obra[0].func.func1 + getfuncsalario(2)*obra[0].func.func2 + getfuncsalario(3)*obra[0].func.func3 + 5000.00;
    // obra[0].custoFinal = obra[0].custoFinal;
    // obra[0].orc = obra[0].custoFinal + 4000;
    // obra[0].fobra.result = 0;
    // obra[0].fobra.f1 = 0;
    // obra[0].fobra.f2 = 5;
    // obra[0].fobra.f3 = 0;

    obra[1].on = 1;
    obra[1].prog = -1.0;
    obra[1].func.func1 = 120;
    obra[1].func.func2 = 100;
    obra[1].func.func3 = 50;
    obra[1].custoInicial = getfuncsalario(1)*obra[1].func.func1 + getfuncsalario(2)*obra[1].func.func2 + getfuncsalario(3)*obra[1].func.func3 + 3000.00;
    obra[1].custoFinal = obra[1].custoInicial;
    obra[1].orc = obra[1].custoFinal + 4000;
    obra[1].mobra.result = 0;
    obra[1].mobra.response = 1;
    // strcpy(obra[1].mobra.mat, "Cimento");
    obra[1].mobra.precos[0] = 200.99;
    obra[1].mobra.precos[1] = 100.99;
    obra[1].mobra.precos[2] = 150.99;
    
    obra[2].on = 1;   
    obra[2].prog = -1.0;
    obra[2].func.func1 = 200;
    obra[2].func.func2 = 90;
    obra[2].func.func3 = 130;
    obra[2].custoInicial = getfuncsalario(1)*obra[2].func.func1 + getfuncsalario(2)*obra[2].func.func2 + getfuncsalario(3)*obra[2].func.func3 + 4000.00;
    obra[2].custoFinal = getfuncsalario(1)*obra[2].func.func1 + getfuncsalario(2)*obra[2].func.func2 + getfuncsalario(3)*obra[2].func.func3 + 4000.00;
    obra[2].orc = obra[2].custoFinal + 4000;
    obra[2].mobra.result = 0;
    obra[2].mobra.response = 0;
    system(os);
    printf("%i\n", so);
    // void loop()
    while (on[0] != 0){
        // Login ----------------------------------------------------------------------------------------------------------------------
        while (logado == 0) {
            do{
                system(os);
                titulo("Digite seu e-mail: ");
                scanf("%s", email);

                for (i = 0; i < 4; i++) {
                    //printf("%s: %i\n", login[i], i);
                    if (strcmp(email, login[i].email) == 0) {
                        email_aceito = 1;
                        not_email = 0;
                        key = i;
                        i = 999;
                    }
                }
            
            } while (not_email == 1);
            
            i=0;
            //printf("%i\n", key);
            system(os);
            do{
                titulo(" ");
                if (i > 0) {
                    printf("Tente Novamente!\n");
                }
                i++;
                printf("Digite sua senha: ");
                scanf("%s", senha);
                if (strcmp(senha, login[key].senha) == 0) {
                    senha_aceita = 1;
                    logado = 1;
                    
                }
                system(os);
                //printf("\"%s\" - \"%s\" = %d\n", login[key].senha, senha, strcmp(senha, login[key].senha));
            } while ((senha_aceita == 0) && (i < 5));
        }
        // Fim do Login ---------------------------------------------------------------------------------------------------------------
        printf("Logado!");
        
        system(os);
        printf("Ola, %s!\nSeja bem-vindo(a), com o que posso ajudar?\n", login[key].nome);
        on[1] = 1;
        clear();
        if (login[key].func == 0) {
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= GESTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=--
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            int creatingObra;
            while (on[1] == 1){
                printf("Menu\n\tA. Criar obra Nova\tB. Verificar Obras\n\tZ. Deslogar\n%s~main> ", login[key].nome);
                scanf("%c", &q);
                clear();
                switch (q){
                    case 'a':
                    case 'A':
                        creatingObra = getNaoTemObra(obra);
                        if (creatingObra == -1){
                            printf("Limite Alcancado, nao e possivel criar mais uma obra.\n");
                        } else {
                            system(os);
                            // clear();
                            printf("Quantos funcionarios do tipo 1 serao empregados na obra?\n%s~main/cr_obra> Funcionarios: ", login[key].nome);
                            scanf("%d", &obra[creatingObra].func.func1);
                            system(os);
                            clear();
                            printf("Quantos funcionarios do tipo 2 serao empregados na obra?\n%s~main/cr_obra> Funcionarios: ", login[key].nome);
                            scanf("%d", &obra[creatingObra].func.func2);
                            system(os);
                            clear();
                            printf("Quantos funcionarios do tipo 3 serao empregados na obra?\n%s~main/cr_obra> Funcionarios: ", login[key].nome);
                            scanf("%d", &obra[creatingObra].func.func3);
                            system(os);
                            clear();
                            printf("Quanto dinheiro sera inicialmente destinado em materiais?\n%s~main/cr_obra> R$ ", login[key].nome);
                            scanf("%f", &fput);
                            system(os);
                            obra[creatingObra].custoInicial = getfuncsalario(1)*obra[creatingObra].func.func1 + getfuncsalario(2)*obra[creatingObra].func.func2 + getfuncsalario(3)*obra[creatingObra].func.func3 + fput;
                            obra[creatingObra].custoFinal = obra[creatingObra].custoInicial;
                            clear();
                            printf("Nesta obra o custo vale R$%.2f.\nQuanto dinheiro sera inicialmente destinado a mais, levando em conta,\neventuais perdas e contratacoes de novos funcionarios?\n%s~main/cr_obra> R$ ", obra[creatingObra].custoInicial, login[key].nome);
                            scanf("%f", &fput);
                            obra[creatingObra].orc = obra[creatingObra].custoInicial + fput;
                            fput = 0;
                            system(os);
                            clear();
                            obra[creatingObra].on = 1;
                            obra[creatingObra].prog = -1.0;
                            printf("OBRA CRIADA!!!\n");
                            // sleep(2);
                        }
                        
                        break;
                    
                    case 'b':
                        /* code */
                    case 'B':
                        for (i = 0; i < 5; i++){
                            printf("Obra %d\n", i+1);
                            if (obra[i].on == 0){
                                printf("Estado: VAZIO\n");
                            } else {
                                if (obra[i].on == 1){
                                    printf("Estado: EM ANDAMENTO\n");
                                } else if (obra[i].on == 2) {
                                    printf("Estado: AGURDANDO FINALIZACAO\n");
                                } else if ((obra[i].on > 2) || (obra[i].on < 0)){
                                    printf("Estado: ERRO ==> %d\n", obra[i].on);
                                }
                                printf("\tProgresso: %d%%\n\tOrcamento:     R$%.2f\n\tCusto Inicial: R$%.2f\n\tCusto Final:   R$%.2f\n\tFuncionarios:  %d pessoas\n", obra[i].prog, obra[i].orc, obra[i].custoInicial, obra[i].custoFinal, obra[i].func.func1 + obra[i].func.func2 + obra[i].func.func3);
                                if (getBalanco(i) > 0){
                                    printf("\tBalanco:       R$+%.2f\n", getBalanco(i));
                                } else {
                                    printf("\tBalanco:       R$%.2f\n", getBalanco(i));
                                }
                            }
                        }
                        break;
                    case 'z':
                        /* code */
                    case 'Z':
                        on[1] = 0;
                        printf("Deslogando....\n");
                        
                        break;
                    
                    default:
                        break;
                }
                if ((q != 'b') && (q != 'B')){
                    system(os);
                }
            }
            
        } else if (login[key].func == 1) {
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= ENGENHEIRO -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=--
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            while (on[1] == 1){
                printf("Menu\n\tA. Iniciar obras\tB. Contratar Funcionarios\n\tC. Pedidos      \tD. Verificar Custo de Obras\n\tZ. Deslogar\n%s~main> ", login[key].nome);
                scanf("%c", &q);
                clear();
                system(os);
                switch (q){
                    case 'a':
                        //code
                    case 'A':
                        printf("Verificando se o gestor comecou alguma obra...\n");
                        for (i = 0; i < QTOBRAS; i++) {
                            if (getArrayTemObra(i) == 1){
                                printf("Obra %i ativa esperando inicio!\n", i+1);
                                printf("%s~main/iniciar_obras> Dar inicio as obras? [s/n] ", login[key].nome);
                                scanf("%c", &q);
                                clear();
                                switch (q){
                                    case 's':
                                    case 'S':
                                        obra[i].prog = 0;
                                        printf("Inicio das obras! Obra %i iniciada\n", i+1);
                                        break;
                                    default:
                                        printf(" ");
                                        break;
                                }
                            } else {
                                printf("Obra %i inativa!\n", i+1);
                            }
                        }
                        break;
                    case 'b':
                    case 'B':
                        printf("Qual tipo de funcionario voce quer contratar?\n %s~main/ct_func> ", login[key].nome);
                        scanf("%d", &iput);
                        system(os);
                        printf("Quantos deles?\n%s~main/ct_func> ", login[key].nome);
                        scanf("%d", &iput1);
                        printf("Para qual obra? ");
                        scanf("%d", &iput2);
                        iput2 = iput2-1;
                        if (obra[iput2].on > 0){
                            printf("O impacto dessa decisao aumentara os custos:\n\tAntes:      R$%.2f\n\tAgora:     ⬆R$%.2f\n\tOrcamento:  R$%.2f\n", obra[iput2].custoFinal, obra[iput2].custoFinal + getfuncsalario(iput)*iput1, obra[iput2].orc);
                        } else {
                            printf("SELECIONE UMA OBRA ATIVA!!!\n");
                        }
                        iput = 999;
                        iput1 = 999;
                        iput2 = 999;
                        break;
                    case 'c':
                    case 'C':
                        while (menu2 == 0){
                            iput = 0;
                            printf("CAIXA DE MENSAGENS\n");
                            for (i = 0; i < QTOBRAS; i++){
                                if ((getObraOn(i) == 1) && ((obra[i].fobra.result == 0 ) || (obra[i].mobra.result == 0) || (obra[i].mobra.response == 0))){
                                    iput = iput + 1;
                                    printf("Obra %d tem pedidos pendentes!\n", i+1);
                                }
                            }
                            if (iput == 0){
                                printf("\tNao ha pedidos a serem atendidos\n");
                                break;
                            } else {
                                printf("De qual obra deseja ver os pedidos? 1 - 5, 6 volta\n%s~main/cx_msg> ", login[key].nome);
                                scanf("%d", &iput1);
                                printf("--------------------------------------------------------\n");
                                iput1 = iput1 - 1;
                                if (((0 <= iput1) || (iput1 < QTOBRAS)) && ((obra[i].fobra.result == 0 ) || (obra[i].mobra.result == 0) || (obra[i].mobra.response == 0))){
                                    iput2 = 0;
                                    while (iput2 != 3){
                                        printf("Pedidos:\n");
                                        if (obra[iput1].fobra.result != 999){
                                            printf("1. Funcionarios\n");
                                        }
                                        if (obra[iput1].mobra.result != 999){
                                            printf("2. Materiais\n");
                                        }
                                        printf("3. Voltar\n");
                                        printf("%s~main/cx_msg> O que verificar? ", login[key].nome);
                                        scanf("%d", &iput2);
                                        system(os);
                                        menu3 = 0;
                                        switch (iput2){
                                            case 1:
                                                while (menu3 == 0){
                                                    printf("Pedido:\n\tEstado: ");
                                                    switch (obra[iput1].fobra.result){
                                                        case 0:
                                                            printf("AGUARDANDO RESPOSTA");
                                                            break;
                                                        case 1:
                                                            printf("APROVADO");
                                                            break;
                                                        case -1:
                                                            printf("REPROVADO");
                                                            break;
                                                    }
                                                    printf("\n\tFuncionarios:\n\t  Tipo 1: %i\n\t  Tipo 2: %i\n\t  Tipo 3: %i", obra[iput1].fobra.f1, obra[iput1].fobra.f2, obra[iput1].fobra.f3);
                                                    printf("\n1. Responder\n2. Voltar\n%s~main/cx_msg>", login[key].nome);
                                                    scanf("%d", &iput3);
                                                    // system(so);
                                                    switch (iput3){
                                                        case 1:
                                                            printf("O impacto nos custos dessa obra serao mais R$%.2f\nCusto Final: R$%.2f\nOrcamento: R$%.2f\n", ((obra[iput1].fobra.f1 * getfuncsalario(1)) + (obra[iput1].fobra.f2 * getfuncsalario(2)) + (obra[iput1].fobra.f3 * getfuncsalario(3))), obra[iput1].custoFinal, obra[iput1].orc );
                                                            printf("%s~main/cx_msg> 0. Voltar | 1. Aceitar | 2. Declinar:", login[key].nome);
                                                            scanf("%d", &answ);
                                                            switch (answ){
                                                                case 1:
                                                                    obra[iput1].fobra.result = 1;
                                                                    menu3 = -1;
                                                                    iput2 = 3;
                                                                    break;
                                                                case 2:
                                                                    obra[iput1].fobra.result = -1;
                                                                    menu3 = -1;
                                                                    iput2 = 3;
                                                                    break;
                                                                default:
                                                                    break;
                                                            }
                                                            break;
                                                        default:
                                                            menu3 = -1; // Voltando ao menu anterior alterando menu3
                                                            break;
                                                    }
                                                    system(os);
                                                }
                                                break;
                                            case 2:
                                                while (menu3 == 0){
                                                    printf("Pedido:\n\tEstado: ");
                                                    switch (obra[iput1].mobra.result){
                                                        case 0:
                                                            printf("AGUARDANDO RESPOSTA");
                                                            break;
                                                        case 1:
                                                            printf("APROVADO");
                                                            break;
                                                        case -1:
                                                            printf("REPROVADO");
                                                            break;
                                                    }
                                                    switch (obra[iput1].mobra.response){
                                                        case 0:
                                                            printf("\n\tCotacoes: Esperando resposta do fornecedor!\n");
                                                            break;
                                                        case 1:
                                                            printf("\n\tCotacoes:\n\t\tR$%.2f\n\t\tR$%.2f\n\t\tR$%.2f\n", obra[iput1].mobra.precos[0], obra[iput1].mobra.precos[1], obra[iput1].mobra.precos[2]);
                                                            break;
                                                        default:
                                                            printf("\n\tCotacoes: Peça uma cotacao ao fornecedor!\n");
                                                            break;
                                                    }
                                                    printf("\n1. Responder\t");
                                                    if (obra[iput1].mobra.response != 1){
                                                        printf("2. Pedir Cotacao\n3. Responder sem cotacao\t4. Voltar");
                                                    } else {
                                                        printf("4. Voltar");
                                                    }
                                                    printf("\n%s~main/cx_msg>", login[key].nome);
                                                    scanf("%d", &iput3);
                                                    system(os);
                                                    switch (iput3){
                                                        case 1:
                                                            printf("%s, esta decisao pode ter impacto no custo da obra.\nCotacoes: 1. R$%.2f 2. R$%.2f 3. R$%.2f\nCusto Atual: R$%.2f\nOrcamento: %.2f\nLembre-se que o custo nao pode passar do orcamento\npara nao tornar-se uma obra deficitaria!\n", login[key].nome, obra[iput1].mobra.precos[0], obra[iput1].mobra.precos[1], obra[iput1].mobra.precos[2], obra[iput1].custoFinal, obra[iput1].orc);
                                                            printf("Para aceitar, digite o numero da cotacao correspondente,\nPara rejeitar, digite 4.\nPara retornar, digite 0.\n%s~main/cx_msg> Resposta: ", login[key].nome);
                                                            scanf("%d", &answ);
                                                            switch (answ){
                                                                case 1:
                                                                    obra[iput1].custoFinal = obra[iput1].custoFinal + obra[iput1].mobra.precos[0];
                                                                    obra[iput1].mobra.result = 1;
                                                                    obra[iput1].mobra.escolha = answ-1;
                                                                    menu3 = -1;
                                                                    iput2 = 3;
                                                                    break;
                                                                case 2:
                                                                    obra[iput1].custoFinal = obra[iput1].custoFinal + obra[iput1].mobra.precos[1];
                                                                    obra[iput1].mobra.result = 1;
                                                                    menu3 = -1;
                                                                    iput2 = 3;
                                                                    break;
                                                                case 3:
                                                                    obra[iput1].custoFinal = obra[iput1].custoFinal + obra[iput1].mobra.precos[2];
                                                                    obra[iput1].mobra.result = 1;
                                                                    menu3 = -1;
                                                                    iput2 = 3;
                                                                    break;
                                                                case 4:
                                                                    obra[iput1].mobra.result = -1;
                                                                    menu3 = -1;
                                                                    iput2 = 3;
                                                                    break;
                                                                default:
                                                                    //code
                                                                    break;
                                                            }
                                                            break;
                                                        case 2:
                                                            obra[iput1].mobra.response = 0;
                                                            printf("Solicitacao Enviada!\n");
                                                            break;
                                                        case 3:
                                                            printf("Nesta secao voce so podera negar o pedido.\nVolte, se nao quiser fazer isso.\n0. Voltar\t1. Continuar\n%s~main/cx_msg> Resposta: ", login[key].nome);
                                                            scanf("%d", &answ);
                                                            switch (answ){
                                                                case 0:
                                                                    menu3 = -1;
                                                                    iput2 = 3;
                                                                    break;
                                                                case 1:
                                                                    obra[iput1].mobra.response = -1;
                                                                    printf("PEDIDO NEGADO!\n");
                                                                    menu3 = -1;
                                                                    iput2 = 3;
                                                                    break;
                                                                default:
                                                                    //code
                                                                    break;
                                                            }
                                                            break;
                                                        case 4:
                                                            menu3 = -1; // Voltando ao menu anterior alterando menu3
                                                            break;
                                                    }
                                                    system(os);
                                                }
                                                break;
                                            default:
                                                break;
                                        }
                                    }
                                } else if (iput == 5){
                                    menu2 = -1;
                                }
                            }
                        }
                        break;
                    case 'd':
                    case 'D':
                        for (i = 0; i < 5; i++){
                            printf("Obra %d\n", i+1);
                            if (obra[i].on == 0){
                                printf("Estado: VAZIO\n");
                            } else {
                                if (obra[i].on == 1){
                                    printf("Estado: EM ANDAMENTO\n");
                                } else if (obra[i].on == 2) {
                                    printf("Estado: AGURDANDO FINALIZACAO\n");
                                } else if ((obra[i].on > 2) || (obra[i].on < 0)){
                                    printf("Estado: ERRO ==> %d\n", obra[i].on);
                                }
                                printf("\tProgresso: %d%%\n\tOrcamento:     R$%.2f\n\tCusto Inicial: R$%.2f\n\tCusto Final:   R$%.2f\n\tFuncionarios:  %d pessoas\n", obra[i].prog, obra[i].orc, obra[i].custoInicial, obra[i].custoFinal, obra[i].func.func1 + obra[i].func.func2 + obra[i].func.func3);
                                if (getBalanco(i) > 0){
                                    printf("\tBalanco:       R$+%.2f\n", getBalanco(i));
                                } else {
                                    printf("\tBalanco:       R$%.2f\n", getBalanco(i));
                                }
                            }
                        }
                        break;
                    case 'z':
                    case 'Z':
                        on[1] = 0;
                        printf("Deslogando....\n");
                        
                        break;
                }
                clear();
            }
        } else if (login[key].func == 2) {
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- MESTRE DE OBRAS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=--
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            
            while (on[1] == 1){
                printf("Menu\n\tA. Fazer Pedido de Materiais\tB. Fazer Pedido de Funcionarios\n\tC. Andamento dos Pedidos\tZ. Deslogar\n%s~main> ", login[key].nome);
                scanf("%c", &q);
                clear();
                switch (q){
                    case 'a':
                    case 'A':
                        while (menu3 >= 0){
                            printf("Pedido de Materiais ----------------------------------------------------\n");
                            iput = 0;
                            for (i = 0; i < QTOBRAS; i++){
                                printf("Na Obra %d,", i+1);
                                if ((getObraOn(i) == 1) && (obra[i].mobra.result == 999)){
                                    printf(" e possivel fazer um pedido", i, i+1);
                                    iput = iput + 1;
                                } else {
                                    printf(" nao e possivel fazer um pedido");
                                }
                                printf("\n");
                                // printf(" on = %i; mobra.result = %i; mobra.response = %i\n", obra[i].on, obra[i].mobra.result, obra[i].mobra.response);
                            }
                            printf("Digite o numero da obra para fazer pedidos ou 0 para voltar.\n%s~main/pedidos> ", login[key].nome);
                            scanf("%d", &iput1);
                            iput1 = iput1 -1;
                            if (iput1 <= 0){
                                menu3 = -1;
                                continue;
                            } else if (iput1 < QTOBRAS) {
                                printf("Para prosseguir voce dara o nome do material para o Engenheiro\nescolher se aceita ou o rejeita.\n");
                                printf("%s~main/pedidos/obra_%d>Material: ", login[key].nome, iput1+1);
                                scanf("%s", obra[key].mobra.mat);
                                obra[iput1].mobra.result = 0;
                            } else {
                                printf("ERROR INDEX NOT FOUND IN obra\n");
                                menu3 = -1;
                                continue;
                            }
                        }
                        break;
                    case 'b':
                    case 'B':
                        while (menu3 >= 0){
                            printf("Pedido de Materiais ----------------------------------------------------\n");
                            iput = 0;
                            for (i = 0; i < QTOBRAS; i++){
                                printf("Na Obra %d,", i+1);
                                if ((getObraOn(i) == 1) && (obra[i].mobra.result == 999)){
                                    printf(" e possivel fazer um pedido", i, i+1);
                                    iput = iput + 1;
                                } else {
                                    printf(" nao e possivel fazer um pedido");
                                }
                                printf("\n");
                                // printf(" on = %i; mobra.result = %i; mobra.response = %i\n", obra[i].on, obra[i].mobra.result, obra[i].mobra.response);
                            }
                            printf("Digite o numero da obra para fazer pedidos ou 0 para voltar.\n%s~main/pedidos> ", login[key].nome);
                            scanf("%d", &iput1);
                            iput1 = iput1 -1;
                            if (iput1 <= 0){
                                menu3 = -1;
                                continue;
                            } else if (iput1 < QTOBRAS) {
                                printf("Para prosseguir voce dara o nome do material para o Engenheiro\nescolher se aceita ou o rejeita.\n");
                                printf("%s~main/pedidos/obra_%d>Material: ", login[key].nome, iput1+1);
                                scanf("%s", obra[key].mobra.mat);
                                obra[iput1].mobra.result = 0;
                            } else {
                                printf("ERROR INDEX NOT FOUND IN obra\n");
                                menu3 = -1;
                                continue;
                            }
                        }
                        break;
                    case 'c':
                    case 'C':
                        menu2 = 0;
                        while (menu2 >= 0){
                            printf("Pedido de Materiais ----------------------------------------------------\n");
                            for (i = 0; i < QTOBRAS; i++){
                                printf("Na Obra %d, ", i+1);
                                if ((getObraOn(i) == 1) && (obra[i].mobra.result != 0) && (obra[i].fobra.result != 0) && (obra[i].mobra.result != 999) && (obra[i].fobra.result != 999)){
                                    printf("tem ");
                                } else{
                                    printf("nao tem ");
                                }
                                printf("atualizacoes.\n");
                                // printf(" on = %i; mobra.result = %i; mobra.response = %i\n", obra[i].on, obra[i].mobra.result, obra[i].mobra.response);
                            }
                            printf("Digite o numero da obra para olhar atualizacoes ou 0 para voltar.\n%s~main/check> ", login[key].nome);
                            scanf("%d", &iput1);
                            iput1 = iput1 -1;
                            menu3 = 0;
                            if (iput1 <= 0){
                                menu2 = -1;
                                continue;
                            } else if (iput1 < QTOBRAS) {
                                while (menu3 == 0){
                                    printf("Obra %d\n\t1. Pedido de Material: %s\n\t2. Pedido de Funcionarios: %s\n", iput1, getInfo(obra[iput1].mobra.result), getInfo(obra[iput1].fobra.result));
                                    printf("Caso o pedido tenha status \"aprovado\" ou \"reprovado\",\nDigite o numero correspondente, ou 0 para voltar ");
                                    scanf("%d", &iput2);
                                    switch (iput2){
                                        case 1:
                                            if ((obra[iput1].mobra.result == 1) || (obra[iput1].mobra.result == -1)){
                                                printf("Vamos imprimir um recibo do pedido.\nSempre escrevemos o arquivo com mesmo nome,\nentao salve em outro lugar.\n");
                                                fp = fopen("recibo.txt", "w+");
                                                fprintf(fp, "-----------------------------------\n");
                                                fprintf(fp, "Obra %d\n", iput1);
                                                fprintf(fp, "Pedido de Material\n\n\t");
                                                fprintf(fp, "Resultado: %s", getInfo(obra[iput1].mobra.result));
                                                fprintf(fp, "\n\tMaterial: %s\n", obra[iput1].mobra.mat);
                                                if (obra[iput1].mobra.result == 1){
                                                    fprintf(fp, "\tValor: R$ %.2f\n", obra[iput1].mobra.precos[obra[iput1].mobra.escolha]);
                                                }
                                                fprintf(fp, "-----------------------------------\n");
                                                fclose(fp);
                                                printf("Pedido Resetado! Agora voce pode fazer outro pedido para o engenheiro.\n");
                                                obra[iput1].mobra.result = 999;
                                                obra[iput1].mobra.response = -1;
                                                strcpy(obra[iput1].mobra.mat, "nada");
                                                obra[iput1].mobra.escolha = -1;
                                                obra[iput1].mobra.precos[0] = 0;
                                                obra[iput1].mobra.precos[1] = 0;
                                                obra[iput1].mobra.precos[2] = 0;
                                            } else {
                                                break;
                                            }
                                            break;
                                        case 2:
                                            if ((obra[iput1].fobra.result == 1) || (obra[iput1].fobra.result == -1)){
                                                printf("Vamos imprimir um recibo do pedido.\nSempre escrevemos o arquivo com mesmo nome,\nentao salve em outro lugar.\n");
                                                fp = fopen("recibo.txt", "w+");
                                                fprintf(fp, "-----------------------------------\n");
                                                fprintf(fp, "Obra %d\n", iput1);
                                                fprintf(fp, "Pedido de Material\n\n\tResultado: %s", getInfo(obra[iput1].fobra.result));
                                                fprintf(fp, "\n\tF. tipo 1: %d", obra[iput1].fobra.f1);
                                                fprintf(fp, "\n\tF. tipo 2: %d", obra[iput1].fobra.f2);
                                                fprintf(fp, "\n\tF. tipo 3: %d", obra[iput1].fobra.f3);
                                                fprintf(fp, "\n-----------------------------------\n");
                                                fclose(fp);
                                                printf("Pedido Resetado! Agora voce pode fazer outro pedido para o engenheiro.\n");
                                                obra[iput1].fobra.result = 999;
                                                obra[iput1].fobra.f1 = 0;
                                                obra[iput1].fobra.f2 = 0;
                                                obra[iput1].fobra.f2 = 0;
                                            } else {
                                                break;
                                            }
                                            break;
                                        default:
                                            //code
                                            break;
                                    }
                                }
                            } else {
                                menu2 = -1;
                                continue;
                            }
                        }
                        break;
                    case 'z':
                    case 'Z':
                        on[1] = 0;
                        printf("Deslogando....\n");
                        
                        break;
                }
                system(os);
            }
        } else if (login[key].func == 3) {
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= FORNECEDOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=--
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            
            while (on[1] == 1){
                printf("Menu\n\tA. Verificar Pedidos\tZ. Deslogar\n%s~main> ", login[key].nome);
                scanf("%c", &q);
                clear();
                menu3 = 0;
                // system(so);
                switch (q){
                    case 'a':
                    case 'A':
                        while (menu3 >= 0){
                            printf("Pedido de Materiais ----------------------------------------------------\n");
                            iput = 0;
                            for (i = 0; i < QTOBRAS; i++){
                                printf("Obra %d", i+1);
                                if ((getObraOn(i) == 1) && (obra[i].mobra.result == 0) && (obra[i].mobra.response == 0)){
                                    printf(" necessita de materiais", i, i+1);
                                    iput = iput + 1;
                                } else {
                                    printf(", nada por aqui.");
                                }
                                printf("\n");
                                // printf(" on = %i; mobra.result = %i; mobra.response = %i\n", obra[i].on, obra[i].mobra.result, obra[i].mobra.response);
                            }
                            if (iput == 0){
                                printf("Nao ha pedidos hoje!\n");
                                menu3 = -1;
                                continue;
                            }
                            printf("Entre no pedido com o numero da obra ou 0 para voltar.\n%s~main/pedidos> ", login[key].nome);
                            scanf("%d", &iput1);
                            iput1 = iput1 -1;
                            if (iput1 <= 0){
                                menu3 = -1;
                                continue;
                            } else if (iput1 < QTOBRAS) {
                                printf("Para prosseguir voce dara tres valores para o Engenheiro\nescolher se aceita um dos valores ou os rejeita.\n");
                                printf("%s~main/pedidos/obra_%d>O valor da primeira fonte: ", login[key].nome, iput1+1);
                                scanf("%f", &fput1);
                                printf("%s~main/pedidos/obra_%d>O valor da segunda fonte: ", login[key].nome, iput1+1);
                                scanf("%f", &fput2);
                                printf("%s~main/pedidos/obra_%d>O valor da terceira fonte: ", login[key].nome, iput1+1);
                                scanf("%f", &fput3);
                                obra[iput1].mobra.precos[0] = fput1;
                                obra[iput1].mobra.precos[1] = fput2;
                                obra[iput1].mobra.precos[2] = fput3;
                                obra[iput1].mobra.response = 1;
                            } else {
                                printf("ERROR INDEX NOT FOUND IN obra\n");
                                menu3 = -1;
                                continue;
                            }
                        }
                        break;
                    case 'z':
                    case 'Z':
                        on[1] = 0;
                        printf("Deslogando....\n");
                        
                        break;
                }
                system(os);
            }
        } else {
            printf("ERROR FATAL!!! USER TYPE NOT RECOGNIZED!!!\n");
        }
        titulo("Deseja logar novamente? [s/n]: ");
        scanf("%c", &q);
        switch (q){
            case 'S':
            case 's':
                logado = 0;
                not_email = 1;
                email_aceito = 0;
                senha_aceita = 0;
                key = 0;
                on[0] = 1;
                on[1] = 0;
                break;

            default:
                titulo("Tem certeza? Iremos desligar o sistema, e voce nao tera mais acesso ao sistema\nSIM ou NAO [s/n] ");
                clear();
                scanf("%c", &q);
                if ((q == 's') || (q == 'S')) {
                    on[0] = 0;
                    printf("Volte Sempre, %s!!!\n", login[key].nome);
                }
                break;
        }
        
    }
    return 0;
}

void clear(void){
  char c;
  while(((c=getchar()) != '\n') && (c != EOF));
}

int getTemObra(){
    int qwertyuiop = 0; // Iterador
    for (; qwertyuiop < 5; qwertyuiop++){
        if (obra[qwertyuiop].on > 0)
            return qwertyuiop;
    }
    return -1;
}

int getArrayTemObra(int n){
    if ((0 <= n) && (n < 5)){
        return obra[n].on;
    } else {
        return -1;
    }
}

int getNaoTemObra(){
    int qwertyuiop = 0; // Iterador
    for (; qwertyuiop < 5; qwertyuiop++){
        if (obra[qwertyuiop].on == 0)
            return qwertyuiop;
    }
    return -1;
}

int getObraOn(int indice){
    /*Esta função retorna o estado da Obra.
    :param int n: recebe o índice da obra.
    :return: Estado 1, obra ativa; -1, inativa;*/
    if ((obra[indice].on != 0) && (obra[indice].on <= 2) && (obra[indice].prog >= 0)){
        return 1;
    }
    return -1;
}

int nao(int inteiro){
    if (inteiro == 0)
        return 1;
    else 
        return 0;
}

void titulo(char* texto){
    printf("--------------------------\nSistema Alana Construcoes\n--------------------------\n");
    printf("%s\n", texto);
}

float getfuncsalario(int n){
    if (n == 1){
        return 1079.00;
    } else if (n == 2) {
        return 1915.32;
    } else if (n == 3)
    {
        return 2500.65;
    }
    return 0;
}

float getBalanco(int n){
    /*Esta função retorna o balanço da Obra.
    :param state est: recebe o estado das obras.
    :param int n: recebe o índice da obra.
    :return: balanço*/
    return obra[n].orc - obra[n].custoFinal;
}


char* getInfo(int n){
    char* resposta;
    if (n == 999){
        resposta = "NAO REQUISITADO";
    } else if (n == 0){
        resposta = "ESPERANDO RESPOSTA";
    } else if (n == 1){
        resposta = "APROVADO";
    } else if (n == -1){
        resposta = "REPROVADO";
    }
    return &resposta;
}

void imprime(char* msg, char* limiters, int spaces){
    if (strlen(msg) > 0){
        int it;
        if (strlen(limiters) == 0){
            limiters = "\n";
        }
        for (it = 0; it <= strlen(msg); it++){
            if (msg[it] != ' '){
                printf("%c", msg[it]);
            } else if ((it%spaces < 3) && ((spaces-3) > it%spaces)) {
                printf("");
            } else {
                printf(" ");
            }
            if ((it%spaces == 0) && (it != 0)){
                printf("%s", limiters);
            }
        }
    }
}

void msgput(char* msg, char* end){
    if (strcmp(end, "") == 0){
        end = "\n>>> ";
    }
    printf("%s %s", msg, end);
}