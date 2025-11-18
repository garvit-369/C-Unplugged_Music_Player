#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list_func.h"


void print_album_list(FILE *file) {
    fseek(file,0L,SEEK_SET);

    char step[500];
    int lines_read = 0;
    int count=1;
    while (fgets(step,500,file) != NULL) {

        if (strlen(step)<=1) {continue;}
        char *token=strtok(step,",\n");
        lines_read++;
        printf("%d) %s\n",count,token);
        count++;
    }

    if (lines_read==0) {
        printf("No Albums Found!\n");
    }

    printf("\n");
}




void print_list(FILE *file) {
    fseek(file, 0L, SEEK_SET);

    char step[500];
    int lines_read = 0;
    int count=1;
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

        printf("%d) %s\t\t%s\t\t%d\n", count, name, artist, duration);
        count++;
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


void append_list(FILE *library, FILE *list, int song_index) {
    fseek(library, 0L, SEEK_SET);
    
    int current_index = 1;
    char dum[500];
    int found=0;

    while (fgets(dum, 500, library)!=NULL) {        
        if (current_index==song_index) {
            found=1;
            break;
        }
        current_index++;
    }
    if(found==0) {printf("Song not found!!\n");return;}

    fseek(list, 0L, SEEK_END);
    fprintf(list, "%s", dum);
    fflush(list);
    printf("\nSuccessfully Executed!!\n");
}

FILE *open_album_from_index(FILE *album_list, int album_index) {
    fseek(album_list, 0L, SEEK_SET);

    int current_index = 1;
    char dum[500];
    int found=0;

    while (fgets(dum, 500, album_list)!=NULL) {        
        if (current_index==album_index) {
            found=1;
            break;
        }
        current_index++;
    }
    if(found==0) {printf("Album not found!!\n");return NULL;}

    char location[270] = "src/albums/";
    char unique_filename[100];
    char *album_name=strtok(dum,",\n");
    char *id=strtok(NULL,",\n");
    sprintf(unique_filename, "%s#%s.csv",album_name,id);
    strcat(location, unique_filename);
    return fopen(location, "r+");
}

void album_location_from_index(FILE *album_list, int album_index, char *location) {
    fseek(album_list, 0L, SEEK_SET);

    int current_index = 1;
    char dum[500];
    int found=0;

    while (fgets(dum, 500, album_list)!=NULL) {        
        if (current_index==album_index) {
            found=1;
            break;
        }
        current_index++;
    }
    if(found==0) {printf("Album not found!!\n");return;}

    char unique_filename[100];
    char *album_name=strtok(dum,",\n");
    char *id=strtok(NULL,",\n");
    sprintf(unique_filename, "%s#%s.csv",album_name,id);
    strcat(location, unique_filename);
}

void item_name_from_index(FILE *album_list, int album_index, char *name) {
    fseek(album_list, 0L, SEEK_SET);

    int current_index = 1;
    char dum[500];
    int found=0;

    while (fgets(dum, 500, album_list)!=NULL) {        
        if (current_index==album_index) {
            found=1;
            break;
        }
        current_index++;
    }
    if(found==0) {printf("Item not found!!\n");return;}

    char unique_filename[100];
    char *album_name=strtok(dum,",\n");
    sprintf(unique_filename, "%s",album_name);
    strcat(name, unique_filename);
}

void append_album_playlist(FILE *playlist,FILE *album_list,int album_index) {
    FILE* fptr = open_album_from_index(album_list,album_index);
    fseek(fptr, 0L, SEEK_SET);
    char dum_copy[500];
    while(fgets(dum_copy,500,fptr)!=NULL) {
        fseek(playlist,0L,SEEK_END);
        fprintf(playlist, "%s", dum_copy);
    }
    fflush(playlist);
    fclose(fptr);
    printf("\nSuccessfully Executed!!\n");
}



void remove_song(char *list_file_name, int song_index) {
    FILE *tmp=fopen("src/temp.txt", "w"); 
    FILE *list=fopen(list_file_name,"r");

    int current_index = 1;
    char dum[500];
    int found=0;

    while (fgets(dum, 500, list) != NULL) {
        char dum_copy[500];
        strcpy(dum_copy, dum); 
        
        if (current_index==song_index) {
            found = 1;
        } else {
            fputs(dum_copy, tmp);
        }
        current_index++;
    }
    fclose(tmp);
    fclose(list);

    if (found==1) {
        remove(list_file_name);                 
        rename("src/temp.txt", list_file_name);
        printf("\nSuccessfully Executed!!\n");   
    } else {
        remove("src/temp.txt");
        printf("Item not found in the list!!\n");
    }
}

void create_album(FILE *album_list,char album_name[]) {
    fseek(album_list,0L,SEEK_SET);

    char line[500];
    int id=0;
    
    while (fgets(line, 500, album_list)!=NULL) {
        char temp_line[500];
        strcpy(temp_line,line);
        char *token = strtok(temp_line,",\n");
        if (token!=NULL && strcmp(token,album_name)==0) {
            token=strtok(NULL, ",\n");
            if (token!=NULL) {
                int current_id = atoi(token);
                if (current_id > id) {
                    id = current_id;
                }
            }
        }
    }
    id++;
    
    fseek(album_list, 0L, SEEK_END);
    fprintf(album_list, "%s,%d\n", album_name,id);
    fflush(album_list);
    char location[270] = "src/albums/";
    char unique_filename[100];
    sprintf(unique_filename, "%s#%d.csv",album_name,id);
    strcat(location, unique_filename);
    FILE* fptr = fopen(location, "w");
    fclose(fptr);
}