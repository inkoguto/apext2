#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "entity.h"
#include "inode.h"
#include "fs_metadata.h"
#include "reader.h"

void append(struct DirList * dir_list, char * buff, int offset) {
    struct Entity* current = malloc(sizeof(struct Entity));
    short int rec_len = NULL;

    memcpy(&rec_len, &buff[offset + 4], 2);
    if (rec_len > sizeof(struct Entity)) {
        rec_len = sizeof(struct Entity);
    }
    memcpy(current, &buff[offset], rec_len);
    current->name[current->name_len] = '\0';
    current->prev = dir_list->tail;
    current->next = NULL;

    if (dir_list->tail != NULL) {
        dir_list->tail->next = current;
    } else {
        dir_list->head = current;
    }
    dir_list->tail = current;
}

struct DirList * list(struct DirList * dir_list, char * buff) {
    int offset = 0;
    do {
        append(dir_list, buff, offset);
        offset = offset + (int) dir_list->tail->rec_len;
    } while (offset < 1024);

    return dir_list;
}

void cleanup(struct Entity* head) {
    struct Entity* current = head;
    struct Entity* next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int count_entities(struct DirList * list) {
    int count = 0;
    struct Entity* curr = list->head;
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
    struct DirList * dir_list = malloc(sizeof(struct DirList));
    int block = inode->i_block[0];

    dir_list->tail = NULL;
    dir_list->head = NULL;

    read_fs(block * block_size, buff, block_size);
    
    dir_list = list(dir_list, buff);
    free(sb);

    return dir_list;
}

char * get_file_data(Inode * inode) {
    struct Superblock *sb = get_superblock();
    int block_size = 1024 << sb->s_log_block_size;
    char * buff = malloc(block_size * sizeof(char));
    char * content = NULL;
    int idx = 0;

    for (idx = 0; idx < 14; idx++) {
        if (inode->i_block[idx] != 0) {
            read_fs(inode->i_block[idx] * block_size, buff, block_size);
            content = realloc(content, (idx+1) * block_size * sizeof(char));
            strncpy(content + (idx * block_size), buff, block_size);
        }
    }

    return content;
}