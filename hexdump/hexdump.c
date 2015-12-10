#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static inline void
usage(char * const str)
{
	fprintf(stderr, "usage: %s filename\n", str);
	exit(EXIT_FAILURE);
}

static inline void
die(char * const str)
{
 	perror(str);
	exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
	if (argc < 2)
		usage(argv[0]);

	FILE *f = fopen(argv[1], "r");
	if (!f)
		die(argv[1]);


	unsigned char buf[1];
	int d = fread(buf, 1, 1, f);
	while (d)
	{
		printf("%x", *buf >> 4);
		printf("%x", (*buf & 0x0F));
		d = fread(buf, 1, 1, f);
	}
	puts("");
	
	fclose(f);
	return EXIT_SUCCESS;
}
