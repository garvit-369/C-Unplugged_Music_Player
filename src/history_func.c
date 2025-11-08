#include <stdio.h>
#include <string.h>

#include "history_func.h"

void print_log(FILE *history) {
    fseek(history,0L,SEEK_SET);
    char step[50];
    while(fgets(step,50,history)!=NULL) {
        printf("%s",step);
    }
    fseek(history,0L,SEEK_END);
}

void add_log(FILE *history, char str[]) {
    char dum[strlen(str)+1];
    strcpy(dum,str);
    char *cmnd=strtok(dum," ");
    if(strcmp(cmnd, "CREATE") == 0 || strcmp(cmnd, "APPEND") == 0 || 
        strcmp(cmnd, "REMOVE") == 0 || strcmp(cmnd, "DELETE") == 0 || 
        strcmp(cmnd, "ADD") == 0) {fputs("[COMMAND]\t",history);}

    else if (strcmp(cmnd, "PLAY") == 0 || strcmp(cmnd, "NEXT") == 0 || 
             strcmp(cmnd, "PREVIOUS") == 0 || strcmp(cmnd, "REPLAY") == 0)
            {fputs("[PLAY]\t",history);}

    else if (strcmp(cmnd,"EXIT")==0) {fputs("[EXIT]\t",history);}
    else if (strcmp(cmnd,"QUIT")==0) {fflush(history);return;}
    else {printf("[INVALID INPUT]\n");fflush(history);return;}

    fflush(history);

    fprintf(history,"%s",str);
}