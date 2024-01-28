#ifndef DIR_H
#define DIR_H
#include "inode.h"

struct Entity{
    int inode;
    short int rec_len;
    unsigned char name_len;
    unsigned char file_type;
    char name[256];
    struct Entity* next;
    struct Entity* prev;
};

struct DirList {
    struct Entity* head;
    struct Entity* tail;
};

struct DirList * get_dir_data(Inode * inode);

void cleanup(struct Entity* head);

int count_entities(struct DirList * list);

char * get_file_data(Inode * inode);

#endif