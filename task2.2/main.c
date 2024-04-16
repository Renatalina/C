#include <stdio.h>

#define  length 10
#define  width 15

int main(void)
{
	const int length2 = 10, width2 = 15;

	typedef enum {
		length3 = 10,
		width3 = 15
	} rectangle;

	printf("constant literal as define: %d, %d", length, width);
	printf("\nconstant literal as constant: %d, %d", length2, width2);
	printf("\nconstant literal as enum: %d, %d", length3, width3);

	return 0;
}