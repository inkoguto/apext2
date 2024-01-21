#ifndef BGD_TABLE_H
#define BGD_TABLE_H
#include "superblock.h"

typedef struct {
    int bg_block_bitmap;
    int bg_inode_bitmap;
    int bg_inode_table;
    int bg_free_blocks_count;
    int bg_free_inodes_count;
    int bg_used_dirs_count;
    int bg_pad;
    char bg_reserved[12];
} Bgd_table;

void load_bgd_table(Bgd_table * bgd_table, struct Superblock * sb, char * location);
#endif