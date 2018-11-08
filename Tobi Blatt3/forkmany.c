#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sys/wait.h>
#include "list.h"



int main(int argc , char *argv[] , char *envp[]){

    int k=10;   //default
    int n=1;    //default
    int random = 0; //default 0 => kein random
    int option;
    while((option=getopt(argc,argv,"k:n:r"))!=-1){
        switch(option){
            case 'k':k = atoi(optarg);break;
            case 'n':n = atoi(optarg);break;
            case 'r':random = 1;break;
            default:break;
        }
    }

    pid_t pidReturn;
    list_t *list;               //In diese Liste werden die erzeugten Kinder gehängt
    list = list_init();

    for(int i=0;i<n;i++){
        pidReturn = fork();                     //Bei dem Vater steht hier die PID des Kindes, bei dem Kind 0
        if(!pidReturn){                         //Bricht die Schleife sofort für Kinder ab => kein unendliches forken..
            break;
        }
        list_insert(list,pidReturn);            //hängt die pid des erzeugten Kindes in die Liste
    }
    //########################################################
    //VATER CODE: Warten, bis alle Kinder fertig sind
    //#######################################################
   if(pidReturn){   //pidReturn ist für den Vater die pid des letzten erzeugten Kindes => nicht 0.
       time_t timeNow = time(0);                //Holt sich die aktuelle Zeit
       printf("Start: %s",ctime(&timeNow));     //Schreib diese Zeit in die Console
       struct list_elem *tester = list->first;  //holt sich das erste Element in der Liste (Dieses Element enthält die PID des zuletzt angehängten Processes)
       while(tester){                           //solange dies Liste nicht leer ist
           waitpid(tester->pid,NULL,0);         //Wartet auf genau diesen prozess, nur wenn der prozess terminiert geht es weiter
           list_removeFirst(list);       //löscht den Prozess auf den gerade gewartet wurde und der jetzt terminiert ist aus der Liste
           tester = list->first;                //Durch das löschen des Prozesses in Zeile vorher rückt der nächste Prozess in list->first (null wenn kein prozess mehr in Liste)
                                                //tester ist jetzt der nächste Prozess in der liste
        }   
       timeNow = time(0);                       //holt sich wieder die Zeit + ausgabe auf konsole
       printf("Ende: %s",ctime(&timeNow));
   }

    //########################################################
   //KIND CODE
   //#########################################################
   if(!pidReturn){                      //pidReturn = 0 => ist ein erzeugtes Kind
        if(random){                     //wenn random nicht 0 => random angeschaltet
            srand(getpid());            //jeder Kindprozess hat eine einzigartige pid => der seed für random ist für jeden Prozess unterschiedlich
                                        //  => rand liefert nicht für jeden die selber random number
            k = k/2 + rand() % (k+1);   // rand() ist irgeneine positive integerzahl => durch %(k+1) wird diese große Zahl auf eine zufällige Zahl zwischen 0,...,k heruntergebrochen
        }
        //Zählt im sekundentakt hoch und druckt die eigen pid, dann die ppid und die hochzählende zahl aus
        for(int i=1;i<=k;i++){          
           printf("%d %d %d\n",(int)getpid(),(int)getppid(),i);
           sleep(1);
        }
        //Druckt den Exit-Code zusammen mit der (pid + k)%100
        printf("Exit-Code: %d\n",((int)getpid() + k)%100);  //
   }



}