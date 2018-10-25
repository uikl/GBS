#include <stdio.h>


void hexdump (FILE *output, char *buffer, int length){
    for(int i=0;i<length;i++){
        //Puffer ofset alle 16 Zeichen
        if(i%16 == 0){
            printf("%06x : ",i);
        }
        //Schreibt die chars
        printf("%02x ",buffer[i]);
        //am Ende
        if((i+1)%16 == 0){
            char stuck[17];
            stuck[16] = '\0';
            int count = 0;
            for(int k=i-15;k<=i;k++){
                if(buffer[k] >= 32 && buffer[k] <=126){
                    stuck[count] = buffer[k];
                }
                else{
                    stuck[count] = '.';
                }
                count++;
            }
            printf("  %s\n",stuck);
        }
    }
    for(int i=0;i<16 - length%16;i++){
        printf("   ");
    }
    int lenge = length%16 +1;
    char stuck1[lenge];
    stuck1[lenge-1] = '\0';
    int count = 0;
    for(int i=16*(length/16);i<length;i++){
        if(buffer[i] >= 32 && buffer[i] <=126){
            stuck1[count] = buffer[i];
        }
        else{
            stuck1[count] = '.';
        }
        count++;
    }
    printf("  %s\n",stuck1);

}
















