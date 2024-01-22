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

void append(struct DirList * dir_list, char * buff, int offset) {
    struct Dir * current = malloc(sizeof(struct Dir));
    short int rec_len;

    memcpy(&rec_len, &buff[offset + 4], 2);
    if (rec_len > sizeof(struct Dir)) {
        rec_len = sizeof(struct Dir);
    }
    memcpy(current, &buff[offset], rec_len);

    current->prev = dir_list->tail;
    current->next = NULL;

    if (dir_list->tail != NULL) {
        dir_list->tail->next = current;
    } else {
        dir_list->head = current;
    }
    dir_list->tail = current;

    printf("");
}

void list(struct DirList * dir_list, char * buff) {
    int offset = 0;
    do {
        append(dir_list, buff, offset);
        offset = offset + (int) dir_list->tail->rec_len;
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

int count_entities(struct DirList * list) {
    int count = 0;
    struct Dir * curr = list->head;
    while (curr != NULL) {
        curr = curr->next;
        count++;
    }

    return count;
}

struct DirList * get_dir_data(Inode * inode) {
    struct Superblock * sb = get_superblock();
    int block_size = 1024 << sb->s_log_block_size;
    char buff[block_size];
    struct Dir * dir;
    struct DirList * dir_list = malloc(sizeof(struct DirList));
    int block = inode->i_block[0];

    dir_list->tail = NULL;
    dir_list->head = NULL;

    if ((inode->i_mode & 0xF000) != 0x4000) {
        free(sb);
        exit(1);
    }
    read_fs(block * block_size, buff, block_size);
    
    list(dir_list, buff);
  //  render(dir_list->head);
    free(sb);

    return dir_list;
}