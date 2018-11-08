#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sys/wait.h>



int main(int argc , char *argv[] , char *envp[]){

    int waitTime;       //Variable, die die dem Program mitgegebene Zeit speichern soll
    if(argc > 1){                           //Checkt, ob es ein 2 Argument gibt
        waitTime = atoi(argv[1]);           //Übergebene Zeit wird in waitTime gepspeichert
                                            //Kein Check, ob es eine Zahl ist, wenn es keine Zahl ist steht in waitTime 0
    }
    else{
        perror("No time to wait specified!");   //Fehlermeldung wenn es kein Argument gibt
        exit(-1);
    }

    
    

   pid_t pidReturn = fork();                    //Erzeugt Kind Prozess; bei dem Vater steht hier die PID des Kindes, bei dem Kind 0


   //Vater Code
   if(pidReturn){   //Bei dem Vater steht hier die pid des kindes => nicht null
       time_t timeNow = time(0);                //Holt sich die aktuelle Zeit
       printf("Start: %s",ctime(&timeNow));     //Gibt die aktuelle Zeit aus
       wait(NULL);                              //Wartet solange, bis ein Kind terminiert
       timeNow = time(0);                       //Holt sich wieder die aktuelle Zeit
       printf("Ende: %s",ctime(&timeNow));      //Gibt sie wieder aus
   }


   //Kind Code
   if(!pidReturn){  //Im Kind steht in der PID return 0, so erkennt man das Kind
        for(int i=1;i<=waitTime;i++){                               //läuft von 1 bis zur angegebenen Zeit hoch
           printf("%d %d %d\n",(int)getpid(),(int)getppid(),i);     //gibt dies eigene pid, die ppid und die zähler aus
           sleep(1);                                                //"Schläft" eine Sekunde
        }
        printf("Exit-Code: %d\n",((int)getpid() + waitTime)%100);   //Gibt den Exit-Code + (eigen pid + waitTime)%100 aus
   }



}