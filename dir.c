#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dir.h"
#include "inode.h"
#include "fs_metadata.h"
#include "reader.h"

void static render(struct Dir * dir) {
    struct Dir * current = dir;
    while (current != NULL) {
        printf("name: %s - inode: %d\n", current->name, current->inode);
        current = current->next;
    }    
}

void append(struct Dir ** head, char * buff, int offset) {
    struct Dir * current = malloc(sizeof(struct Dir));
    short int rec_len;

    memcpy(&rec_len, &buff[offset + 4], 2);
    if (rec_len > sizeof(struct Dir)) {
        rec_len = sizeof(struct Dir);
    }
    memcpy(current, &buff[offset], rec_len);

    current->next = *head;
    *head = current;
}

void list(struct Dir ** current, char * buff) {
    int offset = 0;
    do {
        append(current, buff, offset);
        offset = offset + (int) (*current)->rec_len;
    } while (offset < 1024);
}

void cleanup(struct Dir * head) {
    struct Dir * current = head;
    struct Dir * next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void get_dir_data(Inode * inode) {
    struct Superblock * sb = get_superblock();
    int block_size = 1024 << sb->s_log_block_size;
    char buff[block_size];
    struct Dir * directory = NULL;
    int block = inode->i_block[0];
   
    read_fs(block * block_size, buff, block_size);
    
    list(&directory, buff);
    
    if (directory == NULL) {
        perror("null directory \n");
    }
    render(directory);
    cleanup(directory);
    free(sb);
}