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

void dir(struct Dir * dir, char * buff);

void get_root_dir(Inode * inode, struct Superblock * sb, Bgd_table * bgd_table,  char * location);

#endif