#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gestor() {
    /*Esta função corresponde ao cargo de gestor*/
    FILE *fp = fopen("gestor.txt", "r");
    if (fp == NULL){
        printf("File not open error\n");
        return -1;
    }
    
    return 0;
}

int eng() {
    /*Esta função corresponde ao cargo de engenheiro*/
    
    return 0;
}

int main() {
    int i, logado = 0, not_email = 1, email_aceito = 0, senha_aceita = 0, key = 0;
    int info_p_linha = 3;
    char email[24], senha[24];
    //                             "e-mail", "senha", "função"
    char* login[] = {"allanlucas@empresa.com", "123", "E",
                     "alanamorais@empresa.com", "321", "F",
                     "lirielterto@empresa.com", "012", "M",
                     "lucaslins@iesp.edu.br", "000", "G"
                    };
    
    // Login
    while (logado == 0) {
        do{
            printf("Digite seu e-mail: ");
            scanf("%s", &email);

            for (i = 0; i < 12; i=i+info_p_linha) {
                //printf("%s: %i\n", login[i], i);
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
        //printf("%i\n", key);

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
    
    if (strcmp(login[key+2], "G") == 0) {
        gestor();
    } else if (strcmp(login[key+2], "E") == 0) {
        eng();
    } else {
        printf("ERROR FATAL!!! USER TYPE NOT RECOGNIZED!!!\n");
    }
    return 0;
}