#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "song_list_func.h"

song_list_ll* file_to_ll(song_list_ll *art, FILE *song_list) {
    fseek(song_list,0L,SEEK_SET);
    char dum[500];
    song_list_ll *head=art;
    song_list_ll *previous=art;

    if (fgets(dum, 500, song_list) == NULL) {
        free(head);
        head = NULL;
        return head;
    }

    char *token = strtok(dum, ",");
    if (token != NULL) strcpy(art->name, token);
    token = strtok(NULL, ",");
    if (token != NULL) strcpy(art->artist, token);
    token = strtok(NULL, ",\n");
    art->duration = atoi(token);

    while(fgets(dum,500,song_list)!=NULL) {
        art->next=(song_list_ll*)malloc(sizeof(song_list_ll));

        if (art->next == NULL) {
            printf("Error: Memory allocation failed!\n");
            art->next=head;
            head->prev=art;
            return head;
        }

        art=art->next;
        art->prev=previous;

        char *token=strtok(dum,",");
        strcpy(art->name,token);
        token=strtok(NULL,",");
        strcpy(art->artist,token);
        token=strtok(NULL,",\n");
        art->duration=atoi(token);

        previous=art;
        
    }
    art->next=head;
    head->prev=art;
    
    return head;
}

void play_song_list(song_list_ll *queue) {
    char cmd[20]; 

    while (1) { 
        printf("Playing song: %s\n", queue->name);
        invalid:
        printf("Enter command (NEXT, PREV, REPLAY, EXIT): ");
        scanf("%s", cmd);
        int c; 
        while ((c = getchar()) != '\n' && c != EOF);
        if (strcmp("NEXT", cmd) == 0) queue = queue->next;
        else if (strcmp("PREV", cmd) == 0) queue = queue->prev;
        else if (strcmp("REPLAY", cmd) == 0) {}
        else if (strcmp("EXIT", cmd) == 0) return;
        else {printf("Invalid Input\n");goto invalid;}
    }
}


void freeing_ll(song_list_ll *head) {
    if (head==NULL) {
        return;
    }
    song_list_ll *current=head;
    song_list_ll *next_node=NULL;
    do {
        next_node=current->next;
        free(current);
        current=next_node;
    } while (current!=head);
}