#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    int on;
    int func;
    float custo;
} obra;

typedef struct {
    char* titulo;
    char corpo[144];
} email;

typedef struct{
    email emails[10];
} caixa_de_email;

typedef struct{
    obra obras[5];
    caixa_de_email usuarios[4];

} state;

typedef struct{
    char email[24];
    char senha[3];
    char nome[10];
    int func;
} log;

void clear(void);
int cls(char sis);

int main() {
    // void setup()
    void clear(void);
    state estado;
    int i;
    int logado = 0;
    int not_email = 1;
    int email_aceito = 0;
    int senha_aceita = 0;
    int key = 0;
    int on[] = {1,0};
    int menu;
    char email[24];
    char senha[24];
    char q = 'z';
    char so = '0';
    char* sis[2] = {"cls", "clear"};
    log login[4];

    strcpy(login[1].email, "allanlucas@empresa.com");
    strcpy(login[1].senha, "123");
    login[1].func = 1; //"Engenheiro"
    strcpy(login[1].nome, "Allan");

    strcpy(login[3].email, "alanamorais@empresa.com");
    strcpy(login[3].senha, "321");
    login[3].func = 3; //"Fornecedor"
    strcpy(login[3].nome, "Alana");

    strcpy(login[2].email, "lirielterto@empresa.com");
    strcpy(login[2].senha, "012");
    login[2].func = 2; //"Mestre de Obras"
    strcpy(login[2].nome, "Liriel");

    strcpy(login[0].email, "lucaslins@iesp.edu.br");
    strcpy(login[0].senha, "000");
    login[0].func = 0; //"Gestor UNIESP"
    strcpy(login[0].nome, "Lucas");
    
    while (3 > 2)
    {
        printf("Qual SO:\n\tW. Windows\n\tL. Linux/Mac\nletra em minúsculo >>>");
        scanf("%c", &so);
        clear();
        if ((so == 'w') || (so == 'l')){
            break;
        }
    }
    printf("%d\n", so);
    // void loop()
    cls(so);
    while (on[0] != 0){
        // Login
        while (logado == 0) {
            do{
                printf("--------------------------\nSistema Alana Construções\n--------------------------\n");
                printf("Digite seu e-mail: ");
                scanf("%s", &email);

                for (i = 0; i < 4; i++) {
                    //printf("%s: %i\n", login[i], i);
                    if (strcmp(email, login[i].email) == 0) {
                        email_aceito = 1;
                        not_email = 0;
                        key = i;
                        i = 999;
                    }
                    printf("email aceito %d\n", email_aceito);
                }
            
            } while (not_email == 1);
            
            i=0;
            //printf("%i\n", key);

            do{
                if (i > 0) {
                    printf("Tente Novamente!\n");
                }
                i++;
                cls(so);
                printf("--------------------------\nSistema Alana Construções\n--------------------------\n");
                printf("Digite sua senha: ");
                scanf("%s", &senha);
                if (strcmp(senha, login[key].senha) == 0) {
                    senha_aceita = 1;
                    logado = 1;
                    
                }
            } while ((senha_aceita == 0) && (i < 5));
            
            cls(so);
        }
        
        printf("Logado!");
        sleep(3);
        cls(so);
        printf("Olá, %s!\nBem vindo de volta, com o que posso ajudar?\n", login[key].nome);
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
                    printf("Criamos uma nova Obra!!!\n");
                    break;
                case 'z':
                    /* code */
                case 'Z':
                    on[1] = 0;
                    printf("Deslogando....\n");
                    sleep(3);
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
            logado = 0;
            not_email = 1;
            email_aceito = 0;
            senha_aceita = 0;
            key = 0;
            on[0] = 1;
            on[1] = 0;
            break;
        }
        
    }
    return 0;
}

void clear(void){
  char c;
  while(((c=getchar()) != '\n') && (c != EOF));
}

int cls(char sis){
    if (sis == 'w') {
        system("cls");
    } else if (sis == 'l') {
        system("clear");
    } else {
        printf("WTF!!\n");
        return -1;
    }
    return 0;
}