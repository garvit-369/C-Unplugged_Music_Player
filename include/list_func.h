#ifndef LIST_FUNC_H
#define LIST_FUNC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_list(FILE *file);
void print_album_list(FILE *file);
int check_presence(FILE *file, char song[]);
void append_list(FILE *library,FILE *list,char song[]);
void append_album_playlist(FILE *playlist,FILE *album);
void remove_item(char *list_file_name, char item[]);
void create_album(FILE *album_list,char album_name[]);

#endif