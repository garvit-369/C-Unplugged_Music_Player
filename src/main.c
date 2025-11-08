#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "song_list_func.h"
#include "list_func.h"
#include "history_func.h"


int main() {
    FILE *history = fopen("src/history.log","a+");
    fputs("[---OPEN PROGRAM---]\n",history);
    FILE *library = fopen("src/library.csv","r");
    FILE *album_list = fopen("src/albums/albums_list.txt","r+");
    FILE *playlist = fopen("src/playlist.csv","w+");

    printf("\nWelcome To C-Unplugged:\n");
    printf("Note: Please ensure you read all the instructions provided in C-Unplugged/README.md\n\n");

    char cmd[500]=" ",cmd_dum[500];

    while (1) {
        printf("\nEnter Command: ");
        fgets(cmd,500,stdin);
        add_log(history,cmd);
        strcpy(cmd_dum,cmd);
        char *token=strtok(cmd_dum," ");

        if(strncmp(token,"QUIT",4)==0) {
            printf("Thanks for using!!\n\n");
            break;
        }


        else if(strcmp(token,"DISPLAY")==0) {
            token=strtok(NULL,"\n");
            if(strcmp(token,"library")==0) {print_list(library);printf("Successfully Executed...\n");}
            else if(strcmp(token,"albums")==0) {print_album_list(album_list);printf("Successfully Executed...\n");}
            else if(strcmp(token,"playlist")==0) {print_list(playlist);printf("Successfully Executed...\n");}
            else if(strcmp(token,"history")==0) {print_log(history);printf("Successfully Executed...\n");}

            else {
                char *token1=strtok(token, " ");
                if(strcmp(token1,"album")!=0) printf("Invalid Input\n");
                else {
                    token1=strtok(NULL,"\n");
                    if(check_presence(album_list,token1)==0) printf("No such album found.\n");
                    else {
                        char location[270]="src/albums/";
                        strcat(location,token1);
                        strcat(location,".csv");
                        FILE *album=fopen(location,"r");
                        print_list(album);
                        fclose(album);
                        printf("Successfully Executed...\n");
                    }
                }
            }
        }




        else if (strcmp(token,"PLAY")==0) {
            token=strtok(NULL,"\n");
            if(strcmp(token,"library")==0) {
                song_list_ll *queue = (song_list_ll*)malloc(sizeof(song_list_ll));
                queue=file_to_ll(queue,library);
                if(queue!=NULL) {play_song_list(queue);printf("Successfully Executed...\n");freeing_ll(queue);}
                else {printf("The album is empty.\n");}
            }
            else if(strcmp(token,"playlist")==0) {
                song_list_ll *queue = (song_list_ll*)malloc(sizeof(song_list_ll));
                queue=file_to_ll(queue,playlist);
                if(queue != NULL) {play_song_list(queue);printf("Successfully Executed...\n");freeing_ll(queue);}
                else {printf("The playlist is empty.\n");}
            }
            else {
                char *token1=strtok(token," ");
                if(strcmp(token1,"album")==0) {
                    token1=strtok(NULL,"\n");
                    if(check_presence(album_list,token1)==0) printf("No such album found.\n");
                    else {
                        char location[270]="src/albums/";
                        strcat(location,token1);
                        strcat(location,".csv");
                        FILE *album=fopen(location,"r");

                        song_list_ll *queue = (song_list_ll*)malloc(sizeof(song_list_ll));
                        queue=file_to_ll(queue,album);
                        if(queue != NULL) {play_song_list(queue);printf("Successfully Executed...\n");freeing_ll(queue);}
                        else {printf("The album is empty.\n");}
                        fclose(album);
                        printf("Successfully Executed...\n");
                    }
                }
                else if(strcmp(token1,"song")==0) {
                    token1=strtok(NULL,"\n");
                    if(check_presence(library,token1)==0) printf("No such song found in library.\n");
                    else {
                        printf("Playing song: %s\n",token1);
                        printf("Successfully Executed...\n");
                    }
                }
                else printf("Invalid Input\n");
            }
        }


        

        else if (strcmp(token,"DELETE")==0) {
            token=strtok(NULL," ");
            if(strcmp(token,"song")==0) {
                token=strtok(NULL,"-");
                char *song_name=token;
                token=strtok(NULL," ");
                if(strcmp(token,"album")!=0) {printf("Invalid Input\n");}
                else {
                    token=strtok(NULL,"\n");
                    char *album_name=token;
                    if(check_presence(album_list,album_name)==0) {printf("No such album found.\n");}
                    else {
                        char location[270]="src/albums/";
                        strcat(location,album_name);
                        strcat(location,".csv");
                        FILE *album=fopen(location,"r");
                        if(check_presence(album,song_name)==0) {printf("No such song found in %s.\n",album_name);}
                        else {remove_item(location,song_name);printf("Successfully Executed...\n");}
                        fclose(album);
                    }
                }
            }
        
            else if(strcmp(token,"album")==0) {
                token=strtok(NULL,"\n");
                if(check_presence(album_list,token)==0) printf("No such album found.\n");
                else {
                    char location[270]="src/albums/";
                    strcat(location,token);
                    strcat(location,".csv");
                    remove(location);
                    remove_item("src/albums/albums_list.txt",token);
                    printf("Successfully Executed...\n");
                }
            }
            else printf("Invalid Input\n");
        }



        else if (strcmp(token,"APPEND")==0) {
            token=strtok(NULL," ");
            if(strcmp(token,"song")==0) {
                token=strtok(NULL,"-");
                char *song_name=token;
                token=strtok(NULL," \n");
                if(strcmp(token,"album")==0) {
                    token=strtok(NULL,"\n");
                    char *album_name=token;
                    if(check_presence(album_list,album_name)==0) {printf("No such album found.\n");}
                    else {
                        char location[270]="src/albums/";
                        strcat(location,album_name);
                        strcat(location,".csv");
                        FILE *album=fopen(location,"r+");
                        append_list(library,album,song_name);
                        printf("Successfully Executed...\n");
                        fclose(album);
                    }
                }

                else if(strcmp(token,"playlist")==0) {
                    append_list(library,playlist,song_name);
                    printf("Successfully Executed...\n");
                }

                else printf("Invalid Input\n");
            }

            else if(strcmp(token,"album")==0) {
                token=strtok(NULL,"-");
                char *album_name=token;
                token=strtok(NULL,"\n");
                
                if(strcmp(token,"playlist")==0) {
                    char location[270]="src/albums/";
                    strcat(location,album_name);
                    strcat(location,".csv");
                    FILE *album=fopen(location,"r+");
                    append_album_playlist(playlist,album);
                    fclose(album);
                    printf("Successfully Executed...\n");
                }
                else printf("Invalid Input\n");
            }
            else printf("Invalid Input\n");
        }

        else if (strcmp(token,"CREATE")==0) {
            token=strtok(NULL," ");
            if(strcmp(token,"album")==0) {
                token=strtok(NULL,"\n");
                char *album_name=token;
                if(check_presence(album_list,album_name)==1) {
                    printf("Album already present.\n");
                }
                else {
                    create_album(album_list,album_name);
                    printf("Successfully Executed...\n");
                }
            }
            else printf("Invalid Input\n");
        }

        else printf("Invalid Input\n");
    }


    fputs("[---QUIT PROGRAM---]\n\n",history);
    fclose(history);
    fclose(library);
    fclose(album_list);
    fclose(playlist);
    remove("src/playlist.csv");
    return 0;
}