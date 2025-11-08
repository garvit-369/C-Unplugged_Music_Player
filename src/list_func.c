#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list_func.h"


void print_album_list(FILE *file) {
    fseek(file, 0L, SEEK_SET);

    char step[500];
    int lines_read = 0;

    while (fgets(step, 500, file) != NULL) {

        if (strlen(step) <= 1) {continue;}

        lines_read++;
        printf("%s", step);
    }

    if (lines_read == 0) {
        printf("No Albums Found!\n");
    }

    printf("\n");
    fseek(file, 0L, SEEK_END);
}




void print_list(FILE *file) {
    fseek(file, 0L, SEEK_SET);

    char step[500];
    int lines_read = 0;

    while (fgets(step, 500, file) != NULL) {

        if (strlen(step) <= 1) {continue;}

        lines_read++;
        char *token;
        char *name, *artist, *duration_str;

        token = strtok(step, ",");
        name = token;
        token = strtok(NULL, ",");
        artist = token;
        token = strtok(NULL, ",\n");
        duration_str = token;

        int duration = atoi(duration_str);

        printf("%s\t\t%s\t\t%d\n", name, artist, duration);
    }

    if (lines_read == 0) {
        printf("Empty List!\n");
    }

    printf("\n");
    fseek(file, 0L, SEEK_END);
}




int check_presence(FILE *file, char song[]) {
    fseek(file,0L,SEEK_SET);

    char dum[500];
    while (fgets(dum,500,file)!=NULL) {
        char *token=strtok(dum,",\n");
        if (token!=NULL && strcmp(token,song)==0) {
            return 1;
        }
    }
    fseek(file,0L,SEEK_SET);
    return 0;
}


void append_list(FILE *library, FILE *list, char song[]) {
    fseek(library, 0L, SEEK_SET);
    
    if (check_presence(list, song)==1) {
        printf("Song already present!\n");
        return;
    }
    
    char dum[500];
    char dum_copy[500];
    int flag=0;
    
    while (fgets(dum, 500, library) != NULL) {
        strcpy(dum_copy,dum); 

        char *token=strtok(dum,",\n");
        if (token != NULL && strcmp(token,song)==0) {flag=1;break;}
    }

    if (flag==0) {
        printf("Song not present in Library!\n");
        return;
    }

    fseek(list, 0L, SEEK_END);
    fprintf(list, "%s", dum_copy);
    fflush(list);
}


void append_album_playlist(FILE *playlist,FILE *album) {
    fseek(playlist, 0L, SEEK_SET);
    fseek(album, 0L, SEEK_SET);

    char dum[500];
    char dum_copy[500];

    while(fgets(dum,500,album)!=NULL) {
        strcpy(dum_copy,dum);
        char *tok=strtok(dum,",");
        
        if (check_presence(playlist, tok)==1) continue;

        fseek(playlist,0L,SEEK_END);
        fprintf(playlist, "%s", dum_copy);
    }
    fflush(playlist);

}





void remove_item(char *list_file_name, char item[]) {
    FILE *tmp=fopen("src/temp.txt", "w"); 
    FILE *list=fopen(list_file_name,"r");

    char dum[500];
    int item_found = 0;

    while (fgets(dum,500,list)!=NULL) {
        
        char dum_copy[500];
        strcpy(dum_copy, dum); 
        
        char *token = strtok(dum,",\n");

        if (token != NULL && strcmp(token, item) == 0) {
            item_found = 1;
        } else {
            fputs(dum_copy,tmp);
        }
    }
    fclose(tmp);
    fclose(list);

    if (item_found==1) {
        remove(list_file_name);                 
        rename("src/temp.txt", list_file_name);   
        printf("Removed %s successfully!\n", item);
    } else {
        remove("src/temp.txt");
        printf("%s was not present.\n", item);
    }
}

void create_album(FILE *album_list,char album_name[]) {
    fseek(album_list,0L,SEEK_END);
    fprintf(album_list,"%s\n",album_name);
    fflush(album_list);
    char location[270]="src/albums/";
    strcat(location,album_name);
    strcat(location,".csv");
    FILE* fptr=fopen(location,"w");
    fclose(fptr);
}