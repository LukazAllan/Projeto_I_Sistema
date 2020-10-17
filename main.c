#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int i, logado = 0, not_email = 1, email_aceito = 0, senha_aceita = 0, key = 0;
    char* email[24], senha[24];
    char* login[] = {"allanlucas@empresa.com", "123",
                     "alanamorais@empresa.com", "321",
                     "lirielterto@empresa.com", "012",
                     "lucaslins@iesp.edu.br", "000"
                    };
    
    // Login
    while (logado == 0) {
        do{
            printf("Digite seu e-mail: ");
            scanf("%s", &email);
            for (i = 0; i < 8; i=i+2) {
                if (strcmp(email, login[i]) == 0) {
                    email_aceito = 1;
                    not_email = 0;
                    key = i;
                }
                if (email_aceito == 1) {
                    i = 999;
                }
            }
        
        } while (not_email == 1);
        
        i=0;
        printf("%i\n", key);

        do{
            if (i > 0) {
                printf("Tente Novamente!\n");
            }
            i++;
            printf("Digite sua senha: ");
            scanf("%s", &senha);
            if (strcmp(senha, login[key+1]) == 0) {
                senha_aceita = 1;
                logado = 1;
                printf("Logado!\n");
            }
        } while ((senha_aceita == 0) && (i < 5));
    }
    printf("Dentro\n");
    return 0;
}