#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprime(char* msg, char* limiters, int spaces);

int main() {
    int i;
    char txt[144]; //"Mussum Ipsum, cacilds vidis litro abertis. Nao sou faixa preta cumpadi, sou preto inteiris, inteiris. Admodum accumsan disputationi eu sit. Vide electram sadipscing et per. Vehicula non. Ut sed ex eros. Vivamus sit amet nibh non tellus tristique interdum. Paisis, filhis, espiritis santis.";
    printf("TXT: ");
    scanf("%s", txt);
    printf("%s\t", txt);
    imprime(txt, "\n\t", 70);
    return 0;
}
void imprime(char* msg, char* limiters, int spaces){
    if (strlen(msg) > 0){
        int it;
        if (strlen(limiters)==0){
            limiters = "\n";
        }
        for (it = 0; it < strlen(msg); it++){
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