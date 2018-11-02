#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void print_string (char *data){
    printf("%s",data);
}



/*int main(){
    list_t *list = list_init();
    struct list_elem *eins = list_insert(list,"eins ");
    struct list_elem *zwei = list_insert(list,"zwei ");
    struct list_elem *drei = list_append(list,"drei ");
    struct list_elem *vier = list_insert(list,"vier ");
    struct list_elem *funf = list_insert(list,"fünf ");
    list_remove(list,eins);
    struct list_elem *sechs = list_append(list,"sechs ");
    list_remove(list,sechs);
    list_print(list,print_string);
    
    list_finit(list);
    list = list_init();
    list_append(list,"neu1 ");
    list_append(list,"neu2 ");
    list_append(list,"neu3 ");
    list_append(list,"neu4 ");
    list_append(list,"neu5 ");
    list_print(list,print_string);

    
}*/
//cd Desktop/Hausaufgaben/Informatik Betriebssystem

int main (int argc , char *argv[] , char *envp[]) {
    list_t *list;
    if((list = list_init()) == NULL) {
        perror("Cannot allocate memory");
        exit(-1);
    } 

    for(int i=1;i<argc;i++){
        if(!strcmp(argv[i],"-i")){
            if(list_insert(list,argv[++i]) == NULL) {
                perror("Cannot allocate memory");
                exit(-1);
            }
        }
        else if(!strcmp(argv[i],"-r")){
            struct list_elem *gefunden = list_find(list,argv[++i],strcmp);
            if(!gefunden){
                printf("Konnte ""%s"" nicht finden\n", argv[i]);
            }
            else{
                list_remove(list,gefunden);
            }
        }
        else if(!strcmp(argv[i],"-a")){
            if(list_append(list,argv[++i]) == NULL) {
                perror("Cannot allocate memory");
                exit(-1);
            }
        }
        else{
            printf("wrong format\n");
        }
    }
    list_print(list,print_string);
    exit(0);
     
}
