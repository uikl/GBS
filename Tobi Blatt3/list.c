#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sys/wait.h>
#include "list.h"


list_t *list_init(){
    list_t *list = malloc(sizeof(list_t));
    list->first = NULL;
    return list;
}
void list_insert(list_t *list,pid_t pid){
    struct list_elem *element = malloc(sizeof(struct list_elem));
    element->next = list->first;
    element->pid = pid;
    list->first = element;
}

void list_removeFirst(list_t *list){
    struct list_elem *tester = list->first;
    if(tester){
        list->first = tester->next;
        free(tester);
        return;
    }

}

void list_finit(list_t *list){
    if(!list->first){
        free(list);
    }
    else{
        printf("In list first steht noch ein pointer der nicht NULL ist");
    }

}

