#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char eingabe[256];              //Speicherort der Eingabe (max Länge 255)
    char exitText[] = "exit\n";     //Speicherort des Wortes, welches die while Schleife bricht

    while(1){
        fgets(eingabe,256,stdin);   
        if(!strncmp(eingabe, exitText,6)){
            break;
        }
        system(eingabe);
    }
}