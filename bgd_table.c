#include <stdio.h>
#include <stdlib.h>
#include "bgd_table.h"
#include "superblock.h"
#include "node.h"

void set_bgp_data(Bgd_table * bgd_table, char * buff) {
    bgd_table->bg_block_bitmap = get_node(buff, 0, 4).number;
    bgd_table->bg_inode_bitmap = get_node(buff, 4, 4).number;
    bgd_table->bg_inode_table = get_node(buff, 8,4).number;
    bgd_table->bg_free_blocks_count = get_node(buff, 12, 2).number;
    bgd_table->bg_free_inodes_count = get_node(buff, 14, 2).number;
    bgd_table->bg_used_dirs_count = get_node(buff, 16, 2).number;
}

void bgp_render(Bgd_table * bgd_table) {
    printf("block bitmap: %d\n", bgd_table->bg_block_bitmap);
    printf("inode bitmap: %d\n", bgd_table->bg_inode_bitmap);
    printf("inode table: %d\n", bgd_table->bg_inode_table);
    printf("free blocks count: %d\n", bgd_table->bg_free_blocks_count);
    printf("free inodes count: %d\n", bgd_table->bg_free_inodes_count);
}

void load_bgd_table(Bgd_table * Bgd_table, struct Superblock * sb , char * location) {
    int block_size = 1024 << sb->s_log_block_size;
    char buff[block_size];
    int offset = 2;
    FILE * fh;

    fh = fopen(location, "r");
    if (fseek(fh, offset * block_size, SEEK_SET)) {
        exit(1);
    }

    fread(buff, block_size, 1, fh);
    fclose(fh);
    set_bgp_data(Bgd_table, buff);
    //bgp_render(Bgd_table);
}