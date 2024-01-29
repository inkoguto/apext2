#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "inode.h"
#include "reader.h"
#include "fs_metadata.h"


static void render(Inode * inode) {
    printf("Inode mode: %d\n", inode->i_mode);
    printf("Inode uuid: %d \n", inode->i_uid);
    printf("Inode atime %d\n", inode->i_atime);
    printf("Inode size: %d\n", inode->i_size);
    printf("Data blocks: %d\n", inode->i_block[0]);
}

static int get_inode_location(struct Superblock *sb, Bgd_table * bgd_table, int index) {
    int block_size = 1024 << sb->s_log_block_size;
    int block_group = (index - 1) / sb->s_inodes_per_group;
    int local_inode = (index - 1) % sb->s_inodes_per_group;

    return block_size * bgd_table->bg_inode_table + ((index - 1 ) % sb->s_inodes_per_group) * sb->s_inode_size;
}

Inode * get_first_inode() {
    struct Superblock * sb = get_superblock();
    Bgd_table * bgd_table = get_bgd_table();
    Inode * inode = malloc(sizeof(Inode));
    read_fs(get_inode_location(sb, bgd_table, sb->s_first_ino), inode, sizeof(Inode));

    free(sb);
    free(bgd_table);

    return inode;
}

Inode * get_inode(int inode_index) {
    Bgd_table * bgd_table;
    struct Superblock * sb;
    Inode * inode = malloc(sizeof(Inode));

    sb = get_superblock();
    bgd_table = get_bgd_table();

    read_fs(get_inode_location(sb, bgd_table, inode_index), inode, sizeof(Inode));

    free(bgd_table);
    free(sb);

    return inode;
}

int is_file(int inode_idx) {
    Inode * inode = get_inode(inode_idx);
    
    if ((inode->i_mode & 0xF000) != 0x8000) {
        free(inode);
        return 0;
    }

    free(inode);
    return 1;
}

int is_directory(int inode_idx) {
    Inode * inode = get_inode(inode_idx);

    if ((inode->i_mode & 0xF000) != 0x4000) {
        free(inode);
        return 0;
    }

    free(inode);
    return 1;
}

int is_symlink() {

}