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
    fseek(history,0L,SEEK_END);
    fprintf(history,"%s\n",str);
    fflush(history);
}