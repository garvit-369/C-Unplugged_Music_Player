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

    int cmd=-1;

    main_func:
    printf("\nCommands List: (Main)\n1) DISPLAY Functions\n2) PLAY Functions\n3) ALBUM Functions\n4) PLAYLIST Functions\n5) QUIT Program\n\n");
    printf("Enter command: ");
    if (scanf("%d", &cmd)!=1) {
        int c;
        while ((c = getchar())!='\n' && c!=EOF);
        cmd = -1;
    }
    if (cmd==1) {goto display_func;}
    else if (cmd==2) {goto play_func;}
    else if (cmd==3) {goto album_func;}
    else if (cmd==4) {goto playlist_func;}
    else if(cmd==5) {goto quit_func;}
    else {printf("Invalid input!!\n");goto main_func;}

    
    

    display_func:
    printf("\nCommands List: (DISPLAY)\n");
    printf("1) All Library Songs\n");
    printf("2) All Albums List\n");
    printf("3) All songs of a specific album\n");
    printf("4) All songs of a playlist\n");
    printf("5) History\n");
    printf("6) BACK to Main\n");
    printf("7) QUIT Program\n\n");
    printf("Enter command: ");
    if (scanf("%d", &cmd) != 1) {
        int c;
        while ((c = getchar())!='\n' && c!=EOF);
        cmd = -1;
    }
    if (cmd==1) {
        print_list(library);
        printf("\nSuccessfully Executed!!\n");
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        add_log(history,"DISPLAY library");
        goto display_func;
    }
    else if (cmd==2) {
        print_album_list(album_list);
        printf("\nSuccessfully Executed!!\n");
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        add_log(history,"DISPLAY albums list");
        goto display_func;
    }
    else if (cmd==3) {
        int album_index=-1;
        printf("\nAlbums List:-\n");
        print_album_list(album_list);
        printf("Enter album index: ");
        if (scanf("%d", &album_index) != 1) {
            int c;
            while ((c = getchar())!='\n' && c!=EOF);
            album_index = -1;
        }
        FILE *fptr=open_album_from_index(album_list,album_index);
        if(fptr!=NULL) {
            print_list(fptr);
            fclose(fptr);
            printf("Successfully Executed...\n");
            char album[50]={0};
            item_name_from_index(album_list,album_index,album);
            char strr[200]="DISPLAY album ";
            strcat(strr,album);
            add_log(history,strr);
        }
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        goto display_func;
    }
    else if (cmd==4) {
        print_list(playlist);
        printf("\nSuccessfully Executed!!\n");
        add_log(history,"DISPLAY playlist");
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        goto display_func;
    }
    else if (cmd==5) {
        print_log(history);
        printf("\nSuccessfully Executed!!\n");
        add_log(history,"DISPLAY history");
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        goto display_func;
    }
    else if (cmd==6) {goto main_func;}
    else if(cmd==7) {goto quit_func;}
    else {printf("Invalid input!!\n");goto display_func;}



    play_func:
    printf("\nCommands List: (PLAY)\n");
    printf("1) Specific album\n");
    printf("2) Playlist\n");
    printf("3) Entire Library\n");
    printf("4) BACK to Main\n");
    printf("5) QUIT Program\n\n");
    printf("Enter command: ");
    if (scanf("%d", &cmd) != 1) {
        int c;
        while ((c = getchar())!='\n' && c!=EOF);
        cmd = -1;
    }   

    if (cmd==1) {
        int album_index=-1;
        printf("\nAlbums List:-\n");
        print_album_list(album_list);
        printf("Enter album index: ");
        if (scanf("%d", &album_index) != 1) {
            int c;
            while ((c = getchar())!='\n' && c!=EOF);
            album_index = -1;
        }
        FILE *albums=open_album_from_index(album_list,album_index);
        song_list_ll *queue = (song_list_ll*)malloc(sizeof(song_list_ll));
        queue=file_to_ll(queue,albums);
        if(queue!=NULL) {
            play_song_list(queue);
            printf("Successfully Executed...\n");
            freeing_ll(queue);
            char album[50]={0};
            item_name_from_index(album_list,album_index,album);
            char strr[200]="PLAY album ";
            strcat(strr,album);
            add_log(history,strr);
        }
        else {printf("The album is empty.\n");}
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        fclose(albums);
        goto play_func;
    }
    else if (cmd==2) {
        song_list_ll *queue = (song_list_ll*)malloc(sizeof(song_list_ll));
        queue=file_to_ll(queue,playlist);
        if(queue!=NULL) {play_song_list(queue);printf("Successfully Executed...\n");freeing_ll(queue);}
        else {printf("The album is empty.\n");}
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        char strr[200]="PLAY playlist";
        add_log(history,strr);
        goto play_func;
    }
    else if (cmd==3) {
        song_list_ll *queue = (song_list_ll*)malloc(sizeof(song_list_ll));
        queue=file_to_ll(queue,library);
        if(queue!=NULL) {play_song_list(queue);printf("Successfully Executed...\n");freeing_ll(queue);}
        else {printf("The album is empty.\n");}
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        char strr[200]="PLAY library";
        add_log(history,strr);
        goto play_func;
    }
    else if (cmd==4) {goto main_func;}
    else if(cmd==5) {goto quit_func;}
    else {printf("Invalid input!!\n");goto play_func;}




    album_func:
    printf("\nCommands List: (Album)\n");
    printf("1) Create new album\n");
    printf("2) Add song to specific album\n");
    printf("3) Delete song from album\n");
    printf("4) Delete specific album\n");
    printf("5) Display All Albums List\n");
    printf("6) Display All songs of a specific album\n");
    printf("7) PLAY\n");
    printf("8) BACK to Main\n");
    printf("9) QUIT Program\n\n");

    printf("Enter command: ");
    if (scanf("%d", &cmd) != 1) {
        int c;
        while ((c = getchar())!='\n' && c!=EOF);
        cmd = -1;
    }   

    if (cmd==1) {
        char album_name[40];
        printf("Enter album name to add: ");
        int c; while ((c = getchar()) != '\n' && c != EOF);
        scanf("%39s",album_name);
        create_album(album_list,album_name);
        printf("Successfully Executed...\n");
        char arr[400]="Created New Album ";
        strcat(arr,album_name);
        add_log(history,arr);
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        goto album_func;
    }
    else if (cmd==2) {
        printf("\nLibrary Songs:-\n");
        print_list(library);
        printf("Enter song index to add: ");
        int song_index=-1,album_index=-1;
        if (scanf("%d", &song_index) != 1) {
            int c;
            while ((c = getchar())!='\n' && c!=EOF);
            song_index = -1;
        }
        printf("\nAlbums List:-\n");
        print_album_list(album_list);
        printf("Enter album index: ");
        if (scanf("%d", &album_index) != 1) {
            int c;
            while ((c = getchar())!='\n' && c!=EOF);
            album_index = -1;
        }
        FILE *fptr = open_album_from_index(album_list,album_index);
        append_list(library,fptr,song_index);
        fclose(fptr);
        char arr[400];
        memset(arr, 0, sizeof(char));
        char song_name[100];
        memset(song_name, 0, sizeof(char));
        item_name_from_index(library,song_index,song_name);
        char album_name[100];
        memset(album_name, 0, sizeof(char));
        item_name_from_index(album_list,album_index,album_name);
        sprintf(arr,"Added song %s to album %s",song_name,album_name);
        add_log(history,arr);
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        goto album_func;
    }
    else if (cmd==3) {
        int song_index=-1,album_index=-1;
        printf("\nAlbums List:-\n");
        print_album_list(album_list);
        printf("Enter album index: ");
        if (scanf("%d", &album_index) != 1) {
            int c;
            while ((c = getchar())!='\n' && c!=EOF);
            album_index = -1;
        }
        printf("\nAlbum Songs:-\n");
        print_list(library);
        printf("Enter song index to delete: ");
        if (scanf("%d", &song_index) != 1) {
            int c;
            while ((c = getchar())!='\n' && c!=EOF);
            song_index = -1;
        }
        char location[270] = "src/albums/";
        album_location_from_index(album_list,album_index,location);
        remove_song(location,song_index);
        char arr[400];
        memset(arr, 0, sizeof(char));
        char song_name[100];
        memset(song_name, 0, sizeof(char));
        item_name_from_index(library,song_index,song_name);
        char album_name[100];
        memset(album_name, 0, sizeof(char));
        item_name_from_index(album_list,album_index,album_name);
        sprintf(arr,"Deleted song %s to album %s",song_name,album_name);
        add_log(history,arr);
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        goto album_func;
    }
    else if (cmd==4) {
        int album_index=-1;
        printf("\nAlbums List:-\n");
        print_album_list(album_list);
        printf("Enter album index: ");
        if (scanf("%d", &album_index) != 1) {
            int c;
            while ((c = getchar())!='\n' && c!=EOF);
            album_index = -1;
        }
        char location[270] = "src/albums/";
        char name[100]={0};
        memset(name, 0, sizeof(char));
        item_name_from_index(album_list,album_index,name);
        album_location_from_index(album_list,album_index,location);
        remove(location);
        remove_song("src/albums/albums_list.csv",album_index);
        char arr[400]={0};
        sprintf(arr,"Deleted album %s",name);
        add_log(history,arr);
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        goto album_func;
    }

    else if (cmd==5) {
        print_album_list(album_list);
        printf("\nSuccessfully Executed!!\n");
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        add_log(history,"DISPLAY albums list");
        goto album_func;
    }
    else if (cmd==6) {
        int album_index=-1;
        printf("\nAlbums List:-\n");
        print_album_list(album_list);
        printf("Enter album index: ");
        if (scanf("%d", &album_index) != 1) {
            int c;
            while ((c = getchar())!='\n' && c!=EOF);
            album_index = -1;
        }
        FILE *fptr=open_album_from_index(album_list,album_index);
        if(fptr!=NULL) {
            print_list(fptr);
            fclose(fptr);
            printf("Successfully Executed...\n");
            char album[50]={0};
            item_name_from_index(album_list,album_index,album);
            char strr[200]="DISPLAY album ";
            strcat(strr,album);
            add_log(history,strr);
        }
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        goto album_func;
    }
    else if (cmd==7) {goto play_func;}
    else if (cmd==8) {goto main_func;}
    else if (cmd==9) {goto quit_func;}
    else {printf("Invalid input!!\n");goto album_func;}



    playlist_func:
    printf("\nCommands List: (Playlist)\n");
    printf("1) ADD song to playlist\n");
    printf("2) ADD specific album to playlist\n");
    printf("3) Delete song from playlist\n");
    printf("4) Display playlist\n");
    printf("5) PLAY\n");
    printf("6) BACK to Main\n");
    printf("7) QUIT Program\n\n");

    printf("Enter command: ");
    if (scanf("%d", &cmd) != 1) {
        int c;
        while ((c = getchar())!='\n' && c!=EOF);
        cmd = -1;
    }   

    if (cmd==1) {
        printf("\nLibrary Songs:-\n");
        print_list(library);
        printf("Enter song index to add to playlist: ");
        if (scanf("%d", &cmd) != 1) {
            int c;
            while ((c = getchar())!='\n' && c!=EOF);
            cmd = -1;
        }
        append_list(library,playlist,cmd);
        char arr[400]={0};
        memset(arr, 0, sizeof(char));
        char song_name[100];
        memset(song_name, 0, sizeof(char));
        item_name_from_index(library,cmd,song_name);
        sprintf(arr,"Added song %s to playlist",song_name);
        add_log(history,arr);
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        goto playlist_func;
    }
    else if (cmd==2) {
        printf("\nAlbums List:-\n");
        print_album_list(album_list);
        printf("Enter album index to add to playlist: ");
        if (scanf("%d", &cmd) != 1) {
            int c;
            while ((c = getchar())!='\n' && c!=EOF);
            cmd = -1;
        }
        append_album_playlist(playlist,album_list,cmd);
        char arr[400]={0};
        char album_name[100];
        memset(album_name, 0, sizeof(char));
        item_name_from_index(album_list,cmd,album_name);
        sprintf(arr,"Added album %s to playlist",album_name);
        add_log(history,arr);
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        goto playlist_func;
    }
    else if (cmd==3) {
        printf("\nPlaylist Songs:-\n");
        print_list(playlist);
        printf("Enter song index to delete: ");
        if (scanf("%d", &cmd) != 1) {
            int c;
            while ((c = getchar())!='\n' && c!=EOF);
            cmd = -1;
        }
        remove_song("src/playlist.csv",cmd);
        char arr[400]={0};
        char song_name[100];
        memset(song_name, 0, sizeof(char));
        item_name_from_index(library,cmd,song_name);
        sprintf(arr,"Deleted song %s to playlist",song_name);
        add_log(history,arr);
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        goto playlist_func;
    }
    else if (cmd==4) {
        print_list(playlist);
        printf("\nSuccessfully Executed!!\n");
        printf("-------------------------------------------------------------------------------------------------------------\n\n");
        add_log(history,"DISPLAY playlist");
        goto playlist_func;
    }
    else if (cmd==5) {goto play_func;}
    else if (cmd==6) {goto main_func;}
    else if (cmd==7) {goto quit_func;}
    else {printf("Invalid input!!\n");goto playlist_func;}



    quit_func:
    printf("\nThanks for using!!\n");
    printf("-------------------------------------------------------------------------------------------------------------\n\n");
    fputs("[---QUIT PROGRAM---]\n\n",history);
    fclose(history);
    fclose(library);
    fclose(album_list);
    fclose(playlist);
    remove("src/playlist.csv");
    return 0;
}