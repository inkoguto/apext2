#ifndef INODE_H
#define INODE_H
#include "fs_metadata.h"

typedef struct {
    short int i_mode;
    short int i_uid;
    int i_size;
    int i_atime;
    int i_ctime;
    int i_mtime;
    int i_dtime;
    short int i_gid;
    short int i_links_count;
    int i_blocks;
    int i_flags;
    int i_osd1;
    int i_block[15];
    int i_generation;
    int i_file_acl;
    int i_dir_acl;
    int i_faddr;
    int i_osd2;
} Inode;

Inode * get_first_inode(struct Superblock * sb, Bgd_table * bgd_table, char * location);

Inode * get_inode(int inode_index);

#endif