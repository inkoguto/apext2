#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dir.h"
#include "inode.h"
#include "superblock.h"
#include "bgd_table.h"
#include "node.h"

void static render(struct Dir * dir) {
    struct Dir * current = dir;
    while (current != NULL) {
        puts(current->name);
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

void get_root_dir(Inode * inode, struct Superblock * sb, Bgd_table * bgd_table,  char * location) {
    int block_size = 1024 << sb->s_log_block_size;
    char buff[block_size];
    struct Dir * directory = NULL;
    int block = inode->i_block[0];
    FILE * fh;

    fh = fopen(location, "rb");
    fseek(fh, block * 1024, SEEK_SET);
    fread(buff, block_size, 1, fh);
    fclose(fh);
    list(&directory, buff);
    
    if (directory == NULL) {
        perror("null directory \n");
    }
    render(directory);
    cleanup(directory);
}