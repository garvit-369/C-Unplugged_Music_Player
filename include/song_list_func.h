#ifndef SONG_LIST_FUNC_H
#define SONG_LIST_FUNC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list_func.h"
#include "history_func.h"

typedef struct song_list_ll {
    char name[151];
    char artist[151];
    int duration;
    struct song_list_ll *next;
    struct song_list_ll *prev;
} song_list_ll;

song_list_ll* file_to_ll(song_list_ll *art, FILE *song_list);
void play_song_list(song_list_ll *queue);
void freeing_ll(song_list_ll *head);


#endif