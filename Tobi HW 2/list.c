#include "list.h"
#include <stdlib.h>
#include <stdio.h>

list_t *list_init (){                   
    list_t *list;                       //Erzeugt einen Pointer, der auf ein list_t element zeigt
    list = malloc(sizeof(list_t));      //Reserviert soviel Speicher, wie list_t benötigt; der zurückgegebene Pointer
    list->first = NULL;
    list->last = NULL;
                                        //wird in list gespeichert => list zeigt jetzt auf den reservierten Bereich
    return list;                        //Gibt den Pointer auf den reservierten Bereich zurück
}

struct list_elem *list_insert (list_t *list, char *data){
    struct list_elem *element = malloc(sizeof(struct list_elem));   //Erzeugt einen Pointer auf ein list_elem, dieser Pointer
                                                                    //zeigt auf ein großgenugen reservierten Speicherbereich
    if(!element){
        return NULL;
    }
    element->next = list->first;                                   //In dem neu erzeugten list_elem wird der next pointer
                                                                   //auf das zuvor vorne stehende Objekt gesetzt
    element->data = data;                                           //Setzt die daten des neuen objekts
    list->first = element;
    if(!list->last){
        list->last = element;
    }
    return element;
}


struct list_elem *list_append (list_t *list, char *data){
    struct list_elem *element = malloc(sizeof(struct list_elem));   //Erzeugt einen Pointer auf ein list_elem, dieser Pointer
                                                                    //zeigt auf ein großgenugen reservierten Speicherbereich
    if(!element){
        return NULL;
    }
    element->next = NULL;                                           //es gibt kein nächstes Element beim letzten Element
    element->data = data;
    if(!list->last){
        list->first = element;
        list->last = element;
    }
    else{
        list->last->next = element;                                     //das vorher letzte element zeigt jetzt auf das neu erzeugte
        list->last = element;
    }
    return element;
}

int list_remove(list_t *list, struct list_elem *elem){
    struct list_elem *tester;               //Erzeugt einen Pointer, der im folgenden durch alle Elemente durchzeigt
    tester = list->first;                   //zu Beginn zeigt der tester auf das erste Element
    if(tester && tester == elem){          //Schaut, ob das zu suchende Element gleich das erste Element ist
        list->first = list->first->next;    //Referenz auf das Objekt wird gelöscht, first zeigt jetzt auf 2 Objekt
        return 0;
    }
    if(tester){                            //Das erste Element der Liste darf nicht null sein
        while(tester->next){                 //solange das nächste Element des testers nicht null ist
            if(tester->next==elem){          //Wenn das nächste Element des Tester gleich das zu suchende Objekt ist
                //Löschen von dem Element?? -> einfach nur aus der Lister entfernen ohne Daten zu löschen?
                tester->next = tester->next->next;     //Die Referenz auf das gesuchte Objekt wird "übersprungen"
                return 0;
            }   
            tester = tester->next;
        }
    }
    return -1;  //nicht gefunden
}

void list_finit(list_t *list){
    struct list_elem *current = list->first;
    struct list_elem *next;
    while(current){
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void list_print (list_t *list, void (*print_elem) (char *)){
    struct list_elem *current = list->first;
    int count = 1;
    while(current){
        printf("%d:",count);
        print_elem(current->data);
        printf("\n");
        current = current->next;
        count++;
    }
}


struct list_elem *list_find(list_t *list, char *data, int (*cmp_elem) (const char *, const char *)){
    struct list_elem *tester;
    tester = list->first;
    int result;
    while(tester){
        result = cmp_elem(tester->data,data);
        if(!result){
            return tester;
        }
        tester = tester->next;
    }
    return NULL; //wurde nicht gefunden
}