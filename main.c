#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char* mat;
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
int nao(int inteiro);
float getBalanco(int n);
float getfuncsalario(int n);
obras obra[QTOBRAS];

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
    int sel; // Iterador
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
    char email[24];
    char senha[24];
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
    }

    
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= TESTES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=--
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // for (i = 0; i < 4; i++)
    //     printf("%d.\n\t%s\n\t%s\n\t%d\n\t%s\n", i, login[i].email, login[i].senha, login[i].func, login[i].nome);
    
    // obra[0].on = 1;   
    // obra[0].prog = -1.0;
    // obra[0].func1 = 40;
    // obra[0].func.func2 = 40;
    // obra[0].func.func.func3 = 40;
    // obra[0].custoInicial = getfuncsalario(1)*obra[0].func.func1 + getfuncsalario(2)*obra[0].func.func2 + getfuncsalario(3)*obra[0].func.func3 + 5000.00;
    // obra[0].custoFinal = obra[0].custoFinal;
    // obra[0].orc = obra[0].custoFinal + 4000;

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
    strcpy(&obra[1].mobra.mat, "Cimento");
    obra[1].mobra.precos[0] = 200.99;
    obra[1].mobra.precos[1] = 100.99;
    obra[1].mobra.precos[2] = 150.99;
    
    // obra[2].on = 1;   
    // obra[2].prog = -1.0;
    // obra[2].func.func1 = 200;
    // obra[2].func.func2 = 90;
    // obra[2].func.func3 = 130;
    // obra[2].custoInicial = getfuncsalario(1)*obra[2].func.func1 + getfuncsalario(2)*obra[2].func.func2 + getfuncsalario(3)*obra[2].func.func3 + 4000.00;
    // obra[2].custoFinal = obra[2].custoFinal;
    // obra[2].orc = obra[2].custoFinal + 4000;

    while (3 > 2)
    {
        printf("Qual SO:\n\t0. Windows\n\t1. Linux/Mac\n>>>");
        scanf("%i", &so);
        // clear();
        if ((so == 0) || (so == 1)){
            break;
        }
    }
    printf("%i\n", so);
    // void loop()
    while (on[0] != 0){
        // Login ----------------------------------------------------------------------------------------------------------------------
        while (logado == 0) {
            do{
                system(sis[so]);
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
            system(sis[so]);
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
                system(sis[so]);
                printf("\"%s\" - \"%s\" = %d\n", login[key].senha, senha, strcmp(senha, login[key].senha));
            } while ((senha_aceita == 0) && (i < 5));
        }
        // Fim do Login ---------------------------------------------------------------------------------------------------------------
        printf("Logado!");
        //sleep(3);
        system(sis[so]);
        printf("Ola, %s!\nSeja bem-vindo, com o que posso ajudar?\n", login[key].nome);
        on[1] = 1;
        clear();
        if (login[key].func == 0) {
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= GESTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=--
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            int creatingObra;
            while (on[1] == 1){
                printf("Menu\n\tA. Criar obra Nova\tB. Verificar Obras\n\tZ. Deslogar\n>>> ");
                scanf("%c", &q);
                clear();
                switch (q)
                {
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
                                printf("Estado: AGURDANDO FINALIZAÇÃO\n");
                            } else if ((obra[i].on > 2) || (obra[i].on < 0)){
                                printf("Estado: ERRO ==> %d\n", obra[i].on);
                            }
                            printf("\tOrcamento:     R$%.2f\n\tCusto Inicial: R$%.2f\n\tCusto Final:   R$%.2f\n\tFuncionarios:  %d pessoas\n", obra[i].orc, obra[i].custoInicial, obra[i].custoFinal, obra[i].func.func1 + obra[i].func.func2 + obra[i].func.func3);
                            if (getBalanco(i) > 0){
                                printf("\tBalanço:       R$+%.2f\n", getBalanco(i));
                            } else {
                                printf("\tBalanço:       R$%.2f\n", getBalanco(i));
                            }
                        }
                    }
                    break;
                case 'a':
                    /* code */
                case 'A':
                    creatingObra = getNaoTemObra(obra);
                    if (creatingObra == -1){
                        printf("Limite Alcancado, nao e possivel criar mais uma obra.\n");
                    } else {
                        system(sis[so]);
                        // clear();
                        printf("Quantos funcionarios do tipo 1 serao empregados na obra?\nFuncionarios: ");
                        scanf("%d", &obra[creatingObra].func.func1);
                        system(sis[so]);
                        clear();
                        printf("Quantos funcionarios do tipo 2 serao empregados na obra?\nFuncionarios: ");
                        scanf("%d", &obra[creatingObra].func.func2);
                        system(sis[so]);
                        clear();
                        printf("Quantos funcionarios do tipo 3 serao empregados na obra?\nFuncionarios: ");
                        scanf("%d", &obra[creatingObra].func.func3);
                        system(sis[so]);
                        clear();
                        printf("Quanto dinheiro sera inicialmente destinado em materiais?\nR$ ");
                        scanf("%f", &fput);
                        system(sis[so]);
                        obra[creatingObra].custoInicial = getfuncsalario(1)*obra[creatingObra].func.func1 + getfuncsalario(2)*obra[creatingObra].func.func2 + getfuncsalario(3)*obra[creatingObra].func.func3 + fput;
                        obra[creatingObra].custoFinal = obra[creatingObra].custoInicial;
                        clear();
                        printf("Nesta obra o custo é R$%.2f.\nQuanto dinheiro sera inicialmente destinado a mais, levando em conta,\neventuais perdas e contratacoes de novos funcionarios?\nR$ ", obra[creatingObra].custoInicial);
                        scanf("%f", &fput);
                        obra[creatingObra].orc = obra[creatingObra].custoInicial + fput;
                        fput = 0;
                        system(sis[so]);
                        clear();
                        obra[creatingObra].on = 1;
                        obra[creatingObra].prog = -1.0;
                        printf("OBRA CRIADA!!!\n");
                        // sleep(2);
                    }
                    //sleep(3);
                    break;

                case 'z':
                    /* code */
                case 'Z':
                    on[1] = 0;
                    printf("Deslogando....\n");
                    //sleep(3);
                    break;
                
                default:
                    break;
                }
                if ((q != 'b') && (q != 'B')){
                    system(sis[so]);
                }
            }
            
        } else if (login[key].func == 1) {
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= ENGENHEIRO -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=--
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            while (on[1] == 1){
                printf("Menu\n\tA. Iniciar obras\tB. Contratar Funcionários\n\tC. Pedidos\tZ. Deslogar\n>>> ");
                scanf("%c", &q);
                clear();
                switch (q){
                    case 'a':
                        //code
                    case 'A':
                        printf("Verificando se o gestor comecou alguma obra...\n");
                        for (i = 0; i < QTOBRAS; i++) {
                            if (getArrayTemObra(i) == 1){
                                printf("Obra %i iniciada!\n", i+1);
                                printf("Dar início as obras? [s/n] >>>\n");
                                scanf("%c", &q);
                                switch (q){
                                    case 's':
                                    case 'S':
                                        obra[i].prog = 0;
                                        printf("Início das obras! Obra %i iniciada\n", i+1);
                                    default:
                                        printf(" ");
                                }
                            } else {
                                printf("Obra %i não iniciada!\n", i+1);
                            }
                        }
                        break;
                    case 'b':
                    case 'B':
                        printf("Qual tipo de funcionário você quer contratar?\n >>>");
                        scanf("%d", &iput);
                        system(sis[so]);
                        printf("Quantos deles?\n >>>");
                        scanf("%d", &iput1);
                        printf("Para qual obra? ");
                        scanf("%d", &iput2);
                        if (obra[iput2].on > 0){
                            printf("O impacto dessa decisão aumentará os custos:\n\tAntes:      R$%.2f\n\tAgora:     ⬆R$%.2f\n\tOrcamento:  R$%.2f\n", obra[iput2].custoFinal, obra[iput2].custoFinal + getfuncsalario(iput)*iput1, obra[iput2].orc);
                        } else {
                            printf("SELECIONE UMA OBRA ATIVA!!!\n");
                        }
                        iput = 999;
                        iput1 = 999;
                        iput2 = 999;
                        break;
                    case 'c':
                    case 'C':
                        iput = 0;
                        printf("CAIXA DE MENSAGENS\n");
                        for (i = 0; i < QTOBRAS; i++){
                            if ((obra[i].on == 1) && ((obra[i].fobra.result == 0 ) || (obra[i].mobra.result == 0) || (obra[i].mobra.response == 0))){
                                iput = iput + 1;
                                printf("Obra %d tem pedidos pendentes!\n", i+1);
                            }
                        }
                        if (iput == 0){
                            printf("\tNao há pedidos a serem atendidos\n");
                            break;
                        } else {
                            printf("De qual obra deseja ver os pedidos? 1 - 5\n>>> ");
                            scanf("%d", &iput1);
                            iput1 = iput1 - 1;
                            if ((obra[iput1].fobra.result != 999) || (obra[iput1].mobra.result != 999)){
                                iput2 = 0;
                                while (iput2 != 3){
                                    printf("Pedidos:\n");
                                    if (obra[iput1].fobra.result != 999){
                                        printf("1. Funcionários\n");
                                    }
                                    if (obra[iput1].mobra.result != 999){
                                        printf("2. Materiais\n");
                                    }
                                    printf("3. Voltar\n");
                                    printf("O que verificar? ");
                                    scanf("%d", &iput2);
                                    system(sis[so]);
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
                                                printf("\n\tFuncionários:\n\t  Tipo 1: %i\n\t  Tipo 2: %i\n\t  Tipo 3: %i", obra[iput1].fobra.f1, obra[iput1].fobra.f2, obra[iput1].fobra.f3);
                                                msgput("\n1. Responder\n2. Voltar", "");
                                                scanf("%d", &iput3);
                                                switch (iput3){
                                                    case 1:
                                                        printf("0. Voltar | 1. Aceitar | 2. Declinar: ");
                                                        scanf("%d", &answ);
                                                        switch (answ){
                                                            case 1:
                                                                obra[iput1].fobra.result = 1;
                                                                break;
                                                            case 2:
                                                                obra[iput1].fobra.result = -1;
                                                                break;
                                                            default:
                                                                break;
                                                        }
                                                        break;
                                                    default:
                                                        menu3 = -1; // Voltando ao menu anterior alterando menu3
                                                        break;
                                                }
                                                system(sis[so]);
                                            }
                                            menu3 = 0;
                                            break;
                                        case 2:
                                            while (menu3 == 0){
                                                printf("Pedido: %s\n\tEstado: ", obra[iput1].mobra.mat);
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
                                                        printf("\n\tCotações: Esperando resposta do fornecedor!\n");
                                                        break;
                                                    case 1:
                                                        printf("\n\tCotações:\n\t\tR$%.2f\n\t\tR$%.2f\n\t\tR$%.2f\n", obra[iput1].mobra.precos[0], obra[iput1].mobra.precos[1], obra[iput1].mobra.precos[2]);
                                                        break;
                                                    default:
                                                        printf("\n\tCotações: Peça uma cotação ao fornecedor!\n");
                                                        break;
                                                }
                                                printf("\n1. Responder\t");
                                                if (obra[iput1].mobra.response == 1){
                                                    printf("2. Pedir Cotação\n3. Responder sem cotacao\t4. Voltar");
                                                } else {
                                                    printf("3. Responder sem cotacao\n4. Voltar");
                                                }
                                                scanf("%d", &iput3);
                                                system(sis[so]);
                                                switch (iput3){
                                                    case 1:
                                                        printf("%s, esta decisao pode ter impacto no custo da obra.\nCotacoes: 1. R$%.2f 2. R$%.2f 3. R$%.2f\nCusto Atual: R$%.2f\nOrcamento: %.2f\nLembre-se que o custo nao pode passar do orcamento\npara nao tornar-se uma obra deficitaria!\n", login[key].nome, obra[iput1].mobra.precos[0], obra[iput1].mobra.precos[1], obra[iput1].mobra.precos[2], obra[iput1].custoFinal, obra[iput1].orc);
                                                        msgput("Para aceitar, digite o numero da cotacao correspondente,\nPara rejeitar, digite 4.\nPara retornar, digite 0.", "");
                                                        scanf("%d", &answ);
                                                        switch (answ){
                                                            case 1:
                                                                obra[iput1].custoFinal = obra[iput1].custoFinal + obra[iput1].mobra.precos[0];
                                                                obra[iput1].mobra.result = 1;
                                                                break;
                                                            case 2:
                                                                obra[iput1].custoFinal = obra[iput1].custoFinal + obra[iput1].mobra.precos[1];
                                                                obra[iput1].mobra.result = 1;
                                                                break;
                                                            case 3:
                                                                obra[iput1].custoFinal = obra[iput1].custoFinal + obra[iput1].mobra.precos[2];
                                                                obra[iput1].mobra.result = 1;
                                                                break;
                                                            case 4:
                                                                obra[iput1].mobra.result = -1;
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
                                                        msgput("Nesta secao voce so podera negar o pedido.\nVolte, se nao quiser fazer isso.\n0. Voltar\t1. Continuar", "");
                                                        scanf("%d", &answ);
                                                        switch (answ){
                                                            case 1:
                                                                obra[iput1].mobra.response = -1;
                                                                printf("PEDIDO NEGADO!\n");
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
                                                system(sis[so]);
                                            }
                                            menu3 = 0;
                                            break;
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        break;
                    case 'z':
                    case 'Z':
                        on[1] = 0;
                        printf("Deslogando....\n");
                        //sleep(3);
                        break;
                }
            }
        } else if (login[key].func == 2) {
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- MESTRE DE OBRAS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=--
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            
            while (on[1] == 1){
                printf("Menu\n\tA. Avançar obras\n\tZ. Deslogar\n>>> ");
                scanf("%c", &q);
                clear();
                switch (q){
                    case 'z':
                    case 'Z':
                        on[1] = 0;
                        printf("Deslogando....\n");
                        //sleep(3);
                        break;
                }
            }
        } else if (login[key].func == 3) {
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= FORNECEDOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=--
            // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
            
            while (on[1] == 1){
                printf("Nao ha nada o que fazer aqui... AINDA!\n\tZ. Deslogar\n>>> ");
                scanf("%c", &q);
                clear();
                switch (q){
                    case 'z':
                    case 'Z':
                        on[1] = 0;
                        printf("Deslogando....\n");
                        //sleep(3);
                        break;
                }
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
                titulo("Tem certeza? Iremos desligar o sistema, e voce não tera mais acesso ao sistema\nSIM ou NAO [s/n] ");
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
    return -1.0;
}

float getBalanco(int n){
    /*Esta função retorna o balanço da Obra.
    :param state est: recebe o estado das obras.
    :param int n: recebe o índice da obra.
    :return: balanço*/
    return obra[n].orc - obra[n].custoFinal;
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