
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>	

#define true	1
#define false	0

typedef int Bool;

Bool is_in_str(const char *str, const char ch);
Bool is_all_dig(const char *str);
void *cmalloc(size_t type, int n);

char *help = 
"Usage:\n\
	\t%s <\"string\"> [options]\n\
Options:\n\
	\t-x <\"characters\">\tcharacters to be extracted.\n\
	\t-f <\"characters\">\tcharacters to be inserted instead of removed characters.\n\
	\t-s \t\t\tcharacters are added periodically.\n\
	\n\
Ready-made character sets can be used with x flag:\n\
	\tnums\t1234567890\n\
	\talph\ta-Z\n\
	\ttnr \t\\t\\n\\r\n";
	
char *nums = "1234567890";
char *alph = "abcdefghijklmnopqrstuvwxyz"
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char *tnr  = "\t\n\r";

int main(int argc, char **argv)
{
	int result;
	int i, j;
	int index = 0;
	int split = 0;
	int charc = 0;

	Bool x_flag = false, s_flag = false;

	char *buf;
	const char *xchars = " \n\t";
	const char *fll    = "";

	size_t leng;

	opterr = 0;

	if (argc == 1) {
		fprintf(stderr, help, argv[0]);
		exit(EXIT_FAILURE);
	}

	while ((result = getopt(argc, argv, "x:f:s")) != (-1)) 
		switch (result) {
			case 'x':
				x_flag = true;
				xchars = optarg;
				break;
			case 'f':
				fll = optarg;
				break;
			case 's':
				s_flag = true;
				break;
			case '?':
				fprintf(stderr, "%c Invalid switch!\n", optopt);
				fprintf(stderr, help, argv[0]);
				exit(EXIT_FAILURE);
		}
	
	if (s_flag) {
		if (!x_flag) {
			fprintf(stderr, "s flag can only be used with x flag!\n");
			fprintf(stderr, help, argv[0]);
			exit(EXIT_FAILURE);
		}
		if (!is_all_dig(xchars)) {
			fprintf(stderr, "Used s flag! Option of x cannot be a string!\n");
			fprintf(stderr, help, argv[0]);
            exit(EXIT_FAILURE);
		}

		split = atoi(xchars);
		leng = strlen(argv[optind]) + (strlen(argv[optind]) / split + 1) * strlen(fll);
		buf = cmalloc(sizeof(char), leng);

		for (i = 0; i < strlen(argv[optind]); ++i) {
			index += sprintf(buf + index, "%c", argv[optind][i]);
			if ((i + 1) % split == 0) {
				index += sprintf(buf + index, "%s", fll);

			}
		}
	}
	else {
		if      (strcmp(xchars, "nums") == 0) xchars = nums;
		else if (strcmp(xchars, "alph") == 0) xchars = alph;
		else if (strcmp(xchars,  "tnr") == 0) xchars = tnr;

		for (i = 0; i < strlen(argv[optind]); ++i)
			if (is_in_str(xchars, argv[optind][i]))
				++charc;

		leng = strlen(argv[optind]) + charc * strlen(fll) - charc + 1;
		buf = cmalloc(sizeof(char), leng);
		printf("%ld\n", leng);
		
		for (i = 0; i < strlen(argv[optind]); ++i) {
			if (is_in_str(xchars, argv[optind][i])) {
				index += sprintf(buf + index, "%s", fll);
				continue;
			}
			index += sprintf(buf + index, "%c", argv[optind][i]);
		}
	}

	fprintf(stdout, "%s\n", buf);
	
	return 0;
}

Bool is_in_str(const char *str, const char ch)
{
	int j;
	for (j = 0; j < strlen(str); ++j)
		if (strchr(str, ch) != NULL)
			return true;
	return false;
}

Bool is_all_dig(const char *str)
{
	int h;
	for (h = 0; h < strlen(str); ++h)
		if (!isdigit(str[h]))
			return false;
	return true;
}

void *cmalloc(size_t type, int n)
{
	void *pt;
	if ((pt = malloc(type * n)) == NULL) {
		fprintf(stderr, "memory space cannot be allocated\n");
		exit(EXIT_FAILURE);
	}

	return pt;
}
