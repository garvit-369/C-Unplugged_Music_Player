#ifndef LIST_FUNC_H
#define LIST_FUNC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_album_list(FILE *file);
void print_list(FILE *file);
int check_presence(FILE *file, char song[]);
void append_list(FILE *library,FILE *list,int song_index);
FILE *open_album_from_index(FILE *album_list, int album_index);
void album_location_from_index(FILE *album_list, int album_index, char *location);
void item_name_from_index(FILE *album_list, int album_index, char *name);
void append_album_playlist(FILE *playlist,FILE *album_list,int album_index);
void remove_song(char *list_file_name, int song_index);
void create_album(FILE *album_list,char album_name[]);

#endif