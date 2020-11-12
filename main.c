#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

typedef struct{
    int on; // 0 = não obra, 1 = Obra em andamento, 2 = Obra finalizada e aguardando encerramento
    int func; // numero de funcionários
    float custo;
} obras;

typedef struct {
    char* titulo;
    char corpo[144];
} email;

typedef struct{
    email emails[10];
} caixa_de_email;

typedef struct{
    obras obra[5];
    caixa_de_email usuarios[4];

} state;

typedef struct{
    char email[24];
    char* senha[3];
    char nome[10];
    int func;
} log;

void clear(void);
int temObra(state est);
int naotemObra(state est);
int nao(int inteiro);

int main() {
    // void setup()
    setlocale(LC_ALL,"");
    void clear(void);
    state estado; // Guarda o estado do applicativo, independendo de usuário
    int i; // Iterador
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

    for (i = 0; i < 4; i++)
        estado.obra[i].on = 0;

    // for (i = 0; i < 4; i++)
    //     printf("%d.\n\t%s\n\t%s\n\t%d\n\t%s\n", i, login[i].email, login[i].senha, login[i].func, login[i].nome);
    
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
                printf("--------------------------\nSistema Alana Construcoes\n--------------------------\n");
                printf("Digite seu e-mail: ");
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
                printf("--------------------------\nSistema Alana Construcoes\n--------------------------\n");
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
        printf("Ola, %s!\nBem vindo de volta, com o que posso ajudar?\n", login[key].nome);
        on[1] = 1;
        clear();
        if (login[key].func == 0) {
            //gestor();
            while (on[1] == 1){
                printf("Menu\n\tA. Criar obra Nova\n\tZ. Deslogar\n>>> ");
                scanf("%c", &q);
                clear();
                switch (q)
                {
                case 'a':
                    /* code */
                case 'A':
                    if (naotemObra(estado) == -1){
                        printf("Limite Alcancado, nao e possivel criar mais uma obra.\n");
                    } else {
                        printf("OBRA CRIADA!!!\n");
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
                system("cls");
            }
            
        } else if (login[key].func == 1) {
            //eng();
        } else {
            printf("ERROR FATAL!!! USER TYPE NOT RECOGNIZED!!!\n");
        }

        printf("DESEJA SAIR [s/n]: ");
        scanf("%c", &q);
        switch (q){
          case 's':
            on[0] = 0;
            printf("Volte Sempre, %s!!!\n", login[key].nome);
            break;

          default:
            break;
        //     logado = 0;
        //     not_email = 1;
        //     email_aceito = 0;
        //     senha_aceita = 0;
        //     key = 0;
        //     on[0] = 1;
        //     on[1] = 0;
        }
        
    }
    return 0;
}

void clear(void){
  char c;
  while(((c=getchar()) != '\n') && (c != EOF));
}

int temObra(state est){
    int qwertyuiop = 0; // Iterador
    for (; qwertyuiop < 5; qwertyuiop++){
        if (est.obra[qwertyuiop].on > 0)
            return qwertyuiop;
    }
    return -1;
}

int naotemObra(state est){
    int qwertyuiop = 0; // Iterador
    for (; qwertyuiop < 5; qwertyuiop++){
        if (est.obra[qwertyuiop].on == 0)
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