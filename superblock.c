#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "superblock.h"

void load_superblock(struct Superblock *sb, char *location)
{
	FILE *fh;

	fh = fopen(location, "r");
	if (fh == NULL) {
		perror("could not open file\n");
		exit(1);
	}
	if (fseek(fh, 1024, SEEK_SET))
	{
		puts("fseek");
		exit(1);
	}

	if(!fread(sb, sizeof(struct Superblock), 1, fh)) {
		perror("could not read the given file\n");
		exit(1);
	}

	fclose(fh);

	return;
}
