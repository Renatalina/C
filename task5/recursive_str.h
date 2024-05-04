#include <stdio.h>

void print_str(char *str, int index) {

	if ((int)str[index] == 10) {
		return;
	}

	print_str(str, ++index);

	printf(" %c  ", str[index-1]);
}

extern void recursive_printf_str(void) {

	char sentence[100];

	printf("\nPlease, enter a sentence for print: \n");
	fgets(sentence, 100, stdin);
	print_str(sentence, 0);

	return;
}