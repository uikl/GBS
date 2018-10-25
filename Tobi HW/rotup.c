#include <stdio.h>
#include <unistd.h>

int main(){
    char eingabe[300];
    read(0,eingabe,300);
    int length = 300;
    char original[300];
    for(int i=0;i<300;i++){
        original[i] = eingabe[i];
    }
    for(int i=0;i<=300;i++){
        if(eingabe[i] >= 'a' && eingabe[i] <= 'z'){
            eingabe[i] = eingabe[i] - 'a' + 'A';
        }
        if(eingabe[i] < 'A' || eingabe[i] > 'Z'){
            length = i;
            break;
        }
    }

    int lenge = 0;
    for(int i=0;i<=300;i++){
        if(original[i] =='\n'){
                lenge = i;
        }


    }
    char ausgabe2[lenge +1];
    for(int i=0;i<lenge;i++){
        ausgabe2[i] = original[i];
    }
    ausgabe2[lenge] = '\0';

    char ausgabe[length+1];
    for(int i=0;i<length;i++){
        ausgabe[i] = eingabe[i];
    }
    ausgabe[length] = '\0';

    for(int i=0;i<length;i++){
        ausgabe[i] = ((ausgabe[i] - 'A' + 13) % 26) + 'A';
    }


    printf("Hallo: %s -- %s\n",ausgabe2,ausgabe);
}