#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "inode.h"
#include "node.h"
#include "superblock.h"
#include "bgd_table.h"

static void render(Inode * inode) {
    printf("Inode mode: %d\n", inode->i_mode);
    printf("Inode uuid: %d \n", inode->i_uid);
    printf("Inode atime %d\n", inode->i_atime);
    printf("Inode size: %d\n", inode->i_size);
    printf("Data blocks: %d\n", inode->i_block[0]);
}

static int get_first_inode_location(struct Superblock *sb, Bgd_table * bgd_table) {
    int block_size = 1024 << sb->s_log_block_size;

    return block_size * bgd_table->bg_inode_table + ((sb->s_first_ino - 1 ) % sb->s_inodes_per_group) * sb->s_inode_size;
}

Inode * get_first_inode(struct Superblock * sb, Bgd_table * bgd_table,  char * location) {
    Inode * inode = malloc(sizeof(Inode));
    FILE * fh;

	fh = fopen(location, "rb");
    if (fh == NULL) {
        perror("blad otwarcia pliku\n");
        exit(1);
    }
	if (fseek(fh, get_first_inode_location(sb, bgd_table), SEEK_SET)) {
		perror("could not fseek");
		exit(1);
	}
	fread(inode, sizeof(Inode), 1, fh);
	fclose(fh);
    // render(inode);
    return inode;
}