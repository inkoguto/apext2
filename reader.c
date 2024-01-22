#include <stdio.h>
#include <stdlib.h>

char * get_location() {
	return "/dev/sdc";
}

void read_fs(int offset, void * data, int data_size) {
    FILE * fh;
	char * location;

	location = get_location();

	fh = fopen(location, "rb");
    if (fh == NULL) {
        perror("blad otwarcia pliku\n");
        exit(1);
    }
	if (fseek(fh, offset, SEEK_SET)) {
		perror("could not fseek");
		exit(1);
	}
	fread(data, data_size, 1, fh);
	fclose(fh);
}