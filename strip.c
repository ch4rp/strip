
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
	\ttnr\t\\t\\n\\r";
	
char *nums = "1234567890";
char *alph = "abcdefghijklmnopqrstuvwxyz"
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char *tnr  = "\t\n\r";

int main(int argc, char **argv)
{
	int result;
	int i, j;
	int split = 0;
	Bool 
		f_flag = false, 
		x_flag = false, 
		s_flag = false;

	const char *xchars = " \n\t";
	const char *fll    = "";

	opterr = 0;

	if (argc == 1) {
		fprintf(stderr, help, argv[0]);
		exit(EXIT_FAILURE);
	}

	while ((result = getopt(argc, argv, "x:f:s")) != (-1)) 
		switch (result) {
			case 'x':
				xchars = optarg;
				x_flag = true;
				break;
			case 'f':
				fll = optarg;
				f_flag = true;
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
		
		for (i = 0; i < strlen(argv[optind]); ++i) {
			fprintf(stdout, "%c", argv[optind][i]);
			if ((i + 1) % split == 0) {
				fprintf(stdout, "%s", fll);
				//continue;
			}
		}
	}else
		if      (strcmp(xchars, "nums") == 0) xchars = nums;
		else if (strcmp(xchars, "alph") == 0) xchars = alph;
		else if (strcmp(xchars,  "tnr") == 0) xchars = tnr;

		for (i = 0; i < strlen(argv[optind]); ++i) {
			if (is_in_str(xchars, argv[optind][i])) {
				fprintf(stdout, "%s", fll);
				continue;
			}
			fprintf(stdout, "%c", argv[optind][i]);
		}

	fprintf(stdout, "\n");
	
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

