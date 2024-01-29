#include <stdio.h>
#include <stdlib.h>
#include "fs_metadata.h"
#include "reader.h"

struct Superblock * get_superblock()
{
    struct Superblock * sb = malloc(sizeof(struct Superblock));
	
    read_fs(1024, sb, sizeof(struct Superblock));

    return sb;
}

Bgd_table * get_bgd_table() {
    struct Superblock * sb;
    Bgd_table * table = malloc(sizeof(Bgd_table));
    int block_size, idx;

    sb = get_superblock();
    block_size = 1024 << sb->s_log_block_size;
    if (block_size == 1024) {
        idx = 2 * block_size;
    } else {
        idx = block_size;
    }
    
    read_fs(idx, table, sizeof(Bgd_table));
    free(sb);
    return table;
}


void bgp_render(Bgd_table * bgd_table) {
    printf("block bitmap: %d\n", bgd_table->bg_block_bitmap);
    printf("inode bitmap: %d\n", bgd_table->bg_inode_bitmap);
    printf("inode table: %d\n", bgd_table->bg_inode_table);
    printf("free blocks count: %d\n", bgd_table->bg_free_blocks_count);
    printf("free inodes count: %d\n", bgd_table->bg_free_inodes_count);
}