#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fs_metadata.h"

char* decode(char * uuid ) {
    char *buff = malloc((2 * strlen(uuid) + 1) * sizeof(char));
    for (int i = 0; i< strlen(uuid); i++) {
        sprintf(buff + 2 * i, "%02x", (unsigned char) uuid[i]);
    }

    return buff;
}

int get_block_size(int log_block_size) {
    return 32 << log_block_size;
}

void render(struct Superblock * sb) {
    char * uuid = decode(sb->s_uuid);
    char * hash = decode(sb->s_hash_seed);
    printf("Filesystem volume name: %s\n", sb->s_volume_name);
    printf("Last mounted on: %s\n", sb->s_last_mounted);
    printf("Filesystem UUID: %s\n", uuid);
    printf("Filesystem magic number: %x\n", sb->s_magic);
    printf("Filesystem revision #: %d\n", sb->s_rev_level);
    printf("Filesystem features: %d\n", sb->s_feature_compat);
    printf("Filesystem flags: \n");
    printf("Default mount options: %d\n", sb->s_default_mount_options);
    printf("Filesystem state: %d\n", sb->s_state);
    printf("Errors behavior: %d\n", sb->s_errors);
    printf("Filesystem OS type: %d\n", sb->s_creator_os);
    printf("Inode count: %d\n", sb->s_inodes_count);
    printf("Block count: %d\n", sb->s_blocks_count);
    printf("Reserved block count: %d\n", sb->s_r_blocks_count);
    printf("Overhead clusters: \n");
    printf("Free blocks: %d\n", sb->s_free_blocks_count);
    printf("Free inodes: %d\n", sb->s_free_inodes_count);
    printf("Block size: %d\n", get_block_size(sb->s_log_block_size));
    printf("Fragment size: %d\n", sb->s_log_frag_size);
    printf("Reserved GDT blocks: \n");
    printf("Blocks per group: %d\n", sb->s_blocks_per_group);
    printf("Fragments per group: %d\n", sb->s_frags_per_group);
    printf("Inodes per group: %d\n", sb->s_inodes_per_group); 
    printf("Inode blocks per group: \n");
    printf("Filesystem created: \n");
    printf("Last mount time: \n");
    printf("Last write time: \n");
    printf("Mount count: %d\n", sb->s_mnt_count);
    printf("Maximum mount count: %d\n", sb->s_max_mnt_count);
    printf("Last checked: %d\n", sb->s_lastcheck);
    printf("Check interval: %d\n", sb->s_checkinterval);
    printf("Reserved blocks uid: %d\n", sb->s_def_resuid);
    printf("Reserved blocks gid: %d\n", sb->s_def_resgid);
    printf("First inode: %d\n", sb->s_first_ino);
    printf("Inode size: %d\n", sb->s_inode_size);
    printf("Required extra isize: \n");
    printf("Desired extra isize: \n");
    printf("Default directory hash: %d\n", sb->s_def_hash_version);
    printf("Directory Hash Seed: %s\n", hash);
    free(hash);
    free(uuid);
}