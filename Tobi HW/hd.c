#include <stdio.h>

void hexdump (FILE *output, char *buffer, int length);
int size(char *buffer);

int main(int argc, char *argv[]){
    if(argc < 2){
        return 0,
    }
    for(int i=1;i<argc;i++){
        hexdump(NULL,argv[i],size(argv[i]));
        if(i+1<argc){
            printf("\n");
        }
    }
    return 0;
}


int size(char *buffer){
    for(int i=0;1;i++){
        if(buffer[i] == '\0'){
            return i+1;
        }
    }
}