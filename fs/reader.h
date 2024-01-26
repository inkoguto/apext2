#ifndef READER_H
#define READER_H

char * get_location();

void set_location(char * location);

void read_fs(int offset, void * data, int data_size);

#endif