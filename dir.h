#ifndef DIR_H
#define DIR_H
#include "inode.h"

struct Dir {
    int inode;
    short int rec_len;
    unsigned char name_len;
    unsigned char file_type;
    char name[256];
    struct Dir * next;
};

void get_dir_data(Inode * inode);

#endif